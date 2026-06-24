
#include <custom/vector.h>
#include <stdlib.h>

vectorND* InitilizeVectorND(int size)
{
    vectorND* tmp =malloc(sizeof(vectorND));
    tmp->data = malloc(sizeof(int)*size);
    tmp->size = size;
    return tmp;
}