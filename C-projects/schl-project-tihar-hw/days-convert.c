#include <stdio.h>

typedef struct{
	int year;
	int month;
	int day;
}date;

date days2date(int days){
	int d = days;
	int y = d/365;
	d = d - (y*365);
	int m = d/30;
	d = d - (m*30);
	date dt;
	dt.year = y;
	dt.month = m;
	dt.day = d;
	return dt;
}

int main(){
	int days;
	date dt;
	printf("Enter the no of days: ");
	scanf("%d",&days);
	dt = days2date(days);
	printf("%d years, %d months and %d days!",dt.year,dt.month,dt.day);
	return 0;
}