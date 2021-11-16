#include<stdio.h>
#include<string.h>
#include "sstring.h"
#include<stdbool.h>
#include<stdlib.h>
#include<math.h>
#include<conio.h>
#include<stddef.h>

/*
A Big Note To the ones saying dont return Local Variable Adresses

Below functions dont return any local variable addresses
to prove it, call the functions MULTIPLE times  -> you will see yourself

They return a typedef of strfunc which contains the string in array format
when the user does [functionname]([parameters])._str; the str array value is sent to the pointer
so no issue will be created! :D

*/


size_t _SSTRING_SSTRLEN(struct sstr _str){
	//just as support for struct sstrs
	//same as strlen!
	return strlen(_str.val);
}

bool _SSTRING_isGMCLCorrupt(void){
	//checks if global max char limit is corrupted
	if(_SSTRING_GLOBAL_MAX_CHAR_LIMIT<=0){
		return true;
	}else{
		return false;
	}
}

_SSTRING_ERRTYPE nullify(sstrinp _Buff,int _count){
	if(_SSTRING_isGMCLCorrupt()){
		return _SSTRING_GMCL_CORRUPT;		
	}else if(_count>_SSTRING_GLOBAL_MAX_CHAR_LIMIT+1){
		return _SSTRING_GMCL_ERR;
	}else{
		for(int i=0;i<_count;i++){
			_Buff[i] = '\0';
		}
		return _SSTRING_NO_ERR;
	}
}

struct sstr _SSTRING_CSTR_2_SSTR(sstrinp _Buff){
	sstrfunc _null;
	_null._err = _SSTRING_NO_ERR;
	if(_SSTRING_isGMCLCorrupt()){
		_null._err = _SSTRING_GMCL_ERR;
		return (struct sstr){.val="",._err=_null._err};
	}
	if(strlen(_Buff)>=_SSTRING_GLOBAL_MAX_CHAR_LIMIT){
		_null._err = _SSTRING_GMCL_ERR;
		return (struct sstr){.val="",._err =_null._err};
	}
	return(struct sstr){.val=_Buff,._err=_SSTRING_NO_ERR};
}

_SSTRING_ERRTYPE _SSTRING_SSTR_2_CSTR(struct sstr _str,sstrinp _Cstr,size_t _upto){
	
	//first null out the _Cstr upto given length
	nullify(_Cstr,_upto);
	
	sstrinp _sstr = _str.val;
	
	if(_SSTRING_isGMCLCorrupt()){
		return _SSTRING_GMCL_CORRUPT;
	}
	if(strlen(_sstr)>=_SSTRING_GLOBAL_MAX_CHAR_LIMIT){
		return _SSTRING_GMCL_ERR;
	}
	
	//blank string
	if(strlen(_sstr)==0){
		return _SSTRING_NO_ERR;
	}
	
	strncpy(_Cstr,_sstr,_upto);
	return _SSTRING_NO_ERR;
}

sstrnum _SSTRING_SSTR_2_NUM(struct sstr _sstr){
	sstrinp _str = _sstr.val;
	char cchar;
	int minus = 1;
	int plus=0;
	sstrnum _return;
	int pointplace=0;
	_return._err = _SSTRING_NO_ERR;
	_return.is_num = true;
	if(_SSTRING_isGMCLCorrupt()){
		_return._err = _SSTRING_GMCL_CORRUPT;
		_return._num = 0;
		_return.is_num = false;
		return _return;
	}else if(strlen(_str)>=_SSTRING_GLOBAL_MAX_CHAR_LIMIT){
		_return._err = _SSTRING_GMCL_ERR;
		_return._num = 0;
		_return.is_num = false;
		return _return;
	}
	for(size_t i=0;i<strlen(_str);i++){
		cchar = _str[i];
		//if non integer found
		if(cchar<'0'||cchar>'9'){
			if(cchar=='-'&&i==0){
				minus = -1;
			}else if(cchar=='-'&&i>0){
				_return._num = 0;
				_return.is_num = false;
				_return._err = _SSTRING_NO_ERR;
				return _return;
			}else if(cchar=='.'&&pointplace==0){
				pointplace+=1;
			}else if(cchar=='.'&&!(pointplace==0)){
				_return._num = 0;
				_return.is_num = false;
				_return._err = _SSTRING_NO_ERR;
				return _return;
			}else if(cchar=='+'&&plus==0){
				plus=1;
			}else if(cchar=='+'&&plus==1){
				_return._num = 0;
				_return.is_num = false;
				_return._err = _SSTRING_NO_ERR;
				return _return;
			}else{
				_return._num = 0;
				_return.is_num = false;
				_return._err = _SSTRING_NO_ERR;
				return _return;
			}
		}else{
			//if integer
			
			//if position is '0'
			if(i==0){
				_return._num = cchar-'0';
				
			//if position not '0'
			}else{
				if(pointplace){
					_return._num+= (cchar-'0')/pow(10,pointplace);
					pointplace+=1;
				}else{
					_return._num*=10;
					_return._num+= (cchar-'0');
				}
			}
		}
	}
	_return._num*=minus;
	return _return;
	
}

struct sstr _SSTRING_SUBSTR(struct sstr _sstr,int _pos,size_t _len){
	//dont store anything make null return value
	sstrfunc _null;
	sstrinp _str = _sstr.val;
	
	//is global max char limit corrupted??
	//returning null means error was caught!
	if(_SSTRING_isGMCLCorrupt()){
		//gmcl is corrupt! errcode: #defined in struct sstr.h
		_null._err = _SSTRING_GMCL_CORRUPT;
		return (struct sstr){.val="",._err =_null._err};
	}
	if(_pos<0){
		_null._err = _SSTRING_INVALID_ARGS;
		return (struct sstr){.val="",._err =_null._err};
	}
	if(strlen(_str)>=_SSTRING_GLOBAL_MAX_CHAR_LIMIT||_pos>=_SSTRING_GLOBAL_MAX_CHAR_LIMIT||_len>=_SSTRING_GLOBAL_MAX_CHAR_LIMIT){
		_null._err = _SSTRING_GMCL_ERR;
		return (struct sstr){.val="",._err =_null._err};
	}
	
	if(_pos>=strlen(_str)||_pos<0||_len>=strlen(_str)||_len<0){
		_null._err = _SSTRING_INVALID_ARGS;
		return (struct sstr){.val="",._err =_null._err};
	}
	
	sstrfunc _ret;
	
	_ret._err = _SSTRING_NO_ERR;
	strncpy(_ret._str,_str+_pos,_len);
	_ret._str[_len] = '\0';
	return (struct sstr){.val=_ret._str,._err =_ret._err};
	
}

struct sstr _SSTRING_STRAPPEND(struct sstr _svar1,sstrinpc _var2){
	//dont store anything make null return value
	sstrfunc _null;
	sstrinp _var1 = _svar1.val;
	
	//is global max char limit corrupted??
	//returning null means error was caught!
	if(_SSTRING_isGMCLCorrupt()){
		//gmcl is corrupt! errcode: #defined in struct sstr.h
		_null._err = _SSTRING_GMCL_CORRUPT;
		return (struct sstr){.val="",._err =_null._err};
	}
	
	
	if(strlen(_var1)+strlen(_var2)>=_SSTRING_GLOBAL_MAX_CHAR_LIMIT){
		_null._err = _SSTRING_GMCL_ERR;
		return (struct sstr){.val="",._err =_null._err};
	}
	//use of string.h functions -> far easier than my previous headscratching!
	char _ret1[strlen(_var1)+strlen(_var2)];
	strcpy(_ret1,_var1);
	strcat(_ret1,_var2);
	sstrfunc _ret;
	//no errors :D
	_ret._err = _SSTRING_NO_ERR;
	return (struct sstr){.val=_ret1,._err =_ret._err};
}



struct sstr _SSTRING_STRINP(void){
	//dont store anything make null return value
	sstrfunc _null;
	//is global max char limit corrupted??
	//returning null means error was caught!
	if(_SSTRING_isGMCLCorrupt()){
		_null._err = _SSTRING_GMCL_CORRUPT;
		return (struct sstr){.val="",._err =_null._err};
	}
	char _tmp[_SSTRING_GLOBAL_MAX_CHAR_LIMIT];
	/*
	First, if i use fgets(_tmp,SSTRING_GLOBAL_MAX_CHAR_LIMIT,stdin) and limit it to gmcl,
	if the program is suppose inputting directory and filename and the path is greater
	than gmcl, the program will be in undefined behaviour if the rest code tries to open the file! because only
	string upto gmcl has been stored. and there are no errors when checking. to solve this :-
	created a bugcheck variable having greater space than gmcl i.e gmcl+1
	input into the variable limit it to gmcl+1
	check if its length exceeds or is equal to gmcl [i.e the extra byte is occupied]
	if yes: return gmcl_error immediately and terminate further process in the function -> now user will recieve error!
	if not, copy the input into tmp and execute rest of the code!

	*/
	char _bugcheck[_SSTRING_GLOBAL_MAX_CHAR_LIMIT+1];
	char * tmpchk;
	
	tmpchk=fgets(_bugcheck,_SSTRING_GLOBAL_MAX_CHAR_LIMIT+1,stdin);
	
	if(tmpchk==NULL){
		return (struct sstr){.val="",._err=_SSTRING_EOF_ERR};
	}
	
	
	if(strlen(_bugcheck)>=_SSTRING_GLOBAL_MAX_CHAR_LIMIT){
		_null._err = _SSTRING_GMCL_ERR;
		return (struct sstr){.val="",._err =_null._err};
	}
	
	strncpy(_tmp,_bugcheck,_SSTRING_GLOBAL_MAX_CHAR_LIMIT);
	
	sstrfunc _ret;
	//ret._str is array upto GLOBAL_MAX_CHAR_LIMIT
	//also tmp is array upto GLOBAL_MAX_CHAR_LIMIT
	//so its safe :) to use strcpy same as strncpy
	strcpy(_ret._str,_tmp);
	//'\n' avoided
	_ret._str[strlen(_tmp)-1] = '\0';
	_ret._err = _SSTRING_NO_ERR;
	return (struct sstr){.val=_ret._str,._err=_ret._err};
}

struct sstr _SSTRING_STRINP_PASS(sstrinp show){
	//dont store anything make null return value
	sstrfunc _null;
	//is global max char limit corrupted??
	//returning null means error was caught!
	if(_SSTRING_isGMCLCorrupt()){
		_null._err = _SSTRING_GMCL_CORRUPT;
		return (struct sstr){.val="",._err =_null._err};
	}
	char _tmp[_SSTRING_GLOBAL_MAX_CHAR_LIMIT];
	//nullify string [if i dont use this WiErD things happen]
	int check_for_err;
	check_for_err = nullify(_tmp,_SSTRING_GLOBAL_MAX_CHAR_LIMIT+1);
	if(check_for_err!=_SSTRING_NO_ERR)
	{
		_null._err = _SSTRING_NO_ERR;
		return (struct sstr){.val="",._err =_null._err};
	}
	char tmpchar;
	bool takeinput = true;
	int done=0;
	//until a certain char has not been pressed
	while(1>0){
		//if exceeds or proceeds to exceed global max char limit
		if(done>=_SSTRING_GLOBAL_MAX_CHAR_LIMIT-1){
			takeinput=false;
		}
		tmpchar = getch();
		//if user pressed enter
		if(tmpchar=='\r'||tmpchar=='\n'){
			//if we were taking input
			if(takeinput){break;} else {
				//if takeinput was false return error when user presses enter!
				_null._err = _SSTRING_GMCL_ERR;
				return (struct sstr){.val="",._err =_null._err};
			}
		}
		//if takeinput is true
		if(takeinput){
			if(tmpchar=='\b'){
				if(strlen(_tmp)>0){
					_tmp[strlen(_tmp)-1] = '\0';
					for(size_t i=0;i<strlen(show);i++){
						printf("\b");
					}
					for(size_t i=0;i<strlen(show);i++){
						printf(" ");
					}
					for(size_t i=0;i<strlen(show);i++){
						printf("\b");
					}
				}
			}else{
				_tmp[strlen(_tmp)]=tmpchar;
				printf(show);
			done+=1;
			}
		//if its false, just print out the show and rub it but dont do anything with _tmp variable!
		//as we will return error when 'enter' is pressed
		}else{
			if(tmpchar=='\b'){
				if(strlen(_tmp)>0){
					for(size_t i=0;i<strlen(show);i++){
						printf("\b");
					}
					for(size_t i=0;i<strlen(show);i++){
						printf(" ");
					}
					for(size_t i=0;i<strlen(show);i++){
						printf("\b");
					}
				}
			}else{
				printf(show);
			}
		}
		
	}
	//print newline buffer
	printf("\n");
	
	sstrfunc _ret;
	//ret._str is array upto GLOBAL_MAX_CHAR_LIMIT
	//also tmp is array upto GLOBAL_MAX_CHAR_LIMIT
	//so its safe :) to use strcpy same as strncpy
	strcpy(_ret._str,_tmp);
	//no errors
	_ret._err = _SSTRING_NO_ERR;
	return (struct sstr){.val=_ret._str,._err =_ret._err};
}

struct sstr _SSTRING_SETCHAR(struct sstr _sstr,ssize_t _pos,char _ch){
	sstrfunc _null;
	sstrinp _str = _sstr.val;
	//is global max char limit corrupted??
	//returning null means error was caught!
	if(_SSTRING_isGMCLCorrupt()){
		_null._err = _SSTRING_GMCL_CORRUPT;
		return (struct sstr){.val="",._err =_null._err};
	}

	sstrfunc _ret;
	if(strlen(_str)>=_SSTRING_GLOBAL_MAX_CHAR_LIMIT){
		_null._err = _SSTRING_GMCL_ERR;
		return (struct sstr){.val="",._err =_null._err};
	}
	if(_pos>=strlen(_str)||_pos<0){
		_null._err = _SSTRING_INVALID_ARGS;
		return (struct sstr){.val="",._err =_null._err};
	}
	strcpy(_ret._str,_str);
	_ret._str[_pos] = _ch;
	_ret._err = _SSTRING_NO_ERR;

	return (struct sstr){.val=_ret._str,._err =_ret._err};
}

void _SSTRING_SHOW_ERRS(_SSTRING_ERRTYPE _err){
	
	if(_err==_SSTRING_GMCL_CORRUPT){
		printf("\nError: SSTRING_GMCL_CORRUPT, _SSTRING_GLOBAL_MAX_CHAR_LIMIT #defined in file 'struct sstr.h' is corrupted!\n");
	}else if(_err==_SSTRING_GMCL_ERR){
		printf("\nError: _SSTRING_GMCL_ERR, provided variable or input comes close or exceeds SSTRING_GLOBAL_MAX_CHAR_LIMIT!\n");
	}else if(_err==_SSTRING_EOF_ERR){
		printf("\nError: _SSTRING_EOF_ERR, End Of File occured without inputting any charachter!\n");
	}else if(_err==_SSTRING_INVALID_ARGS){
		printf("\nError: _SSTRING_INVALID_ARGS, you provided invalid arguments to a function inside file 'struct sstr.c'!\n");
	}else{
		printf("\nError: Unknown Error, an unknown error occured! errcode: %d\n",_err);
	}
	
}


charfunc _SSTRING_GETCHAR(struct sstr _sstr,ssize_t _pos){
	charfunc _null;
	sstrinp _str = _sstr.val;
	//is global max char limit corrupted??
	if(_SSTRING_isGMCLCorrupt()){
		_null._err = _SSTRING_GMCL_CORRUPT;
		return _null;
	}
	// condition checking which are likely make error after
	if(strlen(_str)>=_SSTRING_GLOBAL_MAX_CHAR_LIMIT){
		_null._err = _SSTRING_GMCL_ERR;
		return _null;
	}
	
	if(_pos>=strlen(_str)||_pos<0||strlen(_str)<0){
		_null._err = _SSTRING_INVALID_ARGS;
		return _null;
	}	
	charfunc chr;
	chr._char = _str[_pos];
	chr._err = _SSTRING_NO_ERR;
	return chr;
}

//if the length of string is in size_t
//and charachters in it can also be beyond int who knows!
//used ssize_t to support returning negative numbers, i.e -> -1 and errors

//init is the place to start finding
ssize_t _SSTRING_STRFIND(size_t init,struct sstr _sstr,sstrinp _find){
	sstrinp _str = _sstr.val;
	size_t _len1 = strlen(_str);
	size_t _len2 = strlen(_find);
	size_t matching = 0;
	
	
	
	//is global max char limit corrupted??
	if(_SSTRING_isGMCLCorrupt()){
		return _SSTRING_GMCL_CORRUPT;
	}
	
	if(strlen(_str)>=_SSTRING_GLOBAL_MAX_CHAR_LIMIT||strlen(_find)>=_SSTRING_GLOBAL_MAX_CHAR_LIMIT){
		return _SSTRING_GMCL_ERR;
	}
	
	//some weird conditions check [user, are u fooling the function ?]
	if(_len2>_len1||init<0||init>_len1-1){
		return _SSTRING_INVALID_ARGS;
	}
	
	//security check
	if(_len1>=_SSTRING_GLOBAL_MAX_CHAR_LIMIT||_len2>=_SSTRING_GLOBAL_MAX_CHAR_LIMIT){
		return _SSTRING_GMCL_ERR;
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

struct sstr _SSTRING_STRREPLACE(struct sstr _sStr, sstrinp _find, sstrinp _repl)
{
	sstrinp _Str = _sStr.val;
	
	size_t lens = strlen(_Str);
	size_t lenf = strlen(_find);
	size_t lenr = strlen(_repl);
	
	
	
	sstrfunc _null,_ret;
	int tmp;
	
	nullify(_null._str,_SSTRING_GLOBAL_MAX_CHAR_LIMIT+1);
	nullify(_ret._str,_SSTRING_GLOBAL_MAX_CHAR_LIMIT+1);
	
	bool _rarecondition = false;
	
	//a rare condition where wierd thing happens - found by myself when length is perfectly divisible by 16
	//this fixes it by appending 1 char to it which is not the find string.
	//at last it removes 1 charachter from last as it is appended here
	if(lens%16==0){
		if(strlen(_Str)+1>=_SSTRING_GLOBAL_MAX_CHAR_LIMIT){
			_null._err =  _SSTRING_GMCL_ERR;
			return (struct sstr){.val="",._err =_null._err};
		}
		if(_find!=" "){
			_Str = _SSTRING_STRAPPEND(_sStr," ").val;
		}else{
			_Str = _SSTRING_STRAPPEND(_sStr,"~").val;
		}
		_rarecondition = true;
	}

	sstrinp tmp_check;
	
	tmp_check = _SSTRING_STRAPPEND(_sStr,"").val;

	if(_SSTRING_isGMCLCorrupt()){
		_null._err = _SSTRING_GMCL_CORRUPT;
		return (struct sstr){.val="",._err =_null._err};
	}
	
	if(lens>=_SSTRING_GLOBAL_MAX_CHAR_LIMIT||lenf>=_SSTRING_GLOBAL_MAX_CHAR_LIMIT||lenr>=_SSTRING_GLOBAL_MAX_CHAR_LIMIT){
		_null._err = _SSTRING_GMCL_ERR;
		return (struct sstr){.val="",._err =_null._err};
	}
	
	if(lens<=0||lenf<=0){
		_null._err = _SSTRING_INVALID_ARGS;
		return (struct sstr){.val="",._err =_null._err};
	}
	
	sstrinp _Str2 = tmp_check;
	sstrinp tmps1,tmps2,tmps3;
	size_t tmpint1,tmpint2=0;
	
	for(tmpint1=0;_Str2[tmpint1]!='\0';tmpint1++){
		if(strstr(&_Str2[tmpint1],_find)==&_Str2[tmpint1]){
			tmpint2++;
			tmpint1+=lenf-1;
		}
	}
	
	//check if after replacing of strings or between replacing
	//the length exceeds SSTRING_GLOBAL_MAX_CHAR_LIMIT or not!
	if(lens-(lenf*tmpint2)+(lenr*tmpint2)>=_SSTRING_GLOBAL_MAX_CHAR_LIMIT){
		_null._err = _SSTRING_GMCL_ERR;
		return (struct sstr){.val="",._err =_null._err};
	}
	
	//the below code has been blindly done because all errors are checked beforehand
	tmpint1 = 0;
	while(*_Str2){
		if(strstr(_Str2,_find)==_Str2){
			//except strncpy() is used to stop buffer overflow
			strncpy(_ret._str+tmpint1,_repl,_SSTRING_GLOBAL_MAX_CHAR_LIMIT);
			tmpint1+=lenr;
			_Str2+=lenf;
		}else{
			_ret._str[tmpint1++] = *_Str2++;
		}
	}
	if(_rarecondition==true){
		_ret._str[tmpint1-1] = '\0';
	}
	_ret._str[tmpint1] = '\0';
	_ret._err = _SSTRING_NO_ERR;
	return (struct sstr){.val=_ret._str,._err =_ret._err};
}
sstrinp _SSTRING_STRVAL(struct sstr a){
	return a.val;
}

struct sstr _SSTRING_ASSIGN(sstrinp a){
	_SSTRING_ERRTYPE _err=_SSTRING_NO_ERR;
	if(strlen(a)>=_SSTRING_GLOBAL_MAX_CHAR_LIMIT){
		a = "";_err=_SSTRING_GMCL_ERR;
	}
	return (sstring){.val=a,._err=_err};
}

struct sstr _SSTRING_REFRESH_STR(struct sstr a){
	_SSTRING_ERRTYPE _err=_SSTRING_NO_ERR;
	if(_SSTRING_isGMCLCorrupt()){
		_err=_SSTRING_GMCL_CORRUPT;
	}else if(strlen(a.val)>=_SSTRING_GLOBAL_MAX_CHAR_LIMIT){
		_err = _SSTRING_GMCL_ERR;
	}
	
	return (struct sstr){
		//initial values
		.val=a.val,
		._err = _err
	};
}

struct sstr _SSTRING_SSTR_MAIN_INIT(void){
	struct sstr a;
	_SSTRING_ERRTYPE _err=_SSTRING_NO_ERR;
	if(_SSTRING_isGMCLCorrupt()){
		_err=_SSTRING_GMCL_CORRUPT;
	}
	return (struct sstr){
		//initial values
		.val="",
		._err = _err,
	};
}

struct sstr _SSTRING_NEWSTR(sstrinp _Str){
	struct sstr a;
	int _err=_SSTRING_NO_ERR;
	if(strlen(_Str)>=_SSTRING_GLOBAL_MAX_CHAR_LIMIT){
		_Str = "";
		_err = _SSTRING_GMCL_ERR;
	}else if(_SSTRING_isGMCLCorrupt()){
		_Str = "";
		_err = _SSTRING_GMCL_CORRUPT;
	}
	return (struct sstr){
		//initial values
		.val=_Str,
		._err = _err,
	};
}



//add to respective function
const struct sstrClass sstr={
.newstr=&_SSTRING_NEWSTR,
.init=&_SSTRING_SSTR_MAIN_INIT,
.assign=&_SSTRING_ASSIGN,
.len=&_SSTRING_SSTRLEN,
.convC2S=&_SSTRING_CSTR_2_SSTR,
.convS2C=&_SSTRING_SSTR_2_CSTR,
.tonum=&_SSTRING_SSTR_2_NUM,
.substr=&_SSTRING_SUBSTR,
.append=&_SSTRING_STRAPPEND,
.getinput=&_SSTRING_STRINP,
.getinputpass=&_SSTRING_STRINP_PASS,
.setchar=&_SSTRING_SETCHAR,
.showerrs=&_SSTRING_SHOW_ERRS,
.getchar=&_SSTRING_GETCHAR,
.setchar=&_SSTRING_SETCHAR,
.find=&_SSTRING_STRFIND,
.replace=&_SSTRING_STRREPLACE,
.refresh=&_SSTRING_REFRESH_STR,
.val=&_SSTRING_STRVAL
};

//make sstring easy to use!
typedef struct sstr sstring;
