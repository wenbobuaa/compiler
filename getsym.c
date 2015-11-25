#include "variable.h"
#include "function.h"

void getsym(){
	//词法分析程序
	getChar();
	while(isSpace() || isNewline() || isTab()){
		getChar();
	}
	if(isLetter()){
		while(isLetter() || isDigit()){
			catToken();
			getChar();
		}
		clearToken();
		retract();
		symbol = reserver();
	}else if(isDigit()){
		while(isDigit()){
			catToken();
			getChar();
		}
		clearToken();
		retract();
		num = transNum();
		symbol = INTSY;
	}else if(isColon()){
		catToken();
		getChar();
		if(isEqu()){
			catToken();
			clearToken();
			symbol = BECOMESY;
		}else{
			retract();
			clearToken();
			symbol = COLOSY;
		}
	}else if(isComma()){
		symbol = COMMASY;
	}else if(isSemi()){
		symbol = SEMISY;
	}else if(isPeri()){
        symbol = PERISY;
	}else if(isSquot()){
		getChar();
		if(isLetter() || isDigit()){
			cha = ch;
			getChar();
			if(isSquot()){
				symbol = CHARSY;
			}else{
				error(1);
			}
		}else{
			error(0);
		}
	}else if(isDquot()){
		getChar();
		while(isChar()){
			catString();
			getChar();
		}
		if(isDquot()){
			clearString();
			symbol = STRSY;
		}else{
			error(2);
		}
	}else if(isLbrac()){
		symbol = LBRACSY;
	}else if(isRbrac()){
		symbol = RBRACSY;
	}else if(isEqu()){
		symbol = EQUSY;
	}else if(isLess()){
		catToken();
		getChar();
		if(isEqu()){
			catToken();
			clearToken();
			symbol = LEQSY;
		}else if(isGreat()){
			catToken();
			clearToken();
			symbol = UNEQUSY;
		}else{
			retract();
			clearToken();
			symbol = LESSSY;
		}
	}else if(isGreat()){
		catToken();
		getChar();
		if(isEqu()){
			catToken();
			clearToken();
			symbol = GEQSY;
		}else{
			retract();
			clearToken();
			symbol = GREATSY;
		}
	}else if(isPlus()){
		symbol = PLUSSY;
	}else if(isMinus()){
		symbol = MINUSSY;
	}else if(isStar()){
		symbol = STARSY;
	}else if(isDivi()){
		symbol = DIVISY;
	}else if(isLpar()){
		symbol = LPASY;
	}else if(isRpar()){
		symbol = RPASY;
	}else if(isEnd()){
		symbol = nul;
	}else{
		error(3);
	}
}
