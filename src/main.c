#include "./common.h"
#include "./generic_sequence.h"
#include "./test.h"

int main(int argc, const char **argv) {
	/*
	if (!test_float())
		exit_info(1, "failed testing float");

	if (!test_char())
		exit_info(1, "failed testing float");

	if (!test_char_sort())
		exit_info(1, "failed testing float");
	*/

	if (!test_struct_sort())
		exit_info(1, "failed testing float");

	return 0;
}
