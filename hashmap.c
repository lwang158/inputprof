#include "hashmap.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


hashmap * createhashmap(){
	hashmap * phashmap = (hashmap*)malloc(sizeof(hashmap));
	phashmap->elements = (hashmapelem *)calloc(SLOTLENGTH, sizeof(hashmapelem))
	if (!phashmap || !phashmap->elements) {
		printf("Error in createhashmap(), momory allocation not success\n");
		return NULL;
	}
	else {
		phashmap->slotsize = 0;
		phashmap->totalelem = 0;
		return phashmap;
	}
}

void destroyhashmap(hashmap * hmap){
	hashmap* hm = (hashmap*) hmap;
	free(hm->elements)
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
	hashmapelem * p, * q;
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
	index = keytoindex(startaddr);
	if (index == -1 ){
		printf("Error in hashmapput(), keytoindex error.\n");
		return -1;
	}
	if (hmap->element[index] == NULL){ // the index slot is empty, put the first element
		p = (hashmapelem *)malloc(sizeof(struct hashmapelem));
		if (p==NULL){
			printf("Error in hashmapput() 1, hashmapelem allocation error.\n"); 
			return -1;
		}
		p->key = key;
		p->next = NULL;
		p->value = value;
		hmap->element[index] = p;
		
		hmap->slotsize++;
		hmap->totalelem++;
		
		return MAP_SUCCESS;
	}
	q = hmap->element[index];  // the index slot is not empty
	if (!strcmp(q->key, key)) { // the put element is the first elem
		oldvalue = q->value;
		q->value = value;
		return oldvalue;
	}
	while(q->next != NULL){ // the put element is in the list
		if (!strcmp(q->next->key, key)) {
			oldvalue = q->next->value;                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                            
			q->next->value = value;
			return oldvalue;
		}
		q=q->next;
	}
	p = (hashmapelem *)malloc(sizeof(struct hashmapelem)); //the put element is not in the list. put the new element at the first position
	if (p==NULL){
		printf("Error in hashmapput() 2, hashmapelem allocation error.\n"); 
		return -1;
	}
	p->key = key;
	p->value = value;
	p->next = hmap->element[index]->next; // ***here needs to be very careful. insert the put node as the first node
	hmap->element[index] = p;
	hmap->totalelem++;
	return MAP_SUCCESS;
}

int hashmapget(hashmap * hmap, char * key, int value) {
	unsigned int index;
	hashmapelem * p;
	
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
		p = hmap->element[index];
		if (!strcmp(p->key, key)) 
			return p->value;
		while (p->next!=NULL){
			if (!strcmp(p->next->key, key))
				return p->next->value;
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