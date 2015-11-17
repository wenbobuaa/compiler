#ifndef norw
#define norw	21	//保留字个数
#endif // norw

#ifndef txmax
#define txmax	100	//符号表的长度
#endif // txmax

#ifndef nmax
#define nmax	14	//数字的最大长度
#endif // nmax

#ifndef al
#define al	18	//标识符的最大长度
#endif // al

#ifndef lmax
#define lmax	81  //行缓冲区的最大长度
#endif // lmax

#ifndef strmax
#define strmax	100	//字符串最大长度
#endif // strmax

#ifndef SYMBOL
#define SYMBOL
    typedef enum SYMBOL_ { IDSY, ARRAYSY, BEGINSY, CASESY, CHARACTER, CONSTSY, DOSY, DOWNTO,
                    ELSESY, ENDSY, FORSY, FUNCSY, IFSY, INTEGER, OFSY, PROCSY, READSY, THENSY, TOSY,
                    VARSY, WRITESY, INTSY, CHARSY, STRSY, PLUSSY, MINUSSY, STARSY,DIVISY, LPASY, RPASY,
                    COLOSY, COMMASY, SEMISY, PERISY, BECOMESY, EQUSY, LESSSY, GREATSY,  LBRACSY, RBRACSY ,
                    UNEQUSY, LEQSY, GEQSY, nul} _SYMBOL;//单词类型助记符号
#endif // SYMBOL
