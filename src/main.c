#include "./common.h"
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

	printf(">>> test float, buffer size: %ld\n", s->buffer_size);

	for (i = 0; i < 10; i++)
		assert(gs_set(s, i, &i));

	gs_reset_cursor(s);

	while (gs_iternext(s, &tmp))
		printf("test float: %.2f\n", tmp);

	gs_cleanup(s);

	return 1;
}

int test_char() {
	struct generic_sequence *s;
	char i;
	char tmp;

	s = gs_new(10, sizeof(char));
	if (s == NULL)
		return 0;

	printf(">>> test char, buffer size: %ld\n", s->buffer_size);

	for (i = 0; i < 10; i++)
		assert(gs_push(s, &i));

	for (i = 0; i < 10; i++) {
		assert(gs_pop(s, &tmp));
		printf("test char %d\n", tmp);
	}

	gs_cleanup(s);
	return 1;
}

int main(int argc, const char **argv) {
	if (!test_float())
		exit_info(1, "failed testing float");

	if (!test_char())
		exit_info(1, "failed testing float");

	return 0;
}
