#include "function.h"
#include "variable.h"

void grammar(){
	tabtop = 0;
	atabtop = 0;
	btabtop = 0;
	termnum = 0;
	btabnow->last = -1;
	btabnow->lastpar = -1;
	btabnow->psize = 0;
	btabnow->adr = 0;
	btabnow->vsize = 0;
	btab[btabtop++] = btabnow;
	getsym();
	procedure();
	list();
}

void procedure(){
	symNeed[PERISY] = 1;
	subPro(1, -1, 0);
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

void subPro(int lev, int levtop, int adr){
	
	void constDef(){
		if(symbol == IDSY && tabtest(lev, token) == -1){
			strcpy(tabnow->name, token);
			tabnow->obj = CONST;
			tabnow->lev = lev;
			tabnow->normal = nul;
			tabnow->link = levtop++;
			tabnow->ref = 0;
			
			getsym();
			if(symbol == EQUSY){
				getsym();
			}else{
				error();
				printf("need a equ=\n");
				while(symNeed[symbol] != 1 && symbol != PLUS && symbol != MINUSSY && symbol != INTSY && symbol != CHARSY){
					getsym();
				}
			}
			constAnaly();
		}else{
			error();
			printf("标识符错误或已经被定义.\n");
			while(symNeed[symbol] != 1){
				getsym();
			}
		}
		#ifdef DEBUG
			printf("This is a constant define.\n");
		#endif
	}

	void constAnaly(){
		if(symbol == PLUSSY){
			getsym();
			if(symbol == INTSY){
				tabnow->adr = num;
				tabnow->typ = INTSY;
				getsym();
			}
		}else if(symbol == MINUSSY){
			getsym();
			if(symbol == INTSY){
				tabnow->adr = -1 * num;
				tabnow->typ = INTSY;
				
				getsym();
			}
		}else if(symbol == CHARSY){
			tabnow->adr = cha;
			tabnow->typ = CHARSY;
			
			getsym();
		}else{
			error();
			tabnow->adr = 0;
			tabnow->typ = INTSY;
			printf("need an int or a char.\n");
			while(symNeed[symbol] != 1){
				getsym();
			}
		}
		tab[tabtop++] = tabnow;
		#ifdef DEBUG
			printf("This is a constant analysis.\n");
		#endif
	}

	void varDef(){
		termnum = 0;
		if(symbol == IDSY){
			strcpy(tabnow->name, token);
			tabnow->obj = VAR;
			tabnow->lev = lev;
			tabnow->normal = nul;
			tabnow->link = levtop++;
			tabnow->ref = 0;
			tab[tabtop++] = tabnow;
			termnum++;
			
			getsym();
			while(symbol == COMMASY){
				getsym();
				if(symbol == IDSY){
					strcpy(tabnow->name, token);
					tabnow->obj = VAR;
					tabnow->lev = lev;
					tabnow->normal = nul;
					tabnow->link = levtop++;
					tabnow->ref = 0;
					tab[tabtop++] = tabnow;
					termnum++;
					
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
			printf("标识符错误或已经被定义.\n");
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
			if(symbol == IDSY && tabtest(lev, token) == -1){
				strcpy(tabnow->name, token);
				tabnow->obj = PROCEDURE;
				tabnow->typ = nul;
				tabnow->ref = btabtop;
				tabnow->lev = lev;
				tabnow->normal = nul;
				tabnow->adr = ctabtop;
				tabnow->link = levtop++;
				tab[tabtop++] = tabnow;
				btabnow->last = tabtop-1;
				btabnow->psize = 0;
				btab[btabtop++] = btabnow;
				gen("-", LAB, tab[tabtop-1]->name, "-");
				
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
				printf("标识符错误或已经被定义.\n");
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
			if(symbol == IDSY && tabtest(lev, token) == -1){
				strcpy(tabnow->name, token);
				tabnow->obj = FUNCTION;
				tabnow->ref = btabtop;
				tabnow->lev = lev;
				tabnow->normal = nul;
				tabnow->adr = ctabtop;
				tabnow->link = levtop++;
				tab[tabtop++] = tabnow;
				btabnow->psize = 0;
				batbnow->vsize = 0;
				btab[btabtop++] = btabnow;
				
				gen("-", LAB, tab[tabtop-1]->name, "-");
				
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
				tabnow[tabtop - (termnum+1)]->typ = baseType();
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
				printf("标识符错误或已经被定义.\n");
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
			tabtype(ARRARY, termnum);
			tabref(atabtop, termnum);
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
				atabnow->high = num;
				tabadr(adrtop, num, termnum);
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
				atabnow->typ = baseType();
				atab[atabtop++] = atabnow;
			}else{
				error();
				printf("need a int number.\n");
				while(symNeed[symbol] != 1){
					getsym();
				}
				atabnow->high = 1;
				tabadr(adrtop, 1, termnum);
			}
		}else{
			tabtype(baseType(), termnum);
			tabadr(adrtop, 1, termnum);
		}
		#ifdef DEBUG
			printf("This is a type statement.\n");
		#endif
	}

	_SYMBOL baseType(){
		if(symbol == INTEGER){
			getsym();
			return INTEGER;
		}else if(symbol == CHARACTER){
			getsym();
			return CHARACTER;
		}else{
			error();
			printf("wrong Type.\n");
			while(symNeed[symbol] != 1){
				getsym();
			}
			return nul;
		}
		#ifdef DEBUG
			printf("This is a base type statement.\n");
		#endif
	}

	void formParaSeg(){
		int flag = 0;
		termnum = 0;
		if(symbol == VARSY){
			flag = 1;
			getsym();
		}
		if(symbol == IDSY && tabtest(lev, token) == -1){
			strcpy(tabnow->name, token);
			tabnow->obj = VAR;
			tabnow->ref = nul;
			tabnow->lev = lev+1;
			if(flag){
				tabnow->normal = TRUE;
			}else{
				tabnow->normal = FALSE;
			}
			tab[tabtop++] = tabnow;
			termnum++;
			
			getsym();
			while(symbol == COMMASY){
				getsym();
				if(symbol == IDSY && tabtest(token) == -1){
					strcpy(tabnow->name, token);
					tabnow->obj = VAR;
					tabnow->ref = nul;
					tabnow->lev = lev;
					if(flag){
						tabnow->normal = TRUE;
					}else{
						tabnow->normal = FALSE;
					}
					termnum++;
					
					getsym();
				}else{
					error();
					printf("标识符错误或已经被定义.\n");
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
			tabtype(baseType(), termnum);
			tabadr(adrtop, 1, termnum);
			btab[btabtop-1]->psize = termnum;
			batb[batbtop-1]->lastpar = tabtop-1;
		}else{
			error();
			printf("标识符错误或已经被定义.\n");
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
		int i = 0;
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
			i = tabfind(token);
			if(i == -1){
				error();
				printf("未定义的标识符\n");
			}else{
				if(tab[i]->obj == VAR || tab[i]->obj == FUNCTION){
					assignment(i);
				}else if(tab[i]->obj == PROCEDURE){
					proCall(i);
				}else{
					error();
					printf("尝试为常量赋值错误\n");
				}
			}
		}else{

		}
		#ifdef DEBUG
			printf("This is a statement.\n");
		#endif
	}

	void assignment(int i){
		int type = 0;
		int temp = 0;
		getcym();
		if(symbol == BECOMESY){
			getsym();
			type = expression();
			if(tab[i]->typ == INT && type == 0){
				gen(tab[i]->name, PLUS, ctab[ctabtop-1]->des, "0");
			}else if(tab[i]->typ == CHAR && type > 0){
				gen(tab[i]->name, PLUS, ctab[ctabtop-1]->des, "0");
			}else{
				error();
				printf("赋值类型不匹配\n");
			}
		}else if(symbol == LBRACSY){
			getsym();
			expression();
			gen("T", PLUS, tab[i]->name, ctab[ctabtop-1]->des);
			temp = ctabtop-1;
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
			gen("-", STO, ctab[temp]->des, ctab[ctabtop-1]->des);
		}else{

		}
		#ifdef DEBUG
			printf("This is a assignment statement.\n");
		#endif
	}

	void conditionState(){
		int temp = 0;
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
			gen(ctab[ctabtop-1]->des, JMP, "-", "-");
			temp = ctabtop-1;
			
			symNeed[symbol] = 1;
			state();
			symNeed[symbol] = 0;
			
			gen("-", JMP, "-", "-");
			gen("-", LAB, "L", "-");
			ctab[temp]->fir = ctab[ctabtop-1]->fir;
			temp = ctabtop-2;
			if(symbol == ELSESY){
				getsym();
				symNeed[symbol] = 1;
				state();
				symNeed[symbol] = 0;
			}
			gen("-", LAB, "L", "-");
			ctab[temp]->fir = ctab[ctabtop-1]->fir;
		}else{

		}
		#ifdef DEBUG
			printf("This is a condition statement.\n");
		#endif
	}

	void caseState(){
		int temp = 0;
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
			temp = ctabtop-1;
			
			symNeed[SEMISY] = 1;
			symNeed[ENDSY] = 1;
			caseelement(temp);
			symNeed[SEMISY] = 0;
			symNeed[ENDSY] = 0;

			while(symbol == SEMISY){
				getsym();
				symNeed[SEMISY] = 1;
				symNeed[ENDSY] = 1;
				caseelement(temp);
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

	void proCall(i){
		getsym();
		if(symbol == LPASY){
			actParaList();
			gen("-", CALL, tab[i]->name, "-");
		}else{
			gen("-", CALL, tab[i]->name, "-");
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
				if(tabfind(token) != -1){
					gen(token, RED, "-", "-");
				}else{
					error();
					printf("未定义的标识符\n");
				}
				getsym();
				while(symbol == COMMASY){
					getsym();
					if(symbol == IDSY){
						getsym();
					}else{
						error();
						printf("need a id.\n");
						if(tabfind(token) != -1){
							gen(token, RED, "-", "-");
						}else{
							error();
							printf("未定义的标识符\n");
						}
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
				gen("-", WRI, str, "-");
				getsym();
				if(symbol == COMMASY){
					getsym();
					symNeed[RPASY] = 1;
					expression();
					symNeed[RPASY] = 0;
					gen("-", WRI, ctab[ctabtop-1]->des, "-");
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
				gen("-", WRI, ctab[ctabtop-1]->des, "-");
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
		int temp = 0;
		int label = 0;
		int flag = 0;
		if(symbol == FORSY){
			getsym();
			if(symbol == IDSY){
				gen(token, PLUS, "-", "0");
				temp = ctabtop-1;
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
				
				ctab[temp]->fir = ctab[ctabtop-1]->des;

				if(symbol == DOWNTO){
					gen(ctab[temp]->des, PLUS, ctab[temp]->des, "1");
					gen("-", LAB, "L", "-");
					label = ctabtop-1;
					gen(ctab[temp]->des, MINUS, ctab[temp]->des, "1");
					temp = ctabtop-1;
					flag = 1;
					getsym();
				}else if(symbol == TOSY){
					gen(ctab[temp]->des, MINUS, ctab[temp]->des, "1");
					gen("-", LAB, "L", "-");
					label = ctabtop-1;
					gen(ctab[temp]->des, PLUS, ctab[temp]->des, "1");
					temp = ctabtop-1;
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
				
				if(flag){
					gen("T", LTH, ctab[temp]->des, ctab[ctabtop-1]->des);
				}else{
					gen("T", GTH, ctab[temp]->des, ctab[ctabtop-1]->des);
				}
				
				gen(ctab[ctabtop-1]->des, JMP, "-", "-");
				temp = ctabtop-1;
				
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
				gen("-", JMP, ctab[label]->fir, "-");
				gen("-", LAB, "L", "-");
				ctab[temp]->fir = ctab[ctabtop-1]->fir;
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

	int expression(){
		int rst = 0;
		int flag = 0;
		char[al] temp;
		if(symbol == PLUSSY || symbol == MINUSSY){
			if(symbol == MINUSSY){
				flag = 1;
			}
			getsym();
		}
		symNeed[PLUSSY] = 1;
		symNeed[MINUSSY] = 1;
		rst += term();
		symNeed[PLUSSY] = 0;
		symNeed[MINUSSY] = 0;
		if(flag){
			gen(ctab[ctabtop-1], MINUS, "0", ctab[ctabtop-1]->des);
		}
		strcpy(temp, ctab[ctabtop-1]->des);
		while(symbol == PLUSSY || symbol == MINUSSY){
			if(symbol == PLUSSY){
				flag = 2
			}
			getsym();
			symNeed[PLUSSY] = 1;
			symNeed[MINUSSY] = 1;
			rst += term();
			symNeed[PLUSSY] = 0;
			symNeed[MINUSSY] = 0;
			if(flag == 2){
				gen("T", PLUS, temp, ctab[ctabtop-1]->des)
			}else{
				gen("T", MINUS, temp, ctab[ctabtop-1]->des)
			}
		}
		#ifdef DEBUG
			printf("This is a expression.\n");
		#endif
		return rst;
	}

	void condition(){
		int temp = 0;
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
		
		temp = ctabtop-1;
		if(symbol == EQUSY){
			getsym();
			expression();
			gen("T", UEQ, ctab[temp]->des, ctab[ctabtop-1]->des);
		}else if(symbol == LESSSY){
			getsym();
			expression();
			gen("T", GEQ, ctab[temp]->des, ctab[ctabtop-1]->des);
		}else if(symbol == GREATSY){
			getsym();
			expression();
			gen("T", LEQ, ctab[temp]->des, ctab[ctabtop-1]->des);
		}else if(symbol == LEQSY){
			getsym();
			expression();
			gen("T", GTH, ctab[temp]->des, ctab[ctabtop-1]->des);
		}else if(symbol == GEQSY){
			getsym();
			expression();
			gen("T", LTH, ctab[temp]->des, ctab[ctabtop-1]->des);
		}else if(symbol == UNEQUSY){
			getsym();
			expression();
			gen("T", EQU, ctab[temp]->des, ctab[ctabtop-1]->des);
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

	void caseelement(int i){
		int temp = 0;
		
		symNeed[COLOSY] = 1;
		symNeed[IDSY] = 1;
		symNeed[IFSY] = 1;
		symNeed[CASESY] = 1;
		symNeed[BEGINSY] = 1;
		symNeed[READSY] = 1;
		symNeed[WRITESY] = 1;
		symNeed[FORSY] = 1;
		constant();
		symNeed[COLOSY] = 0;
		symNeed[IDSY] = 0;
		symNeed[IFSY] = 0;
		symNeed[CASESY] = 0;
		symNeed[BEGINSY] = 0;
		symNeed[READSY] = 0;
		symNeed[WRITESY] = 0;
		symNeed[FORSY] = 0;
		
		gen("T", UEQ, ctab[i]->des, ctab[ctabtop-1]->des);
		if(symbol == COLOSY){
			getsym();
		}else{
			error();
			printf("need a colon:\n");
			while(symNeed[symbol] != 1 && symbol != IDSY && symbol != IFSY && symbol != CASESY && symbol != BEGINSY && symbol != READSY && symbol != WRITESY && symbol != FORSY){
				getsym();
			}
		}
		gen(ctab[ctabtop-1]->des, JMP, "-", "-");
		temp = ctabtop-1;
		state();
		gen("-", LAB, "L", "-");
		ctab[temp]->fir = ctab[ctabtop-1]->fir;
		#ifdef DEBUG
			printf("This is a case element.\n");
		#endif
	}

	void actParaList(int i){
		int last = btab[i]->lastpar;
		int num = batb[i]->psize;
		int type = 0;
		if(symbol == LPASY){
			getsym();

			symNeed[COMMASY] = 1;
			symNeed[LPASY] = 1;
			type = expression();
			if(num > 0 && tab[last-num+1]->typ == CHARSY){
				if(type == 0){
					error();
					printf("参数类型错误\n");
				}else{
					gen(tab[las-num+1]->name, PLUS, ctab[tabtop-1]->des, "0");
				}
			}else{
				if(type == 1){
					error();
					printf("参数类型错误\n");
				}else{
					gen(tab[las-num+1]->name, PLUS, ctab[tabtop-1]->des, "0");
				}
			}
			num--;
			symNeed[COMMASY] = 0;
			symNeed[LPASY] = 0;

			while(symbol == COMMASY){
				getsym();
				symNeed[COMMASY] = 1;
				symNeed[LPASY] = 1;
				type = expression();
				if(num > 0 && tab[last-num+1]->typ == CHARSY){
					if(type == 0){
						error();
						printf("参数类型错误\n");
					}else{
						gen(tab[las-num+1]->name, PLUS, ctab[tabtop-1]->des, "0");
					}
				}else{
					if(type == 1){
						error();
						printf("参数类型错误\n");
					}else{
						gen(tab[las-num+1]->name, PLUS, ctab[tabtop-1]->des, "0");
					}
				}
				num--;
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

	int term(){
		int rst = 0;
		int flag = 0;
		char[al] temp;
		symNeed[STARSY] = 1;
		symNeed[DIVISY] = 1;
		rst += factor();
		symNeed[STARSY] = 0;
		symNeed[DIVISY] = 0;
		strcpy(temp, ctab[ctabtop-1]->des);

		while(symbol == STARSY || symbol == DIVISY){
			if(symbol == STARSY){
				flag = 1;
			}
			getsym();
			symNeed[STARSY] = 1;
			symNeed[DIVISY] = 1;
			rst += factor();
			symNeed[STARSY] = 0;
			symNeed[DIVISY] = 0;
			gen("T", STAR, temp, ctab[ctabtop-1]->des);
		}

		#ifdef DEBUG
			printf("This is a term.\n");
		#endif
		return rst;
	}

	int factor(){
		int rst = 0;
		char[al] temp;
		if(symbol == INTSY){
			itoa(num, temp, al);
			gen("T", LI, temp, "-");
			getsym();
		}else if(symbol == LPASY){
			symNeed[RPASY] = 1;
			rst += expression();
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
		}else if(tab[tabfind(token)]->typ == ARRAYSY){
			if(atab[tab[tabfind(token)->ref]]->typ == CHARSY){
				rst = 1;
			}
			strcpy(temp, tab[tabfind(token)]->name);
			getsym();
			if(symbol == LBRACSY){
				symNeed[RBRACSY] = 1;
				expression();
				symNeed[RBRACSY] = 0;
				
				gen("T", ARR, temp, ctab[ctabtop-1]->des);
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
				error();
				printf("未定义的变量\n");
				while(symNeed[symbol] != 1){
					getsym();
				}
			}
		}else if(tab[tabfind(token)]->obj == FUCTION){
			rst += funCall();
		}else{
			
		}
		#ifdef DEBUG
			printf("This is a factor.\n");
		#endif
	}

	int funcCall(){
		int rst;
		int i = 0;
		int temp;
		if(symbol == IDSY){
			i = tabfind(token);
			if(tab[i]->obj == FUNCTION){
				if(tab[i]->typ == CHARSY){
					rst = 1;
				}
				getsym();
				if(symbol == LPASY){
					actParaList(tab[i]->ref);
				}
				
				gen("T", CALL, token, "-");
			}else{
				error();
				printf("未定义的函数名\n");
			}
		}
		#ifdef DEBUG
			printf("This is a function call.\n");
		#endif
		return rst;
	}

	
	tablink(levtop, btab[lev-1]->psize);
	levtop += btab[lev-1]->psize;
	adr += btab[lev-1]->psize;
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
	btab[lev-1]->last = tabtop-1;
	btab[lev-1]->vsize = tabtop-(1+batb[lev-1]->lastpar);
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
		subPro(lev++, levtop, 0);
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
		subPro(lev++);
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

int tabtest(int lev, char * name){//查符号表检查重复定义
	int top = tabtop;
	int levnow = lev;
	for(;top > 0 && lev == levnow; top--){
		if(strcmp(tab[top]->name, name) == 0){
			return top;
		}
	}
	return 0;
}
void tabtype(_SYMBOL symbol, int ternnum){//批量填充类型
	int top = tabtop-1;
	for(; tabtop - top <= termnum; top--){
		tab[top]->obj = symbol;
	}
}
void tabadr(int adrtop, int num, int termnum){
	int top = tabtop-1;
	for(; tabtop - top <= termnum; top--){
		tab[top]->adr = adrtop;
		adrtop += num;
	}
}
void tabref(int atabtop, int termnum){
	int top = tabtop-1;
	for(; tabtop - top <= termnum; top--){
		tab[top]->ref = adrtop;
		adrtop += num;
	}
}
void tablink(int levtop, int termnum){
	int top = tabtop-(1+termnum);
	int lev = levtop;
	for(; top < tabtop; top++){
		tab[top]->link = lev++;
	}
}
int tabfind(char * name){
	int top = tabtop;
	while(top > 0){
		if(strcmp(tab[top]->name, name) == 0){
			return top;
		}else{
			top = tab[top]->link;
		}
	}
	return 0;
}
void gen(char * des, _OP opt, char * fir, char * sec){
	char[al] temp0;
	char[al] temp1;
	temp0[0] = 'T';
	temp0[1] = '\0';
	if(strcmp(des, "T") == 0){
		itoa(Tnum, temp1, al);
		Tnum++;
		strcat(temp0, temp1);
		strcpy(ctabnow->des, temp0);
	}
	ctabnow->opt = opt;
	strcpy(ctabnow->fir, fir);
	strcpy(ctabnow->sec, sec);
	if(strcmp(fir, "L") == 0){
		temp0[0] = 'L';
		temp0[1] = '\0';
		itoa(Label, temp1, al);
		strcat(temp0, temp1);
		strcpy(ctabnow->fir, temp0);
	}
	ctab[ctabtop++] = ctabnow;
}
void list(){
	FIFE * OUT;
	int i = 0;
	char[al] temp;
	OUT = fopen("pcode.txt", "w");
	while(i < ctabtop){
		switch(ctab[i]->opt){
			case PLUS: strcpy(temp, "PLUS");break;
			case MINUS: strcpy(temp, "MINUS");break;
			case STAR: strcpy(temp, "STAR");break;
			case DIVI: strcpy(temp, "DIVI");break;
			case EQU : strcpy(temp, "EQU");break; 
			case UNE : strcpy(temp, "UNE");break; 
			case GTH : strcpy(temp, "GTH");break;
			case LTH : strcpy(temp, "LTH");break;
			case GEQ : strcpy(temp, "GEQ");break;
			case LEQ : strcpy(temp, "LEQ");break;
			case LOD : strcpy(temp, "LOD");break;
			case CALL : strcpy(temp, "CALL");break; 
			case STO : strcpy(temp, "STO");break;
			case LAB : strcpy(temp, "LAB");break; 
			case LI : strcpy(temp, "LI");break;
			case ARR : strcpy(temp, "ARR");break;
			case JMP : strcpy(temp, "JMP");break;
			case RED : strcpy(temp, "RED");break;
			case WRI : strcpy(temp, "WRI");break;
			default : strcpy(temp, "-");break;
		}
		fprintf(OUT, "%s\t%s\t%s\t%s\n", ctab[i]->des, temp, ctab[i]->fir, ctab[i]->sec);
	}
}
void constant(){
	char[al] label;
	if(symbol == PLUSSY){
		getsym();
		if(symbol == INTSY){
			itoa(num, label);
			gen("T", LI, label, "-");
			getsym();
		}else{
			error();
			printf("need an int or a char.\n");
			while(symNeed[symbol] != 1){
				getsym();
			}
		}
	}else if(symbol == MINUSSY){
		getsym();
		if(symbol == INTSY){
			itoa(num, label);
			gen("T", LI, label, "-");
			gen(ctab[ctabtop-1]->des, MINUS, "0", label);
			getsym();
		}else{
			error();
			printf("need an int or a char.\n");
			while(symNeed[symbol] != 1){
				getsym();
			}
		}
	}else if(symbol == CHARSY){
		itoa(cha, label);
		gen("T", LI, label, "-");
		getsym();
    }else{
        error();
		printf("need an int or a char.\n");
        while(symNeed[symbol] != 1){
            getsym();
        }
	}
}

