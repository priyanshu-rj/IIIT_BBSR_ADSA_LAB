#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAX 100

int stack[MAX];
int top = -1;

void push(int value) {
    stack[++top] = value;
}

int pop() {
    return stack[top--];
}

int evaluatePostfix(char postfix[]) {
    int i, op1, op2, result;
    char ch;

    for (i = 0; i < strlen(postfix); i++) {
        ch = postfix[i];
        if (isdigit(ch)) {
            push(ch - '0');  // convert char to int
        } else {
            op2 = pop();
            op1 = pop();

            switch (ch) {
                case '+': result = op1 + op2; break;
                case '-': result = op1 - op2; break;
                case '*': result = op1 * op2; break;
                case '/': result = op1 / op2; break;
                case '^': result = op1 ^ op2; break;
            }
            push(result);
        }
    }
    return pop();
}

int main() {
    char postfix[MAX];
    printf("Enter Postfix Expression (use single digits): ");
    scanf("%s", postfix);

    int result = evaluatePostfix(postfix);
    printf("Result of Postfix Evaluation: %d\n", result);

    return 0;
}
