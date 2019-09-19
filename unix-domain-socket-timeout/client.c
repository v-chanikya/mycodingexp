#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <errno.h>
#include <sys/un.h>
#include <time.h>

#define SOCK_FILE_NAME "/tmp/test_socket.sock"

void main(void)
{
    int fd = 0;
    struct sockaddr_un addr = {0,};
    struct timeval tv = { 0, };
    char buff_to_write[256] = {0,};
    size_t written_size = 256;
    socklen_t tv_size = 0;

    fd = socket(AF_UNIX, SOCK_STREAM, 0);
    memset(&addr, 0, sizeof(addr));
    addr.sun_family = AF_UNIX;
    strncpy(addr.sun_path, SOCK_FILE_NAME , sizeof(addr.sun_path)-1);

    connect(fd, (struct sockaddr*)&addr, sizeof(addr));
    
    tv.tv_sec = 2;
    tv.tv_usec = 0;
    setsockopt(fd, SOL_SOCKET, SO_RCVTIMEO, (char *)&tv, sizeof(tv));
    getsockopt(fd, SOL_SOCKET, SO_RCVTIMEO, (char *)&tv, &tv_size);
    printf("set the value of sockopt to %ld\n", tv.tv_sec);

    send(fd, "hello from client1", 18 ,0);
    printf("sent message waiting for response for 2 sec\n");
    if(recv(fd, buff_to_write, written_size, 0) < 0){
        if (EAGAIN == errno || EWOULDBLOCK == errno) {
            printf("time out expired\n");
        }
    }else{
        printf("received buffer %s\n", buff_to_write);
    }

}
