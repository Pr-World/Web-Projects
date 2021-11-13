#include <stdio.h>

int main(){
	double add,mul,sub,div,num1,num2;
	printf("Enter num1: ");
	scanf("%lf",&num1);
	printf("Enter num2: ");
	scanf("%lf",&num2);
	add = num1+num2;
	sub = num1-num2;
	mul = num1*num2;
	div = num1/num2;
	printf("Addition: %lf\nSubtraction: %lf\nMultiplication: %lf\nDivision: %lf",add,sub,mul,div);
	return 0;
}