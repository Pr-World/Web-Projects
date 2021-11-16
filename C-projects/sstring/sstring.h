
#ifndef SSTRING_H_INCL
//stdbool for sstrnum typedef
#include<stdbool.h>
#include<stddef.h>
#define SSTRING_H_INCL

#define _SSTRING_GLOBAL_MAX_CHAR_LIMIT 500

#define _SSTRING_NO_ERR -80
#define _SSTRING_GMCL_CORRUPT -81
#define _SSTRING_INVALID_ARGS -82
#define _SSTRING_GMCL_ERR -83
#define _SSTRING_EOF_ERR -84

typedef char * sstrinp;
typedef const char * sstrinpc;
typedef int _SSTRING_ERRTYPE;

typedef struct{
	double _num;
	bool is_num;
	_SSTRING_ERRTYPE _err;
}sstrnum;

typedef struct{
	char _str[_SSTRING_GLOBAL_MAX_CHAR_LIMIT];
	_SSTRING_ERRTYPE _err;
}sstrfunc;

typedef struct{
	char _char;
	_SSTRING_ERRTYPE _err;
}charfunc;

//sstr initial things
struct sstr{
	//initial things
	sstrinp val;
	int _err;
};



//declaration of all member functions
//declare the to-be-used function not original one!
extern const struct sstrClass{
	//member functions!!
	struct sstr (*init)(void);
	struct sstr (*newstr)(sstrinp _Str);
	struct sstr (*assign)(sstrinp sa);
	size_t (*len)(struct sstr _str);
	struct sstr (*convC2S)(sstrinp _Buff);
	_SSTRING_ERRTYPE (*convS2C)(struct sstr _str,sstrinp _Cstr,size_t _upto);
	sstrnum (*tonum)(struct sstr _sstr);
	struct sstr (*substr)(struct sstr _sstr,int _pos,size_t _len);
	struct sstr (*append)(struct sstr _svar1,sstrinpc _var2);
	struct sstr (*getinput)(void);
	struct sstr (*getinputpass)(sstrinp show);
	struct sstr (*setchar)(struct sstr _sstr,ssize_t _pos,char _ch);
	void (*showerrs)(_SSTRING_ERRTYPE _err);
	charfunc (*getchar)(struct sstr _sstr,ssize_t _pos);
	ssize_t (*find)(size_t init,struct sstr _sstr,sstrinp _find);
	struct sstr (*replace)(struct sstr _sStr, sstrinp _find, sstrinp _repl);
	struct sstr (*refresh)(struct sstr a);
	sstrinp (*val)(struct sstr a);
} sstr;

typedef sstrfunc sstrfuncerr;
typedef struct sstr sstring;

#endif
