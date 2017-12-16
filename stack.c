#include "inputpro.h"

int expandstack(shadowstack * psstack){
	
}

shadowstackelem * createstackelem(shadowstack * psstack){
	shadowstackelem * ssnode;
	int expand;
	if (psstack == NULL){
		printf("createstacknode(): psstack is NULL. \n");
		return NULL;
	}
	ssnode = (struct _shadowstackelem *)malloc(sizeof(struct _shadowstackelem));
	if (ssnode == NULL){
		printf("fail to create a new shadownode.\n");
		return NULL;
	} else { // successfully create a stack element
		if (psstack->top + 1 >= psstack->stacksize){ // need to expand stack length;
			expand=expandstack(psstack);
			if ()
		} 
	}
}

shadowstack * createshadowstack(){
	shadowstack * psstack;
	psstack = (shadowstack *) malloc (sizeof(shadowstack));
	psstack->stackelements = (struct shadowstackelem *)calloc(INIEXPOSIZE,sizeof(struct _shadowstackelem));
	
	if (!psstack || !psstack->stackelements) {
		printf("Error in createshadowstack(), momory allocation not success\n");
		return NULL;
	}
	else {
		psstack -> stacksize= 0;
		psstack -> top = 0;
		psstack -> exposize = INIEXPOSIZE;
		return phashmap;
	}
}

void call(char * funcname) {
	count++;
	top++;

	s[top].funcname = funcname;
	s[top].ts = count;
	s[top].rms = 0;
	s[top].cost = 0;	
}

int callexit() {
	if (top == 0) 
		return 1;//error, return 1;
	else { 
		s[top-1].rms += s[top].rms;
		top--;
		return 0;
	}
	 
}

void read(unsigned long int startaddr, unsigned int length) {
	unsigned long int i;
	unsigned int j,l;
	j = length; // j records byte length
	for (i=startaddr; j > 0; j--){ // i is the current byte address
		if (ts[i] < s[top].ts){//first access byte cell
			s[top].rms++;
		} 
		if (ts[i] != 0) {
			for (l=top;s[l].ts <= ts[i];l--)//find max index in s, that s[l].ts <= ts[i]
				break;
			s[l].rms--;
		}
		ts[i] = count;
		i += 8;// continue on next byte
	}
		
}

void write(unsigned long int  startaddr, unsigned int length) {
	unsigned long int i;
	unsigned int j = length;
	for (i = startaddr; j > 0; j--){
		ts[i] = count;
		i += 8;
	}
}

