#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "SPArrayList.h"

SPArrayList* spArrayListCreate(int maxSize) {
    if (maxSize <= 0) { // invalid list size
        return NULL;
    }

    SPArrayList *newList = (SPArrayList *)malloc(sizeof(SPArrayList));
    if (newList == NULL) { // failed to allocate list
        return NULL;
    }


    newList->maxSize = maxSize;
    newList->actualSize=0;
    newList->elements = (int*) malloc(sizeof(int) * (maxSize));
    if (newList->elements == NULL) { // failed to allocate elements
        free(newList);
        return NULL;
    }

    return newList;
}

SPArrayList* spArrayListCopy(SPArrayList* src) {
    if (src == NULL) { // nothing to copy
        return NULL;
    }
    SPArrayList* newList = spArrayListCreate(src->maxSize);

    if (newList == NULL) {
        return NULL;
    }

    memcpy(newList->elements, src->elements, sizeof(int) * src->actualSize);
    newList->actualSize = src->actualSize;

    return newList;
}

void spArrayListDestroy(SPArrayList* src) {
    if (src == NULL) {
        return;
    }

    free(src->elements);
    free(src);
    return;
}

SP_ARRAY_LIST_MESSAGE spArrayListClear(SPArrayList* src) {
    if (src == NULL) {
        return SP_ARRAY_LIST_INVALID_ARGUMENT;
    }
    src->actualSize = 0;
    return SP_ARRAY_LIST_SUCCESS;
}

SP_ARRAY_LIST_MESSAGE spArrayListAddAt(SPArrayList* src, int elem, int index){
    if (src == NULL) {
        return SP_ARRAY_LIST_INVALID_ARGUMENT;
    } else if (src->actualSize == src->maxSize) {
        return SP_ARRAY_LIST_FULL;
    } else if (index < 0 || index > src->actualSize) {
        return SP_ARRAY_LIST_INVALID_ARGUMENT;
    }

    int cur = elem;
    int next = src->elements[index];

    while (index <= (src->actualSize - 1)) {
        src->elements[index] = cur;
        index++;
        cur = next;
        next = src->elements[index];
    }

    src->elements[index] = cur;
    src->actualSize++;

    return SP_ARRAY_LIST_SUCCESS;
}

SP_ARRAY_LIST_MESSAGE spArrayListAddFirst(SPArrayList* src, int elem){
    return spArrayListAddAt(src, elem, 0);
}

SP_ARRAY_LIST_MESSAGE spArrayListAddLast(SPArrayList* src, int elem){
    if (src == NULL) {
        return SP_ARRAY_LIST_INVALID_ARGUMENT;
    }
    return spArrayListAddAt(src, elem, src->actualSize);
}

SP_ARRAY_LIST_MESSAGE spArrayListRemoveAt(SPArrayList* src, int index){
    if (src == NULL) {
        return SP_ARRAY_LIST_INVALID_ARGUMENT;
    } else if (src->actualSize == 0) {
        return SP_ARRAY_LIST_EMPTY;
    } else if (index < 0 || index > src->actualSize - 1) {
        return SP_ARRAY_LIST_INVALID_ARGUMENT;
    }

    int next;
    
    while (index < src->actualSize - 1) {
        next = src->elements[index+1];
        src->elements[index] = next;
        index++;
    }

    src->actualSize--;

    return SP_ARRAY_LIST_SUCCESS;
}

SP_ARRAY_LIST_MESSAGE spArrayListRemoveFirst(SPArrayList* src){
    return spArrayListRemoveAt(src, 0);
}

SP_ARRAY_LIST_MESSAGE spArrayListRemoveLast(SPArrayList* src){
    if (src == NULL) {
        return SP_ARRAY_LIST_INVALID_ARGUMENT;
    }
    return spArrayListRemoveAt(src, src->actualSize-1);
}

int spArrayListGetAt(SPArrayList* src, int index){
    if (src == NULL || index < 0 || index > src->actualSize - 1) {
        return 0;
    }

    return src->elements[index];
}

int spArrayListGetFirst(SPArrayList* src){
    return spArrayListGetAt(src, 0);
}

int spArrayListGetLast(SPArrayList* src){
    if (src==NULL) {
        return 0;
    }
    return spArrayListGetAt(src, src->actualSize - 1);
}

int spArrayListMaxCapacity(SPArrayList* src){
    if (src==NULL) {
        return 0;
    }
    return src->maxSize;
}

int spArrayListSize(SPArrayList* src){
    if (src==NULL) {
        return 0;
    }
    return src->actualSize;
}

bool spArrayListIsFull(SPArrayList* src){
    if (src==NULL) {
        return false;
    }
    return (src->actualSize == src->maxSize);
}

bool spArrayListIsEmpty(SPArrayList* src){
    if (src==NULL) {
        return false;
    }
    return (src->actualSize == 0);
}

void spArrayListPrintList(SPArrayList* src) {
    printf("List: MaxSize %d Actual Size %d\n", src->maxSize, src->actualSize);
    for (int i=0; i < src->actualSize; i++) {
        printf("%d->", src->elements[i]);
    }
    printf("\n");
}