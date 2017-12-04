int count = 0; //global variable 
int top = 0; // index of stack

typedef struct _shadowstack {
	char * funcname; // function name of current activation
	unsigned int ts; // time stamp of 
	unsigned int rms;
	int cost;
} shadowstack;

void call(char *);
int callexit();
void read(unsigned long int startaddr, unsigned int length);
void write(unsigned long int startaddr, unsigned int length);
