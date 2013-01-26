#ifndef P_ENUMS
#define P_ENUMS

/** \file penums.h
 * \brief Plik nagłówkowy z definicjami enumeracji
 *
 * Plik nagłówkowy zawiera wszystkie definicje enumeracji które są wykorzystywane w projekcie.
 */

/** \brief Standardowe kolory
 *
 * Enumeracja wyszczególniająca kolory standardowe wykorzystywane do określania wykonywanej instrukcji.
 */
enum PStdColors {
	color_light_red,
	color_normal_red,
	color_dark_red,
	color_light_yellow,
	color_normal_yellow,
	color_dark_yellow,
	color_light_green,
	color_normal_green,
	color_dark_green,
	color_light_cyan,
	color_normal_cyan,
	color_dark_cyan,
	color_light_blue,
	color_normal_blue,
	color_dark_blue,
	color_light_magenta,
	color_normal_magenta,
	color_dark_magenta,
	color_white,
	color_black
};

/** \brief Interpretacja niestandardowych kolorów
 *
 * Enumeracja wyszczególniająca możliwe sposoby interpretacji kolorów niestandardowych.
 */
enum PNonStdColorBehavior {
	beh_treat_as_white,
	beh_treat_as_black,
	beh_nearest_upper,
	beh_nearest_lower,
	beh_nearest_neighbour
};

/** \brief Tryby codel chooser
 *
 * Enumeracja wyszczególniająca tryby pracy codel chooser, czyli kierunki w których głowica ma szukać skrajnego kodela po dojściu do granicy bloku w kierunku wskazanym przez direction pointer.
 */
enum PCodelChooserValues {
	cc_left,
	cc_right
};

/** \brief Tryby direction pointer
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
	pietInstr_special_empty, /** 0 - dodatkowa instrukcja wysyłana do wirtualnej maszyny komunikująca o 8 nieudanych próbach wykonania przez głowicę ruchu, zakończenie pracy programu */
	pietInstr_stack_push, /** 1 - instrukcja PUSH */
	pietInstr_stack_pop, /** 2 - instrukcja POP */
	pietInstr_arithm_add, /** 3 - instrukcja ADD */
	pietInstr_arithm_subtract, /** 4 - instrukcja SUB */
	pietInstr_arithm_multiply, /** 5 - instrukcja MUL */
	pietInstr_arithm_divide, /** 6 - instrukcja DIV */
	pietInstr_arithm_modulo, /** 7 - instrukcja MOD */
	pietInstr_logic_not, /** 8 - instrukcja NOT */
	pietInstr_logic_greater, /** 9 - instrukcja GREATER */
	pietInstr_runtime_pointer, /** 10 - instrukcja POINER */
	pietInstr_runtime_switch, /** 11 - instrukcja SWITCH */
	pietInstr_stack_duplicate, /** 12 - instrukcja DUP */
	pietInstr_stack_roll, /** 13 - instrukcja ROLL */
	pietInstr_io_in_number, /** 14 - instrukcja IN(number) */
	pietInstr_io_in_char, /** 15 - instrukcja IN(char) */
	pietInstr_io_out_number, /** 16 - instrukcja OUT(number) */
	pietInstr_io_out_char, /** 17 - instrukcja OUT(char) */
	pietInstr_special_terminate, /** 18 - instrukcja TERMINATE */
};

#endif
