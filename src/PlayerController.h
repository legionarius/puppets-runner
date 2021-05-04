//
// Created by acroquelois on 29/04/2021.
//

#ifndef GODOT_NATIVE_PLAYERCONTROLLER_H
#define GODOT_NATIVE_PLAYERCONTROLLER_H

#include "Action.h"
#include "Player.h"

#include <Godot.hpp>
#include <Node.hpp>
#include <SceneTree.hpp>
#include <Viewport.hpp>
#include <sstream>
#include <list>


namespace godot {

class PlayerController : public Node {
	GODOT_CLASS(PlayerController, Node);

	Player *player;

	std::list<Action> _actions;

public:
	static void _register_methods();
	void _init();
	void _ready();
	void _process(const real_t delta);
	void _exit();

	void connect_player();
	void fill_action_list(std::list<Action> action_list);

};

}

#endif //GODOT_NATIVE_PLAYERCONTROLLER_H
