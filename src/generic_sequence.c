#include "generic_sequence.h"
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

/// The implementation details of this struct do not need to be exposed to users.
/// A forward declaration in header file is enough for users.
struct generic_sequence {
	size_t elem_nums;
	size_t elem_size;
	size_t buffer_size;
	uint8_t *buffer;
	/// the cursor can be used as both iterator index and stack pointer
	size_t cursor;
	generic_sequence_cmp_fn cmp_fn;
};

static inline void _gs_get(struct generic_sequence *self, size_t index, void *result) {
	memcpy(result, self->buffer + index * self->elem_size, self->elem_size);
}

static inline void _gs_set(struct generic_sequence *self, size_t index, void *value) {
	memcpy(self->buffer + index * self->elem_size, value, self->elem_size);
}

/// Please ensure this function is not inlined since it uses `alloca`.
/// Or memory consumption could be big when you call this function in a loop.
static void _gs_swap(struct generic_sequence *self, size_t i, size_t j) {
	uint8_t *tmp;
	tmp = alloca(self->elem_size);
	_gs_get(self, i, tmp);
	memcpy(self->buffer + i * self->elem_size, self->buffer + j * self->elem_size, self->elem_size);
	_gs_set(self, j, tmp);
}

static inline int _gs_cmp(struct generic_sequence *self, size_t i, size_t j) {
	return self->cmp_fn(self->buffer + i * self->elem_size, self->buffer + j * self->elem_size);
}

/// return 1 on succeed
int gs_get(struct generic_sequence *self, size_t index, void *result) {
	if (index >= self->elem_nums)
		return 0;

	_gs_get(self, index, result);
	return 1;
}

/// return 1 on succeed
int gs_set(struct generic_sequence *self, size_t index, void *value) {
	if (index >= self->elem_nums)
		return 0;

	_gs_set(self, index, value);
	return 1;
}

/// using self->cursor as stack pointer
/// return 1 on succeed
int gs_push(struct generic_sequence *self, void *item) {
	if (self->cursor >= self->elem_nums)
		return 0;

	_gs_set(self, self->cursor, item);
	self->cursor++;
	return 1;
}

/// return 1 on succeed
int gs_pop(struct generic_sequence *self, void *item) {
	if (self->cursor == 0)
		return 0;

	self->cursor--;
	_gs_get(self, self->cursor, item);
	return 1;
}

void gs_reset_cursor(struct generic_sequence *self) {
	self->cursor = 0;
}

/// using self->cursor as iterator index
/// return 1 on succeed
int gs_iternext(struct generic_sequence *self, void *item) {
	if (self->cursor >= self->elem_nums) {
		self->cursor = 0;
		return 0;
	}

	_gs_get(self, self->cursor, item);
	self->cursor++;
	return 1;
}

void gs_set_cmp_fn(struct generic_sequence *self, generic_sequence_cmp_fn fn) {
	self->cmp_fn = fn;
}

int gs_sort(struct generic_sequence *self) {
	int i, j, k;

	if (self->cmp_fn == NULL)
		return 0;

	for (i = 0; i < self->elem_nums - 1; i++)
		for (j = 0, k = 1; j < self->elem_nums - 1 - i; j++, k++)
			if (_gs_cmp(self, j, k) > 0)
				_gs_swap(self, j, k);
	return 1;
}

struct generic_sequence *gs_new(size_t elem_nums, size_t elem_size) {
	struct generic_sequence *self;
	self = malloc(sizeof(struct generic_sequence));
	if (self == NULL)
		goto fail;

	self->elem_nums = elem_nums;
	self->elem_size = elem_size;
	self->buffer_size = elem_size * elem_nums;
	self->buffer = malloc(self->buffer_size);
	if (self->buffer == NULL)
		goto fail2;

	memset(self->buffer, 0, self->buffer_size);
	self->cursor = 0;
	self->cmp_fn = NULL;
	return self;

fail2:
	free(self);
fail:
	return NULL;
}

void gs_free(struct generic_sequence *self) {
	free(self->buffer);
	free(self);
}
