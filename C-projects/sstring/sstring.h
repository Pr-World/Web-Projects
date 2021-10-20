#ifndef SSTRING_H_DEFINED
#define SSTRING_H_DEFINED

//define the maximum char limit here
#define GLOBAL_MAX_CHAR_LIMIT 300

typedef char * sstring;

typedef struct{
	char _str[GLOBAL_MAX_CHAR_LIMIT];
}sstrfunc;

sstrfunc sstrappend(sstring _var1,sstring _var2);
sstrfunc sstrinput();
size_t sstrfind(int init,sstring _str,sstring _find);
size_t sstrlen(sstring _str);
sstrfunc ssetchar(sstring _str,size_t _pos,char _ch);

#endif
