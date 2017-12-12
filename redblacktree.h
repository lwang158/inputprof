#define BLACK 1
#define RED 0

typedef struct _redblacktree{
	int value;
	bool color;
	RBTNode *lefttree, *righttree, *parent;
	
} rbtnode;

rbtnode * grandparent(rbtnode * p);
rbtnode * uncle(rbtnode * p);
rbtnode * sibling( rbtnode * p);
void rotate_right(rbtnode * p);
void rotate_left(rbtnode * p);
void inorder(rbtnode * p);
char * outputcolor (bool color);
rbtnode * getsmallestchild(rbtnode * p);
bool delete_child(rbtnode * p, int data);
void delete_one_child(rbtnode * p);
void delete_case(rbtnode * p);
void insert(rbtnode * p, int data);
void insert_case(rbtnode * p);
void deletetree(rbtnode * p);
void inorder(rbtnode * p);
void insert(int x);
bool deletevalue (int data);
