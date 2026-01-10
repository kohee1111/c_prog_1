//converting form a chat to int (ASCII) 
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
