#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

struct Node{
    char data;
    struct Node *next;
};

struct Node *top=NULL;

void push(struct Node *ptr, char value){
    struct Node *newData=(struct Node *)malloc(sizeof(struct Node));
    newData->data=value;
    newData->next=top;
    top=newData;
}

char pop(struct Node *ptr){
    if(ptr==NULL){
        return '\0';
    }
    struct Node *temp=top;
    top=top->next;
    char value=temp->data;
    free(temp);
    return value;
}

char peek(struct Node *ptr){
    if(ptr==NULL){
        return '\0';
    }
    return top->data;
}

bool isempty(struct Node *ptr){
    return ptr==NULL;
}

int assignPrecedence(char operator){
    if(operator=='^'){
        return 3;
    }
    else if(operator=='*' || operator=='/'){
        return 2;
    }
    else if(operator=='+' || operator=='-'){
        return 1;
    }
    else{
        return 0;
    }
}

void infixToPostfix(char *infix, char *postfix){
    while(*infix!='\0'){
        if(isalnum(*infix)){
            *postfix=*infix;
            postfix++;
        }
        else if(*infix=='('){
            push(top, *infix);
        }
        else if(*infix==')'){
            while(!isempty(top) && peek(top)!='('){
                *postfix=pop(top);
                postfix++;
            }
            pop(top);
        }
        else{
            while(!isempty(top) && assignPrecedence(peek(top)) >= assignPrecedence(*infix)){
                *postfix=pop(top);
                postfix++;
            }
            push(top, *infix);
        }
        infix++;
    }
    while(!isempty(top)){
        *postfix=pop(top);
        postfix++;
    }
    *postfix='\0';
}

void inputInfix(char **ptr){
    *ptr=(char *)malloc(500*sizeof(char));
    printf("Enter the INFIX Expression: \n");
    scanf("%s", *ptr);
}

void displayPostfix(char *ptr){
    printf("Postfix Expression is: \n");
    printf("%s", ptr);
}

int main(){
    char *infix, *postfix;
    inputInfix(&infix);
    postfix=(char *)malloc(strlen(infix)*sizeof(char)+1);
    infixToPostfix(infix, postfix);
    displayPostfix(postfix);
}
