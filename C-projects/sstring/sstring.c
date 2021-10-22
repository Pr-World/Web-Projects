#include<stdio.h>
#include<string.h>
#include "sstring.h"
#include<stdbool.h>

/*
A Big Note To the ones saying dont return Local Variable Adresses

Below functions dont return any local variable addresses
to prove it, call the functions MULTIPLE times  -> you will see yourself

They return a typedef of strfunc which contains the string in array format
when the user does [functionname]([parameters])._str; the str array value is sent to the pointer
so no issue will be created! :D

*/


size_t sstrlen(sstring _str){
	//just as support for sstrings
	// all functions included are better!
	return strlen(_str);
}

bool isGMCLCorrupt(){
	//checks if global max char limit is corrupted
	if(GLOBAL_MAX_CHAR_LIMIT<=0){
		return true;
	}else{
		return false;
	}
}

sstrfunc ssubstr(sstring _str,ssize_t _pos,size_t _len){
	//dont store anything make null return value
	sstrfunc _null;
	
	//is global max char limit corrupted??
	//returning null means error was caught!
	if(isGMCLCorrupt()){
		//gmcl is corrupt! errcode: #defined in sstring.h
		_null._err = GMCL_CORRUPT;
		return _null;
	}
	//idk why but this removes a weird glitch
	printf("%c\b",' ');
	if(sstrlen(_str)>=GLOBAL_MAX_CHAR_LIMIT||_pos>=GLOBAL_MAX_CHAR_LIMIT||_len>=GLOBAL_MAX_CHAR_LIMIT){
		_null._err = GMCL_ERR;
		return _null;
	}
	
	if(_pos>=sstrlen(_str)||_pos<0||_len>=sstrlen(_str)||_len<0){
		_null._err = INVALID_ARGS;
		return _null;
	}
	
	sstrfunc _ret;
	
	_ret._err = NO_ERR;
	strncpy(_ret._str,_str+_pos,_len);
	_ret._str[_len] = '\0';
	return _ret;
	
}

sstrfunc sstrappend(sstring _var1,sstring _var2){
	//dont store anything make null return value
	sstrfunc _null;
	
	//is global max char limit corrupted??
	//returning null means error was caught!
	if(isGMCLCorrupt()){
		//gmcl is corrupt! errcode: #defined in sstring.h
		_null._err = GMCL_CORRUPT;
		return _null;
	}
	
	
	if(sstrlen(_var1)+sstrlen(_var2)>=GLOBAL_MAX_CHAR_LIMIT){
		_null._err = GMCL_ERR;
		return _null;
	}
	//use of string.h functions -> far easier than my previous headscratching!
	char _ret1[sstrlen(_var1)+sstrlen(_var2)];
	strcpy(_ret1,_var1);
	strcat(_ret1,_var2);
	sstrfunc _ret;
	//no errors :D
	_ret._err = NO_ERR;
	strcpy(_ret._str,_ret1);
	return _ret;
}

sstrfunc sstrinput(){
	//dont store anything make null return value
	sstrfunc _null;
	//is global max char limit corrupted??
	//returning null means error was caught!
	if(isGMCLCorrupt()){
		_null._err = GMCL_CORRUPT;
		return _null;
	}
	char _tmp[GLOBAL_MAX_CHAR_LIMIT];
	//fgets for safety :)
	fgets(_tmp,GLOBAL_MAX_CHAR_LIMIT,stdin);
	sstrfunc _ret;
	//ret._str is array upto GLOBAL_MAX_CHAR_LIMIT
	//also tmp is array upto GLOBAL_MAX_CHAR_LIMIT
	//so its safe :) to use strcpy same as strncpy
	strcpy(_ret._str,_tmp);
	//'\n' avoided
	_ret._str[strlen(_tmp)-1] = '\0';
	_ret._err = NO_ERR;
	return _ret;
}

sstrfunc ssetchar(sstring _str,ssize_t _pos,char _ch){
	sstrfunc _null;
	//is global max char limit corrupted??
	//returning null means error was caught!
	if(isGMCLCorrupt()){
		_null._err = GMCL_CORRUPT;
		return _null;
	}

	sstrfunc _ret;
	if(sstrlen(_str)>=GLOBAL_MAX_CHAR_LIMIT){
		_null._err = GMCL_ERR;
		return _null;
	}
	if(_pos>=sstrlen(_str)||_pos<0){
		_null._err = INVALID_ARGS;
		return _null;
	}
	strcpy(_ret._str,_str);
	_ret._str[_pos] = _ch;
	_ret._err = NO_ERR;

	return _ret;
}

void showerrs(){
	printf("\n---- ERRORS Corresponding to their codes ----\n");
	printf("%d :- GMCL [global max char limit] is corrupted\n",GMCL_CORRUPT);
	printf("%d :- INVALID ARGS [the provided arguments are invalid]\n",INVALID_ARGS);
	printf("%d :- GMCL_ERR [provided variable has length greater than GMCL]\n",GMCL_ERR);
	printf("Other :- Unknown Error - Not Known Errors \n");
	printf("---------------------------------------------\n");
}


charfunc sgetchar(sstring _str,ssize_t _pos){
	charfunc _null;
	//is global max char limit corrupted??
	if(isGMCLCorrupt()){
		_null._err = GMCL_CORRUPT;
		return _null;
	}
	// condition checking which are likely make error after
	if(sstrlen(_str)>=GLOBAL_MAX_CHAR_LIMIT){
		_null._err = GMCL_ERR;
		return _null;
	}
	
	if(_pos>=sstrlen(_str)||_pos<0||sstrlen(_str)<0){
		_null._err = INVALID_ARGS;
		return _null;
	}	
	charfunc chr;
	chr._char = _str[_pos];
	chr._err = NO_ERR;
	return chr;
}

//if the length of string is in size_t
//and charachters in it can also be beyond int who knows!
//used ssize_t to support returning negative numbers, i.e -> -1 and errors

//init is the place to start finding
ssize_t sstrfind(size_t init,sstring _str,sstring _find){
	size_t _len1 = sstrlen(_str);
	size_t _len2 = sstrlen(_find);
	size_t matching = 0;
	
	//is global max char limit corrupted??
	if(isGMCLCorrupt()){
		return GMCL_CORRUPT;
	}
	
	if(sstrlen(_str)>=GLOBAL_MAX_CHAR_LIMIT||sstrlen(_find)>=GLOBAL_MAX_CHAR_LIMIT){
		return GMCL_ERR;
	}
	
	//some weird conditions check [user, are u fooling the function ?]
	if(_len2>_len1||init<0||init>_len1-1){
		return INVALID_ARGS;
	}
	
	//security check
	if(_len1>=GLOBAL_MAX_CHAR_LIMIT||_len2>=GLOBAL_MAX_CHAR_LIMIT){
		return GMCL_ERR;
	}
	
	if(_len1==0||_len2==0){
		//obviously it wont be found if the string itself is null or the tobefound string is null
		return -1;
	}
	
	//the main finder -by myself
	for(size_t i=init;i<_len1+1;i++){
		if(_str[i]==_find[0]){
			for(int z=0;z<_len2+1;z++){
				if(matching==_len2){
					return i;
				}
				else if(_str[i+z]==_find[z]){
					matching+=1;
				}
				else{
					matching=0;
					break;
				}
			}
		}
	}
	return -1;
}



