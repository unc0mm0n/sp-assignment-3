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


int main() {
	
	RUN_TEST(spArrayListBasicGetTest);
	return 0;
}