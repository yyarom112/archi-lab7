#include <stdio.h>

int counter_digit(char* s){
    int digits=0;
    for(int i=0;s[i]!='\0';i++){
            if(s[i]>='0' && s[i]<='9')
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
    printf("The number of digits in the string is: %d\n",counter );
    return 0;
}
