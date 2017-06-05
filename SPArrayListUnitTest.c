#include "unit_test_util.h"
#include "SPArrayList.h"
#include <stdbool.h>

#define CAPACITY_SIZE (10)

static bool spArrayListBasicGetTest() {
	SPArrayList* list = spArrayListCreate(CAPACITY_SIZE);
	ASSERT_TRUE(list != NULL);
	for (int i = 0; i < CAPACITY_SIZE; i++) {
		//printf("Adding %d to list\n", i);
		ASSERT_TRUE(spArrayListAddLast(list, i) == SP_ARRAY_LIST_SUCCESS);
	}
	for (int i = 0; i < CAPACITY_SIZE; i++) {
		ASSERT_TRUE(spArrayListGetAt(list, i) == i);
		//printf("Got %d from list\n", i);
	}
	spArrayListDestroy(list);
	return true;
}

static bool spArrayListBasicCopyTest() {
	SPArrayList* list = spArrayListCreate(CAPACITY_SIZE);
	//printf("Created list\n");
	ASSERT_TRUE(list!=NULL);
	for (int i = 0; i < CAPACITY_SIZE; i++) {
		//printf("Adding element %d\n", i);
		ASSERT_TRUE(spArrayListAddFirst(list, i) == SP_ARRAY_LIST_SUCCESS);
	}
	//printf("Copying list\n");
	SPArrayList* copyList = spArrayListCopy(list);
	for (int i = 0; i < CAPACITY_SIZE; i++) {
		ASSERT_TRUE(spArrayListGetAt(copyList, i) == spArrayListGetAt(list, i));
	}
	spArrayListDestroy(list);
	spArrayListDestroy(copyList);
	return true;
}

static bool spArrayListBasicRemoveTest() {
	SPArrayList* list = spArrayListCreate(CAPACITY_SIZE);
	ASSERT_TRUE(list!=NULL);
	for (int i = 0; i < CAPACITY_SIZE; i++) {
		ASSERT_TRUE(spArrayListAddFirst(list, i) == SP_ARRAY_LIST_SUCCESS);
	}
	ASSERT_TRUE(spArrayListSize(list) == CAPACITY_SIZE);
	for (int i = 0; i < CAPACITY_SIZE; i++) {
		ASSERT_TRUE(spArrayListRemoveFirst(list) == SP_ARRAY_LIST_SUCCESS);
		ASSERT_TRUE(spArrayListSize(list) == CAPACITY_SIZE - i - 1);
	}
	spArrayListDestroy(list);

	list = spArrayListCreate(CAPACITY_SIZE);
	ASSERT_TRUE(list!=NULL);
	for (int i = 0; i < CAPACITY_SIZE; i++) {
		ASSERT_TRUE(spArrayListAddFirst(list, i) == SP_ARRAY_LIST_SUCCESS);
	}
	ASSERT_TRUE(spArrayListSize(list) == CAPACITY_SIZE);
	for (int i = 0; i < CAPACITY_SIZE; i++) {
		ASSERT_TRUE(spArrayListRemoveLast(list) == SP_ARRAY_LIST_SUCCESS);
		ASSERT_TRUE(spArrayListSize(list) == CAPACITY_SIZE - i - 1);
	}

	ASSERT_TRUE(spArrayListIsEmpty(list));
	spArrayListDestroy(list);
	return true;
}

static bool spArrayListAddFullTest() {
	SPArrayList* list = spArrayListCreate(3);
	ASSERT_TRUE(list!=NULL);
	for (int i = 0; i < 3; i++) {
		ASSERT_TRUE(spArrayListAddFirst(list, i) == SP_ARRAY_LIST_SUCCESS);
	}

	ASSERT_TRUE(spArrayListIsFull(list));

	for (int i = 0; i < CAPACITY_SIZE; i++) {
		ASSERT_TRUE(spArrayListAddFirst(list, i) == SP_ARRAY_LIST_FULL);
	}
	spArrayListDestroy(list);
	return true;
}

static bool spArrayListGetFullTest() {
    SPArrayList *list = spArrayListCreate(CAPACITY_SIZE); 
	ASSERT_TRUE(list!=NULL);
	for (int i = 0; i < CAPACITY_SIZE; i++) {
		ASSERT_TRUE(spArrayListAddFirst(list, i) == SP_ARRAY_LIST_SUCCESS);
	}
	for (int i = 0; i < CAPACITY_SIZE; i++) {
		ASSERT_TRUE(spArrayListAddFirst(list, i) == SP_ARRAY_LIST_FULL);
        ASSERT_TRUE(spArrayListAddLast(list, i) == SP_ARRAY_LIST_FULL);
	}

	ASSERT_TRUE(spArrayListIsFull(list));

	for (int i = 0; i < CAPACITY_SIZE; i++) {
		ASSERT_TRUE(spArrayListGetAt(list, i) == CAPACITY_SIZE - i - 1);
	}

	ASSERT_TRUE(spArrayListIsFull(list));

	spArrayListDestroy(list);
	return true;
}

static bool spArrayListRemoveFullTest() {
	SPArrayList* list = spArrayListCreate(3);
	ASSERT_TRUE(list!=NULL);
	for (int i = 0; i < 3; i++) {
		ASSERT_TRUE(spArrayListAddLast(list, i) == SP_ARRAY_LIST_SUCCESS);
	}

	ASSERT_TRUE(spArrayListRemoveLast(list) == SP_ARRAY_LIST_SUCCESS);
	ASSERT_FALSE(spArrayListIsFull(list));

	for (int i = 0; i < 2; i++) {
		ASSERT_TRUE(spArrayListGetAt(list, i) == i);
	}

	ASSERT_TRUE(spArrayListGetAt(list, 2) == 0);
	ASSERT_TRUE(spArrayListGetAt(list, 3) == 0);

	spArrayListDestroy(list);
	return true;
}

static bool spArrayListBasicAddTest() {
	SPArrayList* list = spArrayListCreate(CAPACITY_SIZE);
	ASSERT_TRUE(list!=NULL);
	for (int i = 0; i < CAPACITY_SIZE; i++) {
		ASSERT_TRUE(spArrayListAddFirst(list, i) == SP_ARRAY_LIST_SUCCESS);
		ASSERT_TRUE(spArrayListSize(list) == i + 1);
	}
	ASSERT_TRUE(spArrayListSize(list) == CAPACITY_SIZE);
	spArrayListDestroy(list);
	return true;
}
static bool spArrayListCreateTest() {
	SPArrayList* list = spArrayListCreate(CAPACITY_SIZE);
	ASSERT_TRUE(list != NULL);
    ASSERT_TRUE(list->maxSize == CAPACITY_SIZE);
    ASSERT_TRUE(list->actualSize == 0);
	spArrayListDestroy(list);
	return true;
}

static bool spArrayListIsEmptyTest() {
    SPArrayList* list = spArrayListCreate(CAPACITY_SIZE);
    ASSERT_TRUE(spArrayListIsEmpty(list));

    spArrayListAddFirst(list, 0);
    ASSERT_FALSE(spArrayListIsEmpty(list));

    spArrayListRemoveLast(list);
    ASSERT_TRUE(spArrayListIsEmpty(list));
    spArrayListDestroy(list);
    return true;
}

int main() {
	
	RUN_TEST(spArrayListCreateTest);
	RUN_TEST(spArrayListBasicAddTest);
	RUN_TEST(spArrayListBasicRemoveTest);
	RUN_TEST(spArrayListBasicCopyTest);
	RUN_TEST(spArrayListGetFullTest);
	RUN_TEST(spArrayListAddFullTest);
	RUN_TEST(spArrayListRemoveFullTest);
    RUN_TEST(spArrayListBasicGetTest);
    RUN_TEST(spArrayListIsEmptyTest);
	return 0;
}
