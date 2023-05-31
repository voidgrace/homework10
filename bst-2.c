/*
 * Binary Search Tree #2
 *
 * Data Structures
 *
 * School of Computer Science
 * at Chungbuk National University
 *
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct node {			//���
	int key;
	struct node *left;
	struct node *right;
} Node;

/* for stack */
#define MAX_STACK_SIZE	20		//���� max������
Node* stack[MAX_STACK_SIZE];	//����(����ü �迭)
int top = -1;					//ž �ε���

Node* pop();					//���� pop�Լ�
void push(Node* aNode);			//���� push�Լ�

/* for queue */
#define MAX_QUEUE_SIZE	20		//ť max������
Node* queue[MAX_QUEUE_SIZE];	//ť(����ü �迭)
int front = -1;					//����Ʈ
int rear = -1;					//����



int initializeBST(Node** h);			//����Ž��Ʈ�� �ʱ�ȭ
void recursiveInorder(Node* ptr);	  /* recursive inorder traversal */
int insert(Node* head, int key);      /* insert a node to the tree */
int freeBST(Node* head); /* free all memories allocated to the tree */

/* functions that you have to implement */
void iterativeInorder(Node* ptr);     /* iterative inorder traversal */
void levelOrder(Node* ptr);	          /* level order traversal */
int deleteNode(Node* head, int key);  /* delete the node for the key */
Node* pop();							//���� ��
void push(Node* aNode);					//���� Ǫ��
Node* deQueue();						//ť ��ť
void enQueue(Node* aNode);				//ť ��ť

/* you may add your own defined functions if necessary */


void printStack();						//���� ���



int main()
{
	char command;		//��� Ŀ��� ���� 
	int key;			
	Node* head = NULL;	//��� ������ NULL

	do{
		printf("\n\n");
		printf("------------------[ 2022041047  ������ ]-------------------------\n");
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

		switch(command) {
		case 'z': case 'Z':
			initializeBST(&head);
			break;
		case 'q': case 'Q':
			freeBST(head);
			break;
		case 'i': case 'I':
			printf("Your Key = ");
			scanf("%d", &key);
			insert(head, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(head, key);
			break;

		case 'r': case 'R':
			recursiveInorder(head->left);
			break;
		case 't': case 'T':
			iterativeInorder(head->left);
			break;

		case 'l': case 'L':
			levelOrder(head->left);
			break;

		case 'p': case 'P':
			printStack();
			break;

		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}

int initializeBST(Node** h) {			//����Ž��Ʈ�� �ʱ�ȭ

	/* if the tree is not empty, then remove all allocated nodes from the tree*/
	if(*h != NULL)
		freeBST(*h);					//Ʈ�� ����

	/* create a head node */
	*h = (Node*)malloc(sizeof(Node));	//����� �Ҵ�
	(*h)->left = NULL;	/* root */ 		//������� ���� NULL
	(*h)->right = *h;					//������� ������ �ڱ��ڽ� ����Ŵ
	(*h)->key = -9999;					//Ű �ʱ�ȭ

	top = -1;							//���� ž �ʱ�ȭ

	front = rear = -1;					//����Ʈ&���� �ʱ�ȭ

	return 1;
}



void recursiveInorder(Node* ptr)		//������ȸ
{
	if(ptr) {							//
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
	for(;;)
	{
		for(; node; node = node->left)
			push(node);
		node = pop();

		if(!node) break;
		printf(" [%d] ", node->key);

		node = node->right;
	}
}

/**
 * textbook: p 225
 */
void levelOrder(Node* ptr)
{
	// int front = rear = -1;

	if(!ptr) return; /* empty tree */

	enQueue(ptr);

	for(;;)
	{
		ptr = deQueue();
		if(ptr) {
			printf(" [%d] ", ptr->key);

			if(ptr->left)
				enQueue(ptr->left);
			if(ptr->right)
				enQueue(ptr->right);
		}
		else
			break;

	}

}


int insert(Node* head, int key)		//��� ����
{
	Node* newNode = (Node*)malloc(sizeof(Node));	//���ο��� �Ҵ�
	//����� �ʱ�ȭ
	newNode->key = key;								
	newNode->left = NULL;
	newNode->right = NULL;

	//��� �̿��� ù����� ���ʿ� ��� ����
	if (head->left == NULL) {
		head->left = newNode;
		return 1;
	}


	/* head->left is the root */
	Node* ptr = head->left;

	Node* parentNode = NULL;
	while(ptr != NULL) {

		/* if there is a node for the key, then just return */
		//�̹� ����Ű���� ���� ��尡 �ִٸ� �Լ� �� 
		if(ptr->key == key) return 1;

		/* we have to move onto children nodes,
		 * keep tracking the parent using parentNode */
		//�θ���� ptr �ű�
		parentNode = ptr;

		/* key comparison, if current node's key is greater than input key
		 * then the new node has to be inserted into the right subtree;
		 * otherwise the left subtree.
		 */
		//Ž���� Ű���� ������� Ű������ �۴ٸ� ������ ����Ʈ���� ����
		if(ptr->key < key)
			ptr = ptr->right;
		else
		// ... ... ... ũ�ٸ� �������� ����
			ptr = ptr->left;
	}

	/* linking the new node to the parent */
	//���ο� ��带 �θ���� ����
	if(parentNode->key > key)
		parentNode->left = newNode;
	else
		parentNode->right = newNode;
	return 1;
}

// ��带 �����ϴ� �Լ�
int deleteNode(Node* head, int key)
{
	Node *temp = head->left;
	Node *temp2 = NULL;
	Node *previous = head;
	for (;;) {
		if (temp == NULL || temp->key == key) {
			// �ݺ��ϸ� �˻�, temp�� NULL�� ��� temp->key���� �˻��ϸ� ������ �߻������� temp==NULL���� �˻�
			// OR�� Ư���� ���� �ϳ��� ���̸� ������ �ؼ��ϱ� ������ ���� ������ ���ϰ�� �ڸ� �˻����� �ʴ� ��� �̿�
			break;
		}
		previous = temp;
		// ���߿� temp���� ������ ���� ���� previous�� �̵��ϱ� �� temp�� ��ġ ����
		if (temp->key > key) {
			temp = temp->left;
		}
		else {
			temp = temp->right;
		}
	}

	if (temp == NULL) {
		// ã���� �ϴ� key���� ���� ���
		printf(" [%d] is not found", key);
		return -1;
	}
	else {
		if (temp->left == NULL && temp->right == NULL) {
			// key���� �ִ� ��忡 �ڽĳ�尡 ���� ���
			if (previous->left == temp) {
				// temp�� �ش��ϴ� ��带 ã�� ���� �����ֱ�
				previous->left = NULL;
			}
			else {
				previous->right = NULL;
			}
			free(temp);
			return 0;
		}
		else {
			temp2 = temp;
			if (temp->right != NULL) {
				// key���� �ִ� ��忡 �ڽĳ�尡 �ְ�, �� �ڽĳ���� rigth�ڽ��� �ִ� ���
				previous = NULL;
				// ������ previous�� temp2 ������ ��带 ����Ű�� �����Ƿ� �ʱ�ȭ
				temp = temp->right;
				for (; temp->left; previous = temp, temp = temp->left);
				//temp�� left���� ���� ���� ���� ã�Ƽ� �̵�
				temp2->key = temp->key;
				// key�� �̵�
				if (previous != NULL) {
					//temp�� left��尡 ������ ���
					previous->left = temp->right;
				}
				else {
					// temp�� left ��尡 �������� ���� ���
					temp2->right = temp->right;
				}
				temp->right = NULL;
				free(temp);
				return 0;
			}
			else {
				// key���� �ִ� ��忡 �ڽĳ�尡 �ְ�, �� �ڽĳ���� left�ڽĸ� �ִ� ���
				temp2 = temp;
				previous = NULL;
				// ������ previous�� temp2 ������ ��带 ����Ű�� �����Ƿ� �ʱ�ȭ
				temp = temp->left;
				for (; temp->right; previous = temp, temp = temp->right);
				//temp�� right���� ���� ���� ū���� ã�Ƽ� �̵�
				temp2->key = temp->key;
				// key�� �̵�
				if (previous != NULL) {
					//temp�� right��尡 ������ ���
					previous->right = temp->left;
				}
				else {
					// temp�� right ��尡 �������� ���� ���
					temp2->left = temp->left;
				}
				temp->left = NULL;
				free(temp);
				return 0;
			}
		}
	}
}

//�������
void freeNode(Node* ptr)		//��� �Ҵ� ����
{
	if(ptr) { 					//����� ���ʳ�尡 ����ٸ�
		freeNode(ptr->left);	//�� ��尡 ���ö����� �ڽĳ��� ����	//����Լ�
		freeNode(ptr->right);	//��Ʈ��尡 ���ö����� ���������� ����		//����Լ�
		free(ptr);				//ptr����
	}
}

int freeBST(Node* head)		//����Ž��Ʈ�� �Ҵ�����
{

	if(head->left == head)	//����� ������ �ڽ��� ����Ű�� �ִٸ�
	{
		free(head);//��� ����
		return 1;
	}

	Node* p = head->left;	//����� ���ʳ��

	freeNode(p);			//�������

	free(head);				//�������
	return 1;
}


//����
// stack�� �ִ� ���� ��ȯ�ϴ� �Լ�
Node* pop()
{
	if (top < 0) return NULL;
	return stack[top--];
}
//���ÿ� ���� ���� �ִ� �Լ�
void push(Node* aNode)
{
	stack[++top] = aNode;
}

//���� ���
void printStack()
{
	int i = 0;
	printf("--- stack ---\n");
	while(i <= top)
	{
		printf("stack[%d] = %d\n", i, stack[i]->key);
	}
}

//��ť
Node* deQueue()
{
	if (front == rear) {
		// printf("\n....Now Queue is empty!!\n" );
		return NULL;
	}
	//ť�� ������� �ʴٸ� ����
	front = (front + 1) % MAX_QUEUE_SIZE;
	return queue[front];

}

//��ť
void enQueue(Node* aNode)
{
	rear = (rear + 1) % MAX_QUEUE_SIZE;
	//ť�� �� ���� �ʾҴٸ� ����
	if (front == rear) {
		// printf("\n....Now Queue is full!!\n");
		return;
	}

	queue[rear] = aNode;
}





