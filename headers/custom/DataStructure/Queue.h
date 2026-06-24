#define maxLogQueueSizeR 20
#define maxLogQueueSizeC 300


typedef struct Queue{
    int max;
    char arr[maxLogQueueSizeR][maxLogQueueSizeC];
    int front;
    int rear;
}Queue;

Queue* CreateQueue();
void enQueue(Queue** q,char Log[maxLogQueueSizeC]);
char* deQueue(Queue** q);