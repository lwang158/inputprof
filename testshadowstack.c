# include<stdlib.h>
# include<stdio.h>
# include<string.h>
# include "hashmap.h"
# include "inputpro.h"

typedef struct datastruct{
	char keystring[30];
	int number;
}datas;

 comp(int i){
	printf("the address of i as comp's parameter is %p\n",&i);
}
 
int main () {
	int i,length;
	int error;
	hashmap * hmap;
	char key_string[256];
	datas * value;
	
	shadowstack * psstack;
	struct _shadowstackelem * ssnode;
	int popresult;
	psstack = createshadowstack();
	if (psstack == NULL) {
		printf("cannot create shadowstack\n");
		return -1;
	}
	unsigned long index, size = 1024;
	//size = size * 1024*2*64;
    	printf("after createshadowstack()\n");
	
	if(emptystack(psstack)==0)printf("the psstack is empty\n");
	
	for (index=0;index<size;index++){
		value = (datas *)malloc(sizeof(struct datastruct));
		sprintf(value->keystring,"%lx",index);
                //printf("entering outter for, current size = %lu, value->string is %s. \n",size, value->keystring);
		length = strlen(value->keystring);
                //printf("keystring+/0's  length is %d. \n", length+1);
		for (i=length+2;i>=2;i--){ // add ox prefix to keystring
                        value->keystring[i] = value->keystring[i-2];// move a[i-2] to a[i]
		}
		value->keystring[0]='0';
		value->keystring[1]='x';            
		//printf("after inner for, the value->keystring is %s\n",value->keystring);
		value->number = index;
		error = pushstackelem(psstack, value->keystring);
		if (error == -1) printf("pushstackelem(): there is an error in %luth round\n", index);
	}
	printf("after pushstackelem() test, psstack->stacksize=%lu, psstack->elementsnum=%lu. \n\n",psstack->stacksize, psstack->elementsnum);
	if(emptystack(psstack)==0)printf("the psstack is empty\n");
	else printf("now the psstack is not empty\n");
	
	for (index=0; index<size; index++){
		printf("------start topstackelem() & popstackelem() test:\n" );
		ssnode = topstackelem(psstack);
		if (ssnode != NULL){
			printf("current top node, ssnode->funcname is %s\n",ssnode->funcname);
		} else {
			printf("popstackelem() fail, empty stack\n");
		}
		printf("start popstackelem()");
		popresult = popstackelem(psstack);
		if (popresult == 0){
			printf("pop stack success, psstack->elementsnum=%lu\n",psstack->elementsnum);
		} else {
			printf("pos stack failure: there is an error in %luth round\n\n", index);
		}
	}
	printf("after topstackelem() & popstackelem() test\n");
/*	for (index=5;index<1000;index++) {
		value = (datas *)malloc(sizeof(struct datastruct));
		sprintf(value->keystring,"%lx",index);
		length = strlen(value->keystring);
		for (i=length+2;i>=2;i--){ // add ox prefix to keystring
			value->keystring[i] = value->keystring[i-2];// move a[i-2] to a[i]
		}
		value->keystring[0]='0';
		value->keystring[1]='x';
		value->number = index;
		
		error = hashmapremove(hmap, value->keystring);
		if (error < 0) printf("hashmapremove(): there is an error in %luth round\n\n", index);
	}
	printf("after hashmapremove() test\n\n");
	printf("after hashmapremove() test, hmap->slotsize=%lu, hmap->totalelem=%lu. \n\n",hmap->slotsize, hmap->totalelem);
	for (index=0;index<size;index++){
		value = (datas *)malloc(sizeof(struct datastruct));
		sprintf(value->keystring,"%lx",index);
                //printf("entering outter for, current size = %lu, value->string is %s. \n",size, value->keystring);
		length = strlen(value->keystring);
                //printf("keystring+/0's  length is %d. \n", length+1);
		for (i=length+2;i>=2;i--){ // add ox prefix to keystring
                        value->keystring[i] = value->keystring[i-2];// move a[i-2] to a[i]
		}
		value->keystring[0]='0';
		value->keystring[1]='x';
                //printf("after inner for, the value->keystring is %s\n",value->keystring);
		value->number = index;
		error = hashmapput(hmap, value->keystring, value->number);
		if (error == -1) printf("2nd hashmapput(): there is an error in %luth round\n", index);
	}
	printf("add elements again, hmap->slotsize=%lu, hmap->totalelem=%lu. \n\n",hmap->slotsize, hmap->totalelem);
*/	return 1;
}
