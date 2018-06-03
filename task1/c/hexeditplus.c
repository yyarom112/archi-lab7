#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <memory.h>

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

int open_file_stream(int option){
    int fd;
    // Check if filename is null, and if it is print an error message and return.
    if(!file_name){
        perror("file name is null\n");
        return -1;
    }
    // Open filename for reading. If this fails, print an error message and return.
    if((fd = open(file_name, option))<0){
        perror("Failed open file stream\n");
        return -1;
    }

    return fd;
}

void File_Display(){
    int fd=0,loc=0,len;
    char* number;

    if((fd = open_file_stream(O_RDONLY))<0){
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

void File_Modify(){
    int fd=0,loc=0,val=0,f_size=0;
    unsigned int* tmp;
    if((fd = open_file_stream(O_RDWR))<0){
        return;
    }
    //Prompt the user for location and val (all in hexadecimal).
    printf("Please enter <location> <val>:\n");
    scanf("%x %x",&loc,&val);

    //lseek return in succsful the offset from the beginig of fiele to cur point
    ;
    if((f_size= lseek(fd,0,SEEK_END))<0 ){
        perror("The location is wrong\n");
        return;
    }
    if(f_size+1<loc ){
        perror("The location is wrong\n");
        return;
    }
    lseek(fd,0,SEEK_SET);
    lseek(fd,loc,SEEK_SET);
    tmp = (unsigned int ) val;
    if(write(fd, &tmp, (size_t) size)!=size) {
        perror("the write is failed\n");
    }
    close(fd);
}

void Copy_From_File(){
    char *src_file=malloc(100* sizeof(char));;
    printf("Please enter <src_file> <src_offset> <dst_offset> <length>:\n");
    //prompted for src_file, src_offset, dst_offset, and length.
    int src_offset=0,dst_offset=0,len=0;
    FILE* fd_src;
    FILE* fd_dst;
    scanf("%s %x %x %d", src_file, &src_offset, &dst_offset, &len);

    //Check if src_file or dst_file is null, and if it is print an error message and return.
    if(!file_name || !src_file){
        perror("The file src or file dest is null");
        free(src_file);
        return;
    }
    //Open src_file for reading. If this fails, print an error message and return.
    if((fd_src = fopen(src_file,"r")) == (FILE *) -1){
        perror("Open stream to source file failed");
        free(src_file);
        return;
    }

    //Open dst_file for read & write (not write only). If this fails, print an error message and return.
    if((fd_dst = fopen(file_name,"r+")) == (FILE *) -1){
        perror("Open stream to source file failed");
        free(src_file);
        return;
    }

    //Read length bytes from src_file at offset src_offset and write them to dst_file at dst_offset
    fseek(fd_src,src_offset,SEEK_SET);
    fseek(fd_dst,dst_offset,SEEK_SET);
    char * to_copy = malloc(len*size* sizeof(char));
    //size=This is the size in bytes of each element to be read
    //len= This is the number of elements, each one with a size of size bytes
    if(fread(to_copy,size,len,fd_src)!=len){
        perror("The read from source file failed");
        free(src_file);
        free(to_copy);
        return;
    }
    if(fwrite(to_copy,size,len,fd_dst)!=len){
        perror("The write into dest file failed");
        free(src_file);
        free(to_copy);
        return;
    }

    printf("Loaded %d bytes into %x FROM %s TO %s\n",size*len,dst_offset,src_file,file_name);
    // Close the files.
    fclose(fd_src);
    fclose(fd_dst);

    //free the memory on heap
    free(src_file);
    free(to_copy);

};

int main(int argc, char **argv) {
    int input;
    size=1;

    struct main_menu menu[] = {{"1 - Set File Name", Set_File_Name},
                              {"2 - Set Unit Size", Set_Unit_Size},{"3 - File Display",File_Display},
                               {"4 - File File Modify",File_Modify},{"5 - Copy From File",Copy_From_File},
                               {"6 - Exit",quit},{NULL,NULL}};
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
