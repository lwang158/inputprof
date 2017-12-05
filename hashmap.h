#define MAXNUM 268435456; //max number of hashmap elements
#define MAP_MISS -3;
#define MAP_FULL -2;
#define MAP_EXCEED -1;
#define MAP_SUCCESS 0;

typedef struct _hashmap {
	char * key;
	int value;
	hashmap * next;
}hashmap;

typedef struct _hashmapelem {
	hashmap element[MAXNUM];
	unsigned int n; // current size of hashmap
} hashmapelem;

extern hashmap * newhashmap();

hashmap * createhashmap();
void destroyhashmap(hashmap * hmap);
int hashmapput(hashmap * hmap, char * key, int value);
int hashmapget(hashmap * hmap, char * key, int value);

