// Author: Josh Matni
// CS 302 PA 3: Stacks
// Purpose: Implementing the linkedStack

#include "linkedStack.h"
#include <string>

int precedence(char);
double calculatePostfix(const string&);

int main()
{
    string infix; 
    LinkedStack<char> stack; 
    //cout << "Enter an Infix Expression (Must be a valid calculator operation): ";
    getline(cin, infix);
    
    string postFix;
    for(int index = 0; index < infix.length(); index++)
    {
        if(infix[index] == ' ') continue; // ignore spaces

        if(infix[index] == '(')
        {
            stack.push(infix[index]);
        }
        else if(infix[index] == ')') // pop from stack until open parenthesis is found
        {
            while(!stack.isEmpty() && stack.peek() != '(')
            {
                postFix += stack.peek();
                stack.pop();
            }
            stack.pop(); // remove ( from stack
        }

        else if(precedence(infix[index]) > 0) // handles operators
        {
            while(!stack.isEmpty() && precedence(infix[index]) <= precedence(stack.peek()) && stack.peek() != '(')
            {
                postFix += stack.peek();
                stack.pop();
            }
            stack.push(infix[index]);
        }
        else if(precedence(infix[index]) == -1) // handles operands
        {
            postFix += infix[index];
        }
    }

    while(!stack.isEmpty()) // pop any remaining operators from the stack
    {
        postFix += stack.peek();
        stack.pop();
    }

    cout << postFix << endl;
    double result = calculatePostfix(postFix);
    cout << result << endl;
    return 0;
}

int precedence(char operatorChar)
{
    switch(operatorChar)
    {
        case '*':
        case '/':
            return 2; // these operands get priority
        case '+':
        case '-':
            return 1; 
        default:
            return -1;
    }
}

double calculatePostfix(const string& postFix) 
{
    LinkedStack<double> stack; 

    for(int i = 0; i < postFix.length(); i++) 
    {
        char c = postFix[i];

        if(c >= '0' && c <= '9') 
        {
            stack.push(c - '0');  // convert char digit to double
        } 
        else 
        {
            double operand2 = stack.peek(); 
            stack.pop();
            double operand1 = stack.peek(); 
            stack.pop();

            switch(c) 
            {
                case '+': 
                    stack.push(operand1 + operand2); 
                    break;
                case '-': 
                    stack.push(operand1 - operand2); 
                    break;
                case '*': 
                    stack.push(operand1 * operand2); 
                    break;
                case '/': 
                    stack.push(operand1 / operand2); 
                    break;
            }
        }
    }
    return stack.peek();
}
