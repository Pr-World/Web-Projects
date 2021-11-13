#include <stdio.h>
#include <math.h>
#include "pi.h"

double VolOfSpehere(double radius){
	double r;
	r = (4/3)*PI*pow(radius,2);
	return r;
}

int main()
{
	double radius,volume;
	printf("Enter radius: ");
	scanf("%lf",&radius);
	volume = VolOfSpehere(radius);
	printf("Volume of spehere is: %lf",volume);
	return 0;
}