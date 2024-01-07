#ifndef __GENERIC_SEQUENCE_H
#define __GENERIC_SEQUENCE_H

#include <stddef.h>
#include <stdint.h>

typedef int (*generic_sequence_cmp_fn)(void *left, void *right);

struct generic_sequence {
	size_t elem_nums;
	size_t elem_size;
	size_t buffer_size;
	uint8_t *buffer;
	/// the cursor can be used as both iterator index and stack pointer
	size_t cursor;
	generic_sequence_cmp_fn cmp_fn;
};

struct generic_sequence *gs_new(size_t elem_nums, size_t elem_size);
void gs_free(struct generic_sequence *self);

int gs_get(struct generic_sequence *self, size_t index, void *result);
int gs_set(struct generic_sequence *self, size_t index, void *value);

int gs_push(struct generic_sequence *self, void *item);
int gs_pop(struct generic_sequence *self, void *item);

void gs_reset_cursor(struct generic_sequence *self);
int gs_iternext(struct generic_sequence *self, void *item);

void gs_set_cmp_fn(struct generic_sequence *self, generic_sequence_cmp_fn fn);
int gs_sort(struct generic_sequence *self);

#endif
