#define _CRT_SECURE_NO_WARNINGS
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>


void readFile();
bool isKeyword(char*);
bool isLetter(char);
bool isDigit(char);
bool isOperator(char);
bool isIdentifier(char*);
bool isInteger(char*);
bool isDecNumber(char*);
bool isDelimeter(char);

int main() {

	
	char token[10];
	char c, str[100];
	int vel, i=0, n=0, br=0, z=0, count=0;
	FILE* fp = fopen("tekst.txt", "r");


	if (fp == NULL) {
		printf("greska pri otvaranju datoteke\n");
		return;
	}

	while (!feof(fp)) {
		fgets(str, sizeof(str), fp);
		br = 0;
		vel = strlen(str);

		while (br < vel) {

			for (i = 0; i < 10; i++)
				token[i] = NULL;

			c = str[br++];

			while (c == ' ')
				c = str[br++];

			if (isLetter(c)) {
				n = 0;
				while (isLetter(c) || isDigit(c)) {
					token[n++] = c;
					c = str[br++];
				}
				token[n++] = '\0';
				br--;
				if (isKeyword(token))
					printf("Keyword: %s\n", token);
				else if (isIdentifier(token))
					printf("Identifier: %s\n", token);
			}
			else if (isDigit(c)) {
				n = 0;
				while (isDigit(c) || isLetter(c) || c == '.') {

					token[n++] = c;
					c = str[br++];

				}
				token[n++] = '\0';

				br--;
				for (z = 0; z < n; z++) {
					if (isDigit(token[z]) || token[z] == '.')
						count++;
				}

				if (count == n - 1) {
					if (isInteger(token))
						printf("Integer: %s\n", token);
					else if (isDecNumber(token))
						printf("Decimal number with point: %s\n", token);
				}
				else
					if (!isIdentifier(token))
						printf("Invalid identifier: %s\n", token);

				count = 0;
			}
			else if (isOperator(c)) {
				n = 0;
				if (c == '=') {
					token[n++] = c;
					c = str[br++];
					if (c == '=') {
						token[n++] = c;
						
					}
					else
						br--;
					token[n] = '\0';
					
					printf("Operator: %s\n", token);
				}
				else if (c == '>') {
					token[n++] = c;
					c = str[br++];
					if (c == '=') {
						token[n++] = c;
					}
					else if (c == '>') {
						token[n++] = c;
						
					}
					else
						br--;
					token[n] = '\0';
					
					printf("Operator: %s\n", token);
				}
				else if (c == '<') {
					token[n++] = c;
					c = str[br++];
					if (c == '=') {
						token[n++] = c;
						
					}
					else if (c == '<') {
						token[n++] = c;
						
					}else
						br--;
					token[n] = '\0';
					
					printf("Operator: %s\n", token);
				}
				else if (c == '+') {
					token[n++] = c;
					c = str[br++];
					if (c == '+') {
						token[n++] = c;

					}
					else
						br--;
					token[n] = '\0';
					
					printf("Operator: %s\n", token);
				}
				else if (c == '-') {
					token[n++] = c;
					c = str[br++];
					if (c == '-') {
						token[n++] = c;
						
					}
					else
						br--;
					

					token[n] = '\0';
				
					printf("Operator: %s\n", token);
				}
				else
					printf("Operator: %c\n", c);
			}
			else if (isDelimeter(c)) {
				printf("Delimiter: %c\n", c);
			}
		}

	}



	return 0;
}

bool isKeyword(char* str) {
	char *words[16]={"begin", "if", "then", "while", "do", "end", "for", "return", "float", "int", "double", "bool", "struct", "static", "void", "else"};
	int i;

	for (i = 0; i < 16; i++) {
		if (strcmp(str, words[i]) == 0)
			return true;
		
	}

	return false;
}
bool isLetter(char ch) {

	ch = tolower(ch);
	if (ch >= 'a' && ch <= 'z')
		return true;
	else return false;
}
bool isDigit(char n) {

	if (n >= '0' && n <= '9')
		return true;
	else
		return false;
}
bool isOperator(char ch) {
	char op[] = { '+', '-', '/', '*', '=', '<', '>' };
	int i;

	for (i = 0; i < strlen(op); i++)
		if (ch == op[i])
			return true;

	return false;
}
bool isIdentifier(char* str) {
	if (isDigit(str[0]) || isDelimeter(str[0]))
		return false;
	else
		return true;
}
bool isInteger(char* str) {
	int i, len, count=0;
	len = strlen(str);
	if (len == 0)
		return false;
	else
	{
		for (i = 0; i < len; i++)
			if (!isDigit(str[i]))
				count++;
		if (count != 0)
			return false;
		else return true;
				
	}
}
bool isDecNumber(char* str) {
	int i, len = strlen(str);
	bool decPoint = false;
	if (len == 0)
		return false;
	for (i = 0; i < len; i++) {
		if (str[i] != '0' && str[i] != '1' && str[i] != '2' && str[i] != '3' && str[i] != '4' && str[i] != '5' && str[i] != '6' && str[i] != '7' && str[i] != '8'
			&& str[i] != '9' && str[i] != '.' || (str[i] == '-' && i > 0))
			return false;
		if (str[i] == '.')
			decPoint = true;
	}
	return decPoint;

}
bool isDelimeter(char ch) {
	if (ch == ',' || ch == ';' || ch == '(' || ch == ')' || ch == '[' || ch == ']' || ch == '{' || ch == '}')
		return true;
	else return false;
}