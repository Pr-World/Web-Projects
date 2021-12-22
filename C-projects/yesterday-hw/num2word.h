#ifndef _NUMTOWORD_H_INCL
#define _NUMTOWORD_H_INCL

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <conio.h>

int NumLen(int _Num){
	int a=_Num,i=1;
	if(a<0){
		return 0;
	}
	while(1){
		a/=10;
		if(a==0){
			return i;
		}
		i++;
	}
}

int GetDigit(int _Num,int _place){
	if(_place>NumLen(_Num)){
		return 0;
	}
	if(_place==NumLen(_Num)){
		return _Num%10;
	}
	int a=_Num,b;
	for(int i=NumLen(_Num)-1;i>=0;i--){
		if(i==_place){
			return a%10;
		}
		a/=10;
	}
}

int ToVal(int _num){
	int i,c=0;
	for(i=0;i<_num+10;i+=10){
		
		c++;
		if(_num==i){
			return (_num-9*(c-3));
		}
	}
}

int Num2Word(int _num){
	const char * _NUMWORDS[28];
	const char * _PLACEVAL[6];
	int i,tmp,tmp2,tmp3;
		
	_PLACEVAL[0] = "Hundred";
	_PLACEVAL[1] = "Thousand";
	_PLACEVAL[2] = "Lakh";
	_PLACEVAL[3] = "Crore";
	_PLACEVAL[4] = "Arab";
	_PLACEVAL[5] = "Kharab";
	
	_NUMWORDS[0] = "Zero";	
	_NUMWORDS[1] = "One";	
	_NUMWORDS[2] = "Two";	
	_NUMWORDS[3] = "Three";	
	_NUMWORDS[4] = "Four";	
	_NUMWORDS[5] = "Five";	
	_NUMWORDS[6] = "Six";	
	_NUMWORDS[7] = "Seven";	
	_NUMWORDS[8] = "Eight";	
	_NUMWORDS[9] = "Nine";	
	_NUMWORDS[10] = "Ten";	
	_NUMWORDS[11] = "Eleven";	
	_NUMWORDS[12] = "Twelve";	
	_NUMWORDS[13] = "Thirteen";	
	_NUMWORDS[14] = "Fourteen";	
	_NUMWORDS[15] = "Fifteen";	
	_NUMWORDS[16] = "Sixteen";	
	_NUMWORDS[17] = "Seventeen";	
	_NUMWORDS[18] = "Eighteen";	
	_NUMWORDS[19] = "Nineteen";	
	_NUMWORDS[20] = "Twenty";	
	_NUMWORDS[21] = "Thirty";	
	_NUMWORDS[22] = "Fourty";	
	_NUMWORDS[23] = "Fifty";	
	_NUMWORDS[24] = "Sixty";	
	_NUMWORDS[25] = "Seventy";	
	_NUMWORDS[26] = "Eighty";	
	_NUMWORDS[27] = "Ninety";	
	
	
	if(NumLen(_num)==1){
		if(_num!=0){
			printf("%s",_NUMWORDS[_num]);
			return 1;	
		}
	}
	
	if(NumLen(_num)==2){
		if(GetDigit(_num,0)<2){
			printf("%s",_NUMWORDS[_num]);
		}else if(GetDigit(_num,1)!=0){
			tmp = GetDigit(_num,0);
			printf("%s %s",_NUMWORDS[ToVal(tmp*10)],_NUMWORDS[GetDigit(_num,1)]);			
		}else{
			tmp = GetDigit(_num,0);
			printf("%s",_NUMWORDS[ToVal(tmp*10)]);
		}
		return 1;
	}
	
	if(NumLen(_num)==3){
		tmp = GetDigit(_num,0);
		tmp2 = GetDigit(_num,1)*10+GetDigit(_num,2);
		printf("%s %s ",_NUMWORDS[tmp],_PLACEVAL[0]);
		Num2Word(tmp2);
	}
	
	if(NumLen(_num)==4){
		tmp = GetDigit(_num,0);
		tmp2 = GetDigit(_num,1)*100+GetDigit(_num,2)*10+GetDigit(_num,3);
		printf("%s %s ",_NUMWORDS[tmp],_PLACEVAL[1]);
		Num2Word(tmp2);
	}
	
	if(NumLen(_num)==5){
		tmp = GetDigit(_num,0);
		tmp2 = GetDigit(_num,2)*100+GetDigit(_num,3)*10+GetDigit(_num,4);
		if(GetDigit(_num,1)>2){
			printf("%s %s %s ",_NUMWORDS[ToVal(tmp*10)],_NUMWORDS[GetDigit(_num,1)],_PLACEVAL[1]);
		}else if(GetDigit(_num,1)==0){
			printf("%s %s ",_NUMWORDS[ToVal(tmp*10)],_PLACEVAL[1]);
		}else{
			printf("%s %s ",_NUMWORDS[tmp*10+GetDigit(_num,1)],_PLACEVAL[1]);
		}
		
		Num2Word(tmp2);
	}
	
	if(NumLen(_num)==6){
		tmp = GetDigit(_num,0);
		tmp2 = GetDigit(_num,1)*10000+GetDigit(_num,2)*1000+GetDigit(_num,3)*100+GetDigit(_num,4)*10+GetDigit(_num,5);
		printf("%s %s ",_NUMWORDS[tmp],_PLACEVAL[2]);
		Num2Word(tmp2);
	}
	
	if(NumLen(_num)==7){
		tmp = GetDigit(_num,0);
		tmp2 = GetDigit(_num,2)*10000+GetDigit(_num,3)*1000+GetDigit(_num,4)*100+GetDigit(_num,5)*10+GetDigit(_num,6);
		if(GetDigit(_num,1)>2){
			printf("%s %s %s ",_NUMWORDS[ToVal(tmp*10)],_NUMWORDS[GetDigit(_num,1)],_PLACEVAL[2]);
		}else if(GetDigit(_num,1)==0){
			printf("%s %s ",_NUMWORDS[ToVal(tmp*10)],_PLACEVAL[2]);
		}else{
			printf("%s %s ",_NUMWORDS[tmp*10+GetDigit(_num,1)],_PLACEVAL[2]);
		}
		Num2Word(tmp2);
	}
	
	if(NumLen(_num)==8){
		tmp = GetDigit(_num,0);
		
		tmp2 = GetDigit(_num,1)*1000000+GetDigit(_num,2)*100000+GetDigit(_num,3)*10000
		+GetDigit(_num,4)*1000+GetDigit(_num,5)*100+GetDigit(_num,6)*10+GetDigit(_num,7);
		
		printf("%s %s ",_NUMWORDS[tmp],_PLACEVAL[3]);
		Num2Word(tmp2);
	}
	
	if(NumLen(_num)==9){
		
		tmp = GetDigit(_num,0);
		
		tmp2 = GetDigit(_num,2)*1000000+GetDigit(_num,3)*100000+GetDigit(_num,4)*10000
		+GetDigit(_num,5)*1000+GetDigit(_num,6)*100+GetDigit(_num,7)*10+GetDigit(_num,8);
		
		printf("\n %d",tmp2);
		
		if(GetDigit(_num,1)>2){
			printf("%s %s %s ",_NUMWORDS[ToVal(tmp*10)],_NUMWORDS[GetDigit(_num,1)],_PLACEVAL[3]);
		}else if(GetDigit(_num,1)==0){
			printf("%s %s ",_NUMWORDS[ToVal(tmp*10)],_PLACEVAL[3]);
		}else{
			printf("%s %s ",_NUMWORDS[tmp*10+GetDigit(_num,1)],_PLACEVAL[3]);
		}
		Num2Word(tmp2);
		
	}
	
}

#endif
