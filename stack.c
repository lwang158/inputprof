#include "inputpro.h"

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

