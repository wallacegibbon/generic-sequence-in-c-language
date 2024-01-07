#include "./generic_sequence.h"
#include <assert.h>
#include <stdio.h>

int test_char() {
	struct generic_sequence *s;
	char i;
	char tmp;

	s = gs_new(10, sizeof(char));
	if (s == NULL)
		return 0;

	for (i = 0; i < 10; i++)
		assert(gs_push(s, &i));

	for (i = 0; i < 10; i++) {
		assert(gs_pop(s, &tmp));
		printf(">>3 %d\n", tmp);
	}

	gs_free(s);
	return 1;
}
