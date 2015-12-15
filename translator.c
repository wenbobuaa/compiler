
#include "variable.h"
#include "const.h"
#include "function.h"
void initreg(){
	int i = 8;
	for(i = 8; i <= 25; i++){
		regtab[i] = -1;
		regtabbuf[i] = -1;
		regnum[i] = 0;
	}
	fprintf(MOUT, "\t\tli,\t$fp,\t0x10000000\n");
}
void coverreg(){
    int i = 8;
	for(i = 8; i <= 25; i++){
		regtab[i] = -1;
		regnum[i] = 0;
	}
}
void recoverreg(){
    int i = 8;
	for(i = 8; i <= 25; i++){
		regtab[i] = regtabbuf[i];
	}
}
int regfind(char * name){
	int i = vartabtop;
	for(; i >= 0; i--){
		if(strcmp(name, vartab[i].name) == 0){
			return i;
		}
	}
	return -1;
}
int regsellect(){
	int i = 8;
	int j = 0;
	int temp = 0;
	for(; i <= 25; i++){
		if(regtab[i] == -1){
            for(j = 8; j < 25; j++){
                regnum[j] = regnum[j] + 1;
            }
            regnum[i] = 0;
			return i;
		}
	}
	temp = 8;
	for(j = 8; j <= 25; j++){
		if(regnum[temp] < regnum[j]){
			temp = j;
		}
	}
	fprintf(MOUT, "\t\tsw,\t$%d,\t%d($fp)\n", temp, regtab[temp]*4);
	vartab[regtab[temp]].reg = -1;
	for(i = 8; i <= 25; i++){
		regnum[i] = regnum[i] + 1;
	}
	regnum[temp] = 0;
	return temp;
}
int regalloc(char * name, int * desi){
	int i = 0;
	int j = 0;
	_VARTAG temp;
	int adr = 0;
	int p;
	if(name[0] >= '0' && name[0] <= '9'){
		*desi = -1;
		return -1;
	}else if(name[0] != 'T'){
		i = tabfind(name, btab[ref].last);
		j = nowctabadr-tab[i].lev;
		p = nowctabadr-1;
		fprintf(MOUT, "\t\tadd,\t$26,\t$sp,\t$0\n");
		if(tab[i].obj == FUNCTION){
            j--;
		}
		for(; j > 0; j--){
			fprintf(MOUT, "\t\tlw,\t$26,\t0($26)\n");
		}
		p = regsellect();
		fprintf(MOUT, "\t\taddi,\t$%d,\t$26,\t%d\n", p, tab[i].adr*4);
		*desi = 0;
		if(tab[i].normal == TRUE){
            fprintf(MOUT, "\t\tlw,\t$%d,\t0($%d)\n", p, p);
		}
		return p;
	}else{
	    *desi = 1;
		i = regfind(name);
		if(i == -1){
			strcpy(temp.name, name);
			temp.reg = regsellect();
			regtab[temp.reg] = vartabtop;
			regtabbuf[temp.reg] = vartabtop;
			vartab[vartabtop++] = temp;
			return temp.reg;
		}else{
			if(vartab[i].reg == -1){
				vartab[i].reg = regsellect();
				fprintf(MOUT, "\t\tlw,\t$%d,\t%d($fp)\n", vartab[i].reg, i*4);
				regtab[vartab[i].reg] = i;
				regtabbuf[vartab[i].reg] = i;
				return vartab[i].reg;
			}else{
				for(j = 8; j <= 25; j++){
					regnum[j] = regnum[j] + 1;
				}
				regnum[vartab[i].reg] = 0;
				return vartab[i].reg;
			}
		}
	}
}

void trans(){
	int i = 0;
	int desi;
	int desj;
	int firi;
	int firj;
	int seci;
	int secj;
	char des[al];
	char fir[strmax];
	char sec[al];
	char temp0[al];
	char temp1[al];
	int blev;
	_OP opt;
	initreg();
	for(i = 0; i < ctabtop; i++){
		strcpy(des, ctab[i].des);
		strcpy(fir, ctab[i].fir);
		strcpy(sec, ctab[i].sec);
		opt = ctab[i].opt;
		nowctabadr = ctab[i].lev;
		ref = ctab[i].ref;
		switch(opt){
			case PLUS: {
				firj = regalloc(fir, &firi);
				secj = regalloc(sec, &seci);
				desj = regalloc(des, &desi);
				if(firi == -1 && seci == -1){
					firj = atoi(fir);
					secj = atoi(sec);
					if(desi == 0){
						fprintf(MOUT, "\t\tli,\t$26,\t%d\n", firj+secj);
						fprintf(MOUT, "\t\tsw,\t$26,\t0($%d)\n", desi);
					}else{
						fprintf(MOUT, "\t\tli,\t$%d,\t%d\n", desj, firj+secj);
					}
				}else if(firi != -1 && seci == -1){
					secj = atoi(sec);
					if(firi == 0){
						fprintf(MOUT, "\t\tlw,\t$27,\t0($%d)\n", firj);
						if(desi == 0){
							fprintf(MOUT, "\t\taddi,\t$26,\t$27,\t%d\n", secj);
							fprintf(MOUT, "\t\tsw,\t$26,\t0($%d)\n", desj);
						}else{
							fprintf(MOUT, "\t\taddi,\t$%d,\t$27,\t%d\n", desj, secj);
						}
					}else{
						if(desi == 0){
							fprintf(MOUT, "\t\taddi,\t$26,\t$%d,\t%d\n", firj, secj);
							fprintf(MOUT, "\t\tsw,\t$26,\t0($%d)\n", desj);
						}else{
							fprintf(MOUT, "\t\taddi,\t$%d,\t$%d,\t%d\n", desj, firj, secj);
						}
					}
				}else if(firi == -1 && seci != -1){
					firj = atoi(fir);
					if(seci == 0){
						fprintf(MOUT, "\t\tlw,\t$27,\t0($%d)\n", secj);
						if(desi == 0){
							fprintf(MOUT, "\t\taddi,\t$26,\t$27,\t%d\n", firj);
							fprintf(MOUT, "\t\tsw,\t$26,\t0($%d)\n", desj);
						}else{
							fprintf(MOUT, "\t\taddi,\t$%d,\t$27,%d\n", desj, firj);
						}
					}else{
						if(desi == 0){
							fprintf(MOUT, "\t\taddi,\t$26,\t$%d,\t%d\n", secj, firj);
							fprintf(MOUT, "\t\tsw,\t$26,\t0($%d)\n", desj);
						}else{
							fprintf(MOUT, "\t\taddi,\t$%d,\t$%d,\t%d\n", desj, secj, firj);
						}
					}
				}else{
					if(firi == 0 && seci != 0){
						fprintf(MOUT, "\t\tlw,\t$27,\t0($%d)\n", firj);
						if(desi == 0){
							fprintf(MOUT, "\t\tadd,\t$26,\t$27,\t$%d\n", secj);
							fprintf(MOUT, "\t\tsw,\t$26,\t0($%d)\n", desj);
						}else{
							fprintf(MOUT, "\t\tadd,\t$%d,\t$27,\t$%d\n", secj);
						}
					}else if(firi != 0 && seci == 0){
						fprintf(MOUT, "\t\tlw,\t$27,\t0($%d)\n", secj);
						if(desi == 0){
							fprintf(MOUT, "\t\tadd,\t$26,\t$27,\t$%d\n", firj);
							fprintf(MOUT, "\t\tsw,\t$26,\t0($%d)\n", desj);
						}else{
							fprintf(MOUT, "\t\tadd,\t$%d,\t$27,\t$%d\n", desj, firj);
						}
					}else if(firi == 0 && seci == 0){
						fprintf(MOUT,"\t\tlw,\t$27,\t0($%d)\n", firj);
						fprintf(MOUT, "\t\tlw,\t$26,\t0($%d)\n", secj);
						if(desi == 0){
							fprintf(MOUT, "\t\tadd,\t$26,\t$27,\t$26\n");
							fprintf(MOUT, "\t\tsw,\t$26,\t0($%d)\n", desj);
						}else{
							fprintf(MOUT, "\t\tadd,\t$%d,\t$27,\t$26\n", desj);
						}
					}else{
						fprintf(MOUT, "\t\tadd,\t$%d,\t$%d,\t$%d\n", desj, firj, secj);
					}
				}
			}break;
			case MINUS:{
				firj = regalloc(fir, &firi);
				secj = regalloc(sec, &seci);
				desj = regalloc(des, &desi);
				if(firi == -1 && seci == -1){
					firj = atoi(fir);
					secj = atoi(sec);
					if(desi == 0){
						fprintf(MOUT, "\t\tli,\t$26,\t%d\n", firj-secj);
						fprintf(MOUT, "\t\tsw,\t$26,\t0($%d)\n", desi);
					}else{
						fprintf(MOUT, "\t\tli,\t$%d,\t%d\n", desj, firj-secj);
					}
				}else if(firi != -1 && seci == -1){
					secj = atoi(sec);
					if(firi == 0){
						fprintf(MOUT, "\t\tlw,\t$27,\t0($%d)\n", firj);
						if(desi == 0){
							fprintf(MOUT, "\t\tsubi,\t$26,\t$27,\t%d\n", secj);
							fprintf(MOUT, "\t\tsw,\t$26,\t0($%d)\n", desj);
						}else{
							fprintf(MOUT, "\t\tsubi,\t$%d,\t$27,\t%d\n", desj, secj);
						}
					}else{
						if(desi == 0){
							fprintf(MOUT, "\t\tsubi,\t$26,\t$%d,\t%d\n", firj, secj);
							fprintf(MOUT, "\t\tsw,\t$26,\t0($%d)\n", desj);
						}else{
							fprintf(MOUT, "\t\tsubi,\t$%d,\t$%d,\t%d\n", desj, firj, secj);
						}
					}
				}else if(firi == -1 && seci != -1){
					firj = atoi(fir);
					if(seci == 0){
                        fprintf(MOUT, "\t\tli,\t$26,\t%d\n", firj);
						fprintf(MOUT, "\t\tlw,\t$27,\t0($%d)\n", secj);
						if(desi == 0){
							fprintf(MOUT, "\t\tsub,\t$26,\t$26,\t$27\n");
							fprintf(MOUT, "\t\tsw,\t$26,\t0($%d)\n", desj);
						}else{
							fprintf(MOUT, "\t\tsub,\t$%d,\t$26,\t$27\n", desj);
						}
					}else{
					    fprintf(MOUT, "\t\tli,\t$27,\t%d\n", firj);
						if(desi == 0){
							fprintf(MOUT, "\t\tsub,\t$26,\t$27,\t$%d\n", secj);
							fprintf(MOUT, "\t\tsw,\t$26,\t0($%d)\n", desj);
						}else{
							fprintf(MOUT, "\t\tsub,\t$%d,\t$27,\t$%d\n", desj, secj);
						}
					}
				}else{
					if(firi == 0 && seci != 0){
						fprintf(MOUT, "\t\tlw,\t$27,\t0($%d)\n", firj);
						if(desi == 0){
							fprintf(MOUT, "\t\tsub,\t$26,\t$27,\t$%d\n", secj);
							fprintf(MOUT, "\t\tsw,\t$26,\t0($%d)\n", desj);
						}else{
							fprintf(MOUT, "\t\tsub,\t$%d,\t$27,\t$%d\n", secj);
						}
					}else if(firi != 0 && seci == 0){
						fprintf(MOUT, "\t\tlw,\t$27,\t0($%d)\n", secj);
						if(desi == 0){
							fprintf(MOUT, "\t\tsub,\t$26,\t$27,\t$%d\n", firj);
							fprintf(MOUT, "\t\tsw,\t$26,\t0($%d)\n", desj);
						}else{
							fprintf(MOUT, "\t\tsub,\t$%d,\t$27,\t$%d\n", desj, firj);
						}
					}else if(firi == 0 && seci == 0){
						fprintf(MOUT,"\t\tlw,\t$27,\t0($%d)\n", firj);
						fprintf(MOUT, "\t\tlw,\t$26,\t0($%d)\n", secj);
						if(desi == 0){
							fprintf(MOUT, "\t\tsub,\t$26,\t$27,\t$26\n");
							fprintf(MOUT, "\t\tsw,\t$26,\t0($%d)\n", desj);
						}else{
							fprintf(MOUT, "\t\tsub,\t$%d,\t$27,\t$26\n", desj);
						}
					}else{
						fprintf(MOUT, "\t\tsub,\t$%d,\t$%d,\t$%d\n", desj, firj, secj);
					}
				}
			}break;
			case STAR:{
				firj = regalloc(fir, &firi);
				secj = regalloc(sec, &seci);
				desj = regalloc(des, &desi);
				if(firi == -1 && seci == -1){
					firj = atoi(fir);
					secj = atoi(sec);
					if(desi == 0){
						fprintf(MOUT, "\t\tli,\t$26,\t%d\n", firj*secj);
						fprintf(MOUT, "\t\tsw,\t$26,\t0($%d)\n", desi);
					}else{
						fprintf(MOUT, "\t\tli,\t$%d,\t%d\n", desj, firj*secj);
					}
				}else if(firi != -1 && seci == -1){
					secj = atoi(sec);
					if(firi == 0){
						fprintf(MOUT, "\t\tlw,\t$27,\t0($%d)\n", firj);
						if(desi == 0){
							fprintf(MOUT, "\t\tmul,\t$26,\t$27,\t%d\n", secj);
							fprintf(MOUT, "\t\tsw,\t$26,\t0($%d)\n", desj);
						}else{
							fprintf(MOUT, "\t\tmul,\t$%d,\t$27,\t%d\n", desj, secj);
						}
					}else{
						if(desi == 0){
							fprintf(MOUT, "\t\tmul,\t$26,\t$%d,\t%d\n", firj, secj);
							fprintf(MOUT, "\t\tsw,\t$26,\t0($%d)\n", desj);
						}else{
							fprintf(MOUT, "\t\tmul,\t$%d,\t$%d,\t%d\n", desj, firj, secj);
						}
					}
				}else if(firi == -1 && seci != -1){
					firj = atoi(fir);
					if(seci == 0){
						fprintf(MOUT, "\t\tlw,\t$27,\t0($%d)\n", secj);
						if(desi == 0){
							fprintf(MOUT, "\t\tmul,\t$26,\t$27,\t%d\n", firj);
							fprintf(MOUT, "\t\tsw,\t$26,\t0($%d)\n", desj);
						}else{
							fprintf(MOUT, "\t\tmul,\t$%d,\t$27,%d\n", desj, firj);
						}
					}else{
						if(desi == 0){
							fprintf(MOUT, "\t\tmul,\t$26,\t$%d,\t%d\n", secj, firj);
							fprintf(MOUT, "\t\tsw,\t$26,\t0($%d)\n", desj);
						}else{
							fprintf(MOUT, "\t\tmul,\t$%d,\t$%d,\t%d\n", desj, secj, firj);
						}
					}
				}else{
					if(firi == 0 && seci != 0){
						fprintf(MOUT, "\t\tlw,\t$27,\t0($%d)\n", firj);
						if(desi == 0){
							fprintf(MOUT, "\t\tmulo,\t$26,\t$27,\t$%d\n", secj);
							fprintf(MOUT, "\t\tsw,\t$26,\t0($%d)\n", desj);
						}else{
							fprintf(MOUT, "\t\tmulo,\t$%d,\t$27,\t$%d\n", secj);
						}
					}else if(firi != 0 && seci == 0){
						fprintf(MOUT, "\t\tlw,\t$27,\t0($%d)\n", secj);
						if(desi == 0){
							fprintf(MOUT, "\t\tmulo,\t$26,\t$27,\t$%d\n", firj);
							fprintf(MOUT, "\t\tsw,\t$26,\t0($%d)\n", desj);
						}else{
							fprintf(MOUT, "\t\tmulo,\t$%d,\t$27,\t$%d\n", desj, firj);
						}
					}else if(firi == 0 && seci == 0){
						fprintf(MOUT,"\t\tlw,\t$27,\t0($%d)\n", firj);
						fprintf(MOUT, "\t\tlw,\t$26,\t($%d)\n", secj);
						if(desi == 0){
							fprintf(MOUT, "\t\tmulo,\t$26,\t$27,\t$26\n");
							fprintf(MOUT, "\t\tsw,\t$26,\t0($%d)\n", desj);
						}else{
							fprintf(MOUT, "\t\tmulo,\t$%d,\t$27,\t$26\n", desj);
						}
					}else{
						fprintf(MOUT, "\t\tmulo,\t$%d,\t$%d,\t$%d\n", desj, firj, secj);
					}
				}
			}break;
			case DIVI:{
				firj = regalloc(fir, &firi);
				secj = regalloc(sec, &seci);
				desj = regalloc(des, &desi);
				if(firi == -1 && seci == -1){
					firj = atoi(fir);
					secj = atoi(sec);
					if(desi == 0){
						fprintf(MOUT, "\t\tli,\t$26,\t%d\n", firj/secj);
						fprintf(MOUT, "\t\tsw,\t$26,\t0($%d)\n", desi);
					}else{
						fprintf(MOUT, "\t\tli,\t$%d,\t%d\n", desj, firj/secj);
					}
				}else if(firi != -1 && seci == -1){
					secj = atoi(sec);
					if(firi == 0){
						fprintf(MOUT, "\t\tlw,\t$27,\t0($%d)\n", firj);
						if(desi == 0){
							fprintf(MOUT, "\t\tdiv,\t$26,\t$27,\t%d\n", secj);
							fprintf(MOUT, "\t\tsw,\t$26,\t0($%d)\n", desj);
						}else{
							fprintf(MOUT, "\t\tdiv,\t$%d,\t$27,\t%d\n", desj, secj);
						}
					}else{
						if(desi == 0){
							fprintf(MOUT, "\t\tdiv,\t$26,\t$%d,\t%d\n", firj, secj);
							fprintf(MOUT, "\t\tsw,\t$26,\t0($%d)\n", desj);
						}else{
							fprintf(MOUT, "\t\tdiv,\t$%d,\t$%d,\t%d\n", desj, firj, secj);
						}
					}
				}else if(firi == -1 && seci != -1){
					firj = atoi(fir);
					if(seci == 0){
                        fprintf(MOUT, "\t\tli,\t$26,\t%d\n", firj);
						fprintf(MOUT, "\t\tlw,\t$27,\t0($%d)\n", secj);
						if(desi == 0){
							fprintf(MOUT, "\t\tdiv,\t$26,\t$26,\t$27\n");
							fprintf(MOUT, "\t\tsw,\t$26,\t0($%d)\n", desj);
						}else{
							fprintf(MOUT, "\t\tdiv,\t$%d,\t$26,\t$27\n", desj);
						}
					}else{
					    fprintf(MOUT, "\t\tli,\t$27,\t%d\n", firj);
						if(desi == 0){
							fprintf(MOUT, "\t\tdiv,\t$26,\t$27,\t$%d\n", secj);
							fprintf(MOUT, "\t\tsw,\t$26,\t0($%d)\n", desj);
						}else{
							fprintf(MOUT, "\t\tdiv,\t$%d,\t$27,\t$%d\n", desj, secj);
						}
					}
				}else{
					if(firi == 0 && seci != 0){
						fprintf(MOUT, "\t\tlw,\t$27,\t0($%d)\n", firj);
						if(desi == 0){
							fprintf(MOUT, "\t\tdiv,\t$26,\t$27,\t$%d\n", secj);
							fprintf(MOUT, "\t\tsw,\t$26,\t0($%d)\n", desj);
						}else{
							fprintf(MOUT, "\t\tdiv,\t$%d,\t$27,\t$%d\n", secj);
						}
					}else if(firi != 0 && seci == 0){
						fprintf(MOUT, "\t\tlw,\t$27,\t0($%d)\n", secj);
						if(desi == 0){
							fprintf(MOUT, "\t\tdiv,\t$26,\t$27,\t$%d\n", firj);
							fprintf(MOUT, "\t\tsw,\t$26,\t0($%d)\n", desj);
						}else{
							fprintf(MOUT, "\t\tdiv,\t$%d,\t$27,\t$%d\n", desj, firj);
						}
					}else if(firi == 0 && seci == 0){
						fprintf(MOUT,"\t\tlw,\t$27,\t0($%d)\n", firj);
						fprintf(MOUT, "\t\tlw,\t$26,\t0($%d)\n", secj);
						if(desi == 0){
							fprintf(MOUT, "\t\tdiv,\t$26,\t$27,\t$26\n");
							fprintf(MOUT, "\t\tsw,\t$26,\t0($%d)\n", desj);
						}else{
							fprintf(MOUT, "\t\tdiv,\t$%d,\t$27,\t$26\n", desj);
						}
					}else{
						fprintf(MOUT, "\t\tdiv,\t$%d,\t$%d,\t$%d\n", desj, firj, secj);
					}
				}
			}break;
			case EQU :{
				firj = regalloc(fir, &firi);
				secj = regalloc(sec, &seci);
				if(firi == -1 && seci == -1){
					firi = atoi(fir);
					seci = atoi(sec);
					if(firi == seci){
						fprintf(MOUT, "\t\tj,\t%s\n", des);
					}else{

					}
				}else if(firi != -1 && seci == -1){
					if(firi == 0){
						fprintf(MOUT, "\t\tlw,\t$26,\t0($%d)\n", firj);
						fprintf(MOUT, "\t\tbeq,\t$26,\t%d,\t%s\n", secj, des);
					}else{
						fprintf(MOUT, "\t\tbeq,\t$%d,\t%d,\t%s\n", firj, secj, des);
					}
				}else if(firi == -1 && seci != -1){
					if(seci == 0){
						fprintf(MOUT, "\t\tlw,\t$26,\t0($%d)\n", secj);
						fprintf(MOUT, "\t\tbeq,\t$26,\t%d,\t%s\n", firj, des);
					}else{
						fprintf(MOUT, "\t\tbeq,\t$%d,\t%d,\t%s\n", secj, firj, des);
					}
				}else{
					if(firi == 0 && seci != 0){
						fprintf(MOUT, "\t\tlw,\t$26,\t0($%d)\n", firj);
						fprintf(MOUT, "\t\tbeq,\t$26,\t$%d,\t%s\n", secj, des);
					}else if(firi != 0 && seci == 0){
						fprintf(MOUT, "\t\tlw,\t$26,\t%d($sp)\n", secj);
						fprintf(MOUT, "\t\tbeq,\t$%d,\t$26,\t%s\n", firj, des);
					}else if(firi == 0 && seci == 0){
						fprintf(MOUT, "\t\tlw,\t$26,\t0($%d)\n", firj);
						fprintf(MOUT, "\t\tlw,\t$27,\t0($%d)\n", secj);
						fprintf(MOUT, "\t\tbeq,\t$26,\t$26,\t%s\n", des);
					}else{
						fprintf(MOUT, "\t\tbeq,\t$%d,\t$%d,\t%s\n", firj, secj, des);
					}
				}
			}break;
			case UNE :{
				firj = regalloc(fir, &firi);
				secj = regalloc(sec, &seci);
				if(firi == -1 && seci == -1){
					firi = atoi(fir);
					seci = atoi(sec);
					if(firi != seci){
						fprintf(MOUT, "\t\tj,\t%s\n", des);
					}else{

					}
				}else if(firi != -1 && seci == -1){
					if(firi == 0){
						fprintf(MOUT, "\t\tlw,\t$26,\t0($%d)\n", firj);
						fprintf(MOUT, "\t\tbne,\t$26,\t%d,\t%s\n", secj, des);
					}else{
						fprintf(MOUT, "\t\tbne,\t$%d,\t%d,\t%s\n", firj, secj, des);
					}
				}else if(firi == -1 && seci != -1){
					if(seci == 0){
						fprintf(MOUT, "\t\tlw,\t$26,\t0($%d)\n", secj);
						fprintf(MOUT, "\t\tbne,\t$26,\t%d,\t%s\n", firj, des);
					}else{
						fprintf(MOUT, "\t\tbne,\t$%d,\t%d,\t%s\n", secj, firj, des);
					}
				}else{
					if(firi == 0 && seci != 0){
						fprintf(MOUT, "\t\tlw,\t$26,\t0($%d)\n", firj);
						fprintf(MOUT, "\t\tbne,\t$26,\t$%d,\t%s\n", secj, des);
					}else if(firi != 0 && seci == 0){
						fprintf(MOUT, "\t\tlw,\t$26,\t0($%d)\n", secj);
						fprintf(MOUT, "\t\tbne,\t$%d,\t$26,\t%s\n", firj, des);
					}else if(firi == 0 && seci == 0){
						fprintf(MOUT, "\t\tlw,\t$26,\t0($%d)\n", firj);
						fprintf(MOUT, "\t\tlw,\t$27,\t0($%d)\n", secj);
						fprintf(MOUT, "\t\tbne,\t$26,\t$26,\t%s\n", des);
					}else{
						fprintf(MOUT, "\t\tbne,\t$%d,\t$%d,\t%s\n", firj, secj, des);
					}
				}
			}break;
			case GTH :{
				firj = regalloc(fir, &firi);
				secj = regalloc(sec, &seci);
				if(firi == -1 && seci == -1){
					firi = atoi(fir);
					seci = atoi(sec);
					if(firi > seci){
						fprintf(MOUT, "\t\tj,\t%s\n", des);
					}else{

					}
				}else if(firi != -1 && seci == -1){
					if(firi == 0){
						fprintf(MOUT, "\t\tlw,\t$26,\t0($%d)\n", firj);
						fprintf(MOUT, "\t\tbgt,\t$26,\t%d,\t%s\n", secj, des);
					}else{
						fprintf(MOUT, "\t\tbgt,\t$%d,\t%d,\t%s\n", firj, secj, des);
					}
				}else if(firi == -1 && seci != -1){
					if(seci == 0){
						fprintf(MOUT, "\t\tlw,\t$26,\t0($%d)\n", secj);
						fprintf(MOUT, "\t\tbgt,\t$26,\t%d,\t%s\n", firj, des);
					}else{
						fprintf(MOUT, "\t\tbgt,\t$%d,\t%d,\t%s\n", secj, firj, des);
					}
				}else{
					if(firi == 0 && seci != 0){
						fprintf(MOUT, "\t\tlw,\t$26,\t0($%d)\n", firj);
						fprintf(MOUT, "\t\tbgt,\t$26,\t$%d,\t%s\n", secj, des);
					}else if(firi != 0 && seci == 0){
						fprintf(MOUT, "\t\tlw,\t$26,\t0($%d)\n", secj);
						fprintf(MOUT, "\t\tbgt,\t$%d,\t$26,\t%s\n", firj, des);
					}else if(firi == 0 && seci == 0){
						fprintf(MOUT, "\t\tlw,\t$26,\t0($%d)\n", firj);
						fprintf(MOUT, "\t\tlw,\t$27,\t0($%d)\n", secj);
						fprintf(MOUT, "\t\tbgt,\t$26,\t$26,\t%s\n", des);
					}else{
						fprintf(MOUT, "\t\tbgt,\t$%d,\t$%d,\t%s\n", firj, secj, des);
					}
				}
			}break;
			case LTH :{
				firj = regalloc(fir, &firi);
				secj = regalloc(sec, &seci);
				if(firi == -1 && seci == -1){
					firi = atoi(fir);
					seci = atoi(sec);
					if(firi < seci){
						fprintf(MOUT, "\t\tj,\t%s\n", des);
					}else{

					}
				}else if(firi != -1 && seci == -1){
					if(firi == 0){
						fprintf(MOUT, "\t\tlw,\t$26,\t0($%d)\n", firj);
						fprintf(MOUT, "\t\tblt,\t$26,\t%d,\t%s\n", secj, des);
					}else{
						fprintf(MOUT, "\t\tblt,\t$%d,\t%d,\t%s\n", firj, secj, des);
					}
				}else if(firi == -1 && seci != -1){
					if(seci == 0){
						fprintf(MOUT, "\t\tlw,\t$26,\t0($%d)\n", secj);
						fprintf(MOUT, "\t\tblt,\t$26,\t%d,\t%s\n", firj, des);
					}else{
						fprintf(MOUT, "\t\tblt,\t$%d,\t%d,\t%s\n", secj, firj, des);
					}
				}else{
					if(firi == 0 && seci != 0){
						fprintf(MOUT, "\t\tlw,\t$26,\t0($%d)\n", firj);
						fprintf(MOUT, "\t\tblt,\t$26,\t$%d,\t%s\n", secj, des);
					}else if(firi != 0 && seci == 0){
						fprintf(MOUT, "\t\tlw,\t$26,\t0($%d)\n", secj);
						fprintf(MOUT, "\t\tblt,\t$%d,\t$26,\t%s\n", firj, des);
					}else if(firi == 0 && seci == 0){
						fprintf(MOUT, "\t\tlw,\t$26,\t0($%d)\n", firj);
						fprintf(MOUT, "\t\tlw,\t$27,\t0($%d)\n", secj);
						fprintf(MOUT, "\t\tblt,\t$26,\t$26,\t%s\n", des);
					}else{
						fprintf(MOUT, "\t\tblt,\t$%d,\t$%d,\t%s\n", firj, secj, des);
					}
				}
			}break;
			case GEQ :{
				firj = regalloc(fir, &firi);
				secj = regalloc(sec, &seci);
				if(firi == -1 && seci == -1){
					firi = atoi(fir);
					seci = atoi(sec);
					if(firi >= seci){
						fprintf(MOUT, "\t\tj,\t%s\n", des);
					}else{

					}
				}else if(firi != -1 && seci == -1){
					if(firi == 0){
						fprintf(MOUT, "\t\tlw,\t$26,\t0($%d)\n", firj);
						fprintf(MOUT, "\t\tbge,\t$26,\t%d,\t%s\n", secj, des);
					}else{
						fprintf(MOUT, "\t\tbge,\t$%d,\t%d,\t%s\n", firj, secj, des);
					}
				}else if(firi == -1 && seci != -1){
					if(seci == 0){
						fprintf(MOUT, "\t\tlw,\t$26,\t0($%d)\n", secj);
						fprintf(MOUT, "\t\tbge,\t$26,\t%d,\t%s\n", firj, des);
					}else{
						fprintf(MOUT, "\t\tbge,\t$%d,\t%d,\t%s\n", secj, firj, des);
					}
				}else{
					if(firi == 0 && seci != 0){
						fprintf(MOUT, "\t\tlw,\t$26,\t0($%d)\n", firj);
						fprintf(MOUT, "\t\tbge,\t$26,\t$%d,\t%s\n", secj, des);
					}else if(firi != 0 && seci == 0){
						fprintf(MOUT, "\t\tlw,\t$26,\t0($%d)\n", secj);
						fprintf(MOUT, "\t\tbge,\t$%d,\t$26,\t%s\n", firj, des);
					}else if(firi == 0 && seci == 0){
						fprintf(MOUT, "\t\tlw,\t$26,\t0($%d)\n", firj);
						fprintf(MOUT, "\t\tlw,\t$27,\t0($%d)\n", secj);
						fprintf(MOUT, "\t\tbge,\t$26,\t$26,\t%s\n", des);
					}else{
						fprintf(MOUT, "\t\tbge,\t$%d,\t$%d,\t%s\n", firj, secj, des);
					}
				}
			}break;
			case LEQ :{
				firj = regalloc(fir, &firi);
				secj = regalloc(sec, &seci);
				if(firi == -1 && seci == -1){
					firi = atoi(fir);
					seci = atoi(sec);
					if(firi <= seci){
						fprintf(MOUT, "\t\tj,\t%s\n", des);
					}else{

					}
				}else if(firi != -1 && seci == -1){
					if(firi == 0){
						fprintf(MOUT, "\t\tlw,\t$26,\t0($%d)\n", firj);
						fprintf(MOUT, "\t\tble,\t$26,\t%d,\t%s\n", secj, des);
					}else{
						fprintf(MOUT, "\t\tble,\t$%d,\t%d,\t%s\n", firj, secj, des);
					}
				}else if(firi == -1 && seci != -1){
					if(seci == 0){
						fprintf(MOUT, "\t\tlw,\t$26,\t0($%d)\n", secj);
						fprintf(MOUT, "\t\tble,\t$26,\t%d,\t%s\n", firj, des);
					}else{
						fprintf(MOUT, "\t\tble,\t$%d,\t%d,\t%s\n", secj, firj, des);
					}
				}else{
					if(firi == 0 && seci != 0){
						fprintf(MOUT, "\t\tlw,\t$26,\t0($%d)\n", firj);
						fprintf(MOUT, "\t\tble,\t$26,\t$%d,\t%s\n", secj, des);
					}else if(firi != 0 && seci == 0){
						fprintf(MOUT, "\t\tlw,\t$26,\t%d($sp)\n", secj);
						fprintf(MOUT, "\t\tble,\t$%d,\t$26,\t%s\n", firj, des);
					}else if(firi == 0 && seci == 0){
						fprintf(MOUT, "\t\tlw,\t$26,\t0($%d)\n", firj);
						fprintf(MOUT, "\t\tlw,\t$27,\t0($%d)\n", secj);
						fprintf(MOUT, "\t\tble,\t$26,\t$26,\t%s\n", des);
					}else{
						fprintf(MOUT, "\t\tble,\t$%d,\t$%d,\t%s\n", firj, secj, des);
					}
				}
			}break;
			case LOD :{
				firj = regalloc(fir, &firi);
				desj = regalloc(des, &desi);
				fprintf(MOUT, "\t\tlw,\t$%d,\t0($%d)\n", desj, firj);
			}break;
			case CALLP :{
				for(desi = 8; desi <= 25; desi++){
					fprintf(MOUT, "\t\tsw,\t$%d,\t0($gp)\n", desi);
					fprintf(MOUT, "\t\taddi,\t$gp,\t$gp,\t4\n");
				}
				fprintf(MOUT, "\t\tsw,\t$sp,\t0($gp)\n");
				fprintf(MOUT, "\t\taddi,\t$gp,\t$gp,\t4\n");
				blev = nowctabadr;
				firi = btab[blev].vsize;
				seci = btab[blev].psize;
				firi = (firi+seci+2)*4;
				if(ref != blev){
					fprintf(MOUT, "\t\tadd,\t$26,\t$sp,\t$0\n");
					fprintf(MOUT, "\t\taddi,\t$sp, \t$26,\t%d\n", firi);
					fprintf(MOUT, "\t\tsw,\t$26,\t0($sp)\n");
				}else{
					fprintf(MOUT, "\t\tlw,\t$26,\t0($sp)\n");
					fprintf(MOUT, "\t\taddi,\t$sp, \t$sp,\t%d\n", firi);
					fprintf(MOUT, "\t\tsw,\t$26,\t0($sp)\n");
				}
				secj = atoi(sec);
				firj = 8;
				for(desi = 0; desi < secj; desi++){
					fprintf(MOUT,"\t\tsw,\t$a%d,%d($sp)\n", desi, firj);
					firj += 4;
				}
				strcpy(temp1, "B");
				itoa(ref, temp0, 10);
				strcat(temp1, temp0);
				strcat(fir, temp1);
				fprintf(MOUT, "\t\tjal,\t%s\n", fir);
			}break;
			case CALLF : {
				for(desi = 8; desi <= 25; desi++){
					fprintf(MOUT, "\t\tsw,\t$%d,\t0($gp)\n", desi);
					fprintf(MOUT, "\t\taddi,\t$gp,\t$gp\t4\n");
				}
				fprintf(MOUT, "\t\tsw,\t$sp,\t0($gp)\n");
				fprintf(MOUT, "\t\taddi,\t$gp,\t$gp,\t4\n");
				blev = nowctabadr;
				firi = btab[blev].vsize;
				seci = btab[blev].psize;
				firi = (firi+seci+2)*4;
				if(ref != blev){
					fprintf(MOUT, "\t\tadd,\t$26,\t$sp,\t$0\n");
					fprintf(MOUT, "\t\taddi,\t$sp, \t$26,\t%d\n", firi);
					fprintf(MOUT, "\t\tsw,\t$26,\t0($sp)\n");
				}else{
					fprintf(MOUT, "\t\tlw,\t$26,\t0($sp)\n");
					fprintf(MOUT, "\t\taddi,\t$sp, \t$sp,\t%d\n", firi);
					fprintf(MOUT, "\t\tsw,\t$26,\t0($sp)\n");
				}
				secj = atoi(sec);
				firj = 8;
				for(desi = 0; desi < secj; desi++){
					fprintf(MOUT,"\t\tsw,\t$a%d,%d($sp)\n", desi, firj);
					firj += 4;
				}
				strcpy(temp1, "B");
                itoa(ref, temp0, 10);
                strcat(temp1, temp0);
                strcat(fir, temp1);
				fprintf(MOUT, "\t\tjal,\t%s\n", fir);
				desj = regalloc(des, &desi);
				if(desi == 0){
					fprintf(MOUT, "\t\tsw,\t$v0,\t0($%d)\n", desj);
				}else{
					fprintf(MOUT, "\t\tadd,\t$%d,\t$v0,\t$0\n", desj);
				}
			}break;
			case STO :{
				firj = regalloc(fir, &firi);
				secj = regalloc(sec, &seci);
				fprintf(MOUT, "\t\tsw,\t$%d,\t0($%d)\n", secj, firj);
			}break;
			case LAB :{
				if(tab[tabfind(fir, btab[ref].last)].obj == FUNCTION || tab[tabfind(fir, btab[ref].last)].obj == PROCEDURE){
                    fprintf(MOUT, "%s:\n", des);
                    fprintf(MOUT, "\t\tsw,\t$ra\t0($gp)\n");
                    fprintf(MOUT, "\t\taddi,\t$gp,\t$gp,\t4\n");
                    coverreg();
				}else{
                    fprintf(MOUT, "%s:\n", fir);
				}
			}break;
			case LI :{
				desj = regalloc(des, &desi);
				firj = atoi(fir);
				fprintf(MOUT, "\t\tli,\t$%d,\t%d\n", desj, firj);
			}break;
			case ARRV :{
				firj = regalloc(fir, &firi);
				secj = regalloc(sec, &seci);
				desj = regalloc(des, &desi);
				if(seci == -1){
					secj = atoi(sec);
					fprintf(MOUT, "\t\taddi,\t$27,\t$%d,\t%d\n", firj, secj*4);
					if(desi == 0){
						fprintf(MOUT, "\t\tlw,\t$26,\t0($27)\n");
						fprintf(MOUT, "\t\tsw,\t%26,\t0($%d)\n", desj);
					}else{
						fprintf(MOUT, "\t\tlw,\t$%d,\t0($27)\n", desj);
					}
				}else if(seci == 0){
					fprintf(MOUT, "\t\tlw,\t$26,\t0($%d)\n", secj);
					fprintf(MOUT, "\t\tsll,\t$26,\t$26,\t2\n");
					fprintf(MOUT, "\t\tadd,\t$26,\t$26,\t$%d\n", firj);
					if(desi == 0){
						fprintf(MOUT, "\t\tlw,\t$27,\t0($26)\n");
						fprintf(MOUT, "\t\tsw,\t%27,\t0($%d)\n", desj);
					}else{
						fprintf(MOUT, "\t\tlw,\t$%d,\t0($26)\n", desj);
					}
				}else{
					fprintf(MOUT, "\t\tsll,\t$26,\t$%d,\t2\n", secj);
					fprintf(MOUT, "\t\tadd,\t$26,\t$26,\t$%d\n", firj);
					if(desi == 0){
						fprintf(MOUT, "\t\tlw,\t$27,\t0($26)\n");
						fprintf(MOUT, "\t\tsw,\t%27,\t0($%d)\n", desj);
					}else{
						fprintf(MOUT, "\t\tlw,\t$%d,\t0($26)\n", desj);
					}
				}
			}break;
			case ARRA :{
                firj = regalloc(fir, &firi);
				secj = regalloc(sec, &seci);
				desj = regalloc(des, &desi);
				if(seci == -1){
					secj = atoi(sec);
					fprintf(MOUT, "\t\taddi,\t$%d,\t$%d,\t%d\n", desj, firj, secj*4);
				}else if(seci == 0){
					fprintf(MOUT, "\t\tlw,\t$26,\t0($%d)\n", secj);
					fprintf(MOUT, "\t\tsll,\t$26,\t$26,\t2\n");
					fprintf(MOUT, "\t\tadd,\t$%d,\t$26,\t$%d\n",desj, firj);
				}else{
					fprintf(MOUT, "\t\tsll,\t$26,\t$%d,\t2\n", secj);
					fprintf(MOUT, "\t\tadd,\t$%d,\t$26,\t$%d\n", desj, firj);
				}
			}break;
			case JMP :{
				fprintf(MOUT, "\t\tj,\t%s\n", fir);
			}break;
			case REDI :{
				desj = regalloc(des, &desi);
				fprintf(MOUT, "\t\taddi,\t$v0,\t$0,\t5\n");
				fprintf(MOUT, "\t\tsyscall\n");
				fprintf(MOUT, "\t\tsw,\t$v0,\t0($%d)\n", desj);
			}break;
			case REDC :{
				desj = regalloc(des, &desi);
				fprintf(MOUT, "\t\taddi,\t$v0,\t$0,\t12\n");
				fprintf(MOUT, "\t\tsyscall\n");
				fprintf(MOUT, "\t\tsw,\t$v0,\t0($%d)\n", desj);
			}break;
			case WRII :{
				firj = regalloc(fir, &firi);
				if(firi == -1){
					fprintf(MOUT, "\t\taddi,\t$a0,\t$0,\t%d\n", firj);
				}else if(firi == 0){
					fprintf(MOUT, "\t\tlw,\t$a0,\t0($%d)\n", firj);
				}else{
					fprintf(MOUT, "\t\tadd,\t$a0,\t$0,\t$%d\n", firj);
				}
				fprintf(MOUT, "\t\tli,\t$v0,\t1\n");
				fprintf(MOUT, "\t\tsyscall\n");
			}break;
			case WRIC :{
				firj = regalloc(fir, &firi);
				if(firi == -1){
					fprintf(MOUT, "\t\taddi,\t$a0,\t$0,\t%d\n", firj);
				}else if(firi == 0){
					fprintf(MOUT, "\t\tlw,\t$a0,\t0($%d)\n", firj);
				}else{
					fprintf(MOUT, "\t\tadd,\t$a0,\t$0,\t$%d\n", firj);
				}
				fprintf(MOUT, "\t\tli,\t$v0,\t11\n");
				fprintf(MOUT, "\t\tsyscall\n");
			}break;
			case WRIS :{
				fprintf(MOUT, "\t\tadd,\t$27,\t$0,\t$gp\n");
				for(firi = 0; firi <= strlen(fir); firi++){
					fprintf(MOUT, "\t\tli,\t$26,\t%d\n", fir[firi]);
					fprintf(MOUT, "\t\tsb,\t$26,\t0($gp)\n");
					fprintf(MOUT, "\t\taddi,\t$gp,\t$gp,\t1\n");
				}
				fprintf(MOUT, "\t\tadd,\t$gp,\t$0,\t$27\n");
				fprintf(MOUT, "\t\tadd,\t$a0,\t$0,\t$gp\n");
				fprintf(MOUT, "\t\tli,\t$v0,\t4\n");
				fprintf(MOUT, "\t\tsyscall\n");
			}break;
            case TRAV :{
                firj = regalloc(fir, &firi);
                secj = atoi(sec);
                if(firi == 0){
                    fprintf(MOUT, "\t\tlw,\t$26,\t0($%d)\n", firj);
                    fprintf(MOUT, "\t\tadd,\t$a%d,\t$26,\t$0\n", secj);
                }else{
                    fprintf(MOUT, "\t\tadd,\t$a%d,\t$%d,\t$0\n", secj, firj);
                }
            }break;
            case TRAR :{
                firj = regalloc(fir, &firi);
                secj = atoi(sec);
                fprintf(MOUT, "\t\tadd,\t$a%d,\t$%d,\t$0\n", secj, firj);
            }break;
			case RETP :{
			    fprintf(MOUT, "\t\tsubi,\t$gp,\t$gp,\t4\n");
				fprintf(MOUT, "\t\tlw,\t$ra,\t0($gp)\n");
				fprintf(MOUT, "\t\tsubi,\t$gp,\t$gp,\t4\n");
				fprintf(MOUT, "\t\tlw,\t$sp,\t0($gp)\n");
				fprintf(MOUT, "\t\tsubi,\t$gp,\t$gp,\t4\n");
				for(desi = 25; desi > 8; desi--){
					fprintf(MOUT, "\t\tlw,\t$%d,\t0($gp)\n", desi);
					fprintf(MOUT, "\t\tsubi,\t$gp,\t$gp,\t4\n");
				}
				fprintf(MOUT, "\t\tlw,\t$%d,\t0($gp)\n", desi);
				fprintf(MOUT, "\t\tjr,\t$ra\n");
                recoverreg();
			}break;
			case RETF :{
			    fprintf(MOUT, "\t\tsubi,\t$gp,\t$gp,\t4\n");
				fprintf(MOUT, "\t\tlw,\t$ra,\t0($gp)\n");
				fprintf(MOUT, "\t\tsubi,\t$gp,\t$gp,\t4\n");
				fprintf(MOUT, "\t\tlw,\t$v0,\t4($sp)\n");
				fprintf(MOUT, "\t\tlw,\t$sp,\t0($gp)\n");
				fprintf(MOUT, "\t\tsubi,\t$gp,\t$gp,\t4\n");
				for(desi = 25; desi > 8; desi--){
					fprintf(MOUT, "\t\tlw,\t$%d,\t0($gp)\n", desi);
					fprintf(MOUT, "\t\tsubi,\t$gp,\t$gp,\t4\n");
				}
				fprintf(MOUT, "\t\tlw,\t$%d,\t0($gp)\n", desi);
				fprintf(MOUT, "\t\tjr,\t$ra\n");
				recoverreg();
			}break;
			default :{}break;
		}
	}
}

