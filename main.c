#include <stdio.h>

int counter_digit(char* str){
    int digits=0;
    for(int i=0;str[i]!='\0';i++){
            if(str[i]>='0' && str[i]<='9')
            {
                digits++;
            }
    }
    return digits;
}


int main(int argc, char **argv) {
    int counter=0;
    for(int i=1;i<argc;i++){
       counter+= counter_digit(argv[i]);
    }
    printf("%d\n",counter );
    return 0;
}