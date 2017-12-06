#define MAXNUM 268435456; //max number of hashmap elements
#define MAP_MISS -3;
#define MAP_FULL -2;
#define MAP_EXCEED -1;
#define MAP_SUCCESS 0;

typedef struct _hashmapelem {
	char * key;
	int value;
	hashmapelem * next;
}hashmapelem;

typedef struct _hashmap {
	hashmapelem * element[MAXNUM];
	unsigned int m; // size of ELEMENT_LENGTH
} hashmap;


hashmap * createhashmap();
void destroyhashmap(hashmap * hmap);
int keytoindex(char * key);
int hashmapput(hashmap * hmap, char * key, int value);
int hashmapget(hashmap * hmap, char * key, int value);
int hash(char * key);
