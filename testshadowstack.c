# include<stdlib.h>
# include<stdio.h>
# include<string.h>
# include "hashmap.h"
# include "inputprof.h"

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
	psstack = cr
	unsigned long index, size = 1024*1024;
	//size = size * 1024*2*64;
	hmap = createhashmap();
	if (hmap == NULL) {
		printf("create hashmap error\n");
		return -1;
	}
        //printf("after createhashmap()\n");
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
		if (error == -1) printf("hashmapput(): there is an error in %luth round\n", index);
	}
	printf("after hashmapput() test, hmap->slotsize=%lu, hmap->totalelem=%lu. \n\n",hmap->slotsize, hmap->totalelem);
	for (index=0; index<size; index++){
		value = (datas *)malloc(sizeof(struct datastruct));
		sprintf(value->keystring,"%lx",index);
		length = strlen(value->keystring);
		for (i=length+2;i>=2;i--){ // add ox prefix to keystring
			value->keystring[i] = value->keystring[i-2];// move a[i-2] to a[i]
		}
		value->keystring[0]='0';
		value->keystring[1]='x';
		value->number = index;
		//printf("start hashmapget(), keystring: %s, keyvalue: %d \n",value->keystring, value->number);
		error = hashmapget(hmap, value->keystring, value->number);
		if (error < 0) printf("hashmapget(): there is an error in %luth round\n\n", index);
	}
	printf("after hashmapget() test\n");
	for (index=5;index<1000;index++) {
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
	return 1;
}
