#ifndef P_ENUMS
#define P_ENUMS

/** \file penums.h
 * \brief wszystkie enumeracje
 *
 * Plik nagłówkowy zawiera wszystkie enumeracje które są wykorzystywane w projekcie.
 */

enum PNonStdColorBehavior {
	beh_treat_as_white,
	beh_treat_as_black,
	beh_nearest_upper,
	beh_nearest_lower,
	beh_nearest_neighbour
};

enum PCodelChooserValues {
	cc_left,
	cc_right
};

enum PDirectionPointerValues {
	dp_right,
	dp_down,
	dp_left,
	dp_up
};

enum PMachineStates {
	state_ready,
	state_running,
	state_finished
};

enum PInstructions {
	instr__empty, /* 0 */
	instr__stack_push, /* 1 */
	instr__stack_pop, /* 2 */
	instr__arithm_add, /* 3 */
	instr__arithm_substract, /* 4 */
	instr__arithm_multiply, /* 5 */
	instr__arithm_divide, /* 6 */
	instr__arithm_modulo, /* 7 */
	instr__logic_not, /* 8 */
	instr__logic_greater, /* 9 */
	instr__runtime_pointer, /* 10 */
	instr__runtime_switch, /* 11 */
	instr__stack_duplicate, /* 12 */
	instr__stack_roll, /* 13 */
	instr__io_in_number, /* 14 */
	instr__io_in_char, /* 15 */
	instr__io_out_number, /* 16 */
	instr__io_out_char /* 17 */
};

#endif
