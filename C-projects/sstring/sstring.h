#ifndef SSTRING_H_DEFINED
#define SSTRING_H_DEFINED

//define the maximum char limit here
#define GLOBAL_MAX_CHAR_LIMIT 400

#define NO_ERR 0
#define GMCL_CORRUPT -10
#define INVALID_ARGS -11
#define GMCL_ERR -12

typedef char * sstring;

typedef struct{
	char _str[GLOBAL_MAX_CHAR_LIMIT];
	int _err;
}sstrfunc;

typedef struct{
	char _char;
	int _err;
}charfunc;

typedef sstrfunc sstrfuncerr;

sstrfunc sstrappend(sstring _var1,sstring _var2);
sstrfunc sstrinput();
ssize_t sstrfind(size_t init,sstring _str,sstring _find);
size_t sstrlen(sstring _str);
sstrfunc ssetchar(sstring _str,ssize_t _pos,char _ch);
sstrfunc ssubstr(sstring _str,ssize_t _pos,size_t _len);
sstrfunc sstrreplace(sstring _str,sstring _find,sstring _repl);
charfunc sgetchar(sstring _str,ssize_t _pos);
void showerrs();

#endif