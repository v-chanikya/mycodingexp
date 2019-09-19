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
    int fd = 0,acp;
    struct sockaddr_un addr = {0,};
    struct timeval tv = { 0, };
    char buff_to_write[256] = {0,};
    socklen_t tv_size = 0;
    size_t receive_size = 200;

    fd = socket(AF_UNIX, SOCK_STREAM, 0);

    unlink(SOCK_FILE_NAME);

    memset(&addr, 0, sizeof(addr));
    addr.sun_family = AF_UNIX;
    strncpy(addr.sun_path, SOCK_FILE_NAME , sizeof(addr.sun_path)-1);

    bind(fd, (struct sockaddr*)&addr, sizeof(addr));
    listen(fd, SOMAXCONN);
    do{
        acp = accept(fd, NULL, NULL);
        if(-1!= acp){
            
            printf("accepted connection %d\n",acp);
            
            tv.tv_sec = 10;
            tv.tv_usec = 0;
            setsockopt(acp, SOL_SOCKET, SO_RCVTIMEO, (char *)&tv, sizeof(tv));
            
            getsockopt(acp, SOL_SOCKET, SO_RCVTIMEO, (char *)&tv, &tv_size);
            printf("set the value of sockopt to %ld\n", tv.tv_sec);

            if(recv(acp, buff_to_write, receive_size, 0) < 0){
                if (EAGAIN == errno || EWOULDBLOCK == errno) {
                    printf("time out expired\n");
                }
                printf("error in receving data\n");
            }else{
                printf("received buffer %s\n", buff_to_write);
            }

            usleep(5000000);
            printf("sent message after waiting for 5 sec\n");
            send(acp, "hello from client2", 18 ,0);

        } else {
            if ((EWOULDBLOCK == errno) || (EAGAIN == errno)) {
                printf("No more connections to accept\n");
                /* no more connections to accept */
            } else {
                /* error by accept - only log the error and skip it */
                printf("Unexpected error by accepting new connection");
            }
        }
    }while(1);

}
