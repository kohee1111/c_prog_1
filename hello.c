3//all about files 
_______________________________
#include<stdio.h>
#include<stdlib.h>
int main(void){
    FILE *fp = fopen("hello.c" , "r") ; 
    if(fp == NULL){
        perror("Failed to open file!") ; 
            return -1 ;
    }
    int ch ; 
    while((ch = fgetc(fp)) != EOF){
        putchar(ch) ;
    }
    return 0 ;
}
________________________________
#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
int main(void){
    int fd = open("hello.c" , O_WRONLY | O_CREAT | O_TRUNC, 0x1A4) ; 
    if(fd < 0){
        return -1 ;
    }
    dprintf(fd , "Your number is :%d\n" , 100) ;
    close(fd) ;
    return 0 ;
}
_________________________________________
#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
int main(void){

    int fd = open("Hello.c" , O_CREAT | O_WRONLY | O_APPEND , 0x1A4) ; 
    if(fd < 0){

        return -1 ;
    }
    dprintf(fd , "Appending data to file!") ; 
    close(fd) ; 
    return 0  ;
}
_____________________________
#include<stdio.h>
#include<stdlib.h>
int main(void){

    FILE *fp = fopen("hello.c" , "r+") ; 
    if(fp == NULL){

        return -1 ;
    }
    fprintf(fp , "Hello world and ibbo") ; 
    fseek(fp , 0 , SEEK_SET) ; 
    int ch  ; 

    ch = fgetc(fp) ; 
    while(ch != EOF){

        putchar(ch) ;
        ch = fgetc(fp) ;
    }
    fclose(fp) ; 
    return 0 ;
}
_____________________________________
#include<stdio.h>
#include<stdlib.h>
int main(void){

    FILE *fp = fopen("hello.c"  , "r+") ; 
    if(!fp){
        perror("Failed to open file !") ; 
        return -1 ;
    }
    int ch ; 
    ch = fgetc(fp) ; 
    if(ch == EOF && ferror(fp)){
        perror("Cannot read anything ....") ; 
        exit(EXIT_FAILURE) ;
    }else{
        printf("The first char is :%c\n" , ch) ;
    }
    fclose(fp) ; 
    return 0 ;
}
______________________________________
#include<stdio.h>
#include<stdlib.h>
int main(void){
    FILE *fp = fopen("hello.c" , "a+") ; 
    if(fp == NULL){
        perror("Failed to open file !\n") ; 
        return -1 ;
    }
    fprintf(fp , "hello world and ow we are appending ...no data will be vanish !") ; 
    fflush(fp) ; 
    fseek(fp , 0  , SEEK_SET) ;
    fclose(fp) ; 
    fp = fopen("hello.c" , "r+") ; 
    if(!fp){
        return -1 ;
    }
    int ch ; 
    ch = fgetc(fp) ; 
    while(ch != EOF){
        putchar(ch) ; 
        ch = fgetc(fp) ; 
    }
    if(ferror(fp)){
        perror("Some error found !") ;
    }
    fclose(fp) ; 
    return 0 ;
}
____________________________________________
#include<stdio.h>
#include<stdlib.h>
int main(void){
    FILE *fp = fopen("hello.c" , "r") ; 
    if(fp == NULL){
        return -1 ;
    }
    int ch ; 
    int i = 0; 
    char buffer[200] ; 
    while((ch = fgetc(fp)) != EOF && i < 199){
        buffer[i++] = ch ;
    }
    buffer[i] = '\0' ; 
    printf("Your buffer is :%s\n" , buffer) ; 
    fclose(fp) ; 
    return 0 ;
}
________________very_important_code_____________
#include<stdio.h>
#include<stdlib.h>
#define BUF_SIZE 100
int main(void){
    FILE *fp = fopen("log.c" , "r+")  ; 
    if(fp == NULL){
        perror("Failed to open file !") ;
        return -1 ;
    }
    int ch ; 
    size_t size = BUF_SIZE ; 
    size_t i = 0 ; 
    char *buffer = (char *)malloc(size) ; 
    while(1){
        ch = fgetc(fp) ; 
        if(ch == EOF){ 
            break ;
        }
        if(1 >= size -1){
            size *= size ; 
            char *temp = realloc(buffer , size) ; 
            if(temp == NULL){
                perror("realloc failed !\n") ; 
                free(buffer) ; 
                fclose(fp) ;
                exit(EXIT_FAILURE);
            }
            buffer = temp ;
        }
        buffer[i++] = ch ;
    }
    buffer[i] = '\0' ; 
    printf("FILE CONTENT : %s\n" , buffer) ;
    free(buffer) ; 
    fclose(fp) ; 
    return 0 ;
}
_______________________another_example 
#include<stdio.h>
#include<stdlib.h>
int main(void){
    FILE *fp = fopen("log.bin" , "wb") ;
    if(fp == NULL){
        perror("Failed to open file !") ; 
        return -1  ;
    }
    int buffer[3] = {1 ,  2 , 3} ; 
    fwrite(buffer , sizeof(buffer[0]) , sizeof(buffer) / sizeof(buffer[0]) , fp) ; 
    fclose(fp) ; 
    return 0 ;
}
___________________________________
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int write_log(FILE *fp , const char *entry){
    if(fp == NULL || entry == NULL){
        exit(EXIT_FAILURE) ;
    }
    size_t size = strlen(entry) ; 
    size_t unit = sizeof(entry[0]) ; 
    size_t element = size  / unit ; 
    int written = fwrite(entry , unit , element , fp) ; 
    if(written != size){
        return -1 ;
    }
    fwrite("\n" ,1 , 1 , fp) ;
    return 0; 
}
int main(void){
    FILE *fp = fopen("log.c" , "a+") ; 
    if(fp == NULL){
        return -1 ;
    }
    write_log(fp , "Hello world and writing log !") ; 
    fclose(fp) ; 
    return 0;
}
