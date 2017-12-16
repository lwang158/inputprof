#define INIEXPOSIZE 1024
int count = 0; //global variable 



typedef struct _shadowstackelem {
	char * funcname; // function name of current activation
	unsigned int ts; // time stamp of 
	unsigned int rms;
	int cost;
} shadowstackelem;

typedef struct _shadowstack {
	struct _shadowstackelem * stackelemets;
	unsigned long top;
	unsigned long stacksize; // current size of the stack
	unsigned long exposize; // the size for the next expand
} shadowstack;

shadowstackelem * createstackelem(shadowstack * psstack);
shadowstack * createshadowstack();
int expandstack(shadowstack * psstack);
void call(char * funcname);
int callexit();
void read(unsigned long int startaddr, unsigned int length);
void write(unsigned long int startaddr, unsigned int length);
