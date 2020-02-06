#include <stdio.h>
#include <stdlib.h>

void main(int argc, char **argv){
    if(argc < 2){
        printf("Type the number to convert\n");
        return;
    }
    int addr = atoi(argv[1]);
    char *addrp = (char *)&addr;
    char no = 0;
    printf("the size of number is %d\n",(int)sizeof(addr));
    int size = sizeof(addr);
    for(int i = 0;i < size/2;i++){
        printf("%d,%d\n",addrp[i],addrp[size -1 - i]);
        no = addrp[i];
        addrp[i] = addrp[size - 1 - i];
        addrp[size - i -1] = no;
    }
    printf("the flip no is %d\n",addr);
    return;
}
