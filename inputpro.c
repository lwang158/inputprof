#include "inputpro.h"
#include "shadowstack.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

unsigned int count = 0;

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
		exit();
	}

}

void collect(shadowstack * psstack){
	if (psstack == NULL){
		printf("collect(): stack pointer is NULL\n");
	}
	printf("collect(): collecting data functions needs to be finished\n");
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

