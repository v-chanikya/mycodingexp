#include <stdio.h>
#include "stat.h"
void static_func_in_b(void){
    printf("printing from b\n");
    static_func_in_a();
    printf("fininshed from b\n");
}

