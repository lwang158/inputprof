
void call(shadowstack * psstack, char * funcname);
int callreturn();
unsigned int getcost();
void collect(shadowstack * psstack); //cost collection to be finished
void read(unsigned long startaddr, unsigned int length);
void write(unsigned long startaddr, unsigned int length);
