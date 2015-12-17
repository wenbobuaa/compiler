#include "function.h"
#include "variable.h"

void grammar(){
	tabtop = 0;
	atabtop = 0;
	btabtop = 0;
	ctabtop = 0;
	termnum = 0;
	strcpy(btabnow.name, "begin");
	btabnow.last = -1;
	btabnow.lastpar = -1;
	btabnow.psize = 0;
	btabnow.adr = 0;
	btabnow.vsize = 0;
	btab[btabtop++] = btabnow;
	getsym();
	procedure();
	list_();
}

void procedure(){
    char temp[al];
    strcpy(temp, "begin");
    gen(1, 0, "-", JMP, temp, "-");
	symNeed[PERISY] = 1;
	subPro(1, -1, 2);
	symNeed[PERISY] = 0;
	if(isPeri()){
		//printf("finished.\n");
	}else{
		error(-1);
		printf("need peri.");
	}
	#ifdef DEBUG
		printf("This is a procedure.\n");
	#endif
}

void subPro(int lev, int levtop, int adr){
    int btablev = btabtop-1;
	tablink(btab[btabtop-1].adr, btab[btabtop-1].psize);
	levtop = tabtop-1;
	adr += btab[btabtop-1].psize;
	int topnow = 0;
	int num = 0;
	int lastb = 0;//最后一个款子函数的位置
	int lastbtop = 0;
	if(symbol == CONSTSY){//常量说明部分
		symNeed[VARSY] = 1;
		symNeed[PROCSY] = 1;
		symNeed[FUNCSY] = 1;
		symNeed[BEGINSY] = 1;

		getsym();

		symNeed[COMMASY] = 1;
		symNeed[SEMISY] = 1;
		constDef(lev, levtop);
		levtop++;
		symNeed[COMMASY] = 0;
		symNeed[SEMISY] = 0;

		while(symbol == COMMASY){
			getsym();

			symNeed[COMMASY] = 1;
			symNeed[SEMISY] = 1;
			constDef(lev, levtop);
			levtop++;
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

        topnow = tabtop-1;
		symNeed[SEMISY] = 1;
		symNeed[IDSY] = 1;
		varDef(lev, levtop, &adr);
		symNeed[SEMISY] = 0;
		symNeed[IDSY] = 0;
        levtop = levtop + tabtop - 1 - topnow;

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
            topnow = tabtop - 1;
			symNeed[SEMISY] = 1;
			symNeed[IDSY] = 1;
			varDef(lev, levtop, &adr);
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
            levtop = levtop + tabtop - 1 - topnow;

		}
		symNeed[PROCSY] = 0;
		symNeed[FUNCSY] = 0;
		symNeed[BEGINSY] = 0;
		#ifdef DEBUG
			printf("This is a variable statement.\n");
		#endif
	}

	btab[btabtop-1].last = tabtop-1;
	btab[btabtop-1].vsize = adr-2-btab[btabtop-1].psize;
    lastbtop = btabtop-1;
    lastb = tabtop-1;
	if(symbol == PROCSY){//过程说明部分
		symNeed[FUNCSY] = 1;
		symNeed[BEGINSY] = 1;

		symNeed[CONSTSY] = 1;
		symNeed[VARSY] = 1;
		symNeed[PROCSY] = 1;
		symNeed[FUNCSY] = 1;
		symNeed[BEGINSY] = 1;
		proHead(lev, levtop);
		lastb = tabtop-1;
		levtop = btab[btabtop-1].adr;
		symNeed[CONSTSY] = 0;
		symNeed[VARSY] = 0;
		symNeed[PROCSY] = 0;
		symNeed[FUNCSY] = 0;
		symNeed[BEGINSY] = 0;

		symNeed[SEMISY] = 1;
		subPro(lev+1, levtop, 2);
		symNeed[SEMISY] = 0;

        gen(lev, btablev, "-", RETP, "-", "-");

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

			proHead(lev, levtop);
			lastb = tabtop-1;
			levtop = btab[btabtop-1].adr;
			symNeed[CONSTSY] = 0;
			symNeed[VARSY] = 0;
			symNeed[PROCSY] = 0;
			symNeed[FUNCSY] = 0;
			symNeed[BEGINSY] = 0;

			symNeed[SEMISY] = 1;
			subPro(lev+1, levtop, 2);
			symNeed[SEMISY] = 0;

            gen(lev, btablev, "-", RETP, "-", "-");

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
		funcHead(lev, levtop);
		lastb = tabtop-1;
		levtop = btab[btabtop-1].adr;
		symNeed[CONSTSY] = 0;
		symNeed[VARSY] = 0;
		symNeed[PROCSY] = 0;
		symNeed[FUNCSY] = 0;
		symNeed[BEGINSY] = 0;

		symNeed[SEMISY] = 1;
		subPro(lev+1, levtop, 2);
		symNeed[SEMISY] = 0;

        gen(lev, btablev, "-", RETF, "-", "-");

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
			funcHead(lev, levtop);
			lastb = tabtop-1;
			levtop = btab[btabtop-1].adr;
			symNeed[CONSTSY] = 0;
			symNeed[VARSY] = 0;
			symNeed[PROCSY] = 0;
			symNeed[FUNCSY] = 0;
			symNeed[BEGINSY] = 0;

			symNeed[SEMISY] = 1;
			subPro(lev+1, levtop, 2);
			symNeed[SEMISY] = 0;

            gen(lev, btablev, "-", RETF, "-", "-");

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


	gen(lev, btablev, "-", LAB, btab[btablev].name, "-");
	comState(btablev, lev, levtop, adr);
	#ifdef DEBUG
		printf("This is a subProcedrue.\n");
	#endif
}

 _SYMBOL baseType(int lev, int levtop){
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

    void constAnaly(int lev, int levtop){
        int flag = 0;
		if(symbol == PLUSSY){
			getsym();
		}else if(symbol == MINUSSY){
		    flag = 1;
			getsym();
		}
		if(symbol == INTSY){
            if(flag == 1){
                tabnow.adr = -1*num;
            }else{
                tabnow.adr = num;
            }
            tabnow.typ = INTEGER;
            getsym();
        }else if(symbol == CHARSY){
            tabnow.adr = cha;
			tabnow.typ = CHARACTER;
			getsym();
		}else{
			error();
			tabnow.adr = 0;
			tabnow.typ = INTSY;
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

	void constDef(int lev, int levtop){
		if(symbol == IDSY && tabtest(lev, token) == -1){
			strcpy(tabnow.name, token);
			tabnow.obj = CONST;
			tabnow.lev = lev;
			tabnow.normal = nul;
			tabnow.link = levtop++;
			tabnow.ref = 0;

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
			constAnaly(lev, levtop);
		}else{
			error();
			printf("id is wrong or has been decleared.\n");
			while(symNeed[symbol] != 1){
				getsym();
			}
		}
		#ifdef DEBUG
			printf("This is a constant define.\n");
		#endif
	}

    void Type(int lev, int levtop, int * adr){
		if(symbol == ARRAYSY){
			tabtype(ARRAYSY, termnum);
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
				atabnow.high = num;
				tabadr(adr, num, termnum);
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
				atabnow.typ = baseType(lev, levtop);
				atab[atabtop++] = atabnow;
			}else{
				error();
				printf("need a int number.\n");
				while(symNeed[symbol] != 1){
					getsym();
				}
				atabnow.high = 1;
				tabadr(adr, 1, termnum);
			}
		}else{
			tabtype(baseType(lev, levtop), termnum);
			tabadr(adr, 1, termnum);
		}
		#ifdef DEBUG
			printf("This is a type statement.\n");
		#endif
	}

	void varDef(int lev, int levtop, int * adr){
		termnum = 0;
		if(symbol == IDSY){
			strcpy(tabnow.name, token);
			tabnow.obj = VAR;
			tabnow.lev = lev;
			tabnow.normal = nul;
			tabnow.link = levtop++;
			tabnow.ref = 0;
			tab[tabtop++] = tabnow;
			termnum++;

			getsym();
			while(symbol == COMMASY){
				getsym();
				if(symbol == IDSY){
					strcpy(tabnow.name, token);
					tabnow.obj = VAR;
					tabnow.lev = lev;
					tabnow.normal = nul;
					tabnow.link = levtop++;
					tabnow.ref = 0;
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
			Type(lev, levtop, adr);
		}else{
			error();
			printf("a wrong id or id has been decleared.\n");
			while(symNeed[symbol] != 1){
				getsym();
			}
		}
		#ifdef DEBUG
			printf("This is a variable define.\n");
		#endif
	}

    void formParaSeg(int lev, int levtop, int * adr){
		int flag = 0;
		termnum = 0;
		if(symbol == VARSY){
			flag = 1;
			getsym();
		}
		if(symbol == IDSY){
			strcpy(tabnow.name, token);
			tabnow.obj = VAR;
			tabnow.ref = nul;
			tabnow.lev = lev+1;
			tabnow.link = levtop++;
			if(flag){
				tabnow.normal = TRUE;
			}else{
				tabnow.normal = FALSE;
			}
			tab[tabtop++] = tabnow;
			termnum++;

			getsym();
			while(symbol == COMMASY){
				getsym();
				if(symbol == IDSY){
					strcpy(tabnow.name, token);
					tabnow.obj = VAR;
					tabnow.ref = nul;
					tabnow.lev = lev+1;
					tabnow.link = levtop++;
					if(flag){
						tabnow.normal = TRUE;
					}else{
						tabnow.normal = FALSE;
					}
					tab[tabtop++] = tabnow;
					termnum++;

					getsym();
				}else{
					error();
					printf("id is wrong or has been decleared.\n");
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
			tabtype(baseType(lev, levtop), termnum);
			tabadr(adr, 1, termnum);
			btab[btabtop-1].psize += termnum;
			btab[btabtop-1].lastpar = tabtop-1;
		}else{
			error();
			printf("id is wrong or has been decleared.\n");
			while(symNeed[symbol] != 1){
				getsym();
			}
		}
		#ifdef DEBUG
			printf("This is a formal parameter segment.\n");
		#endif
	}

    void formParaList(int lev, int levtop){
        int now = 0;
        int adr = 2;
		if(symbol == LPASY){
			getsym();
            now = tabtop - 1;
			symNeed[SEMISY] = 1;
			symNeed[RPASY] = 1;
			formParaSeg(lev, levtop, &adr);
			symNeed[SEMISY] = 0;
			symNeed[RPASY] = 0;
            levtop = levtop + tabtop - 1 - now;

			while(symbol == SEMISY){
				getsym();
				now = tabtop - 1;
				symNeed[SEMISY] = 1;
				symNeed[RPASY] = 1;
				formParaSeg(lev, levtop, &adr);
				symNeed[SEMISY] = 0;
				symNeed[RPASY] = 0;
				levtop = levtop - 1 - now;
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

	void proHead(int lev, int levtop){
		if(symbol == PROCSY){
			getsym();
			if(symbol == IDSY && tabtest(lev, token) == -1){
				strcpy(tabnow.name, token);
				tabnow.obj = PROCEDURE;
				tabnow.typ = nul;
				tabnow.ref = btabtop;
				tabnow.lev = lev;
				tabnow.normal = nul;
				tabnow.adr = 1;
				tabnow.link = levtop++;
				tab[tabtop++] = tabnow;
				strcpy(btabnow.name, token);
				btabnow.last = -1;
				btabnow.lastpar = tabtop-1;
				btabnow.psize = 0;
				btabnow.vsize = 0;
				btabnow.adr = tabtop-1;
				btabnow.code = ctabtop;
				btab[btabtop++] = btabnow;

				getsym();
				if(symbol == LPASY){
					symNeed[SEMISY] = 1;
					formParaList(lev, tabtop-1);
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
				printf("id is wrong or has been decleared.\n");
				while(symNeed[symbol] != 1){
					getsym();
				}
			}
		}
		#ifdef DEBUG
			printf("This is a procedure head.\n");
		#endif
	}

	void funcHead(int lev, int levtop){
		if(symbol == FUNCSY){
			getsym();
			if(symbol == IDSY && tabtest(lev, token) == -1){
				strcpy(tabnow.name, token);
				tabnow.obj = FUNCTION;
				tabnow.ref = btabtop;
				tabnow.lev = lev;
				tabnow.normal = nul;
				tabnow.adr = 1;
				tabnow.link = levtop++;
				tab[tabtop++] = tabnow;
				strcpy(btabnow.name, token);
				btabnow.last = -1;
				btabnow.lastpar = tabtop-1;
				btabnow.psize = 0;
				btabnow.vsize = 0;
				btabnow.adr = tabtop-1;
				btabnow.code = ctabtop;
				btab[btabtop++] = btabnow;

				getsym();
				if(symbol == LPASY){
					symNeed[symbol] = 1;
					formParaList(lev, tabtop-1);
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
				tab[btab[btabtop-1].adr].typ = baseType(lev, levtop);
				symNeed[SEMISY] = 0;

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
				printf("id is wrong or has been decleared.\n");
				while(symNeed[symbol] != 1){
					getsym();
				}
			}
		}
		#ifdef DEBUG
			printf("This is a function head.\n");
		#endif
	}

    int expression(int btablev, int lev, int levtop, int adr){
		int rst = 0;
		int flag = 0;
		char temp [al];
		if(symbol == PLUSSY || symbol == MINUSSY){
			if(symbol == MINUSSY){
				flag = 1;
			}
			getsym();
		}
		symNeed[PLUSSY] = 1;
		symNeed[MINUSSY] = 1;
		rst = rst + term(btablev, lev, levtop, adr);
		symNeed[PLUSSY] = 0;
		symNeed[MINUSSY] = 0;
		if(ctab[ctabtop-1].opt == ARRA){
            gen(lev, btablev, "T", LOD, ctab[ctabtop-1].des, "0");
        }
		if(flag){
            flag = 0;
			gen(lev, btablev, ctab[ctabtop-1].des, MINUS, "0", ctab[ctabtop-1].des);
		}
		strcpy(temp, ctab[ctabtop-1].des);
		while(symbol == PLUSSY || symbol == MINUSSY){
            if(ctab[ctabtop-1].opt == ARRA){
                gen(lev, btablev, "T", LOD, ctab[ctabtop-1].des, "0");
                strcpy(temp, ctab[ctabtop-1].des);
            }
			if(symbol == PLUSSY){
				flag = 2;
			}
			getsym();
			symNeed[PLUSSY] = 1;
			symNeed[MINUSSY] = 1;
			rst = rst + term(btablev, lev, levtop, adr);
			symNeed[PLUSSY] = 0;
			symNeed[MINUSSY] = 0;
			if(ctab[ctabtop-1].opt == ARRA){
                gen(lev, btablev, "T", LOD, ctab[ctabtop-1].des, "0");
            }
			if(flag == 2){
			    flag = 0;
				gen(lev, btablev, "T", PLUS, temp, ctab[ctabtop-1].des);
			}else{
				gen(lev, btablev, "T", MINUS, temp, ctab[ctabtop-1].des);
			}
            strcpy(temp, ctab[ctabtop-1].des);
		}
		#ifdef DEBUG
			printf("This is a expression.\n");
		#endif
		return rst;
	}

    void condition(int btablev, int lev, int levtop, int adr){
		int temp = 0;
		symNeed[EQUSY] = 1;
		symNeed[LESSSY] = 1;
		symNeed[GREATSY] = 1;
		symNeed[LEQSY] = 1;
		symNeed[GEQSY] = 1;
		symNeed[UNEQUSY] = 1;
		expression(btablev, lev, levtop, adr);
		symNeed[EQUSY] = 0;
		symNeed[LESSSY] = 0;
		symNeed[GREATSY] = 0;
		symNeed[LEQSY] = 0;
		symNeed[GEQSY] = 0;
		symNeed[UNEQUSY] = 0;

		temp = ctabtop-1;
		if(symbol == EQUSY){
			getsym();
			expression(btablev, lev, levtop, adr);
			gen(lev, btablev, "-", UNE, ctab[temp].des, ctab[ctabtop-1].des);
		}else if(symbol == LESSSY){
			getsym();
			expression(btablev, lev, levtop, adr);
			gen(lev, btablev, "-", GEQ, ctab[temp].des, ctab[ctabtop-1].des);
		}else if(symbol == GREATSY){
			getsym();
			expression(btablev, lev, levtop, adr);
			gen(lev, btablev, "-", LEQ, ctab[temp].des, ctab[ctabtop-1].des);
		}else if(symbol == LEQSY){
			getsym();
			expression(btablev, lev, levtop, adr);
			gen(lev, btablev, "-", GTH, ctab[temp].des, ctab[ctabtop-1].des);
		}else if(symbol == GEQSY){
			getsym();
			expression(btablev, lev, levtop, adr);
			gen(lev, btablev, "-", LTH, ctab[temp].des, ctab[ctabtop-1].des);
		}else if(symbol == UNEQUSY){
			getsym();
			expression(btablev, lev, levtop, adr);
			gen(lev, btablev, "-", EQU, ctab[temp].des, ctab[ctabtop-1].des);
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

    void conditionState(int btablev, int lev, int levtop, int adr){
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
			condition(btablev, lev, levtop, adr);
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
			temp = ctabtop-1;

			symNeed[symbol] = 1;
			state(btablev, lev, levtop, adr);
			symNeed[symbol] = 0;

			gen(lev, btablev, "-", JMP, "-", "-");
			gen(lev, btablev, "-", LAB, "L", "-");
			strcpy(ctab[temp].des, ctab[ctabtop-1].fir);
			temp = ctabtop-2;
			if(symbol == ELSESY){
				getsym();
				symNeed[symbol] = 1;
				state(btablev, lev, levtop, adr);
				symNeed[symbol] = 0;
			}
			gen(lev, btablev, "-", LAB, "L", "-");
			strcpy(ctab[temp].fir, ctab[ctabtop-1].fir);
		}else{

		}
		#ifdef DEBUG
			printf("This is a condition statement.\n");
		#endif
	}

    void state(int btablev, int lev, int levtop, int adr){
		int i = 0;
		if(symbol == IFSY){
			conditionState(btablev, lev, levtop, adr);
		}else if(symbol == CASESY){
			caseState(btablev, lev, levtop, adr);
		}else if(symbol == BEGINSY){
			comState(btablev, lev, levtop, adr);
		}else if(symbol == READSY){
			readState(btablev, lev, levtop, adr);
		}else if(symbol == WRITESY){
			writeState(btablev, lev, levtop, adr);
		}else if(symbol == FORSY){
			loop(btablev, lev, levtop, adr);
		}else if(symbol == IDSY){
			i = tabfind(token, levtop);
			if(i == -1){
				error(-1);
				printf("id is not decleared.\n");
			}else{
				if(tab[i].obj == VAR || tab[i].obj == FUNCTION){
					assignment(btablev, i, lev, levtop, adr);
				}else if(tab[i].obj == PROCEDURE){
					proCall(btablev, i, lev, levtop, adr);
				}else{
					error(-1);
					printf("constent cannot been changed.\n");
				}
			}
		}else{

		}
		#ifdef DEBUG
			printf("This is a statement.\n");
		#endif
	}

	void comState(int btablev, int lev, int levtop, int adr){
		if(symbol == BEGINSY){
			getsym();

			symNeed[SEMISY] = 1;
			symNeed[ENDSY] = 1;
			state(btablev, lev, levtop, adr);
			symNeed[SEMISY] = 0;
			symNeed[ENDSY] = 0;

			while(symbol == SEMISY){
				getsym();
				symNeed[SEMISY] = 1;
				symNeed[ENDSY] = 1;
				state(btablev, lev, levtop, adr);
				symNeed[SEMISY] = 0;
				symNeed[ENDSY] = 0;
			}

			if(symbol == ENDSY){
				getsym();
			}else{
				error(-1);
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

	void assignment(int btablev, int i, int lev, int levtop, int adr){
		int type = 0;
		int temp = 0;
		getsym();
		if(symbol == BECOMESY){
			getsym();
			type = expression(btablev, lev, levtop, adr);
			if(tab[i].typ == INTEGER){
				gen(lev, btablev, tab[i].name, PLUS, ctab[ctabtop-1].des, "0");
			}else if(tab[i].typ == CHARACTER && type == 0){
				gen(lev, btablev, tab[i].name, PLUS, ctab[ctabtop-1].des, "0");
			}else{
				error(-1);
				printf("type is wrong.\n");
			}
		}else if(symbol == LBRACSY){
			getsym();
			expression(btablev, lev, levtop, adr);
			gen(lev, btablev, "T", ARRA, tab[i].name, ctab[ctabtop-1].des);
			temp = ctabtop-1;
			if(symbol == RBRACSY){
				getsym();
			}else{
				error(-1);
				printf("need a right bracket].\n");
				while(symNeed[symbol] != 1 && symbol != BECOMESY){
					getsym();
				}
			}
			if(symbol == BECOMESY){
				getsym();
			}else{
				error(-1);
				printf("need a become:=\n");
				while(symNeed[symbol] != 1 && symbol != PLUSSY && symbol != MINUSSY && symbol != IDSY){
					getsym();
				}
			}
			expression(btablev, lev, levtop, adr);
			gen(lev, btablev, "-", STO, ctab[temp].des, ctab[ctabtop-1].des);
		}else{

		}
		#ifdef DEBUG
			printf("This is a assignment statement.\n");
		#endif
	}

	void caseState(int btablev, int lev, int levtop, int adr){
		int temp = 0;
		if(symbol == CASESY){
			getsym();
			symNeed[OFSY] = 1;
			symNeed[PLUSSY] = 1;
			symNeed[MINUSSY] = 1;
			symNeed[INTSY] = 1;
			symNeed[CHARSY] = 1;
			expression(btablev, lev, levtop, adr);
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
			caseelement(btablev, temp, lev, levtop, adr);
			symNeed[SEMISY] = 0;
			symNeed[ENDSY] = 0;

			while(symbol == SEMISY){
				getsym();
				symNeed[SEMISY] = 1;
				symNeed[ENDSY] = 1;
				caseelement(btablev, temp, lev, levtop, adr);
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

	void proCall(int btablev, int i, int lev, int levtop, int adr){
        char temp[al];
        gen(lev, btablev, "-", SAVR, "-", "-");
		getsym();
		itoa(btab[tab[i].ref].psize, temp, 10);
		if(symbol == LPASY){
			actParaList(btablev, tab[i].ref, lev, levtop, adr);
			gen(btablev, tab[i].ref, "-", CALLP, tab[i].name, temp);
		}else{
			gen(btablev, tab[i].ref, "-", CALLP, tab[i].name, temp);
		}
		#ifdef DEBUG
			printf("This is a procedure call statement.\n");
		#endif
	}

	void readState(int btablev, int lev, int levtop, int adr){
	    int i = 0;
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
                i = tabfind(token, levtop);
				if( i != -1){
                    if(tab[i].typ == INTEGER){
                        gen(lev, btablev, token, REDI, "-", "-");
                    }else{
                        gen(lev, btablev, token, REDC, "-", "-");
                    }
				}else{
					error(-1);
					printf("id is not decleared.\n");
				}
				getsym();
				while(symbol == COMMASY){
					getsym();
					if(symbol == IDSY){
                        i = tabfind(token, levtop);
						if( i != -1){
							if(tab[i].typ == INTEGER){
                                gen(lev, btablev, token, REDI, "-", "-");
                            }else{
                                gen(lev, btablev, token, REDC, "-", "-");
                            }
						}else{
							error(-1);
							printf("id is not decleared.\n");
						}
						getsym();
					}else{
						error(-1);
						printf("need a id.\n");
						while(symNeed[symbol] != 1 && symbol != COMMASY && symbol != RPASY){
							getsym();
						}
					}
				}
				if(symbol == RPASY){
					getsym();
				}else{
					error(-1);
					printf("need a right parenthsis.\n");
					while(symNeed[symbol] != 1){
						getsym();
					}
				}
			}else{
				error(-1);
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

	void writeState(int btablev, int lev, int levtop, int adr){
	    int i = 0;
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
				gen(lev, btablev, "-", WRIS, str, "-");
				getsym();
				if(symbol == COMMASY){
					getsym();
					symNeed[RPASY] = 1;
					i = expression(btablev, lev, levtop, adr);
					symNeed[RPASY] = 0;
					if(i > 0){
                        gen(lev, btablev, "-", WRII, ctab[ctabtop-1].des, "-");
					}else{
                        gen(lev, btablev, "-", WRIC, ctab[ctabtop-1].des, "-");
					}
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
				i = expression(btablev, lev, levtop, adr);
				symNeed[RPASY] = 0;
				if(i > 0){
                    gen(lev, btablev, "-", WRII, ctab[ctabtop-1].des, "-");
                }else{
                    gen(lev, btablev, "-", WRIC, ctab[ctabtop-1].des, "-");
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
			}
		}else{

		}
		#ifdef DEBUG
			printf("This is a write statement.\n");
		#endif
	}

	void loop(int btablev, int lev, int levtop, int adr){
		int temp = 0;
		int label = 0;
		int flag = 0;
		char tokentemp[al];
		if(symbol == FORSY){
			getsym();
			if(symbol == IDSY){
				strcpy(tokentemp, token);
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
				expression(btablev, lev, levtop, adr);
				symNeed[DOWNTO] = 0;
				symNeed[TOSY] = 0;

				gen(lev, btablev, tokentemp, PLUS, ctab[ctabtop-1].des, "0");
				temp = ctabtop-1;

				if(symbol == DOWNTO){
					gen(lev, btablev, ctab[temp].des, PLUS, ctab[temp].des, "1");
					gen(lev, btablev, "-", LAB, "L", "-");
					label = ctabtop-1;
					gen(lev, btablev, ctab[temp].des, MINUS, ctab[temp].des, "1");
					temp = ctabtop-1;
					flag = 1;
					getsym();
				}else if(symbol == TOSY){
					gen(lev, btablev, ctab[temp].des, MINUS, ctab[temp].des, "1");
					gen(lev, btablev, "-", LAB, "L", "-");
					label = ctabtop-1;
					gen(lev, btablev, ctab[temp].des, PLUS, ctab[temp].des, "1");
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
				expression(btablev, lev, levtop, adr);
				symNeed[DOSY] = 0;

				if(flag){
					gen(lev, btablev, "-", LTH, ctab[temp].des, ctab[ctabtop-1].des);
				}else{
					gen(lev, btablev, "-", GTH, ctab[temp].des, ctab[ctabtop-1].des);
				}

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

				state(btablev, lev, levtop, adr);
				gen(lev, btablev, "-", JMP, ctab[label].fir, "-");
				gen(lev, btablev, "-", LAB, "L", "-");
				strcpy(ctab[temp].des, ctab[ctabtop-1].fir);
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

	void caseelement(int btablev, int i, int lev, int levtop, int adr){
		int temp = 0;

		symNeed[COLOSY] = 1;
		symNeed[IDSY] = 1;
		symNeed[IFSY] = 1;
		symNeed[CASESY] = 1;
		symNeed[BEGINSY] = 1;
		symNeed[READSY] = 1;
		symNeed[WRITESY] = 1;
		symNeed[FORSY] = 1;
		constant(lev, btablev);
		symNeed[COLOSY] = 0;
		symNeed[IDSY] = 0;
		symNeed[IFSY] = 0;
		symNeed[CASESY] = 0;
		symNeed[BEGINSY] = 0;
		symNeed[READSY] = 0;
		symNeed[WRITESY] = 0;
		symNeed[FORSY] = 0;

		gen(lev, btablev, "-", UNE, ctab[i].des, ctab[ctabtop-1].des);
		if(symbol == COLOSY){
			getsym();
		}else{
			error();
			printf("need a colon:\n");
			while(symNeed[symbol] != 1 && symbol != IDSY && symbol != IFSY && symbol != CASESY && symbol != BEGINSY && symbol != READSY && symbol != WRITESY && symbol != FORSY){
				getsym();
			}
		}
		temp = ctabtop-1;
		state(btablev, lev, levtop, adr);
		gen(lev, btablev, "-", LAB, "L", "-");
		strcpy(ctab[temp].des, ctab[ctabtop-1].fir);
		#ifdef DEBUG
			printf("This is a case element.\n");
		#endif
	}

	void actParaList(int btablev, int i, int lev, int levtop, int adr){
		int last = btab[i].lastpar;
		int num = btab[i].psize;
		int type = 0;
		char temp[al];
		if(num > 4){
            error(-1);
            printf("too many para\n");
		}
		if(symbol == LPASY){
			getsym();

			symNeed[COMMASY] = 1;
			symNeed[LPASY] = 1;
			type = expression(btablev, lev, levtop, adr);
			if(num > 0 && tab[last-num+1].typ == CHARACTER){
				if(type > 0){
					error();
					printf("type is wrong.\n");
				}else{
				    itoa(btab[i].psize-num, temp, 10);
                    if(tab[last-num+1].normal == TRUE){
                        if(ctab[ctabtop-1].opt == LOD){
                            ctabtop--;
                            gen(lev, btablev, "-", TRAR, ctab[ctabtop].fir, temp);
                        }else{
                            error(-1);
                            printf("need an address.\n");
                        }
                    }else{
                        gen(lev, btablev, "-", TRAV, ctab[ctabtop-1].des, temp);
                    }

				}
			}else if(num > 0 && tab[last-num+1].typ == INTEGER){
				if(type == 0){
					error();
					printf("type is wrong.\n");
				}else{
					itoa(btab[i].psize-num, temp, 10);
                    if(tab[last-num+1].normal == TRUE){
                        if(ctab[ctabtop-1].opt == LOD){
                            ctabtop--;
                            gen(lev, btablev, "-", TRAR, ctab[ctabtop].fir, temp);
                        }else{
                            error(-1);
                            printf("need an address.\n");
                        }
                    }else{
                        gen(lev, btablev, "-", TRAV, ctab[ctabtop-1].des, temp);
                    }
				}
			}else{
                error(-1);
                printf("para number is wrong.\n");
			}
			num--;
			symNeed[COMMASY] = 0;
			symNeed[LPASY] = 0;

			while(symbol == COMMASY){
				getsym();
				symNeed[COMMASY] = 1;
				symNeed[LPASY] = 1;
				type = expression(btablev, lev, levtop, adr);
				if(num > 0 && tab[last-num+1].typ == CHARACTER){
					if(type > 0){
						error();
						printf("type is wrong.\n");
					}else{
						itoa(btab[i].psize-num, temp, 10);
                        if(tab[last-num+1].normal == TRUE){
                            if(ctab[ctabtop-1].opt == LOD){
                                gen(lev, btablev, "-", TRAR, ctab[ctabtop-1].fir, temp);
                            }else{
                                error(-1);
                                printf("need an address.\n");
                            }
                        }else{
                            gen(lev, btablev, "-", TRAV, ctab[ctabtop-1].des, temp);
                        }
					}
				}else if(num > 0 && tab[last-num+1].typ == INTEGER){
                    if(type == 0){
                        error();
                        printf("type is wrong.\n");
                    }else{
                        itoa(btab[i].psize-num, temp, 10);
                        if(tab[last-num+1].normal == TRUE){
                            if(ctab[ctabtop-1].opt == LOD){
                                gen(lev, btablev, "-", TRAR, ctab[ctabtop-1].fir, temp);
                            }else{
                                error(-1);
                                printf("need an address.\n");
                            }
                        }else{
                            gen(lev, btablev, "-", TRAV, ctab[ctabtop-1].des, temp);
                        }
                    }
                }else{
                    error(-1);
                    printf("para number is wrong.\n");
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

	int term(int btablev, int lev, int levtop, int adr){
		int rst = 0;
		int flag = 0;
		char temp[al];
		symNeed[STARSY] = 1;
		symNeed[DIVISY] = 1;
		rst += factor(btablev, lev, levtop, adr);
		symNeed[STARSY] = 0;
		symNeed[DIVISY] = 0;
		strcpy(temp, ctab[ctabtop-1].des);

		while(symbol == STARSY || symbol == DIVISY){
            if(ctab[ctabtop-1].opt == ARRA){
                gen(lev, btablev, "T", LOD, temp, "0");
                strcpy(temp, ctab[ctabtop-1].des);
            }
			if(symbol == STARSY){
				flag = 1;
			}
			getsym();
			symNeed[STARSY] = 1;
			symNeed[DIVISY] = 1;
			rst += factor(btablev, lev, levtop, adr);
			symNeed[STARSY] = 0;
			symNeed[DIVISY] = 0;
			if(ctab[ctabtop-1].opt == ARRA){
                gen(lev, btablev, "T", LOD, ctab[ctabtop-1].des , "0");
            }
			if(flag){
                flag = 0;
                gen(lev, btablev, "T", STAR, temp, ctab[ctabtop-1].des);
			}else{
                gen(lev, btablev, "T", DIVI, temp, ctab[ctabtop-1].des);
            }
            strcpy(temp, ctab[ctabtop-1].des);
		}

		#ifdef DEBUG
			printf("This is a term.\n");
		#endif
		return rst;
	}

	int factor(int btablev, int lev, int levtop, int adr){
	    int i = 0;
		int rst = 0;
		char temp[al];
		if(symbol == INTSY){
			itoa(num, temp, 10);
			gen(lev, btablev, "T", LI, temp, "-");
			getsym();
			rst = 1;
		}else if(symbol == LPASY){
		    getsym();
			symNeed[RPASY] = 1;
			rst = expression(btablev, lev, levtop, adr);
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
		}else if(tab[tabfind(token, levtop)].typ == ARRAYSY){
			if(atab[tab[tabfind(token, levtop)].ref].typ == INTEGER){
				rst = 1;
			}
			strcpy(temp, tab[tabfind(token, levtop)].name);
			getsym();
			if(symbol == LBRACSY){
                getsym();
				symNeed[RBRACSY] = 1;
				expression(btablev, lev, levtop, adr);
				symNeed[RBRACSY] = 0;

				gen(lev, btablev, "T", ARRA, temp, ctab[ctabtop-1].des);
				if(symbol == RBRACSY){
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
				printf("id is not decleared.\n");
				while(symNeed[symbol] != 1){
					getsym();
				}
			}
		}else if(tab[tabfind(token, levtop)].obj == FUNCTION){
			rst = funcCall(btablev, lev, levtop, adr);
		}else if(tabfind(token, levtop) != -1){
            i = tabfind(token, levtop);
            if(tab[i].obj == CONST){
                if(tab[i].typ == INTEGER){
                    rst = 1;
                }
                itoa(tab[i].adr, temp, 10);
                gen(lev, btablev, "T", LI, temp, "-");
            }else{
                if(tab[i].typ == INTEGER){
                    rst = 1;
                }
                gen(lev, btablev, "T", LOD, tab[i].name, "-");
            }
            getsym();
		}else{
            error(-1);
            printf("wrong type.\n");
		}
		#ifdef DEBUG
			printf("This is a factor.\n");
		#endif
		return rst;
	}

	int funcCall(int btablev, int lev, int levtop, int adr){
		int rst = 0;
		int i = 0;
		int temp;
        char func[al];
        char temp1[al];
         gen(lev, btablev, "-", SAVR, "-", "-");
		if(symbol == IDSY){
			i = tabfind(token, levtop);
			if(tab[i].obj == FUNCTION){
                strcpy(func, token);
				if(tab[i].typ == INTEGER){
					rst = 1;
				}
				getsym();
				if(symbol == LPASY){
					actParaList(btablev, tab[i].ref, lev, levtop, adr);
				}
                itoa(btab[tab[i].ref].psize, temp1, 10);
				gen(btablev, tab[i].ref, "T", CALLF, func, temp1);
			}else{
				error();
				printf("function is not decleared.\n");
			}
		}
		#ifdef DEBUG
			printf("This is a function call.\n");
		#endif
		return rst;
	}


int tabtest(int lev, char * name){//查符号表检查重复定义
	int top = tabtop-1;
	int levnow = lev;
	for(;top >= 0 && tab[top].lev == levnow; top--){
		if(strcmp(tab[top].name, name) == 0){
			return top;
		}
	}
	if(top >= 0 && tab[top].lev < levnow && strcmp(tab[top].name, name) == 0){
            //函数和它定义的第一个函数也不能重名
            //函数和它并列的一个函数内定义的最后一个函数也不能重名
        return top;
	}
	return -1;
}
void tabtype(_SYMBOL symbol, int ternnum){//批量填充类型
	int top = tabtop-1;
	for(; tabtop - top <= termnum; top--){
		tab[top].typ = symbol;
	}
}
void tabadr(int * adr, int num, int termnum){
	int top = tabtop-termnum;
	for(; tabtop - top > 0; top++){
		tab[top].adr = *adr;
		*adr += num;
	}
}
void tabref(int atabtop, int termnum){
	int top = tabtop-1;
	for(; tabtop - top <= termnum; top--){
		tab[top].ref = atabtop;
	}
}
void tablink(int levtop, int termnum){
	int top = tabtop-(termnum);
	int lev = levtop;
	for(; top < tabtop; top++){
		tab[top].link = lev++;
	}
}
int tabfind(char * name, int levtop){
	int top = levtop;
	while(top >= 0){
		if(strcmp(tab[top].name, name) == 0){
			return top;
		}else{
			top = tab[top].link;
		}
	}
	return -1;
}
void gen(int lev, int btablev, char * des, _OP opt, char * fir, char * sec){
	char temp0[al];
	char temp1[al];
	temp0[0] = 'T';
	temp0[1] = '\0';
	strcpy(ctabnow.des, des);
    if(strcmp(des, "T") == 0){
		itoa(Tnum, temp1, 10);
		Tnum++;
		strcat(temp0, temp1);
		strcpy(ctabnow.des, temp0);
	}
	ctabnow.opt = opt;
	strcpy(ctabnow.fir, fir);
	strcpy(ctabnow.sec, sec);
	if(strcmp(fir, "L") == 0){
		temp0[0] = 'L';
		temp0[1] = '\0';
		itoa(Label, temp1, 10);
		Label++;
		strcat(temp0, temp1);
		strcpy(ctabnow.fir, temp0);
	}else if(opt == LAB){
	    strcpy(temp1, "B");
        itoa(btablev, temp0, 10);
        strcat(temp1, temp0);
        strcat(fir, temp1);
        strcpy(ctabnow.des, fir);
	}
	ctabnow.ref = btablev;
	ctabnow.lev = lev;
	ctab[ctabtop++] = ctabnow;
}
void list_(){
	FILE * OUT;
	int i = 0;
	char temp[al];
	OUT = fopen("pcode.txt", "w");
	while(i < ctabtop){
		switch(ctab[i].opt){
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
			case CALLP : strcpy(temp, "CALLP");break;
			case CALLF : strcpy(temp, "CALLF");break;
			case STO : strcpy(temp, "STO");break;
			case LAB : strcpy(temp, "LAB");break;
			case LI : strcpy(temp, "LI");break;
			case ARRA : strcpy(temp, "ARRA");break;
			case JMP : strcpy(temp, "JMP");break;
			case REDI : strcpy(temp, "REDI");break;
			case REDC : strcpy(temp, "REDC");break;
			case WRII : strcpy(temp, "WRII");break;
			case WRIC : strcpy(temp, "WRIC");break;
			case WRIS : strcpy(temp, "WRIS");break;
			case TRAV : strcpy(temp, "TRAV");break;
			case TRAR : strcpy(temp, "TRAR");break;
			case RETP : strcpy(temp, "RETP");break;
			case RETF : strcpy(temp, "RETF");break;
			case SAVR : strcpy(temp, "SAVR");break;
			default : strcpy(temp, "-");break;
		}
		fprintf(OUT, "%5s\t%5s\t%5s\t%5s\n", ctab[i].des, temp, ctab[i].fir, ctab[i].sec);
		i++;
	}
	fclose(OUT);
}
void constant(int lev, int btablev){
	char label[al];
	int flag = 0;
	if(symbol == PLUSSY){
		getsym();
	}else if(symbol == MINUSSY){
		getsym();
		flag = 1;
	}
	if(symbol == INTSY){
        itoa(num, label, 10);
        gen(lev, btablev, "T", LI, label, "-");
        if(flag){
            gen(lev, btablev, ctab[ctabtop-1].des, MINUS, "0", label);
        }
        getsym();
    }else if(symbol == CHARSY){
		itoa(cha, label, 10);
		gen(lev, btablev, "T", LI, label, "-");
		getsym();
    }else{
        error();
		printf("need an int or a char.\n");
        while(symNeed[symbol] != 1){
            getsym();
        }
	}
}

