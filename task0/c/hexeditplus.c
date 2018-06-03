#include <stdlib.h>
#include <stdio.h>

typedef struct main_menu{
    char *name;
    void (*func)();
}main_menu;

char* file_name ;
int size;


void quit(){
    free(file_name);
    exit(0);
}

void Set_File_Name(){
    free(file_name);
    file_name=malloc(100* sizeof(char));
    printf("Please enter a file name: ");
    //fgets(file_name, 100, stdin);TODO remove this line
    scanf("%s", file_name);
//    printf("%s\n",file_name);TODO remove this line

}
void Set_Unit_Size(){
    printf("Please enter a number: \n");
    scanf("%d", &size);
    //the number is size of char/int
    if (size != 1 && size != 2 && size != 4) {
        printf("The entered number is invalid!\n");
        size=0;
    }
    //printf("%d\n",size);TODO remove this line
}


int main(int argc, char **argv) {
    file_name=malloc(100* sizeof(char));
    int input;
    struct main_menu menu[] = {{"1 - Set File Name", Set_File_Name},
                              {"2 - Set Unit Size", Set_Unit_Size},{"3 - Exit",quit},{NULL,NULL}};
    int size_arr = sizeof(menu)/sizeof(main_menu);
    for( ; ; ){
        printf("Choose action: \n");
        for(int i=0; i<size_arr-1; i++){
            printf("%s \n", menu[i].name);
        }
        scanf("%d", &input);
        if(input<=0 || input>(size_arr-1)) {
            printf("Illegal input, please try again.\n");
            break;//TODO-remove this line
        }
        else {
            input--;
            menu[(input)].func();
        }
    }
    return 0;
}
