#include "function.h"
#include "variable.h"

void grammar(){
	getsym();
	procedure();
}

void procedure(){
	symNeed[PERISY] = 1;
	subPro();
	symNeed[PERISY] = 0;
	if(isPeri()){
		printf("finished.\n");
	}else{
		error();
		printf("need peri.");
	}
	#ifdef DEBUG
		printf("This is a procedure.\n");
	#endif
}

void subPro(){
	if(symbol == CONSTSY){//常量说明部分
		symNeed[VARSY] = 1;
		symNeed[PROCSY] = 1;
		symNeed[FUNCSY] = 1;
		symNeed[BEGINSY] = 1;

		getsym();

		symNeed[COMMASY] = 1;
		symNeed[SEMISY] = 1;
		constDef();
		symNeed[COMMASY] = 0;
		symNeed[SEMISY] = 0;

		while(symbol == COMMASY){
			getsym();

			symNeed[COMMASY] = 1;
			symNeed[SEMISY] = 1;
			constDef();
			symNeed[COMMASY] = 0;
			symNeed[SEMISY] = 0;
		}

		if(symbol == SEMISY){
			getsym();
		}else{
			error();
			printf("need semi;");
			while(symNeed[symbol] != 1){
				getsym();
			}
		}

		symNeed[VARSY] = 0;
		symNeed[PROCSY] = 0;
		symNeed[FUNCSY] = 0;
		symNeed[BEGINSY] = 0;

		#ifdef DEBUG
			printf("This is a constant statement.\n");
		#endif
	}
	if(symbol == VARSY){//变量说明部分
		symNeed[PROCSY] = 1;
		symNeed[FUNCSY] = 1;
		symNeed[BEGINSY] = 1;

		getsym();

		symNeed[SEMISY] = 1;
		symNeed[IDSY] = 1;
		varDef();
		symNeed[SEMISY] = 0;
		symNeed[IDSY] = 0;

		if(symbol == SEMISY){
			getsym();
		}else{
			error();
			printf("need semi;");
			while(symNeed[symbol] != 1 && symbol != IDSY){
				getsym();
			}
		}

		while(symbol == IDSY){
			symNeed[SEMISY] = 1;
			symNeed[IDSY] = 1;
			varDef();
			symNeed[SEMISY] = 0;
			symNeed[IDSY] = 0;

			if(symbol == SEMISY){
				getsym();
			}else{
				error();
				printf("need semi;");
				while(symbol != IDSY && symNeed[symbol] != 1){
					getsym();
				}
			}
		}
		symNeed[PROCSY] = 0;
		symNeed[FUNCSY] = 0;
		symNeed[BEGINSY] = 0;
		#ifdef DEBUG
			printf("This is a variable statement.\n");
		#endif
	}
	if(symbol == PROCSY){//过程说明部分
		symNeed[FUNCSY] = 1;
		symNeed[BEGINSY] = 1;

		symNeed[CONSTSY] = 1;
		symNeed[VARSY] = 1;
		symNeed[PROCSY] = 1;
		symNeed[FUNCSY] = 1;
		symNeed[BEGINSY] = 1;
		proHead();
		symNeed[CONSTSY] = 0;
		symNeed[VARSY] = 0;
		symNeed[PROCSY] = 0;
		symNeed[FUNCSY] = 0;
		symNeed[BEGINSY] = 0;

		symNeed[SEMISY] = 1;
		subPro();
		symNeed[SEMISY] = 0;

		if(symbol == SEMISY){
			getsym();
		}else{
			error();
			printf("need a semi;\n");
			while(symbol != PROCSY && symNeed[symbol] != 1){
				getsym();
			}
		}
		while(symbol == PROCSY){
			symNeed[CONSTSY] = 1;
			symNeed[VARSY] = 1;
			symNeed[PROCSY] = 1;
			symNeed[FUNCSY] = 1;
			symNeed[BEGINSY] = 1;
			proHead();
			symNeed[CONSTSY] = 0;
			symNeed[VARSY] = 0;
			symNeed[PROCSY] = 0;
			symNeed[FUNCSY] = 0;
			symNeed[BEGINSY] = 0;

			symNeed[SEMISY] = 1;
			subPro();
			symNeed[SEMISY] = 0;

			if(symbol == SEMISY){
				getsym();
			}else{
				error();
				printf("need a semi;\n");
				while(symbol != PROCSY && symNeed[symbol] != 1){
					getsym();
				}
			}
		}
		symNeed[FUNCSY] = 0;
		symNeed[BEGINSY] = 0;
		#ifdef DEBUG
			printf("This is a procedure statement.\n");
		#endif
	}
	if(symbol == FUNCSY){//函数说明部分
		symNeed[BEGINSY] = 1;

		symNeed[CONSTSY] = 1;
		symNeed[VARSY] = 1;
		symNeed[PROCSY] = 1;
		symNeed[FUNCSY] = 1;
		symNeed[BEGINSY] = 1;
		funcHead();
		symNeed[CONSTSY] = 0;
		symNeed[VARSY] = 0;
		symNeed[PROCSY] = 0;
		symNeed[FUNCSY] = 0;
		symNeed[BEGINSY] = 0;

		symNeed[SEMISY] = 1;
		subPro();
		symNeed[SEMISY] = 1;

		if(symbol == SEMISY){
			getsym();
		}else{
			error();
			printf("need a semi;\n");
			while(symbol != FUNCSY && symNeed[symbol] != 1){
				getsym();
			}
		}
		while(symbol == FUNCSY){
			symNeed[CONSTSY] = 1;
			symNeed[VARSY] = 1;
			symNeed[PROCSY] = 1;
			symNeed[FUNCSY] = 1;
			symNeed[BEGINSY] = 1;
			funcHead();
			symNeed[CONSTSY] = 0;
			symNeed[VARSY] = 0;
			symNeed[PROCSY] = 0;
			symNeed[FUNCSY] = 0;
			symNeed[BEGINSY] = 0;

			symNeed[SEMISY] = 1;
			subPro();
			symNeed[SEMISY] = 1;

			if(symbol == SEMISY){
				getsym();
			}else{
				error();
				printf("need a semi;\n");
				while(symbol != FUNCSY && symNeed[symbol] != 1){
					getsym();
				}
			}
		}
		symNeed[BEGINSY] = 0;
		#ifdef DEBUG
			printf("This is a function statement.\n");
		#endif
	}
	comState();
	#ifdef DEBUG
		printf("This is a subProcedrue.\n");
	#endif
}

void constDef(){
	if(symbol == IDSY){
		getsym();
		if(symbol == EQUSY){
			getsym();
			constAnaly();
		}else{
			error();
			printf("need a equ=\n");
			while(symNeed[symbol] != 1){
				getsym();
			}
		}
	}else{
		error();
		printf("need a id.\n");
		while(symNeed[symbol] != 1){
			getsym();
		}
	}
	#ifdef DEBUG
		printf("This is a constant define.\n");
	#endif
}

void constAnaly(){
	if(symbol == PLUSSY || symbol == MINUSSY){
		getsym();
	}
	if(symbol == INTSY){
        getsym();
    }else if(symbol == CHARSY){
        getsym();
    }else{
        error();
		printf("need a int or a int or char.\n");
        while(symNeed[symbol] != 1){
            getsym();
        }
	}
	#ifdef DEBUG
		printf("This is a constant analysis.\n");
	#endif
}

void varDef(){
	if(symbol == IDSY){
		getsym();
		while(symbol == COMMASY){
			getsym();
			if(symbol == IDSY){
				getsym();
			}else{
				error();
				printf("need a id.\n");
				while(symbol != COMMASY && symbol != COLOSY && symNeed[symbol] != 1){
					getsym();
				}
			}
		}
		if(symbol == COLOSY){
			getsym();
		}else{
			error();
			printf("need a colon:\n");
			while(symbol != ARRAYSY && symbol != INTEGER && symbol != CHARACTER && symNeed[symbol] != 1){
				getsym();
			}
		}
		Type();
	}else{
		error();
		printf("need a id.\n");
		while(symNeed[symbol] != 1){
			getsym();
		}
	}
	#ifdef DEBUG
		printf("This is a variable define.\n");
	#endif
}

void proHead(){
	if(symbol == PROCSY){
		getsym();
		if(symbol == IDSY){
			getsym();
			if(symbol == LPASY){
				symNeed[SEMISY] = 1;
				formParaList();
				symNeed[SEMISY] = 0;
			}
			if(symbol == SEMISY){
				getsym();
			}else{
				error();
				printf("need a semi;\n");
				while(symNeed[symbol] != 1){
					getsym();
				}
			}
		}else{
			error();
			printf("need a id.\n");
			while(symNeed[symbol] != 1){
				getsym();
			}
		}
	}
	#ifdef DEBUG
		printf("This is a procedure head.\n");
	#endif
}

void funcHead(){
	if(symbol == FUNCSY){
		getsym();
		if(symbol == IDSY){
			getsym();
			if(symbol == LPASY){
				symNeed[symbol] = 1;
				formParaList();
				symNeed[symbol] = 0;
			}
			if(symbol == COLOSY){
				getsym();
			}else{
				error();
				printf("need a colon.\n");
				while(symNeed[symbol] != 1){
					getsym();
				}
			}

			symNeed[SEMISY] = 1;
			baseType();
			symNeed[symbol] = 0;

			if(symbol == SEMISY){
				getsym();
			}else{
				error();
				printf("need a semi;\n");
				while(symNeed[symbol] != 1){
					getsym();
				}
			}
		}else{
			error();
			printf("need a id.\n");
			while(symNeed[symbol] != 1){
				getsym();
			}
		}
	}
	#ifdef DEBUG
		printf("This is a function head.\n");
	#endif
}

void formParaList(){
	if(symbol == LPASY){
        getsym();
		symNeed[SEMISY] = 1;
		symNeed[RPASY] = 1;
		formParaSeg();
		symNeed[SEMISY] = 0;
		symNeed[RPASY] = 0;

		while(symbol == SEMISY){
			getsym();
			symNeed[SEMISY] = 1;
			symNeed[RPASY] = 1;
			formParaSeg();
			symNeed[SEMISY] = 0;
			symNeed[RPASY] = 0;
		}

		if(symbol == RPASY){
			getsym();
		}else{
			error();
			printf("need a right parentheses.\n");
			while(symNeed[symbol] != 1){
				getsym();
			}
		}
	}
	#ifdef DEBUG
		printf("This is a formal parameter list.\n");
	#endif
}

void Type(){
	if(symbol == ARRAYSY){
		getsym();
		if(symbol == LBRACSY){
			getsym();
		}else{
			error();
			printf("need a left brac[\n");
			while(symNeed[symbol] != 1 && symbol != INTSY){
				getsym();
			}
		}
		if(symbol == INTSY){
			getsym();
			if(symbol == RBRACSY){
				getsym();
			}else{
				error();
				printf("need a right brac]\n");
				while(symNeed[symbol] != 1 && symbol != OFSY && symbol != INTEGER && symbol != CHARACTER ){
					getsym();
				}
			}
			if(symbol == OFSY){
				getsym();
			}else{
				error();
				printf("need a of.\n");
				while(symNeed[symbol] != 1 && symbol != INTEGER && symbol != CHARACTER){
					getsym();
				}
			}
			baseType();
		}else{
			error();
			printf("need a int number.\n");
			while(symNeed[symbol] != 1){
				getsym();
			}
		}
	}else{
		baseType();
	}
	#ifdef DEBUG
		printf("This is a type statement.\n");
	#endif
}

void baseType(){
	if(symbol == INTEGER){
		getsym();
	}else if(symbol == CHARACTER){
		getsym();
	}else{
		error();
	printf("wrong Type.\n");
		while(symNeed[symbol] != 1){
			getsym();
		}
	}
	#ifdef DEBUG
		printf("This is a base type statement.\n");
	#endif
}

void formParaSeg(){
	if(symbol == VARSY){
		getsym();
	}
	if(symbol == IDSY){
		getsym();
		while(symbol == COMMASY){
			getsym();
			if(symbol == IDSY){
				getsym();
			}else{
				error();
				printf("need a id.\n");
				while(symNeed[symbol] != 1 && symbol != COMMASY && symbol != COLOSY && symbol != INTEGER && symbol != CHARACTER){
					getsym();
				}
			}
		}
		if(symbol == COLOSY){
			getsym();
		}else{
			error();
			printf("need a colon:\n");
			while(symNeed[symbol] != 1){
				getsym();
			}
		}
		baseType();
	}else{
		error();
		printf("need a id.\n");
		while(symNeed[symbol]
		!= 1){
			getsym();
		}
	}
	#ifdef DEBUG
		printf("This is a formal parameter segment.\n");
	#endif
}

void comState(){
	if(symbol == BEGINSY){
        getsym();

		symNeed[SEMISY] = 1;
		symNeed[ENDSY] = 1;
		state();
		symNeed[SEMISY] = 0;
		symNeed[ENDSY] = 0;

		while(symbol == SEMISY){
			getsym();
			symNeed[SEMISY] = 1;
			symNeed[ENDSY] = 1;
			state();
			symNeed[SEMISY] = 0;
			symNeed[ENDSY] = 0;
		}

		if(symbol == ENDSY){
			getsym();
		}else{
			error();
			printf("need a end.\n");
			while(symNeed[symbol] != 1){
				getsym();
			}
		}
	}else{
		error();
		printf("need a begin.\n");
		while(symNeed[symbol] != 1){
			getsym();
		}
	}
	#ifdef DEBUG
		printf("This is a compound statement.\n");
	#endif
}

void state(){
	if(symbol == IFSY){
		conditionState();
	}else if(symbol == CASESY){
		caseState();
	}else if(symbol == BEGINSY){
		comState();
	}else if(symbol == READSY){
		readState();
	}else if(symbol == WRITESY){
		writeState();
	}else if(symbol == FORSY){
		loop();
	}else if(symbol == IDSY){
		getsym();
		if(symbol == BECOMESY || symbol == LBRACSY){
			assignment();
		}else{
			proCall();
		}
	}else{

	}
	#ifdef DEBUG
		printf("This is a statement.\n");
	#endif
}

void assignment(){
	if(symbol == BECOMESY){
		getsym();
		expression();
	}else if(symbol == LBRACSY){
		getsym();
		expression();
		if(symbol == RBRACSY){
			getsym();
		}else{
			error();
			printf("need a right bracket].\n");
			while(symNeed[symbol] != 1 && symbol != BECOMESY){
				getsym();
			}
		}
		if(symbol == BECOMESY){
			getsym();
		}else{
			error();
			printf("need a become:=\n");
			while(symNeed[symbol] != 1 && symbol != PLUSSY && symbol != MINUSSY && symbol != IDSY){
				getsym();
			}
		}
		expression();
	}else{

	}
	#ifdef DEBUG
		printf("This is a assignment statement.\n");
	#endif
}

void conditionState(){
	if(symbol == IFSY){
		getsym();
		symNeed[THENSY] = 1;
		symNeed[IDSY] = 1;
		symNeed[IFSY] = 1;
		symNeed[CASESY] = 1;
		symNeed[BEGINSY] = 1;
		symNeed[READSY] = 1;
		symNeed[WRITESY] = 1;
		symNeed[FORSY] = 1;
		condition();
		symNeed[IDSY] = 0;
		symNeed[IFSY] = 0;
		symNeed[CASESY] = 0;
		symNeed[BEGINSY] = 0;
		symNeed[READSY] = 0;
		symNeed[WRITESY] = 0;
		symNeed[FORSY] = 0;
		symNeed[THENSY] = 0;

		if(symbol == THENSY){
			getsym();
		}else{
			error();
			printf("need a then.\n");
			while(symNeed[symbol] != 1 && symbol != IDSY && symbol != IFSY && symbol != CASESY && symbol != BEGINSY && symbol != READSY && symbol != WRITESY && symbol != FORSY){
				getsym();
			}
		}
		symNeed[symbol] = 1;
		state();
		symNeed[symbol] = 0;

		if(symbol == ELSESY){
            getsym();
			symNeed[symbol] = 1;
			state();
			symNeed[symbol] = 0;
		}
	}else{

	}
	#ifdef DEBUG
		printf("This is a condition statement.\n");
	#endif
}

void caseState(){
	if(symbol == CASESY){
		getsym();
		symNeed[OFSY] = 1;
		symNeed[PLUSSY] = 1;
		symNeed[MINUSSY] = 1;
		symNeed[INTSY] = 1;
		symNeed[CHARSY] = 1;
		expression();
		symNeed[OFSY] = 0;
		symNeed[PLUSSY] = 0;
		symNeed[MINUSSY] = 0;
		symNeed[INTSY] = 0;
		symNeed[CHARSY] = 0;

		if(symbol == OFSY){
			getsym();
		}else{
			error();
			printf("need a of.\n");
			while(symNeed[symbol] != 1 && symbol != PLUSSY && symbol != MINUSSY && symbol != INTSY && symbol != CHARSY){
				getsym();
			}
		}

		symNeed[SEMISY] = 1;
		symNeed[ENDSY] = 1;
		caseelement();
		symNeed[SEMISY] = 0;
		symNeed[ENDSY] = 0;

		while(symbol == SEMISY){
			getsym();
			symNeed[SEMISY] = 1;
			symNeed[ENDSY] = 1;
			caseelement();
			symNeed[SEMISY] = 0;
			symNeed[ENDSY] = 0;
		}

		if(symbol == ENDSY){
			getsym();
		}else{
			error();
			printf("need a end.\n");
			while(symNeed[symbol] != 1){
				getsym();
			}
		}
	}else{

	}
	#ifdef DEBUG
		printf("This is a case statement.\n");
	#endif
}

void proCall(){
	if(symbol == LPASY){
		actParaList();
	}else{

	}
	#ifdef DEBUG
		printf("This is a procedure call statement.\n");
	#endif
}

void readState(){
	if(symbol == READSY){
		getsym();
		if(symbol == LPASY){
			getsym();
		}else{
			error();
			printf("need a left parenthsis.\n");
			while(symNeed[symbol] != 1 && symbol != IDSY){
				getsym();
			}
		}
		if(symbol == IDSY){
			getsym();
			while(symbol == COMMASY){
				getsym();
				if(symbol == IDSY){
					getsym();
				}else{
					error();
					printf("need a id.\n");
					while(symNeed[symbol] != 1 && symbol != COMMASY && symbol != RPASY){
						getsym();
					}
				}
			}
			if(symbol == RPASY){
				getsym();
			}else{
				error();
				printf("need a right parenthsis.\n");
				while(symNeed[symbol] != 1){
					getsym();
				}
			}
		}else{
			error();
			printf("need a id.\n");
			while(symNeed[symbol] != 1){
				getsym();
			}
		}
	}else{

	}
	#ifdef DEBUG
		printf("This is a read statement.\n");
	#endif
}

void writeState(){
	if(symbol == WRITESY){
        getsym();
		if(symbol == LPASY){
			getsym();
		}else{
			error();
			printf("need a left parenthsis.\n");
			while(symNeed[symbol] != 1 && symbol != STRSY && symbol != PLUSSY && symbol != MINUSSY && symbol != IDSY){
				getsym();
			}
		}
		if(symbol == STRSY){
			getsym();
			if(symbol == COMMASY){
				getsym();
				symNeed[RPASY] = 1;
				expression();
				symNeed[RPASY] = 0;
			}
			if(symbol == RPASY){
				getsym();
			}else{
				error();
				printf("need a left parenthsis.\n");
				while(symNeed[symbol] != 1){
					getsym();
				}
			}
		}else{
			symNeed[RPASY] = 1;
			expression();
			symNeed[RPASY] = 0;
			if(symbol == RPASY){
				getsym();
			}else{
				error();
				printf("need a left parenthsis.\n");
				while(symNeed[symbol] != 1){
					getsym();
				}
			}
		}
	}else{

	}
	#ifdef DEBUG
		printf("This is a write statement.\n");
	#endif
}

void loop(){
	if(symbol == FORSY){
        getsym();
		if(symbol == IDSY){
			getsym();
			if(symbol == BECOMESY){
				getsym();
			}else{
				error();
				printf("need a become:=.\n");
				while(symNeed[symbol] != 1 && symbol != PLUSSY && symbol != MINUSSY && symbol != IDSY){
					getsym();
				}
			}
			symNeed[DOWNTO] = 1;
			symNeed[TOSY] = 1;
			expression();
			symNeed[DOWNTO] = 0;
			symNeed[TOSY] = 0;

			if(symbol == DOWNTO){
				getsym();
			}else if(symbol == TOSY){
				getsym();
			}else{
				error();
				printf("need a downto or to.\n");
				while(symNeed[symbol] != 1 && symbol != PLUSSY && symbol != MINUSSY && symbol != IDSY){
					getsym();
				}
			}

			symNeed[DOSY] = 1;
			expression();
			symNeed[DOSY] = 0;

			if(symbol == DOSY){
				getsym();
			}else{
				error();
				printf("need a do.\n");
				while(symNeed[symbol] != 1 && symbol != IDSY && symbol != IFSY && symbol != CASESY && symbol != BEGINSY && symbol != READSY && symbol != WRITESY && symbol != FORSY){
					getsym();
				}
			}

			state();
		}else{
			error();
			printf("need a id.\n");
			while(symNeed[symbol] != 1){
				getsym();
			}
		}
	}else{

	}
	#ifdef DEBUG
		printf("This is a for loop statement.\n");
	#endif
}

void expression(){
	if(symbol == PLUSSY || symbol == MINUSSY){
		getsym();
	}
	symNeed[PLUSSY] = 1;
	symNeed[MINUSSY] = 1;
	term();
	symNeed[PLUSSY] = 0;
	symNeed[MINUSSY] = 0;

	while(symbol == PLUSSY || symbol == MINUSSY){
		getsym();
		symNeed[PLUSSY] = 1;
		symNeed[MINUSSY] = 1;
		term();
		symNeed[PLUSSY] = 0;
		symNeed[MINUSSY] = 0;
	}
	#ifdef DEBUG
		printf("This is a expression.\n");
	#endif
}

void condition(){
	symNeed[EQUSY] = 1;
	symNeed[LESSSY] = 1;
	symNeed[GREATSY] = 1;
	symNeed[LEQSY] = 1;
	symNeed[GEQSY] = 1;
	symNeed[UNEQUSY] = 1;
	expression();
	symNeed[EQUSY] = 0;
	symNeed[LESSSY] = 0;
	symNeed[GREATSY] = 0;
	symNeed[LEQSY] = 0;
	symNeed[GEQSY] = 0;
	symNeed[UNEQUSY] = 0;

	if(symbol == EQUSY){
        getsym();
        expression();
	}else if(symbol == LESSSY){
	    getsym();
	    expression();
	}else if(symbol == GREATSY){
        getsym();
        expression();
	}else if(symbol == LEQSY){
        getsym();
        expression();
	}else if(symbol == GEQSY){
        getsym();
        expression();
	}else if(symbol == UNEQUSY){
        getsym();
        expression();
	}else{
        error();
        printf("need a condition option.\n");
        while(symNeed[symbol] != 1){
            getsym();
        }
	}

	#ifdef DEBUG
		printf("This is a condition.\n");
	#endif
}

void caseelement(){
	symNeed[COLOSY] = 1;
	symNeed[IDSY] = 1;
	symNeed[IFSY] = 1;
	symNeed[CASESY] = 1;
	symNeed[BEGINSY] = 1;
	symNeed[READSY] = 1;
	symNeed[WRITESY] = 1;
	symNeed[FORSY] = 1;
	constAnaly();
	symNeed[COLOSY] = 0;
	symNeed[IDSY] = 0;
	symNeed[IFSY] = 0;
	symNeed[CASESY] = 0;
	symNeed[BEGINSY] = 0;
	symNeed[READSY] = 0;
	symNeed[WRITESY] = 0;
	symNeed[FORSY] = 0;

	if(symbol == COLOSY){
		getsym();
	}else{
		error();
		printf("need a colon:\n");
		while(symNeed[symbol] != 1 && symbol != IDSY && symbol != IFSY && symbol != CASESY && symbol != BEGINSY && symbol != READSY && symbol != WRITESY && symbol != FORSY){
			getsym();
		}
	}

	state();

	#ifdef DEBUG
		printf("This is a case element.\n");
	#endif
}

void actParaList(){
	if(symbol == LPASY){
		getsym();

		symNeed[COMMASY] = 1;
		symNeed[LPASY] = 1;
		expression();
		symNeed[COMMASY] = 0;
		symNeed[LPASY] = 0;

		while(symbol == COMMASY){
			getsym();
			symNeed[COMMASY] = 1;
			symNeed[LPASY] = 1;
			expression();
			symNeed[COMMASY] = 0;
			symNeed[LPASY] = 0;
		}

		if(symbol == RPASY){
			getsym();
		}else{
			error();
			printf("need a right parenthsis.\n");
			while(symNeed[symbol] != 1){
				getsym();
			}
		}
	}else{

	}
	#ifdef DEBUG
		printf("This is an actuel parameter list.\n");
	#endif
}

void term(){
	symNeed[STARSY] = 1;
	symNeed[DIVISY] = 1;
	factor();
	symNeed[STARSY] = 0;
	symNeed[DIVISY] = 0;

	while(symbol == STARSY || symbol == DIVISY){
		getsym();
		symNeed[STARSY] = 1;
		symNeed[DIVISY] = 1;
		factor();
		symNeed[STARSY] = 0;
		symNeed[DIVISY] = 0;
	}

	#ifdef DEBUG
		printf("This is a term.\n");
	#endif
}

void factor(){
	if(symbol == INTSY){
		getsym();
	}else if(symbol == LPASY){
		symNeed[RPASY] = 1;
		expression();
		symNeed[RPASY] = 0;

		if(symbol == RPASY){
			getsym();
		}else{
			error();
			printf("need a right parenthsis.\n");
			while(symNeed[symbol] != 1){
				getsym();
			}
		}
	}else{
		getsym();
		if(symbol == LBRACSY){
			symNeed[RBRACSY] = 1;
			expression();
			symNeed[RBRACSY] = 0;

			if(symbol == RPASY){
				getsym();
			}else{
				error();
				printf("need a right bracket.\n");
				while(symNeed[symbol] != 1){
					getsym();
				}
			}
		}else{
            if(symbol == LPASY){
                funcCall();
            }
		}
	}
	#ifdef DEBUG
		printf("This is a factor.\n");
	#endif
}

void funcCall(){
	//if(symbol == IDSY){
		//getsym();
		if(symbol == LPASY){
			actParaList();
		//}
	}else{

	}
	#ifdef DEBUG
		printf("This is a function call.\n");
	#endif
}
