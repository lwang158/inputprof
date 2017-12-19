#include "inputpro.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


unsigned int count = 0;

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
	newstackelements = (struct _shadowstackelem *)calloc(newstacksize,sizeof(struct _shadowstackelem));
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
		printf("topstackelem(): stack is empty \n");
		return NULL;
	} else {
		return &(psstack->stackelements[psstack->top -1]);
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

int pushstackelem(shadowstack * psstack, char * funcname, unsigned int count){
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
	(psstack->stackelements[psstack->top]).funcname = funcname;
	(psstack->stackelements[psstack->top]).ts = count;//count;
	(psstack->stackelements[psstack->top]).rms = 0;
	(psstack->stackelements[psstack->top]).cost = 0; // getcost() function;
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
		printf("popstackelem(): stack is empty\n");
		return -1;
	} else {
		psstack->top--;
		psstack->elementsnum--;
		return 0;
	}
	
	
}

shadowstack * createshadowstack(){
	shadowstack * psstack;
	psstack = (shadowstack *) malloc (sizeof(shadowstack));
	psstack->stackelements = (struct _shadowstackelem *)calloc(INIEXPOSIZE,sizeof(struct _shadowstackelem));
	
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


unsigned int getcost(){
	printf("getcost(): to be finished\n");
	return 0;
}

void call(shadowstack * psstack,char * funcname) {
	count++;
	int pushresult;
	
	pushresult = pushstackelem(psstack, funcname, count);
	if (pushresult != 0){
		printf("call(): push stack error.\n");
		exit(0);
	}

}

void collect(shadowstack * psstack){
	if (psstack == NULL){
		printf("collect(): stack pointer is NULL\n");
	}
	printf(":ollect(): collecting data functions needs to be finished\n");
}

int callreturn(shadowstack * psstack) {
	int popresult;
	
	if (psstack == NULL) {
		printf("callreturn(): stack pointer is NULL\n");
		return -1;
	}
	collect(shadowstack * psstack);
	
	if (psstack->top >1){ // stack has at least two elements.
		psstack->stackelements[psstack->top - 2].rms += psstack->stackelements[psstack->top - 1].rms;
	} 
	popresult = popstackelem(psstack);
}

void read(unsigned long startaddr, unsigned int length) {
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

