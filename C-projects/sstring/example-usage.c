#include<stdio.h>
#include "sstring.h"


int main(){
	//simplicity showcase
	sstring a;
	a = "This is a sample string!";
	
	printf("String is: %s\n\n",a);
	
	//functions showcase
	
	//sstrlen
	printf("Length of string %d",sstrlen(a));
	
	//sstrfind
	printf("First Space found in %d place\n\n",sstrfind(0,a," ")._str);
	
	//sstrappend
	printf("Appending 'Yeah so simple!': %s\n\n",sstrappend(a," Yeah! so simple!")._str);
	
	//sstrinput
	printf("Sstrinput is inputting text: ");
	sstring tmp;
	tmp = sstrinput()._str;
	printf("You entered: %s\n\n",tmp);
	
	//ssetchar
	printf("Setting String char[0] to 'F': %s",ssetchar(a,0,'F')._str);
	
	
	
}
