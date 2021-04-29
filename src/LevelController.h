//
// Created by bogdan on 29/04/2021.
//

#ifndef GODOT_NATIVE_LEVELCONTROLLER_H
#define GODOT_NATIVE_LEVELCONTROLLER_H

#include <Godot.hpp>
#include <Node.hpp>
#include <list>
#include "ActionType.h"

namespace godot {
class LevelController : public Node {
	GODOT_CLASS(LevelController, Node);

	std::list<std::list<ActionType>> actions;
	std::list<std::list<ActionType>> generateActions();

public:
	static void _register_methods();
	void _init();
};
} // namespace godot

#endif //GODOT_NATIVE_LEVELCONTROLLER_H
