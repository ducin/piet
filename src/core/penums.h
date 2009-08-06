#ifndef P_ENUMS
#define P_ENUMS

/** \file penums.h
 * \brief wszystkie enumeracje
 *
 * Plik nagłówkowy zawiera wszystkie enumeracje które są wykorzystywane w projekcie.
 */

/** \brief interpretacja niestandardowych kolorów
 *
 * Enumeracja wyszczególniająca możliwe sposoby interpretacji kolorów niestandardowych
 */
enum PNonStdColorBehavior {
	beh_treat_as_white,
	beh_treat_as_black,
	beh_nearest_upper,
	beh_nearest_lower,
	beh_nearest_neighbour
};

/** \brief tryby codel chooser
 *
 * Enumeracja wyszczególniająca tryby pracy codel chooser, czyli kierunki w których głowica ma szukać skrajnego kodela po dojściu do granicy bloku w kierunku wskazanym przez direction pointer.
 */
enum PCodelChooserValues {
	cc_left,
	cc_right
};

/** \brief tryby direction pointer
 *
 * Enumeracja wyszczególniająca tryby pracy direction pointer, czyli kierunki w których głowica ma poruszać się aż dojdzie do granicy bloku kolorów (potem codel chooser określa z której strony przejdzie do nowego bloku - dzięki temu glowica przechodzi z jednego bloku kolorów do drugiego i wykonują się instrukcje Pieta).
 */
enum PDirectionPointerValues {
	dp_right,
	dp_down,
	dp_left,
	dp_up
};

/** \brief stany maszyny wirtualnej
 *
 * Enumeracja wyszczególniająca stany tzw. "maszyny wirtualnej Pieta", która zajmuje się pełną interpretacją kodu Pieta.
 */
enum PMachineStates {
	state_ready,
	state_running,
	state_finished
};

/** \brief instrukcje Pieta
 *
 * Enumeracja wyszczególniająca wszystkie instrukcje wykonywane przez język Piet.
 */
enum PInstructions {
	pietInstr_empty, /* 0 */
	pietInstr_stack_push, /* 1 */
	pietInstr_stack_pop, /* 2 */
	pietInstr_arithm_add, /* 3 */
	pietInstr_arithm_subtract, /* 4 */
	pietInstr_arithm_multiply, /* 5 */
	pietInstr_arithm_divide, /* 6 */
	pietInstr_arithm_modulo, /* 7 */
	pietInstr_logic_not, /* 8 */
	pietInstr_logic_greater, /* 9 */
	pietInstr_runtime_pointer, /* 10 */
	pietInstr_runtime_switch, /* 11 */
	pietInstr_stack_duplicate, /* 12 */
	pietInstr_stack_roll, /* 13 */
	pietInstr_io_in_number, /* 14 */
	pietInstr_io_in_char, /* 15 */
	pietInstr_io_out_number, /* 16 */
	pietInstr_io_out_char /* 17 */
};

#endif
