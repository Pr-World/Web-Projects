#include<stdio.h>
#include<string.h>
#include "sstring.h"
#include<stdbool.h>

/*
sstring.c is a container for all functions for sstring variables :)

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

sstrfunc sstrappend(sstring _var1,sstring _var2){
	//dont store anything make null return value
	sstrfunc _null;
	
	//is global max char limit corrupted??
	//returning null means error was caught!
	if(isGMCLCorrupt()){
		return _null;
	}
	
	
	if(sstrlen(_var1)+sstrlen(_var2)>=GLOBAL_MAX_CHAR_LIMIT){
		return _null;
	}
	//use of string.h functions -> far easier than my previous headscratching!
	char _ret1[sstrlen(_var1)+sstrlen(_var2)];
	strcpy(_ret1,_var1);
	strcat(_ret1,_var2);
	sstrfunc _ret;
	strcpy(_ret._str,_ret1);
	return _ret;
}

sstrfunc sstrinput(){
	//dont store anything make null return value
	sstrfunc _null;
	//is global max char limit corrupted??
	//returning null means error was caught!
	if(isGMCLCorrupt()){
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
	_ret._str[strlen(_tmp)] = '\0';
	return _ret;
}

sstrfunc ssetchar(sstring _str,size_t _pos,char _ch){
	sstrfunc _null;
	//is global max char limit corrupted??
	//returning null means error was caught!
	if(isGMCLCorrupt()){
		return _null;
	}

	sstrfunc _ret;
	if(_pos>=sstrlen(_str)||_pos<0||sstrlen(_str)>=GLOBAL_MAX_CHAR_LIMIT){
		return _null;
	}
	strcpy(_ret._str,_str);
	_ret._str[_pos] = _ch;

	return _ret;
}

//if the length of string is in size_t
//and charachters in it can also be beyond int who knows!
size_t sstrfind(int init,sstring _str,sstring _find){
	size_t _len1 = sstrlen(_str);
	size_t _len2 = sstrlen(_find);
	size_t matching = 0;
	
	//is global max char limit corrupted??
	//returning null means error was caught!
	if(isGMCLCorrupt()){
		return -1;
	}
	
	//some wierd conditions check [user, are u fooling the function ?]
	if(_len2>_len1||init<0||init>_len1-1||_len2==0){
		return -1;
	}
	
	//security check
	if(_len1>=GLOBAL_MAX_CHAR_LIMIT||_len2>=GLOBAL_MAX_CHAR_LIMIT){
		return -1;
	}
	
	//the main finder
	for(int i=init;i<_len1+1;i++){
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



