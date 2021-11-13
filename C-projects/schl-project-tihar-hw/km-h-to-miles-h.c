#include<stdio.h>

double km2miles(double km){
	return km*0.62137119;
}

double miles2km(double miles){
	return miles/0.62137119;
}

int main(){
	double km,m;
	printf("Km/hour : ");
	scanf("%lf",&km);
	m = km2miles(km);
	printf("Miles/hour: %lf",m);
	return 0;
}