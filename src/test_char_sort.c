#include "./generic_sequence.h"
#include <assert.h>
#include <stdio.h>

char *sample = "hello, world!";

//////////////////////////////////////////////////////////////////////////////
/// Comparing functions for `struct blah`
//////////////////////////////////////////////////////////////////////////////
static int cmp_char(char *left, char *right) {
	return *left - *right;
}

//////////////////////////////////////////////////////////////////////////////
/// The testing function
//////////////////////////////////////////////////////////////////////////////
int test_char_sort() {
	struct generic_sequence *s;
	char tmp;
	int i;

	s = gs_new(10, sizeof(char));
	if (s == NULL)
		return 0;

	/// install the comparing function
	gs_set_cmp_fn(s, (generic_sequence_cmp_fn)cmp_char);

	for (i = 0; i < 5; i++)
		assert(gs_push(s, &sample[i]));

	printf("\n=== before sort:\n");
	gs_reset_cursor(s);
	while (gs_iternext(s, &tmp))
		putchar(tmp);

	/// sort the sequence
	assert(gs_sort(s));

	printf("\n=== after sort:\n");
	gs_reset_cursor(s);
	while (gs_iternext(s, &tmp))
		putchar(tmp);

	putchar('\n');

	gs_free(s);
	return 1;
}
