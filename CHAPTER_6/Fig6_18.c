typedef struct node {
valuet data;
struct node *next;
} Node;
Node *top; // top of stack
void push(valuet item) {
Node *oldnode;
Node *newnode;
newnode = malloc(sizeof(Node));
newnode->data = item;
do {
oldnode = top;
newnode->next = oldnode;
}
while (compareandswap(top,oldnode,newnode) != oldnode);
}
valuet pop() {
Node *oldnode;
Node *newnode;
do {
oldnode = top;
if (oldnode == NULL)
return NULL;
newnode = oldnode->next;
}
while (compareandswap(top,oldnode,newnode) != oldnode);
return oldnode->data;
}
