#include "./generic_sequence.h"
#include <assert.h>
#include <stdio.h>

int test_float() {
	struct generic_sequence *s;
	float i;
	float tmp;

	s = gs_new(10, sizeof(float));
	if (s == NULL)
		return 0;

	for (i = 0; i < 10; i++)
		assert(gs_set(s, i, &i));

	for (i = 0; i < 10; i++) {
		assert(gs_get(s, i, &tmp));
		printf(">>1 %.2f\n", tmp);
	}

	gs_reset_cursor(s);
	while (gs_iternext(s, &tmp))
		printf(">>2 %.2f\n", tmp);

	gs_free(s);
	return 1;
}
