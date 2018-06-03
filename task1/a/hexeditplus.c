#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

typedef struct main_menu{
    char *name;
    void (*func)();
}main_menu;

char* file_name ;
int size;


void quit(){
    if(file_name)
        free(file_name);
    exit(0);
}

void print_Hexadecimal_number(char* number, int len){
    int i;
    printf("Hexadecimal Representation:\n");
    switch (size){
        case 2:
            for(i=0;i<len;i+=2){
                printf("%02x%02x ",(unsigned char) number[i+1],(unsigned char) number[i]);
            }
            break;
        case 4:
            for(i=0;i<len;i+=4){
                printf("%02x%02x%02x%02x ", (unsigned char) number[i+3],(unsigned char)  number[i+2],(unsigned char)  number[i+1],(unsigned char)  number[i]);
            }
            break;
        default:
            for(i=0;i<len;i++){
                printf("%02x ",(unsigned char)  number[i]);
            }
            break;
    }
    printf("\n");
}

void print_Decimal_Number(char* number, int len){
    int i;
    printf("Decimal Representation:\n");
    switch (size){
        case 2:
            for(i=0;i<len;i++){
                printf("%hu ",*((short*)number + i));
            }
            break;
        case 4:
            for(i=0;i<len;i++){
                printf("%hu ",*((int*)number + i));
            }
            break;
        default:
            for(i=0;i<len;i++){
                printf("%hu ",*(number + i));
            }
            break;
    }
    printf("\n");
}


void File_Display(){
    int fd=0,loc=0,len;
    char* number;

    // Check if filename is null, and if it is print an error message and return.
    if(!file_name){
        perror("file name is null\n");
        return;
    }
    // Open filename for reading. If this fails, print an error message and return.
    if((fd = open(file_name, O_RDONLY))<0){
        perror("Failed open file stream\n");
        return;
    }
    // Prompt the user for location (in hexadecimal) and a length (in decimal).
    printf("Please enter <location> <length>: \n"
                   "Note: the location in hexadecimal and length in decimal\n");
    scanf("%x %d",&loc,&len);

    // Allocate <unit size> * <length> bytes on the heap.
    number=malloc((len * size));

    //Read length units from file filename, starting from location, into the allocated memory.
    //move fd to loc
    lseek(fd,loc,SEEK_SET);
    //read len*size bytes into buffer;
    read(fd,number,len*size);

    // Close the file.
    close(fd);

    // Display in hexadecimal, the read units.
    print_Hexadecimal_number(number,len);

    // Display in decimal, the read units
    print_Decimal_Number(number,len);

    //Free the allocated memory
    free(number);

}

void Set_File_Name(){
    if(file_name)
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
    int input;
    size=1;
    struct main_menu menu[] = {{"1 - Set File Name", Set_File_Name},
                              {"2 - Set Unit Size", Set_Unit_Size},{"3 - File Display",File_Display},
                               {"4 - Exit",quit},{NULL,NULL}};
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
