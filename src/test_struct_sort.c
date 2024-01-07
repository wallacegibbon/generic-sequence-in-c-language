#include "./generic_sequence.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>

struct blah {
	const char *name;
	int age;
};

/// define a global array to simplify the initializing of the testing generic_sequence.
struct blah people[] = {{"Harry", 10}, {"Albus", 109}, {"Severus", 50}};

//////////////////////////////////////////////////////////////////////////////
/// Methods for `struct blah`
//////////////////////////////////////////////////////////////////////////////
void blah_display(struct blah *self) {
	printf("name %s, age: %d\n", self->name, self->age);
}


//////////////////////////////////////////////////////////////////////////////
/// Comparing functions for `struct blah`
//////////////////////////////////////////////////////////////////////////////
static int cmp_name(struct blah *left, struct blah *right) {
	return strcmp(left->name, right->name);
}

static int cmp_age(struct blah *left, struct blah *right) {
	return left->age - right->age;
}


//////////////////////////////////////////////////////////////////////////////
/// The testing function
//////////////////////////////////////////////////////////////////////////////
int test_struct_sort() {
	struct generic_sequence *s;
	struct blah tmp;
	int i;

	s = gs_new(3, sizeof(struct blah));
	if (s == NULL)
		return 0;

	/// install the comparing function
	//gs_set_cmp_fn(s, (generic_sequence_cmp_fn)cmp_name);
	gs_set_cmp_fn(s, (generic_sequence_cmp_fn)cmp_age);

	/// Pushing values to generic sequence
	for (i = 0; i < 3; i++)
		assert(gs_push(s, &people[i]));

	printf("\n=== before sort:\n");
	gs_reset_cursor(s);
	while (gs_iternext(s, &tmp))
		blah_display(&tmp);

	/// sort the sequence
	assert(gs_sort(s));

	printf("\n=== after sort:\n");
	gs_reset_cursor(s);
	while (gs_iternext(s, &tmp))
		blah_display(&tmp);

	putchar('\n');

	gs_free(s);
	return 1;
}
