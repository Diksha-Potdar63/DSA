#include <stdio.h>
#include <stdlib.h> 

// Structure to represent the circular queue
struct CircularQueue {
    int *items;  
    int front;   
    int rear;     
    int size;    
    int count;   
};

// --- Function Prototypes ---
struct CircularQueue* createQueue(int n);
int isEmpty(struct CircularQueue* q);
int isFull(struct CircularQueue* q);
void enqueue(struct CircularQueue* q, int value);
int dequeue(struct CircularQueue* q);
void display(struct CircularQueue* q);
void freeQueue(struct CircularQueue* q);

// --- Main Function ---
int main() {
    int n, choice, value;

    printf("Enter the size (n) of the queue: ");
    scanf("%d", &n);

    struct CircularQueue* q = createQueue(n);
    printf("Circular Queue of size %d created.\n", n);

    printf("\n--- Let's add some items to the queue ---\n");
    enqueue(q, 10);
    enqueue(q, 20);
    enqueue(q, 30);

    printf("\nCurrent Queue: ");
    display(q);

    // 1.b. Delete the element from the queue and display it
    printf("\n--- Deleting an element (Dequeue) ---\n");
    int deletedItem = dequeue(q);

    if (deletedItem != -1) { 
        printf("Deleted element is: %d\n", deletedItem);
    }

    printf("\nCurrent Queue after deletion: ");
    display(q);
    
    // Additional operations for testing
    printf("\n--- Adding more items ---\n");
    enqueue(q, 40);
    enqueue(q, 50);
    printf("Current Queue: ");
    display(q);

    printf("\n--- Deleting and adding to test wrap-around ---\n");
    dequeue(q); 
    enqueue(q, 60); 
    
    printf("Current Queue (after wrap-around): ");
    display(q);

    // Clean up memory
    freeQueue(q);

    return 0;
}

/**
 * 1.a. Creates and initializes a circular queue of size n.
 */
struct CircularQueue* createQueue(int n) {
    struct CircularQueue* q = (struct CircularQueue*)malloc(sizeof(struct CircularQueue));
    if (q == NULL) {
        printf("Memory allocation failed for queue structure.\n");
        exit(1);
    }
    
    q->size = n;
    q->front = 0;
    q->rear = 0;
    q->count = 0;
    
    // Allocate memory for the items array
    q->items = (int*)malloc(q->size * sizeof(int));
    if (q->items == NULL) {
        printf("Memory allocation failed for queue items array.\n");
        free(q); 
        exit(1);
    }
    
    return q;
}

/**
 * Checks if the queue is empty.
 */
int isEmpty(struct CircularQueue* q) {
    return (q->count == 0);
}

/**
 * Checks if the queue is full.
 */
int isFull(struct CircularQueue* q) {
    return (q->count == q->size);
}

/**
 * Adds (enqueues) an element to the rear of the queue.
 * (This is necessary to test the dequeue operation)
 */
void enqueue(struct CircularQueue* q, int value) {
    if (isFull(q)) {
        printf("Queue is full! Cannot enqueue %d.\n", value);
        return;
    }
    
    q->items[q->rear] = value;
    
    q->rear = (q->rear + 1) % q->size;
    
    q->count++;
    
    printf("Enqueued %d.\n", value);
}

/**
 * 1.b. Deletes (dequeues) an element from the front of the queue
 * and returns it.
 */
int dequeue(struct CircularQueue* q) {
    if (isEmpty(q)) {
        printf("Queue is empty! Cannot dequeue.\n");
        return -1; 
    }

    int item = q->items[q->front];
    
    q->front = (q->front + 1) % q->size;
    
    q->count--;
    
    return item;
}

/**
 * Displays the elements in the queue from front to rear.
 */
void display(struct CircularQueue* q) {
    if (isEmpty(q)) {
        printf("Queue is empty.\n");
        return;
    }
    
    int i = q->front;
    int items_printed = 0;
    
    while (items_printed < q->count) {
        printf("%d ", q->items[i]);
        i = (i + 1) % q->size; 
        items_printed++;
    }
    printf("\n");
}

/**
 * Frees the dynamically allocated memory for the queue.
 */
void freeQueue(struct CircularQueue* q) {
    free(q->items); // Free the array
    free(q);        // Free the structure
    printf("\nQueue memory freed.\n");
}