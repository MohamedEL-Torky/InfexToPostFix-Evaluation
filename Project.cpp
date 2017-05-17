/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: EL-Torky
 *
 * Created on April 20, 2017, 4:48 PM
 */

#include <iostream>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <conio.h>

using namespace std;

// operators stack
struct stackOfChars{
    char data;
    stackOfChars *next;
    stackOfChars(char d){
        data = d;
        next = NULL;
    }
};
// numbers stack
struct stackOfNumbers{
    int num;
    stackOfNumbers *next;
    stackOfNumbers(int no){
        num = no;
        next = NULL;
    }
};
// push operators to the char stack
void push(stackOfChars *&top,char data){
    stackOfChars *temp = new stackOfChars(data);
    temp->next = top;
    top = temp;
}
// push opernads to number stack
void pushNumbers(stackOfNumbers *&top,int data){
    stackOfNumbers *temp = new stackOfNumbers(data);
    temp->next = top;
    top = temp;
}
// pop operators from the char stack
char pop(stackOfChars *&top){
    if(top == NULL){return 0;}
    char data;
    stackOfChars *temp = top;
    top = top->next;
    data = temp->data;
    delete(temp);
    return data;
}
// pop operands from the number stack
int popNumbers(stackOfNumbers *&top){
    if(top == NULL ){ return 0;}
    int data;
    stackOfNumbers *temp = top;
    top = top->next;
    data = temp->num;
    delete(temp);
    return data;
}
// peek first element of char stack without removing it
char peek(stackOfChars *&top){
    if (top == NULL){return 0;}
    return top->data;
}
// check the precedence of the operator
int pirotity(char token){
    if (token == '^'){
        return 3;
    }
    else if (token == '*' || token == '/'){
        return 2;
    }
    else if (token == '+' || token == '-'){
        return 1;
    }
}
/* display all elemtns in the stack by poping them all and printing them
 Implemented for test purpouse only
 not used */
void displayStack(stackOfChars *&top){
    if (top == NULL){printf("Empty Stack\n");return;}
    while(top != NULL){
        printf("%c",pop(top));
    }
    printf("\n");
}
/* method that covert the infex to postfix and evaluate it then print the results
	it takes array of char of size 50 that contains infex forumla*/
void infixToPostFix(char infex[50]){
	// intialize the char array to save postfix notation in
    char postFix[50];
    // for operators and converting infex to postfix only
    stackOfChars *operators = NULL;
    // for operands and evaluate postfix
    stackOfNumbers *evaluation = NULL;
    int result = 0;
    // for numbers of more than one digit only
    int bigNumbers = 0;
    // counters to move the index of postfix and infex array
    int i,z,y,n;
    n = y = i = z = 0;
    char token;
    bool check = true;
    while(infex[i] != '\0'){
        if(infex[i] == '(' || infex[i] == ')' 
          || infex[i] == '^' || infex[i] == '*' 
          || infex[i] == '/' || infex[i] == '+' 
          || infex[i] == '-' ){
                    postFix[z] = ' ';
                    z++;
                if ( infex[i]  == ')'){
                    while(operators != NULL){
                        char token2 = pop(operators);
                        if ( token2 == '('){
                            break;
                        }
                        else{
                        postFix[z] = token2;
                        z++;
                        postFix[z] = ' ';
                        z++;
                        }
                    }
                }
                else if ( (peek(operators) != '^' && infex[i] != '^') &&
                        pirotity(peek(operators)) >= pirotity(infex[i]) 
                        && peek(operators) != '('){
                    postFix[z] = pop(operators);
                    push(operators,infex[i]);
                    z++;
                }
                else{

                    push(operators,infex[i]);
                }
                token = pop(operators);
                while(check){
                if ( (token != '^' || peek(operators) != '^' )
                     &&  pirotity(token) <= pirotity(peek(operators)) 
                     && peek(operators) != 0 && peek(operators) != '('
                    ){
                    postFix[z] = pop(operators);
                    push(operators,token);
                    z++;
                    token = pop(operators);
                }
                else{
                    push(operators,token);
                    check = false;
                }
                }
                check = true;
            }
        else{
            postFix[z] = infex[i];
            z++;

        }
        i++;
    }
    postFix[z] = ' ';
        z++;
	// if the stack is not empty we pop them all and put them into the postfix array
    while(operators != NULL){
        char token2 = pop(operators);
        postFix[z] = token2;
        z++;
        postFix[z] = ' ';
        z++;
    }
    printf("PostFix: \n");
    while(postFix[y] != '\0'){
    	if(postFix[y] == '+' || postFix[y] == '-' || postFix[y] == '/' || postFix[y] == '*'
		   || postFix[y] == '^' || postFix[y] == ' ' ||(postFix[y] >= 48 && postFix[y] <= 57) )
		   {
		   printf("%c",postFix[y]);
           y++;
		   }
		   else{
		   y++;
		   }
        
    }
    printf("\n");
    y = 0;

    ////////////////////////////////////////////////////////////////////////////
    //                         PostFix Evaluation                             //
    ////////////////////////////////////////////////////////////////////////////
    printf("Evaluation: \n");
    while(postFix[y] != '\0'){
        if( isdigit( postFix[y] ) ){
            n = postFix[y] - '0';
            pushNumbers(evaluation,n);
        }
        else if ( postFix[y] == '+'){
            int topOfStack,afterTopOfStack;
            topOfStack = popNumbers(evaluation);
            afterTopOfStack = popNumbers(evaluation);
            result = afterTopOfStack + topOfStack;
            
            pushNumbers(evaluation,result);
        }
        else if ( postFix[y] == '-'){
            int topOfStack,afterTopOfStack;
            topOfStack = popNumbers(evaluation);
            afterTopOfStack = popNumbers(evaluation);
            result = afterTopOfStack - topOfStack;
            pushNumbers(evaluation,result);
        }
        else if ( postFix[y] == '*'){
            int topOfStack,afterTopOfStack;
            topOfStack = popNumbers(evaluation);
            afterTopOfStack = popNumbers(evaluation);
            result = afterTopOfStack * topOfStack;
            pushNumbers(evaluation,result);
        }
        else if ( postFix[y] == '^'){
            int topOfStack,afterTopOfStack;
            topOfStack = popNumbers(evaluation);
            afterTopOfStack = popNumbers(evaluation);
            result = pow(afterTopOfStack , topOfStack);
            pushNumbers(evaluation,result);
        }
        else if ( postFix[y] == '/'){
            int topOfStack,afterTopOfStack;
            topOfStack = popNumbers(evaluation);
            afterTopOfStack = popNumbers(evaluation);
            if(topOfStack == 0){
            printf("Cannot divide by zero");
            result = 0;
            break;
            }
            result = afterTopOfStack / topOfStack;
            pushNumbers(evaluation,result);
        }
        if (isdigit( postFix[y] ) && isdigit( postFix[y-1] )){
            n = popNumbers(evaluation);
            bigNumbers = popNumbers(evaluation) * 10;
            bigNumbers += n;
            pushNumbers(evaluation,bigNumbers);
        }
        y++;
        result = 0;
    }
    printf("%d",popNumbers(evaluation));
}
int main() {
    char tester[50];
    printf("Please Enter a mathematical to evaluate it and convert it to postfix\n");
    scanf("%s",&tester);
    infixToPostFix(tester);
    getch();
    return 0;
}
