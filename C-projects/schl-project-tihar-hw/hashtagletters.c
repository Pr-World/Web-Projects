#include <stdio.h>
#include "hashdata.h"

int PrettyCharPrint(char ch){
	return _HASH_CHAR_PRINT(ch);
}

int main(){
	char a;
	printf("Enter a charachter: ");
	scanf("%c",&a);
	printf("\n");
	PrettyCharPrint(a);
}