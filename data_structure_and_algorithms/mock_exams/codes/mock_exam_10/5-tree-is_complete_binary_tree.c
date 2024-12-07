#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/* Definition for a binary tree node */
typedef struct Node {
    int data;
    struct Node *left;
    struct Node *right;
} Node;

/* Function to create a new tree node */
Node* createNode(int data) {
    Node *newNode = (Node*)malloc(sizeof(Node));
    if (!newNode) {
        fprintf(stderr, "Memory allocation error!\n");
        exit(EXIT_FAILURE);
    }
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

/* A queue to support BFS level-order traversal */
typedef struct Queue {
    Node **arr;
    int front;
    int rear;
    int capacity;
} Queue;

/* Create a queue with a given capacity */
Queue* createQueue(int capacity) {
    Queue *queue = (Queue*)malloc(sizeof(Queue));
    if (!queue) {
        fprintf(stderr, "Memory allocation error!\n");
        exit(EXIT_FAILURE);
    }
    queue->front = 0;
    queue->rear = 0;
    queue->capacity = capacity;
    queue->arr = (Node**)malloc(sizeof(Node*) * capacity);
    if (!queue->arr) {
        fprintf(stderr, "Memory allocation error!\n");
        exit(EXIT_FAILURE);
    }
    return queue;
}

/* Check if the queue is empty */
bool isEmpty(Queue *queue) {
    return (queue->front == queue->rear);
}

/* Enqueue an element to the queue */
void enqueue(Queue *queue, Node *node) {
    if (queue->rear == queue->capacity) {
        // Ideally, you could implement resizing logic here
        // For simplicity, assume the queue is large enough
        fprintf(stderr, "Queue overflow\n");
        return;
    }
    queue->arr[queue->rear++] = node;
}

/* Dequeue an element from the queue */
Node* dequeue(Queue *queue) {
    if (isEmpty(queue)) {
        return NULL;
    }
    return queue->arr[queue->front++];
}

/* Function to check if a binary tree is complete */
bool isCompleteBinaryTree(Node *root) {
    if (root == NULL) {
        return true;  // An empty tree is complete
    }

    // Create a large enough queue (assuming max nodes)
    // For simplicity, assume we won't exceed this size.
    // In practice, you might dynamically allocate based on tree size.
    Queue *queue = createQueue(1024);

    // Start with the root node
    enqueue(queue, root);

    bool encounteredNull = false;

    while (!isEmpty(queue)) {
        Node *current = dequeue(queue);

        if (current == NULL) {
            encounteredNull = true;
        } else {
            // If we have previously encountered a NULL and now a non-NULL appears,
            // this is not a complete tree
            if (encounteredNull) {
                // Clean up the queue
                free(queue->arr);
                free(queue);
                return false;
            }
            // Enqueue the children regardless of whether they are NULL
            enqueue(queue, current->left);
            enqueue(queue, current->right);
        }
    }

    // If we processed all nodes without violation, it's complete
    free(queue->arr);
    free(queue);
    return true;
}

/* Helper function to insert nodes just for demonstration */
Node* insertLevelOrder(int arr[], Node* root, int i, int n) {
    // Base case for recursion
    if (i < n) {
        Node *temp = createNode(arr[i]);
        root = temp;

        // insert left child
        root->left = insertLevelOrder(arr, root->left, 2 * i + 1, n);

        // insert right child
        root->right = insertLevelOrder(arr, root->right, 2 * i + 2, n);
    }
    return root;
}

int main() {
    /*
       Example tree:

             1
            / \
           2   3
          / \ / 
         4  5 6

       This tree is complete.
    */
    int arr[] = {1, 2, 3, 4, 5, 6};
    int n = sizeof(arr)/sizeof(arr[0]);
    Node *root = insertLevelOrder(arr, NULL, 0, n);

    if (isCompleteBinaryTree(root)) {
        printf("The binary tree is complete.\n");
    } else {
        printf("The binary tree is not complete.\n");
    }

    // Freeing all allocated nodes would ideally be done here.
    // For brevity, it is omitted.
    return 0;
}
