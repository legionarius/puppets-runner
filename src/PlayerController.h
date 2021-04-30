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
#include <vector>


namespace godot {

class PlayerController : public Node {
	GODOT_CLASS(PlayerController, Node);

	Player *player;

	std::vector<Action> _actions;
	real_t _elapsed_time;

public:
	static void _register_methods();
	void _init();
	void _ready();
	void _process(const real_t delta);
	void _exit();

	void connect_player();
	void reset_delta_aggregator();
	void fill_action_list(std::vector<Action> action_list);

};

}

#endif //GODOT_NATIVE_PLAYERCONTROLLER_H
