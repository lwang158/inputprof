# include<stdlib.h>
# include<stdio.h>
# include<string.h>
# include"hashmap.h"

typedef struct datastruct{
	char keystring[30];
	int number;
}datas;

 comp(int i){
	printf("the address of i as comp's parameter is %p\n",&i);
}
 
int main () {
	int index,i,length;
	int error;
	hashmap * hmap;
	char key_string[256];
	datas * value;
	
	unsigned long size = 1024*1024;
	//size = size * 1024*2*64;
	hmap = createhashmap();
	if (hmap == NULL) {
		printf("create hashmap error\n");
		return -1;
	}
        printf("after createhashmap()\n");
	for (index=1;index<size;size--){
		value = (datas *)malloc(sizeof(struct datastruct));
		sprintf(value->keystring,"%lx",size);
                printf("outter for, current size = %lu, value->string is %s. \n",size, value->keystring);
		length = strlen(value->keystring);
                printf("keystring+/0's  length is %d. \n", length+1);
		for (i=length+2;i>=2;i--){ // add ox prefix to keystring
                        value->keystring[i] = value->keystring[i-2];// move a[i-2] to a[i]
		}
		value->keystring[0]='0';
		value->keystring[1]='x';
                printf("after inner for, the value->keystring is %s\n",value->keystring);
		value->number = size;
		error = hashmapput(hmap, value->keystring, value->number);
		if (error != -1) printf("there is no error in %dth round\n", index);
	}
	
	return 1;
}
