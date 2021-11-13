#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stddef.h>

//for validation
bool isDOB(char * Str){
	if(strlen(Str)!=10){
		return false;
	}
	for(int i=0;i<strlen(Str);i++){
		if(i==0||i==1||i==3||i==4||i>5){
			if(Str[i]<'0'||Str[i]>'9'){
				return false;
			}
		}else if(!(Str[i]=='-')){
			return false;
		}
	}
	//if format matches check month, date and year
	int day,month,year;
	int CurYear=2021;
	bool isLeapYear = false;
	
	day = ((Str[0]-'0')*10)+(Str[1]-'0');
	month = ((Str[3]-'0')*10)+(Str[4]-'0');
	year = ((Str[6]-'0')*1000)+((Str[7]-'0')*100)+((Str[8]-'0')*10)+(Str[9]-'0');
	
	if(day<=0||month<=0||year<=0||year>=CurYear||CurYear-year>110||month>12||day>31){
		return false;
	}
	
	if(year%4==0){
		isLeapYear = true;
	}else if(year%100==0){
		if(year%400==0){
			isLeapYear = true;
		}
	}
	
	//daycheck for 31 days already done so
	//check for 28/29 days of february and 30 days of rest
	
	if(month==2){
		if(isLeapYear&&day>29){
			return false;
		}else if(isLeapYear==false&&day>28){
			return false;
		}
	}
	
	if(month%2==0&&month!=2&&month<8){
		if(day>30){
			return false;
		}
	}
	if(month%2==1&&month>8){
		if(day>30){
			return false;
		}
	}
	return true;
}

//for validation
bool isPhNo(char * Str){
	if(strlen(Str)==0){
		return false;
	}
	bool tmpbl1 = false;
	int tmpi1,tmpi2;
	for(size_t i=0;i<strlen(Str);i++){
		if(Str[i]<'0'||Str[i]>'9'){
			if(Str[i]=='+'&&i!=0){
				return false;	
			}
		}
	}
	return true;
}

int main(){
	char name[100],db[11],phno[20];
	printf("Enter your name: ");
	scanf("%s",name);
	dbhere:
	printf("\nEnter DOB [A.D] [format: dd-mm-yyyy]: ");
	scanf("%s",db);
	if(isDOB(db)==false){
		printf("Invalid date! try again\n");
		goto dbhere;
	}
	phhere:
	printf("\nPhone number [10 digit, country-code: optional]\nphNo: ");
	scanf("%s",phno);
	if(strlen(phno)<10||isPhNo(phno)==false){
		printf("Invalid phone number! try again\n");
		goto phhere;
	}
	printf("\nYour name: %s\nDOB: %s\nPhone number: %s\n",name,db,phno);
}