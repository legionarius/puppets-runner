//
// Created by bogdan on 28/04/2021.
//

#ifndef GODOT_NATIVE_ACTION_H
#define GODOT_NATIVE_ACTION_H

#include "ActionType.h"

#include <Godot.hpp>

namespace godot {
struct Action {
	ActionType type;
	real_t trigger_position;
};
} // namespace godot

#endif //GODOT_NATIVE_ACTION_H
