#include "p_enums.h"

const char * PEnums::stdColor(PStdColors color)
{
	switch (color) {
		case color_light_red: return "light red";
		case color_normal_red: return "normal red";
		case color_dark_red: return "dark red";
		case color_light_yellow: return "light yellow";
		case color_normal_yellow: return "normal yellow";
		case color_dark_yellow: return "dark yellow";
		case color_light_green: return "light green";
		case color_normal_green: return "normal green";
		case color_dark_green: return "dark green";
		case color_light_cyan: return "light cyan";
		case color_normal_cyan: return "normal cyan";
		case color_dark_cyan: return "dark cyan";
		case color_light_blue: return "light blue";
		case color_normal_blue: return "normal blue";
		case color_dark_blue: return "dark blue";
		case color_light_magenta: return "light magenta";
		case color_normal_magenta: return "normal magenta";
		case color_dark_magenta: return "dark magenta";
		case color_white: return "white";
		case color_black: return "black";
	}
}

const char * PEnums::nonStdColorBehavior(PNonStdColorBehavior behavior)
{
	switch (behavior) {
		case beh_treat_as_white: return "treat as white";
		case beh_treat_as_black: return "treat as black";
		case beh_nearest_upper: return "nearest upper";
		case beh_nearest_lower: return "nearest lower";
		case beh_nearest_neighbour: return "nearest neighbour";
	}
}

const char * PEnums::codelChooser(PCodelChooserValues codel_chooser)
{
	switch (codel_chooser) {
		case cc_left: return "left";
		case cc_right: return "right";
	}
}

const char * PEnums::directionPointer(PDirectionPointerValues direction_pointer)
{
	switch (direction_pointer) {
		case dp_right: return "right";
		case dp_down: return "down";
		case dp_left: return "left";
		case dp_up: return "up";
	}
}

const char * PEnums::machineState(PMachineStates state)
{
	switch (state) {
		case state_ready: return "ready";
		case state_running: return "running";
		case state_finished: return "finished";
	}
}

const char * PEnums::instruction(PInstructions instruction)
{
	switch (instruction) {
		case pietInstr_special_empty: return "empty";
		case pietInstr_stack_push: return "push";
		case pietInstr_stack_pop: return "pop";
		case pietInstr_arithm_add: return "add";
		case pietInstr_arithm_subtract: return "subtract";
		case pietInstr_arithm_multiply: return "multiply";
		case pietInstr_arithm_divide: return "divide";
		case pietInstr_arithm_modulo: return "modulo";
		case pietInstr_logic_not: return "not";
		case pietInstr_logic_greater: return "greater";
		case pietInstr_runtime_pointer: return "pointer";
		case pietInstr_runtime_switch: return "switch";
		case pietInstr_stack_duplicate: return "duplicate";
		case pietInstr_stack_roll: return "roll";
		case pietInstr_io_in_number: return "read number";
		case pietInstr_io_in_char: return "read char";
		case pietInstr_io_out_number: return "print number";
		case pietInstr_io_out_char: return "print char";
		case pietInstr_special_terminate: return "terminate";
	}
}
