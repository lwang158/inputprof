#include "inputpro.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int expandstack(shadowstack * psstack){ // each expand we increase psstack->exposize elements
	shadowstackelem * newstackelements;
	long unsigned i;
	long unsigned newstacksize;
	long unsigned currentstactsize;
	if (psstack == NULL){
		printf("expandstack(): shadow stack is NULL.\n");
		return -1;
	}
	currentstactsize = psstack->stacksize;
	newstacksize = currentstactsize*2;
	newstackelements = (struct shadowstackelem *)calloc(newstacksize,sizeof(struct _shadowstackelem));
	if (newstackelements == NULL){
		printf("expandstack(): memory allocation not success\n");
		return -1;
	} else {  // expand psstack->stackelements with newstacksize size of stack elements
		for (i = 0;i<currentstactsize;i++){ // elements copy from old to new
			newstackelements[i]=psstack->stackelements[i];
		}
		free(psstack->stackelements); // free the memory allocated previously
		psstack->stackelements = newstackelements;
		psstack->stacksize = newstacksize;
		
		return 0;
		
	}
	
}
struct _shadowstackelem * topstackelem(shadowstack * psstack){
	if (psstack == NULL){
		printf("topstackelem(): shadow stack is NULL.\n");
		return NULL;
	}
	if (psstack->top == 0){
		printf("stack is empty \n");
		return NULL;
	} else {
		return psstack->stackelements[psstack->top -1];
	}
}

int emptystack(shadowstack * psstack){
	if (psstack == NULL){
		printf("emptystack(): stack pointer is NULL\n");
		return -1;
	}
	if (psstack->top == 0) return 0;
	else return -2;
}

int pushstackelem(shadowstack * psstack, char * funcname){
	int expand;
	if (psstack == NULL || funcname == NULL){
		printf("createstacknode(): stack pointer or function name is NULL. \n");
		return -1;
	}
	if (psstack->top + 1 >= psstack->stacksize){ // need to expand stack size;
		expand=expandstack(psstack);
		if (expand != 0){
			printf("pushstackelem(): expandstack() not succeed\n");
			return -1;
		}
	} 
	psstack->stackelements[psstack->top]->funcname = funcname;
	psstack->stackelements[psstack->top]->ts = count;
	psstack->stackelements[psstack->top]->rms = 0;
	psstack->stackelements[psstack->top]->cost = conscost;
	psstack->elementsnum++;
	psstack->top++;
	return 0;
}

int popstackelem(shadowstack * psstack){
	if (psstack == NULL){
		printf("popstackelem(): stack pointer is NULL\n");
		return -1;
	}
	if (psstack->top==0){
		printf("stack is empty\n");
		return -1;
	} else {
		psstack->top--;
		psstack->elementnum--;
		return 0;
	}
	
	
}
shadowstack * createshadowstack(){
	shadowstack * psstack;
	psstack = (shadowstack *) malloc (sizeof(shadowstack));
	psstack->stackelements = (struct shadowstackelem *)calloc(INIEXPOSIZE,sizeof(struct _shadowstackelem));
	
	if (!psstack || !psstack->stackelements) {
		printf("Error in createshadowstack(), momory allocation not success\n");
		return NULL;
	} else {
		psstack -> top = 0; // stack starts from 0, top is unsigned long type
		psstack -> stacksize = INIEXPOSIZE; // INIEXPOSIZE is the initial size of the stack.
		psstack -> elementsnum = 0; // the initial elementnum is 0.
		return psstack;
	}
}

void call(shadowstack * psstack,char * funcname) {
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

