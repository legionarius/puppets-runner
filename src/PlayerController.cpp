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
	if(!_actions.empty()){
		if (player->get_position().x > _actions.back().trigger_position && (player->get_position().x - _actions.back().trigger_position < 10)){
			player->set_current_action_type(_actions.back().type);
			_actions.pop_back();
		}
	}
}

void PlayerController::connect_player() {
	player = Object::cast_to<Player>(get_parent()->get_node("Player"));
}

void PlayerController::fill_action_list(std::list<Action> action_list) {
	_actions.insert(_actions.begin(), action_list.begin(), action_list.end());
}

void PlayerController::_register_methods() {
	register_method("_init", &PlayerController::_init);
	register_method("_ready", &PlayerController::_ready);
	register_method("_process", &PlayerController::_process);
}
