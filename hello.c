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
