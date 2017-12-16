#define INIEXPOSIZE 1024
int count = 0; //global variable 
int top = 0; // index of stack


typedef struct _shadowstackelem {
	char * funcname; // function name of current activation
	unsigned int ts; // time stamp of 
	unsigned int rms;
	int cost;
} shadowstackelem;

typedef struct _shadowstack {
	struct _shadowstackelem * sdstack;
	unsigned long stacksize;
	unsigned long exposize;
} shadowstack;

shadowstackelem * createstacknode(shadowstack * psstack);
shadowstack * createshadowstack();
void call(char * funcname);
int callexit();
void read(unsigned long int startaddr, unsigned int length);
void write(unsigned long int startaddr, unsigned int length);
