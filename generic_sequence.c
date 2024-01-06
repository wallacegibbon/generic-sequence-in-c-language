#include "generic_sequence.h"
#include <stdlib.h>
#include <string.h>

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
	return self;

fail2:
	free(self);
fail:
	return NULL;
}

void gs_cleanup(struct generic_sequence *self) {
	free(self->buffer);
	free(self);
}

/// return 1 on succeed
int gs_at(struct generic_sequence *self, size_t index, void *result) {
	if (index >= self->elem_nums)
		return 0;

	memcpy(result, self->buffer + index * self->elem_size, self->elem_size);
	return 1;
}

/// return 1 on succeed
int gs_set(struct generic_sequence *self, size_t index, void *value) {
	if (index >= self->elem_nums)
		return 0;

	memcpy(self->buffer + index * self->elem_size, value, self->elem_size);
	return 1;
}

/// using self->cursor as stack pointer
int gs_push(struct generic_sequence *self, void *item) {
	if (self->cursor >= self->elem_nums)
		return 0;

	memcpy(self->buffer + self->cursor * self->elem_size, item, self->elem_size);
	self->cursor++;
	return 1;
}

int gs_pop(struct generic_sequence *self, void *item) {
	if (self->cursor == 0)
		return 0;

	self->cursor--;
	memcpy(item, self->buffer + self->cursor * self->elem_size, self->elem_size);
	return 1;
}

void gs_reset_cursor(struct generic_sequence *self) {
	self->cursor = 0;
}

/// using self->cursor as iterator index
int gs_iternext(struct generic_sequence *self, void *item) {
	if (self->cursor >= self->elem_nums) {
		self->cursor = 0;
		return 0;
	}

	memcpy(item, self->buffer + self->cursor * self->elem_size, self->elem_size);
	self->cursor++;
	return 1;
}
