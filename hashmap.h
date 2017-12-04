typedef struct _hashmap {
	char * key;
	int timestamp;
	hashmap * next;
}hashmap;

void createhashmap(hashmap * hmap, int size);
void destroyhashmap(hashmap * hmap);
int hashmapput(hashmap * hmap, char * key, int timestamp);
int hashmapget(hashmap * hmap, char * key, int timestamp);

