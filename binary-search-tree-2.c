// 이진 탐색 트리를 구현한 프로그램

#include <stdio.h>
#include <stdlib.h>

// 구조체 정의.
typedef struct node {
    int key; // 노드 식별 키.
    struct node* left; // 현재 노드의 왼쪽 자식 노드를 가리키는 포인터.
    struct node* right; // 현재 노드의 오른쪽 자식 노드를 가리키는 포인터.
} Node;

#define MAX_STACK_SIZE 20 // 스택의 최대 크기를 20으로 정의.
Node* stack[MAX_STACK_SIZE]; // 스택을 구현하기 위한 노드 포인터 배열.
int top = -1; // 스택의 탑 초기화(비어있음).

#define MAX_QUEUE_SIZE 20 // 큐의 최대 크기를 20으로 정의.
Node* queue[MAX_QUEUE_SIZE]; // 큐를 구현하기 위한  노드 포인터 배열.
int front = -1; // 큐의 front를 나타내는 변수 초기화.
int rear = -1; // 큐의 rear를 나타내는 변수 초기화.

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

    printf("[----- [이은총] [2022041043] -----]\n");

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
                printf("\n       잘못된 입력입니다.       \n");
                break;
        }
    } while (command != 'q' && command != 'Q');

    return 1;
}

// 이진 탐색 트리를 초기화하는 함수.
int initializeBST(Node** h)
{
    // 이미 트리가 존재할 경우, 이진 탐색 트리를 해제.
    if (*h != NULL)
        freeBST(h); // 이미 할당된 노드들을 해제하는 freeBST 함수 호출.

    // 헤드 노드 생성 및 초기화
    *h = (Node*)malloc(sizeof(Node)); // 새로운 노드에 동적 메모리 할당.
    (*h)->left = NULL; // 왼쪽 자식 노드 초기화.
    (*h)->right = *h; // 오른쪽 자식 노드 초기화.
    (*h)->key = -9999; // 헤드 노드의 키 값 초기화.

    top = -1; // 스택 초기화.

    front = rear = -1; // 큐 초기화.

    return 1;
}

// 재귀적으로 중위 순회 하는 함수.
void recursiveInorder(Node* ptr)
{
    if (ptr) {
        recursiveInorder(ptr->left); // 왼쪽 자식 노드 방문.
        printf(" [%d] ", ptr->key); // 현재 노드 출력.
        recursiveInorder(ptr->right); // 오른쪽 자식 노드 방문.
    }
}

// 반복적으로 중위 순회 하는 함수. 
void iterativeInorder(Node* node)
{
    top = -1; // 스택 초기화.

    while (1) {
        while (node) {
            push(node); // 현재 노드를 스택에 푸시.
            node = node->left; // 왼쪽 자식 노드로 이동.
        }

        node = pop(); // 스택에서 노드를 팝.

        // 현재 노드가 NULL(중위 순회 할 노드 존재X)일 경우, 반복문 종료.
        if (!node)
            break;

        printf(" [%d] ", node->key); // 현재 노드 출력.

        node = node->right; // 오른쪽 자식 노드로 이동.
    }
}

// 레벨 순서 순회 함수.
void levelOrder(Node* ptr)
{
    // 빈 트리일 경우, 함수 종료.
    if (ptr == NULL)
        return;

    enQueue(ptr); // 루트 노드를 큐에 삽입.

    while (front != rear) {
        ptr = deQueue(); // 큐에서 노드를 노드를 삭제하여 방문.
        printf(" [%d] ", ptr->key); // 현재 노드 출력.

        if (ptr->left)
            enQueue(ptr->left); // 왼쪽 자식 노드를 가리킬 경우, 왼쪽 자식 노드를 큐에 삽입.
        if (ptr->right)
            enQueue(ptr->right); // 오른쪽 자식 노드를 큐에 삽입.
    }
}

// 노드 삽입 함수.
int insert(Node** head, int key)
{
    // 새로운 노드 생성 및 초기화.
    Node* newNode = (Node*)malloc(sizeof(Node)); // 새로운 노드에 동적 메모리 할당.
    newNode->key = key; // 새로운 노드의 키 값 설정.
    newNode->left = NULL; // 새로운 노드의 왼쪽 자식 포인터를 NULL로 초기화.
    newNode->right = NULL; // 새로운 노드의 오른쪽 자식 포인터를 NULL로 초기화.

    // 트리가 비어있을 경우, 새로운 노드를 루트 노드로 설정.
    if ((*head)->left == NULL) {
        (*head)->left = newNode;
        return 1;
    }

    Node* ptr = (*head)->left; // 탐색을 위한 포인터 변수 초기화.

    Node* parentNode = NULL; // 삽입할 위치의 부모 노드.
    while (ptr != NULL) { // 삽입할 위치 찾기 위해 트리 탐색.
        if (ptr->key == key)
            return 1; // 키가 이미 존재하는 경우, 중복 삽입 막음.

        parentNode = ptr; // 현재 탐색 중인 노드를 부모 노드로 설정.

        if (ptr->key < key)
            ptr = ptr->right; // 현재 노드의 키 값이 새로운 노드의 키 값보다 작은 경우, 현재 노드의 오른쪽 자식 노드를 ptr에 할당.
        else
            ptr = ptr->left; // 왼쪽 자식 노드를 ptr에 할당.
    }

    // 부모 노드와 비교하여 새로운 노드를 삽입할 위치 설정.
    if (parentNode->key > key)
        parentNode->left = newNode; // 부모 노드의 키 값이 새로운 노드의 키 값보다 큰 경우, 왼쪽 자식으로 삽입.
    else
        parentNode->right = newNode; // 오른쪽 자식으로 삽입. 

    return 1;
}

// 노드 삭제 함수.
int deleteNode(Node** head, int key)
{
    Node* current = (*head)->left; // 삭제할 노드.
    Node* parent = NULL; // 삭제할 노드의 부모 노드.

    // 삭제할 노드 탐색.
    while (current != NULL && current->key != key) { // 현재 노드가 NULL이 아니고, 현재 노드의 키 값이 삭제할 키 값과 일치하지 않을 때까지 반복.
        parent = current; // 부모 노드를 현재 노드로 설정.

        if (key < current->key) // 삭제할 키 값이 현재 노드의 키 값보다 작은 경우.
            current = current->left; // 현재 노드의 왼쪽 자식 노드로 이동.
        else
            current = current->right; // 현재 노드의 오른쪽 자식 노드로 이동.
    }

    // 삭제할 노드가 존재하지 않는 경우, 0 반환.
    if (current == NULL)
        return 0;

    // 삭제할 노드가 단말 노드인 경우.
    if (current->left == NULL && current->right == NULL) { // 삭제할 노드의 왼쪽, 오른쪽 자식이 모드 NULL인 경우.
        if (parent->left == current) // 삭제할 노드가 부모의 왼쪽 자식인 경우.
            parent->left = NULL; // 왼쪽 자식 노드를 NULL로 설정.
        else
            parent->right = NULL; // 오른쪽 자식 노드를 NULL로 설정.
        // 부모 노드와의 연결을 끊음.

        free(current); // 해당 노드를 해제.
    // 삭제할 노드의 자식이 1개일 경우.
    } else if (current->left == NULL || current->right == NULL) {
        Node* child = NULL; // 자식 노드를 가리킬 포인터 초기화.

        if (current->left != NULL)
            child = current->left; // 왼쪽 자식 노드가 존재하는 경우, 자식 노드 포인터를 왼쪽 자식 노드로 설정.
        else
            child = current->right; // 오른쪽 자식 노드를 자식 노드 포인터로 설정.

        if (parent->left == current)
            parent->left = child; // 삭제할 노드가 부모 노드의 왼쪽 자식 노드인 경우, 부모 노드의 왼쪽 자식 노드를 자식 노드 포인터로 설정.
        else
            parent->right = child; // 삭제할 노드가 부모 노드의 오른쪽 자식 노드인 경우, 부모 노드의 오른쪽 자식 노드를 자식 노드 포인터로 설정.

        free(current); // 삭제할 노드 해제.
    // 삭제할 노드의 자식이 2개일 경우.
    } else {
        Node* succ_parent = current; // 후계자 노드의 부모 노드를 가리킬 포인터를 현재 노드로 초기화.
        Node* succ = current->right; // 후계자 노드를 가리킬 포인터를 현재 노드의 오른쪽 자식 노드로 초기화.

        while (succ->left != NULL) { // 후계자 노드의 왼쪽 자식 노드가 NULL일 떄까지 반복하여 후계자 노드를 찾음.
            succ_parent = succ; // 현재 후계자 노드를 후계자 노드의 부모 노드로 설정.
            succ = succ->left; // 후계자 노드의 왼쪽 자식으로 설정.
        }

        if (succ_parent->left == succ)
            succ_parent->left = succ->right; // 후계자 노드의 왼쪽 자식 노드가 후계자 노드를 가리키는 경우, 후계자 노드의 오른쪽 자식 노드를 후계자 노드의 부모 노드와 연결.
        else
            succ_parent->right = succ->right;

        current->key = succ->key; // 삭제할 노드의 키 값을 후계자 노드의 키 값으로 복사.
        free(succ); // 후계자 노드 해제.
    }

    return 1;
}

// 노드 해제 함수.
void freeNode(Node* ptr)
{
    if (ptr) {
        freeNode(ptr->left); // 왼쪽 자식 노드 해제.
        freeNode(ptr->right); // 오른쪽 자식 노드 해제.
        free(ptr); // 현재 노드 해제.
    }
}

// 이진 탐색 트리 해제 함수.
int freeBST(Node** head)
{
    if ((*head)->left == *head) { // 헤드 노드가 자기 자신을 가리키는 경우(트리가 비어있는 경우.).
        free(*head); // 헤드 노드 해제.
        return 1;
    }

    Node* p = (*head)->left; // 탐색용 포인터.

    freeNode(p); // 트리의 모든 노드 해제.

    free(*head); // 헤드 노드 해제.
    return 1;
}

// 스택 연산 함수.
Node* pop()
{
    if (top == -1) // 스택이 비어있는 경우.
        return NULL;

    return stack[top--]; // 스택에서 원소를 팝.
}

void push(Node* aNode)
{
    if (top >= MAX_STACK_SIZE - 1) { // 스택이 가득 찬 경우.
        printf("Stack is full.\n");
        return;
    }

    stack[++top] = aNode; // 스택에서 원소를 푸시.
}

// 큐 연산 함수.
Node* deQueue()
{
    if (front == rear) // 큐가 비어있는 경우.
        return NULL;

    return queue[++front]; // 큐에서 원소를 디큐.
}

void enQueue(Node* aNode)
{
    if (rear == MAX_QUEUE_SIZE - 1) { // 큐가 가득 찬 경우.
        printf("Queue is full.\n");
        return;
    }

    queue[++rear] = aNode; // 큐에서 원소를 인큐.
}

// 스택 출력 함수.
void printStack()
{
    printf("Stack: ");
    for (int i = 0; i <= top; i++) { // 스택에 저장된 노드들의 키 값 출력.
        printf("%d ", stack[i]->key);
    }
    printf("\n");
}