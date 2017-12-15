#include "hashmap.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


hashmap * createhashmap(){
	hashmap * phashmap = (hashmap*)malloc(sizeof(hashmap));
        int i;
        printf("entering createhashmap\n");
        for (i=0;i<SLOTLENGTH;i++){
                phashmap->elements=(struct _hashmapelem **)calloc(SLOTLENGTH,sizeof(struct _hashmapelem *));// ****errorhere, corrected
                if ((phashmap->elements[i])) printf("calloc() hashmapelem problem, elements[%d] not NULL. \n",i);
                //printf("print hashmap->elements[%d]: %p\n",i,phashmap->elements[i]);
        }
        printf("hashmap and hashmap->elements create finished\n");
	//phashmap->elements = (struct _hashmapelem *)calloc(SLOTLENGTH, sizeof(struct _hashmapelem));
	if (!phashmap || !phashmap->elements) {
		printf("Error in createhashmap(), momory allocation not success\n");
		return NULL;
	}
	else {
		phashmap->slotsize = 0;
		phashmap->totalelem = 0;
		return phashmap;
	}
        printf("exit createhashmap\n");
}

void destroyhashmap(hashmap * hmap){
	hashmap* hm = (hashmap*) hmap;
	free(hm->elements);
	free(hm);
}


unsigned int keytoindex(char * key){  // return -1 means error
	unsigned long int keyint;
	unsigned int index;
	if (key == NULL) {
		printf("Error in keytoindex(), empty key.\n");
		return -1;
	}
	keyint = stringtoint(key);
	index = keyint%SLOTLENGTH;
	if (index >= 0)
		return index;
	else 
		return -1;
}

int hashmapput(hashmap * hmap, char * key, int value){  // return oldvalue of elem <key,value>
	struct _hashmapelem * p, * q;
	char * startaddr = key;
	int oldvalue;
	unsigned int index;
	
	if (hmap == NULL) {
		printf("Error in hashmapput(), empty hmap.\n"); 
		return -1;
	}
	
	if (key == NULL) {
		printf("Error in hashmapput(), empty key.\n"); 
		return -1;
	}
        printf("-----------------entering hashmapput(), key is %s, value is %d,\n", key, value);
	index = keytoindex(startaddr);
        printf("index is %d\n", index);
	if (index == -1 ){
		printf("Error in hashmapput(), keytoindex error.\n");
		return -1;
	}
	if (hmap->elements[index] == NULL){ // the index slot is empty, put the first element
                printf("elements[%u] position is NULL. \n",index);
		p = (struct _hashmapelem *)malloc(sizeof(struct _hashmapelem));
		if (p==NULL){
			printf("Error in hashmapput() 1, hashmapelem allocation error.\n"); 
			return -1;
		}
		p->key = key;
		p->next = NULL;
		p->value = value;
		hmap->elements[index] = p;
		//printf("successfully added one element to elements[%d].\n", index);
		hmap->slotsize++;
		hmap->totalelem++;
		
		return MAP_SUCCESS;
	}
	q = hmap->elements[index];  // the index slot is not empty
	if (!strcmp(q->key, key)) { // the put element is the first elem
                printf("the put element is the first element of elements[%u]\n",index);
		oldvalue = q->value;
		q->value = value;
		return oldvalue;
	}
	while(q->next != NULL){ // the put element is in the list
		if (!strcmp(q->next->key, key)) {
                        
                        printf("the put element is in the list of elements[%u]\n",index);
			oldvalue = q->next->value;                                                                                                                    q->next->value = value;
			return oldvalue;
		}
		q=q->next;
	}
	p = (struct _hashmapelem *)malloc(sizeof(struct _hashmapelem)); //the put element is not in the list. put the new element at the first position
	
        printf("the put element is not in the list of elements[%u]\n",index);
        if (p==NULL){
		printf("Error in hashmapput() 2, hashmapelem allocation error.\n"); 
		return -1;
	}
	p->key = key;
	p->value = value;
	p->next = hmap->elements[index]->next; // ***here needs to be very careful. insert the put node as the first node
	hmap->elements[index] = p;
	hmap->totalelem++;
	return MAP_SUCCESS;
}

int hashmapget(hashmap * hmap, char * key, int value) {
	unsigned int index;
	struct _hashmapelem * p;
	printf("---------entering hashmapget().\n");
	if (hmap == NULL) {
		printf("Error in hashmapget(), empty hmap.\n"); 
		return -1;
	}
	
	if (key == NULL) {
		printf("Error in hashmapget(), empty key");
		return MAP_MISS;
	}
	
	index = keytoindex(key);
	
	if (index != -1){
		p = hmap->elements[index];
		printf("find index:%u, hmap->elements[%u] has key:%s\n", index, index, key);
		if (!strcmp(p->key, key)) {// the first element's key matches. 
			printf(" slot element match.\n");
			return p->value;
		}
		while (p->next!=NULL){
			if (!strcmp(p->next->key, key)) {} // the key is in the list of hmap->elements[index]
				printf("list element matches.\n");
				return p->next->value;
		}
			p = p->next;
		}
		return MAP_MISS;
	} 
	else {
		return MAP_MISS;
	}
}

unsigned long int stringtoint(char * str){
	unsigned long int intaddr;
	if (str == NULL) {// str is NULL
		printf("Error in stringtoint(), empty str\n");
		return -1;
	}
	else {
		intaddr = strtol(str, NULL, 0);
		return intaddr;
	}
}

int currentslotsize(hashmap * hmap){
	hashmap * ph = (hashmap *) hmap;
	if(ph == NULL) {
		printf("Error in currentslotsize(), empty hmap\n");
		return -1;
	}
	else {
		return ph->slotsize;
	}

}

int currentelemsize(hashmap * hmap){
	hashmap * ph = (hashmap *) hmap;
	if(ph == NULL) {
		printf("Error in currentelemsize(), empty hmap\n");
		return -1;
	}
	else {
		return ph->totalelem;
	}
}
