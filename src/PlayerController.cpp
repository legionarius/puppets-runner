//
// Created by acroquelois on 29/04/2021.
//

#include "PlayerController.h"

using namespace godot;

void PlayerController::_init() {
}

void PlayerController::_ready() {
}

void PlayerController::_process(const real_t delta) {
	_elapsed_time += delta;
	std::stringstream test;
	test << "Delta : " << _elapsed_time;
	// Godot::print(test.str().c_str());
	if(!_actions.empty()){
		if (_elapsed_time > _actions.back().timestamp){
			player->set_current_action_type(_actions.back().type);
			_actions.pop_back();
		}
	}
}

void PlayerController::connect_player() {
	player = Object::cast_to<Player>(get_parent()->get_node("Player"));
}

void PlayerController::reset_delta_aggregator() {
	_elapsed_time = 0.f;
}

void PlayerController::fill_action_list(std::vector<Action> action_list) {
	_actions = action_list;
}

void PlayerController::_register_methods() {
	register_method("_init", &PlayerController::_init);
	register_method("_ready", &PlayerController::_ready);
	register_method("_process", &PlayerController::_process);
}
