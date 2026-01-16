//converting form a char to int (ASCII) 
#include<stdio.h>
#include<string.h>
int main(void){
    char a = 'a' ; 
    int int_a = (int)a ; 
    printf("The ascii value of char a is :%d\n"  , int_a) ;
    printf("I am fucking back") ;
    return 0 ;
}
//for Alpha numeric 
#include<stdio.h>
#include<ctype.h>

int main(void){

    char ch = '.' ; 
    if(isalnum(ch)){

        printf("%c is alpha numeric !\n" , ch) ;
    }else{

        printf("%c is not alpha numeric !\n" , ch ) ;
    }
    return 0 ;
}
///learning all functions form stdio.h source 
//code example to learn clearerr() ;
#include<stdio.h>
#include<stdlib.h>
int main(void){

    FILE *fp = fopen("log.c" , "r") ; 
    if(fp == NULL) {

        perror("Failed to open file !\n") ; 
        return -1;
    }
    if(fputc('A' , fp) == EOF){
        perror("Failed to write ~!") ;
    }
    if(ferror(fp)){

        printf("Error deteced ....cleaning error !~") ; 
        clearerr(fp) ;
    }
    return 0 ;
}
//learning about custom functions ....to make reusable code 
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
FILE *open_my_file(const char *file_name , const char *mode){

    FILE *fp = fopen(file_name , mode) ; 
    if(fp == NULL){

        perror("Failed \n") ;
        exit(EXIT_FAILURE) ;
    }
    return fp ;
}
int main(void){
    const char *file_name = "log.c" ; 

    FILE *file_pointer = open_my_file("log.c" , "w+") ; 
    if(file_pointer == NULL){
        return -1 ;
    }
    if(fprintf(file_pointer  , "Hello world and I am back !") < 0){
        printf("Failed to write in file %s\n" , file_name)  ; 
        exit(EXIT_FAILURE) ;
    }
    if(ferror(file_pointer)){

        printf("Error detected \n") ; 
        clearerr(file_pointer) ;
    }
    fclose(file_pointer) ;
    return 0 ;
}
//dprintf() vs fprintf() ........fprintf() use for simple formated stdout and stderr only for file stream but dprintf() only used for file descriptor ....so its compare to more lower level 
//simple example of dprintf 
#include<stdio.h>
#include<unistd.h>
int main(void){
    dprintf(STDIN_FILENO , "Hello world via dprintf()\n") ; 
    return 0  ;
}
//another simple example of dprintf() and fd's
#include<errno.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<string.h>
int main(void){
    const char *file_name = "log.c" ;
    int file_des = open(file_name , O_WRONLY | O_CREAT | O_TRUNC , 0x1A4 ) ; 
    if(file_des < 0){
        dprintf(STDERR_FILENO , "Failed :%s\n" , strerror(errno)) ;
        exit(EXIT_FAILURE) ; 
    }
    signed int n = dprintf(file_des , "Writing something via dprintf and low level sys-calls\n") ;
    if(n < 0){

        dprintf(STDERR_FILENO , "Failed :%s" , strerror(errno)) ;
        close(file_des) ;
        exit(EXIT_FAILURE) ;
    }
    close(file_des) ;
    return 0 ;
}
//multiple code combined 
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<errno.h>
#include<stdarg.h>
int open_my_file(const char *file_name ,  int flags , mode_t permission){

    int fd = open(file_name , flags  , permission) ; 
    if(fd < 0){
        dprintf(STDERR_FILENO , "Failed to open :%s" , strerror(errno)) ; 
        exit(EXIT_FAILURE) ;
    }
    return fd ;
}
void my_print_func(const char *fmt , ...){

    va_list args ; 
    va_start(args , fmt) ; 
    vdprintf(STDOUT_FILENO  , fmt , args) ; 
    va_end(args) ; 
}
int main(void){
    my_print_func("Printing something via custom func") ; 
    const char *file_name = "log.c" ;
    int file_des = open(file_name , O_WRONLY | O_CREAT | O_TRUNC , 0x1A4)  ; 
    signed int n = dprintf(file_des , "Writing something via dprintf and low level system call") ; 
    if(n < 0){
        dprintf(STDERR_FILENO , "Failed to write in the file :%s\n" , strerror(errno)) ; 
        close(file_des) ; 
        exit(EXIT_FAILURE) ;
    }
    close(file_des) ; 
    return 0 ;
} 
//pure custom function 
//avoid using void in the system level for caller control 
#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<errno.h>
#include<stdlib.h>
#include<fcntl.h>
#include<stdarg.h>
void  write_file(int fd , const char *fmt ,...){
    va_list args  ;
    va_start(args , fmt) ; 
    vdprintf(fd , fmt , args) ; 
    va_end(args) ; 
}

int main(void){
    const char *file_name = "log.c" ;
    int file_des = open(file_name , O_WRONLY | O_CREAT | O_TRUNC , 0x1A4) ;
    if(file_des < 0){

        dprintf(STDERR_FILENO , "Failed to open file :%s\n" , strerror(errno))  ;
        return -1 ; 
    }
    write_file(file_des , "process id is :%d\n" , getpid()) ; 
    close(file_des) ;
    return 0 ;
}
//another simple example 
#include <stdio.h>
#include <stdarg.h>
#include <unistd.h>
int myprintf(const char *fmt, ...) {
    va_list ap;
    int ret;
    va_start(ap, fmt);
    ret = vdprintf(STDOUT_FILENO, fmt, ap);
    va_end(ap);
    return ret;
}
int main() {
    myprintf("Dark power: %s %d\n", "vdprintf", 666);
    return 0;
}
//learn to return .....another simple example 
#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<stdarg.h>
#include<stdlib.h>
#include<errno.h>
int print_func_ret(int fd , const char *fmt , ...){
    int ret ; 
    va_list args ; 
    va_start(args , fmt) ; 
    ret = vdprintf(STDOUT_FILENO , fmt , args) ; 
    va_end(args) ; 
    return ret ;
}
void void_func(int fd , const char *fmt , ...){
    va_list args ; 
    va_start(args , fmt) ; 
    vdprintf(STDOUT_FILENO , fmt , args) ; 
    va_end(args) ;
}

int main(void){
    const char *message = "Hello world" ; 
    int n = print_func_ret(STDOUT_FILENO , "Hello world and again :%s" , message) ; 
    if(n < 0){
        dprintf(STDERR_FILENO , "ERROR :%s\n"  , strerror(errno)) ;
        return -1 ;
    }
    void_func(STDOUT_FILENO , "ANOTHER message :%s\n" , message) ;
    return 0 ; 
}
//another simple example
#include<stdio.h>
#include<stdlib.h>
int main(void){
    FILE *fp = fopen("log.c" , "r") ; 
    if(!fp){
        perror("Failed to open file @!") ; 
        return -1 ;
    }
    int ch ; 
    while((ch = fgetc(fp)) != EOF){
        putchar(ch) ;
    }
}
//another example : right use of eof and feof 
#include<stdio.h>
#include<stdlib.h>
int main(void){
    FILE *fp = fopen("log.c" , "r") ; 
    if(fp == NULL){
        fprintf(stderr , "Failed to open file !") ; 
        return -1 ;
    }
    int ch  ; 
    while(1){
        ch = fgetc(fp) ; 
        if(ch == EOF){
            if(feof(fp)){
                break ;
            }
            if(ferror(fp)){
                perror("Failed to  read file !") ; 
                fclose(fp) ;
                return -1 ;
            }
        }
        putchar(ch)  ;
    }
    fclose(fp) ; 
    return 0 ;
}
//learn ferror 
#include<stdio.h>
#include<stdlib.h>
#include<stdlib.h>
int main(void){
    FILE *file = fopen("log.c" , "w") ; 
    if(file == NULL){
        perror("Failed to open file !") ; 
        return -1;
    }
    fputs("Hello world and kohee !" , file) ; 
    if(ferror(file)){
        perror("Failed to write file @!") ; 
        fclose(file) ; 
        return -1 ;
    }
    fclose(file) ; 
    return 0;
}
//learn fflush() ; 
#include<stdio.h>
#include<stdlib.h>
int main(void){
    printf("> ") ; 
    fflush(stdout) ; 
    char ch ; 
    ch = getchar() ; 
    printf("Your char is :%c\n" , ch) ;
}
//another : "Power 1 done" string writing immediately before any unexpected crash or error 
//usecase : Database , loggin system 
#include<stdio.h>
#include<stdlib.h>
int main(void){
    FILE *fp = fopen("log.c"  ,"w") ; 
    if(fp == NULL){
        return -1  ;
    }
    fputs("Power 1 done !" , fp) ; 
    fflush(fp) ;
    fputs("Power 2 done !" , fp) ;
    fclose(fp) ;
}
//learning fgetpos() and fsetpos() 
//file manupulation and bookmarking 
#include<stdio.h>
#include<stdlib.h>
int main(void){
    FILE *fp = fopen("log.c" , "r") ; 
    if(fp == NULL){
        return -1 ;
    }
    int ch ; 
    fpos_t pos  ; 
    for(int i = 0 ; i < 10 && (ch = fgetc(fp)) != EOF ; i++){
        putchar(ch) ; 
    }
    printf("\n") ; 
    fgetpos(fp , &pos) ; 
    for(int i = 0 ; i < 5 && (ch = fgetc(fp)) != EOF ; i++){
        putchar(ch) ;
    }
    printf("\n") ;
    fsetpos(fp , &pos) ; 
    for(int i = 0 ; i < 5 && (ch = fgetc(fp)) != EOF ; i++){
        putchar(ch) ;
    }
    printf("\n") ;
    fclose(fp) ; 
    return 0;
}
