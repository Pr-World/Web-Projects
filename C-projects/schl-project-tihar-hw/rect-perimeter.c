#include<stdio.h>

double RectPerimeter(double length,double breadth){
	return 2*(length+breadth);
}

int main(){
	double l,b,p;
	printf("Enter length: ");
	scanf("%lf",&l);
	printf("Enter breadth: ");
	scanf("%lf",&b);
	p = RectPerimeter(l,b);
	printf("Perimeter of rectangle: %lf",p);
	return 0;
}