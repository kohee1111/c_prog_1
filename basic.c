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
//
