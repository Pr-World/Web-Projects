#include<stdio.h>
#include "sstring.h"

int main(){
	//---------------- Simplicity Showcase -------------------
	
	sstring a;
	a = "This is a sample string!";
	printf("Sample: %s \n\n",a);
	
	// ----------------- Functions ShowCase -------------------
	
	//all functions of sstring have error checking methods!
	//create an error checking variable
	sstrfuncerr var;
	
	
	// -=-=- Sstrinput() -=-=-
	// No other scanf() or gets() support sstring so, specially sstrinput() for sstrings!
	printf("Sstrinput: ");
	var = sstrinput();
	
	//errcheck
	if(var._err){
		printf("\nAn error occured - Errcode: %d",var._err);
		showerrs();
	}else{
		a = var._str;
		printf("You entered: %s\n\n",a);
	}
	
	//-=-=- Sstrlen() -=-=-
	// strlen() from string.h also can do this but added as a support for sstrings!
	printf("Length of a: %d\n\n",sstrlen(a)); // Or printf("Length of a: %d\n\n",strlen(a)); <- from string.h
	
	//-=-=- Ssubstr() -=-=-
	//string from a pos=10, len=6 -> should return "sample"
	
	a = "This is a sample string";
	var = ssubstr(a,10,6);
	
	//errcheck
	if(var._err){
		printf("\nAn error occured - Errcode: %d",var._err);
		showerrs();
	}else{
		a = var._str;
		printf("Substr: %s\n\n",a);
	}
	
	//-=-=- Sstrfind() -=-=-
	
	a = "Here first space is at 4th char!";
	int check;
	
	//start from = 0, in string = a, what to find = " " space
	//should return 4! >>"Here "<<!
	check = sstrfind(0,a," ");
	
	//errcheck
	if((check<NO_ERR&&!(check==-1))||check>=sstrlen(a)){
		printf("\nAn Error occured - Errcode: %d",check);
		showerrs();
	}else{
		printf("First ' ' found at: %d in '%s'",check,a);
	}

}
