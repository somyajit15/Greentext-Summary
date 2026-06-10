#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAX 100

// Stack for characters (operators)
char stack[MAX];
int top = -1;

// Stack for integers (evaluation)
int valStack[MAX];
int valTop = -1;

// Function Prototypes
void push(char);
char pop();
int precedence(char);
void infixToPostfix(char infix[], char postfix[]);
void pushVal(int);
int popVal();
int evaluatePostfix(char postfix[]);

// Push for operator stack
void push(char c) {
    if (top == MAX - 1)
        printf("Stack Overflow\n");
    else
        stack[++top] = c;
}

// Pop for operator stack
char pop() {
    if (top == -1)
        return -1;
    else
        return stack[top--];
}

// Precedence of operators
int precedence(char c) {
    if (c == '^')
        return 3;
    else if (c == '*' || c == '/')
        return 2;
    else if (c == '+' || c == '-')
        return 1;
    else
        return 0;
}

// Convert Infix to Postfix
void infixToPostfix(char infix[], char postfix[]) {
    int i, j = 0;
    char symbol, temp;

    for (i = 0; infix[i] != '\0'; i++) {
        symbol = infix[i];

        if (isalnum(symbol)) { // Operand goes directly to postfix
            postfix[j++] = symbol;
        }
        else if (symbol == '(') {
            push(symbol);
        }
        else if (symbol == ')') {
            while ((temp = pop()) != '(')
                postfix[j++] = temp;
        }
        else { // Operator
            while (top != -1 && precedence(stack[top]) >= precedence(symbol)) {
                postfix[j++] = pop();
            }
            push(symbol);
        }
    }

    while (top != -1) {
        postfix[j++] = pop();
    }
    postfix[j] = '\0';
}

// Push for integer stack (evaluation)
void pushVal(int val) {
    if (valTop == MAX - 1)
        printf("Value Stack Overflow\n");
    else
        valStack[++valTop] = val;
}

// Pop for integer stack (evaluation)
int popVal() {
    if (valTop == -1) {
        printf("Value Stack Underflow\n");
        return -1;
    }
    else
        return valStack[valTop--];
}

// Evaluate Postfix expression
int evaluatePostfix(char postfix[]) {
    int i, op1, op2, result;
    char symbol;

    for (i = 0; postfix[i] != '\0'; i++) {
        symbol = postfix[i];

        if (isdigit(symbol)) {
            pushVal(symbol - '0'); // convert char digit to int
        }
        else { // Operator
            op2 = popVal();
            op1 = popVal();
            switch (symbol) {
                case '+': result = op1 + op2; break;
                case '-': result = op1 - op2; break;
                case '*': result = op1 * op2; break;
                case '/': result = op1 / op2; break;
                case '^': result = 1;
                          for (int k = 0; k < op2; k++)
                              result *= op1;
                          break;
                default: printf("Invalid Operator\n"); return -1;
            }
            pushVal(result);
        }
    }
    return popVal();
}

// Main Function
int main() {
    char infix[MAX], postfix[MAX];
    int result;

    printf("Enter Infix Expression (single-digit operands): ");
    scanf("%s", infix);

    infixToPostfix(infix, postfix);

    printf("Postfix Expression: %s\n", postfix);

    result = evaluatePostfix(postfix);
    printf("Evaluation Result: %d\n", result);

    return 0;
}
