// ���� Ž�� Ʈ���� ������ ���α׷�

#include <stdio.h>
#include <stdlib.h>

// ����ü ����.
typedef struct node {
    int key; // ��� �ĺ� Ű.
    struct node* left; // ���� ����� ���� �ڽ� ��带 ����Ű�� ������.
    struct node* right; // ���� ����� ������ �ڽ� ��带 ����Ű�� ������.
} Node;

#define MAX_STACK_SIZE 20 // ������ �ִ� ũ�⸦ 20���� ����.
Node* stack[MAX_STACK_SIZE]; // ������ �����ϱ� ���� ��� ������ �迭.
int top = -1; // ������ ž �ʱ�ȭ(�������).

#define MAX_QUEUE_SIZE 20 // ť�� �ִ� ũ�⸦ 20���� ����.
Node* queue[MAX_QUEUE_SIZE]; // ť�� �����ϱ� ����  ��� ������ �迭.
int front = -1; // ť�� front�� ��Ÿ���� ���� �ʱ�ȭ.
int rear = -1; // ť�� rear�� ��Ÿ���� ���� �ʱ�ȭ.

int initializeBST(Node** h);
void recursiveInorder(Node* ptr);
void iterativeInorder(Node* ptr);
void levelOrder(Node* ptr); 
int insert(Node** head, int key);
int deleteNode(Node** head, int key); 
Node* pop();
void push(Node* aNode);
Node* deQueue();
void enQueue(Node* aNode);
void freeNode(Node* ptr);
int freeBST(Node** head);
void printStack();

int main()
{
    char command;
    int key;
    Node* head = NULL;

    printf("[----- [������] [2022041043] -----]\n");

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
                freeBST(&head);
                break;
            case 'i':
            case 'I':
                printf("Your Key = ");
                scanf("%d", &key);
                insert(&head, key);
                break;
            case 'd':
            case 'D':
                printf("Your Key = ");
                scanf("%d", &key);
                deleteNode(&head, key);
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
                printf("\n       �߸��� �Է��Դϴ�.       \n");
                break;
        }
    } while (command != 'q' && command != 'Q');

    return 1;
}

// ���� Ž�� Ʈ���� �ʱ�ȭ�ϴ� �Լ�.
int initializeBST(Node** h)
{
    // �̹� Ʈ���� ������ ���, ���� Ž�� Ʈ���� ����.
    if (*h != NULL)
        freeBST(h); // �̹� �Ҵ�� ������ �����ϴ� freeBST �Լ� ȣ��.

    // ��� ��� ���� �� �ʱ�ȭ
    *h = (Node*)malloc(sizeof(Node)); // ���ο� ��忡 ���� �޸� �Ҵ�.
    (*h)->left = NULL; // ���� �ڽ� ��� �ʱ�ȭ.
    (*h)->right = *h; // ������ �ڽ� ��� �ʱ�ȭ.
    (*h)->key = -9999; // ��� ����� Ű �� �ʱ�ȭ.

    top = -1; // ���� �ʱ�ȭ.

    front = rear = -1; // ť �ʱ�ȭ.

    return 1;
}

// ��������� ���� ��ȸ �ϴ� �Լ�.
void recursiveInorder(Node* ptr)
{
    if (ptr) {
        recursiveInorder(ptr->left); // ���� �ڽ� ��� �湮.
        printf(" [%d] ", ptr->key); // ���� ��� ���.
        recursiveInorder(ptr->right); // ������ �ڽ� ��� �湮.
    }
}

// �ݺ������� ���� ��ȸ �ϴ� �Լ�. 
void iterativeInorder(Node* node)
{
    top = -1; // ���� �ʱ�ȭ.

    while (1) {
        while (node) {
            push(node); // ���� ��带 ���ÿ� Ǫ��.
            node = node->left; // ���� �ڽ� ���� �̵�.
        }

        node = pop(); // ���ÿ��� ��带 ��.

        // ���� ��尡 NULL(���� ��ȸ �� ��� ����X)�� ���, �ݺ��� ����.
        if (!node)
            break;

        printf(" [%d] ", node->key); // ���� ��� ���.

        node = node->right; // ������ �ڽ� ���� �̵�.
    }
}

// ���� ���� ��ȸ �Լ�.
void levelOrder(Node* ptr)
{
    // �� Ʈ���� ���, �Լ� ����.
    if (ptr == NULL)
        return;

    enQueue(ptr); // ��Ʈ ��带 ť�� ����.

    while (front != rear) {
        ptr = deQueue(); // ť���� ��带 ��带 �����Ͽ� �湮.
        printf(" [%d] ", ptr->key); // ���� ��� ���.

        if (ptr->left)
            enQueue(ptr->left); // ���� �ڽ� ��带 ����ų ���, ���� �ڽ� ��带 ť�� ����.
        if (ptr->right)
            enQueue(ptr->right); // ������ �ڽ� ��带 ť�� ����.
    }
}

// ��� ���� �Լ�.
int insert(Node** head, int key)
{
    // ���ο� ��� ���� �� �ʱ�ȭ.
    Node* newNode = (Node*)malloc(sizeof(Node)); // ���ο� ��忡 ���� �޸� �Ҵ�.
    newNode->key = key; // ���ο� ����� Ű �� ����.
    newNode->left = NULL; // ���ο� ����� ���� �ڽ� �����͸� NULL�� �ʱ�ȭ.
    newNode->right = NULL; // ���ο� ����� ������ �ڽ� �����͸� NULL�� �ʱ�ȭ.

    // Ʈ���� ������� ���, ���ο� ��带 ��Ʈ ���� ����.
    if ((*head)->left == NULL) {
        (*head)->left = newNode;
        return 1;
    }

    Node* ptr = (*head)->left; // Ž���� ���� ������ ���� �ʱ�ȭ.

    Node* parentNode = NULL; // ������ ��ġ�� �θ� ���.
    while (ptr != NULL) { // ������ ��ġ ã�� ���� Ʈ�� Ž��.
        if (ptr->key == key)
            return 1; // Ű�� �̹� �����ϴ� ���, �ߺ� ���� ����.

        parentNode = ptr; // ���� Ž�� ���� ��带 �θ� ���� ����.

        if (ptr->key < key)
            ptr = ptr->right; // ���� ����� Ű ���� ���ο� ����� Ű ������ ���� ���, ���� ����� ������ �ڽ� ��带 ptr�� �Ҵ�.
        else
            ptr = ptr->left; // ���� �ڽ� ��带 ptr�� �Ҵ�.
    }

    // �θ� ���� ���Ͽ� ���ο� ��带 ������ ��ġ ����.
    if (parentNode->key > key)
        parentNode->left = newNode; // �θ� ����� Ű ���� ���ο� ����� Ű ������ ū ���, ���� �ڽ����� ����.
    else
        parentNode->right = newNode; // ������ �ڽ����� ����. 

    return 1;
}

// ��� ���� �Լ�.
int deleteNode(Node** head, int key)
{
    Node* current = (*head)->left; // ������ ���.
    Node* parent = NULL; // ������ ����� �θ� ���.

    // ������ ��� Ž��.
    while (current != NULL && current->key != key) { // ���� ��尡 NULL�� �ƴϰ�, ���� ����� Ű ���� ������ Ű ���� ��ġ���� ���� ������ �ݺ�.
        parent = current; // �θ� ��带 ���� ���� ����.

        if (key < current->key) // ������ Ű ���� ���� ����� Ű ������ ���� ���.
            current = current->left; // ���� ����� ���� �ڽ� ���� �̵�.
        else
            current = current->right; // ���� ����� ������ �ڽ� ���� �̵�.
    }

    // ������ ��尡 �������� �ʴ� ���, 0 ��ȯ.
    if (current == NULL)
        return 0;

    // ������ ��尡 �ܸ� ����� ���.
    if (current->left == NULL && current->right == NULL) { // ������ ����� ����, ������ �ڽ��� ��� NULL�� ���.
        if (parent->left == current) // ������ ��尡 �θ��� ���� �ڽ��� ���.
            parent->left = NULL; // ���� �ڽ� ��带 NULL�� ����.
        else
            parent->right = NULL; // ������ �ڽ� ��带 NULL�� ����.
        // �θ� ������ ������ ����.

        free(current); // �ش� ��带 ����.
    // ������ ����� �ڽ��� 1���� ���.
    } else if (current->left == NULL || current->right == NULL) {
        Node* child = NULL; // �ڽ� ��带 ����ų ������ �ʱ�ȭ.

        if (current->left != NULL)
            child = current->left; // ���� �ڽ� ��尡 �����ϴ� ���, �ڽ� ��� �����͸� ���� �ڽ� ���� ����.
        else
            child = current->right; // ������ �ڽ� ��带 �ڽ� ��� �����ͷ� ����.

        if (parent->left == current)
            parent->left = child; // ������ ��尡 �θ� ����� ���� �ڽ� ����� ���, �θ� ����� ���� �ڽ� ��带 �ڽ� ��� �����ͷ� ����.
        else
            parent->right = child; // ������ ��尡 �θ� ����� ������ �ڽ� ����� ���, �θ� ����� ������ �ڽ� ��带 �ڽ� ��� �����ͷ� ����.

        free(current); // ������ ��� ����.
    // ������ ����� �ڽ��� 2���� ���.
    } else {
        Node* succ_parent = current; // �İ��� ����� �θ� ��带 ����ų �����͸� ���� ���� �ʱ�ȭ.
        Node* succ = current->right; // �İ��� ��带 ����ų �����͸� ���� ����� ������ �ڽ� ���� �ʱ�ȭ.

        while (succ->left != NULL) { // �İ��� ����� ���� �ڽ� ��尡 NULL�� ������ �ݺ��Ͽ� �İ��� ��带 ã��.
            succ_parent = succ; // ���� �İ��� ��带 �İ��� ����� �θ� ���� ����.
            succ = succ->left; // �İ��� ����� ���� �ڽ����� ����.
        }

        if (succ_parent->left == succ)
            succ_parent->left = succ->right; // �İ��� ����� ���� �ڽ� ��尡 �İ��� ��带 ����Ű�� ���, �İ��� ����� ������ �ڽ� ��带 �İ��� ����� �θ� ���� ����.
        else
            succ_parent->right = succ->right;

        current->key = succ->key; // ������ ����� Ű ���� �İ��� ����� Ű ������ ����.
        free(succ); // �İ��� ��� ����.
    }

    return 1;
}

// ��� ���� �Լ�.
void freeNode(Node* ptr)
{
    if (ptr) {
        freeNode(ptr->left); // ���� �ڽ� ��� ����.
        freeNode(ptr->right); // ������ �ڽ� ��� ����.
        free(ptr); // ���� ��� ����.
    }
}

// ���� Ž�� Ʈ�� ���� �Լ�.
int freeBST(Node** head)
{
    if ((*head)->left == *head) { // ��� ��尡 �ڱ� �ڽ��� ����Ű�� ���(Ʈ���� ����ִ� ���.).
        free(*head); // ��� ��� ����.
        return 1;
    }

    Node* p = (*head)->left; // Ž���� ������.

    freeNode(p); // Ʈ���� ��� ��� ����.

    free(*head); // ��� ��� ����.
    return 1;
}

// ���� ���� �Լ�.
Node* pop()
{
    if (top == -1) // ������ ����ִ� ���.
        return NULL;

    return stack[top--]; // ���ÿ��� ���Ҹ� ��.
}

void push(Node* aNode)
{
    if (top >= MAX_STACK_SIZE - 1) { // ������ ���� �� ���.
        printf("Stack is full.\n");
        return;
    }

    stack[++top] = aNode; // ���ÿ��� ���Ҹ� Ǫ��.
}

// ť ���� �Լ�.
Node* deQueue()
{
    if (front == rear) // ť�� ����ִ� ���.
        return NULL;

    return queue[++front]; // ť���� ���Ҹ� ��ť.
}

void enQueue(Node* aNode)
{
    if (rear == MAX_QUEUE_SIZE - 1) { // ť�� ���� �� ���.
        printf("Queue is full.\n");
        return;
    }

    queue[++rear] = aNode; // ť���� ���Ҹ� ��ť.
}

// ���� ��� �Լ�.
void printStack()
{
    printf("Stack: ");
    for (int i = 0; i <= top; i++) { // ���ÿ� ����� ������ Ű �� ���.
        printf("%d ", stack[i]->key);
    }
    printf("\n");
}