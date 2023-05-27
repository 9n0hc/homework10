#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int key;
    struct node* left;
    struct node* right;
} Node;

/* for stack */
#define MAX_STACK_SIZE 20
Node* stack[MAX_STACK_SIZE];
int top = -1;

/* for queue */
#define MAX_QUEUE_SIZE 20
Node* queue[MAX_QUEUE_SIZE];
int front = -1;
int rear = -1;

int initializeBST(Node** h);
void recursiveInorder(Node* ptr); /* recursive inorder traversal */
int insert(Node* head, int key); /* insert a node to the tree */
int freeBST(Node* head); /* free all memories allocated to the tree */

/* functions that you have to implement */
void iterativeInorder(Node* ptr); /* iterative inorder traversal */
void levelOrder(Node* ptr); /* level order traversal */
int deleteNode(Node* head, int key); /* delete the node for the key */
Node* pop();
void push(Node* aNode);
Node* deQueue();
void enQueue(Node* aNode);

/* you may add your own defined functions if necessary */

void printStack();

int main()
{
    char command;
    int key;
    Node* head = NULL;

    do {
        printf("\n\n");
        printf("----------------------------------------------------------------\n");
        printf("                   Binary Search Tree #2                        \n");
        printf("----------------------------------------------------------------\n");
        printf(" Initialize BST       = z                                       \n");
        printf(" Insert Node          = i      Delete Node                  = d \n");
        printf(" Recursive Inorder    = r      Iterative Inorder (Stack)    = t \n");
        printf(" Level Order (Queue)  = l      Quit                         = q \n");
        printf("----------------------------------------------------------------\n");

        printf("Command = ");
        scanf(" %c", &command);

        switch (command) {
        case 'z':
        case 'Z':
            initializeBST(&head);
            break;
        case 'q':
        case 'Q':
            freeBST(head);
            break;
        case 'i':
        case 'I':
            printf("Your Key = ");
            scanf("%d", &key);
            insert(head, key);
            break;
        case 'd':
        case 'D':
            printf("Your Key = ");
            scanf("%d", &key);
            deleteNode(head, key);
            break;

        case 'r':
        case 'R':
            recursiveInorder(head->left);
            break;
        case 't':
        case 'T':
            iterativeInorder(head->left);
            break;

        case 'l':
        case 'L':
            levelOrder(head->left);
            break;

        case 'p':
        case 'P':
            printStack();
            break;

        default:
            printf("\n       >>>>>   Concentration!!   <<<<<     \n");
            break;
        }

    } while (command != 'q' && command != 'Q');

    return 1;
}

int initializeBST(Node** h)
{
    /* if the tree is not empty, then remove all allocated nodes from the tree*/
    if (*h != NULL)
        freeBST(*h);

    /* create a head node */
    *h = (Node*)malloc(sizeof(Node));
    (*h)->left = NULL; /* root */
    (*h)->right = *h;
    (*h)->key = -9999;

    top = -1;

    front = rear = -1;

    return 1;
}

void recursiveInorder(Node* ptr)
{
    if (ptr) {
        recursiveInorder(ptr->left);
        printf(" [%d] ", ptr->key);
        recursiveInorder(ptr->right);
    }
}

/**
 * textbook: p 224
 */
void iterativeInorder(Node* node)
{
    top = -1; // reset the stack

    while (1) {
        while (node) {
            push(node);
            node = node->left;
        }

        node = pop();

        if (!node)
            break;

        printf(" [%d] ", node->key);

        node = node->right;
    }
}

/**
 * textbook: p 225
 */
void levelOrder(Node* ptr)
{
    if (ptr == NULL)
        return;

    enQueue(ptr);

    while (front != rear) {
        ptr = deQueue();
        printf(" [%d] ", ptr->key);

        if (ptr->left)
            enQueue(ptr->left);
        if (ptr->right)
            enQueue(ptr->right);
    }
}

int insert(Node* head, int key)
{
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->key = key;
    newNode->left = NULL;
    newNode->right = NULL;

    if (head->left == NULL) {
        head->left = newNode;
        return 1;
    }

    /* head->left is the root */
    Node* ptr = head->left;

    Node* parentNode = NULL;
    while (ptr != NULL) {

        /* if there is a node for the key, then just return */
        if (ptr->key == key)
            return 1;

        /* we have to move onto children nodes,
         * keep tracking the parent using parentNode */
        parentNode = ptr;

        /* key comparison, if current node's key is greater than input key
         * then the new node has to be inserted into the right subtree;
         * otherwise the left subtree.
         */
        if (ptr->key < key)
            ptr = ptr->right;
        else
            ptr = ptr->left;
    }

    /* linking the new node to the parent */
    if (parentNode->key > key)
        parentNode->left = newNode;
    else
        parentNode->right = newNode;
    return 1;
}

int deleteNode(Node* head, int key)
{
    // TODO: Implement the deleteNode function
    return 0;
}

void freeNode(Node* ptr)
{
    if (ptr) {
        freeNode(ptr->left);
        freeNode(ptr->right);
        free(ptr);
    }
}

int freeBST(Node* head)
{

    if (head->left == head) {
        free(head);
        return 1;
    }

    Node* p = head->left;

    freeNode(p);

    free(head);
    return 1;
}

Node* pop()
{
    if (top == -1)
        return NULL;

    return stack[top--];
}

void push(Node* aNode)
{
    if (top >= MAX_STACK_SIZE - 1) {
        printf("Stack is full.\n");
        return;
    }

    stack[++top] = aNode;
}

Node* deQueue()
{
    if (front == rear)
        return NULL;

    return queue[++front];
}

void enQueue(Node* aNode)
{
    if (rear == MAX_QUEUE_SIZE - 1) {
        printf("Queue is full.\n");
        return;
    }

    queue[++rear] = aNode;
}

void printStack()
{
    printf("Stack: ");
    for (int i = 0; i <= top; i++) {
        printf("%d ", stack[i]->key);
    }
    printf("\n");
}