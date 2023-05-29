nclude <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

//#define size 50000

// Array DataSet 
struct DataSet {
        int priority;
        char data[50];
};

// Tree DataSet
struct TreeNode {
	int priority;
	char data[50];
	struct TreeNode * left;
	struct TreeNode * right;
};


// Functions
struct TreeNode* delete(struct TreeNode* root, int max);
void inorder(struct TreeNode* root);
void postorder(struct TreeNode* root);
void preorder(struct TreeNode* root);
char* getRandomBinaryString(int length);
struct TreeNode* AddNode(struct TreeNode* root, int num);
void inqueueTree(struct TreeNode** root,int size);
void dequeueTree(struct TreeNode** root,int size);
void seeding();
int getNum(int* size);
void MallocCheck(struct DataSet* Queue);
void inqueue(struct DataSet Queue[], int* size, int* remain);
void displayQueue(struct DataSet Queue[], int size);	
void displayReverseQueue(struct DataSet Queue[], int size);
int isEmpty(int* remain);
void enqueue(struct DataSet Queue[], int* remain, int priority, const char* data);
void swap(struct DataSet *a, struct DataSet *b);
void sortQueue(struct DataSet Queue[], int size);


int main() {

    int size = 50000;

    int i, j, max, max_idx, remain = 0;

    seeding();
	//srand((unsigned int)time(NULL));
	
    clock_t start, end;
    double time_array, time_tree;

	
    //array
    start = clock();

    //making the array
    struct DataSet* Queue = malloc(size* sizeof(struct DataSet));
	
	//malloc check
	MallocCheck(Queue);

    // inqueue setting (make random)
    inqueue(Queue, &size, &remain);

	// sorting
    isEmpty(&remain);
	
    //sort&dequeue
    sortQueue(Queue, size);
        
	//print
	displayQueue(Queue,size);
	
	printf("\n");
	
	//print
	displayReverseQueue(Queue,size);
	printf("\n");
	
    end = clock();
    time_array = (double)(end - start);

	
	//Binary Search Tree
	
	start = clock();
	
	struct TreeNode *root = NULL, *Max;

	inqueueTree(&root, size);
	
	inorder(root);
	printf("inorder\n");
	
	preorder(root);
	printf("preorder\n");
	
	postorder(root);
	printf("postorder\n");

	
	dequeueTree(&root, size);
	
	end = clock();
	
	time_tree = (double)(end - start);
	
    printf("%f\t%f", time_array, time_tree);
	
	free(Queue);
	
	return 0;
}

// Tree Delete Function
struct TreeNode* delete(struct TreeNode* root, int max) {
	// If Tree does not exist
    if (!root) {
        return root;
    } 

	// Deleting Process
    if (max > root->priority) {
        root->right = delete(root->right, max);
    } 
	
	else if (max == root->priority) {
		
        if (!root->left && !root->right) {
            free(root);
            return NULL;
        } 
		
		else if (!root->right) {
            struct TreeNode* temp = root->left;
            free(root);
            return temp;
        } 
		
		else if (!root->left) {
            struct TreeNode* temp = root->right;
            free(root);
            return temp;
        }
		
		else {
            struct TreeNode* parent = root;
            struct TreeNode* temp = root->left;
            while (temp->right) {
                parent = temp;
                temp = temp->right;
            }
			
            if (parent != root) {
                parent->right = temp->left;
                temp->left = root->left;
            }
			
            temp->right = root->right;
            free(root);
			
            return temp;
        }
    }

    return root;
	
}


// Tree Inorder Print Function
void inorder(struct TreeNode* root){
	if (!root){
		return;
	}
	inorder(root->left);
	//printf("%d\t", root->priority);
	printf("Priority: %d, Data: %s\n", root->priority, root->data);
	inorder(root->right);
}

// Tree Postorder Print Function
void postorder(struct TreeNode* root){
	if (!root){
		return;
	}
	postorder(root->left);
	postorder(root->right);
	printf("Priority: %d, Data: %s\n", root->priority, root->data);
}

// Tree Preorder Print Function
void preorder(struct TreeNode* root){
	if (!root){
		return;
	}
	printf("Priority: %d, Data: %s\n", root->priority, root->data);
	preorder(root->left);
	preorder(root->right);
}

char* getRandomBinaryString(int length) {
    char* binaryString = malloc((length + 1) * sizeof(char));

	
    if (binaryString == NULL) {
        printf("Memory allocation failed.\n");
        return NULL;
    }

    //srand((unsigned int)time(NULL));

    for (int i = 0; i < length; i++) {
        int randomDigit = rand() % 2;
        binaryString[i] = '0' + randomDigit;
    }

    binaryString[length] = '\0';

    return binaryString;
}

// Binary Search Tree Add Node
struct TreeNode* AddNode(struct TreeNode* root, int num){
	struct TreeNode *temp;
	temp = (struct TreeNode*)malloc(sizeof(struct TreeNode));
	temp->priority = num;
	
	char* binaryString = getRandomBinaryString(50);
    strncpy(temp->data, binaryString, sizeof(temp->data) - 1);
    free(binaryString);
	temp->left = NULL;
	temp->right = NULL;
	if (!root){root = temp;}
	
	else if (num > root->priority){
		root->right = AddNode(root->right,num);
	}
	else if (num < root->priority){
		root->left = AddNode(root->left, num);
	}
	return root;
}


void seeding(){
    srand((unsigned int)time(NULL));
}

int getNum(int* size){
    return *size;
}

void MallocCheck(struct DataSet* Queue){
	if (Queue == NULL) {
        printf("Memory allocation failed.\n");
        exit(1);
    }
}


void inqueue(struct DataSet Queue[], int* size, int* remain){
    int i;
	
    for (i=0; i< getNum(size); i++){
        int priority = rand();
        char* binaryString = getRandomBinaryString(50);
        strncpy(Queue[i].data, binaryString, sizeof(Queue[i].data) - 1);
        free(binaryString);
		enqueue(Queue, remain, priority, Queue[i].data);
    }
}

void displayQueue(struct DataSet Queue[], int size) {

    for (int i = 0; i < size; i++) {
        printf("Priority: %d, Data: %s\n", Queue[i].priority, Queue[i].data);
    }

}

void displayReverseQueue(struct DataSet Queue[], int size) {

    for (int i = size-1; i >= 0; i--) {
        printf("Priority: %d, Data: %s\n", Queue[i].priority, Queue[i].data);
    }

}

int isEmpty(int* remain) {
    return *remain == 0;
}

void enqueue(struct DataSet Queue[], int* remain, int priority, const char* data) {

    if (*remain >= 50000) {
        printf("Queue is full. Cannot enqueue more elements.\n");
        return;
    }

    Queue[*remain].priority = priority;
    strcpy(Queue[*remain].data, data);
    (*remain)++;
}

void swap(struct DataSet *a, struct DataSet *b) {
    struct DataSet temp = *a;
    *a = *b;
    *b = temp;
}

void inqueueTree(struct TreeNode** root,int size){
	int num; int i;
	
	for (i=0;i<size;i++){
		num = rand();
		*root = AddNode(*root, num);
	}
}

void sortQueue(struct DataSet Queue[], int size) {
	int max = 0; 
	int max_idx = 0;
	int remain = size; 
	int i; int j;
	
	for (i = 0; i < getNum(&size) - 1; i++) {
        for (j = 0; j < getNum(&size) - i - 1; j++) {
            if (Queue[j].priority > Queue[j + 1].priority) {
                swap(&Queue[j], &Queue[j + 1]);
            }
        }
    }
	
	/*
    for (i=0;i<getNum(&size);i++){
            //finding biggest priority
            max = Queue[0].priority;
            max_idx = 0;
            for (j=0;j<remain;j++){
                if (Queue[j].priority > max){
                	max = Queue[j].priority;
                    max_idx = j;
                }
            }
            //deleting
			Queue[remain-1] = Queue[max_idx];
            for (j=max_idx+1;j<remain;j++){
                Queue[j-1] = Queue[j];
            }
            remain--;
    }*/
	
	
}

void dequeueTree(struct TreeNode** root,int size){
	
	struct TreeNode *pre = *root, *node;
	int i;
	
	for (i = 0; i < getNum(&size); i++) {
		node = pre;
		while (node->right) {
			pre = node;
			node = node->right;
		}
		*root = delete(*root, node->priority);
		pre->right = NULL; // Update the reference to the right child of pre
	}
	
}

