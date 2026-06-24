#include <custom/DataStructure/Queue.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

Queue *CreateQueue()
{
    Queue *tmp = malloc(sizeof(Queue));
    tmp->max = maxLogQueueSizeR;
    tmp->front = -1;
    tmp->rear = -1;
    return tmp;
}
void enQueue(Queue **q, char Log[maxLogQueueSizeC])
{
    if(*q == NULL)
    {
        *q = CreateQueue();
    }
    if ((*q)->front == -1)
    {
        (*q)->front++;
        (*q)->rear++;
        strcpy((*q)->arr[(*q)->front], Log);
    }
    else
    {
        (*q)->rear++;
        if ((*q)->rear != maxLogQueueSizeC)
        {
            strcpy((*q)->arr[(*q)->rear], Log);
        }
        else
        {
            if ((*q)->rear % maxLogQueueSizeC != (*q)->front)
            {
                (*q)->rear = (*q)->rear % maxLogQueueSizeC;
                strcpy((*q)->arr[(*q)->rear], Log);
            }
            else
            {
                printf("\n the Queue is full \n");
            }
        }
    }
}
char *deQueue(Queue **q)
{
    if (*q == NULL)
    {
        printf("\nqueue doesn't exists\n");
    }
    else
    {
        if ((*q)->front == -1)
        {
            printf("\nQueue empty\n");
        }
        else
        {
            (*q)->front++;
            if ((*q)->front != (*q)->rear)
            {
                return (*q)->arr[(*q)->front];
            }
            else
            {
                int tmp = (*q)->front;
                (*q)->front = -1;
                (*q)->rear = -1;
                return (*q)->arr[tmp];
            }
        }
    }
    return "No info";
}
