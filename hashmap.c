#include "hashmap.h"
#include <stdio.h>
#include <stdlib.h>


hashmap * createhashmap(){
	hashmap * phashmap = (hashmap*)malloc(sizeof(hashmap));
	if (!phashmap) 
		return null;
	else {
		phashmap.n = 0;
		return phashmap;
	}
}

void destroyhashmap(hashmap * hmap){
	hashmap* m = (hashmap*) hmap;
	free(m);
}


int keytoindex(char * key){  // unfinished
	unsigned int index;
	index = hash(key);
	if index is leagal
		return index;
	else 
		return error;
}

int hashmapput(hashmap * hmap, char * key, int value){  // return oldvalue of elem <key,value>
	hashmapelem * p, * q;
	char * startaddr = key;
	int oldvalue;
	int d = keytoindex(startaddr);
	if (hmap->element[d] == NULL){ // the element list is empty, put first element
		p = (hashmapelem *)malloc(sizeof(struct hashmapelem));
		p->key = key;
		p->next = NULL;
		p->value = value;
		hmap->element[d] = p;
		return MAP_SUCCESS;
	}
	q = hmap->element[d];
	if (q->key == key) { // the put element is the first elem
		oldvalue = q->value;
		q->value = value;
		return oldvalue;
	}
	while(q->next != NULL){ // the put element is in the list
		if(q->next->key == key){
			oldvalue = q->next->value;
			q->next->value = value;
			return oldvalue;
		}
		q=q->next;
	}
	p = (hashmapelem *)malloc(sizeof(struct hashmapelem)); //the put element is not in the list. 
	p->key = key;
	p->value = value;
	p->next = hmap->element[d]->next; // ***here needs to be very careful. insert the put node to the first node
	hmap->element[d] = p;
	return MAP_SUCCESS;
}

int hashmapget(hashmap * hmap, char * key, int value) {
	int d;
	hashmapelem * p;
	
	if (key == NULL)
		return MAP_MISS;
	
	d = keytoindex(key);
	if (d != error){
		p = hmap->element[d];
		if (p->key == key) 
			return p->value;
		while (p->next!=NULL){
			if (p->next->key == key)
				return p->next->value;
			p = p->next;
		}
		return MAP_MISS;
	} 
	else {
		return MAP_MISS;
	}
}

int hash(char * key){ // unfinished
	int index; 
	/* finish the function content*/
	return index;
}