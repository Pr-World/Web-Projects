#include<stdio.h>
#include "sstring.h"

int main(){
	//---------------- Simplicity Showcase -------------------
	
	sstring a;
	a = sstr.assign("This is a sample string!");
	printf("Sample: %s \n\n",sstr.val(a));
	
	// ----------------- Functions ShowCase -------------------
	
	//all functions of sstring have error checking methods!
	
	
	// -=-=- sstr.getinput() -=-=-
	// No other scanf() or gets() support sstring so, specially sstr.getinput() for sstrings!
	printf("Enter a string: ");
	a = sstr.getinput();
	
	//errcheck
	if(a._err!=_SSTRING_NO_ERR){
		sstr.showerrs(a._err);
	}elsse{
		printf("You entered: %s\n\n",sstr.val(a));
	}
	
	//-=-=- sstr.len() -=-=-
	// strlen() from string.h also can do this but added as a support for sstrings!
	printf("Length of a: %d\n\n",sstr.len(a)); // Or printf("Length of a: %d\n\n",strlen(a)); <- from string.h
	
	//-=-=- sstr.substr() -=-=-
	//string from a pos=10, len=6 -> should return "sample"
	
	a = sstr.assign("This is a sample string");
	a = sstr.substr(a,10,6);
	
	//errcheck
	if(a._err){
		sstr.showerrs(a._err);
	}else{
		printf("Substr: %s\n\n",sstr.val(a));
	}
	
	//-=-=- sstr.find() -=-=-
	
	a = sstr.assign("Here first space is at 4th char!");
	int check;
	
	//start from = 0, in string = a, what to find = " " space
	//should return 4! >>"Here "<<!
	check = sstr.find(0,a," ");
	
	//errcheck
	if((check<NO_ERR&&!(check==-1))||check>=sstrlen(a)){
		sstr.showerrs(check);
	}else{
		printf("First ' ' found at: %d in '%s'",check,sstr.val(a));
	}

}
