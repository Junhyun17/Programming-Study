#include<stdio.h>

int add(int a, int b);

int main() {
	int num1 = 3;
	int num2 = 4;
	int result;

	result = add(num1, num2);
	printf("%d", result);
	return 0;
}

int add(int a, int b) {
	return (a + b);
}