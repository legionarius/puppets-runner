//
// Created by bogdan on 29/04/2021.
//

#include "LevelController.h"

using namespace godot;

void LevelController::_init() {
	actions = generateActions();
}

std::list<std::list<ActionType>> LevelController::generateActions() {
	return std::list {
				std::list<ActionType>{ ActionType::RUN },
				std::list<ActionType>{ ActionType::RUN, ActionType::RUN, ActionType::JUMP },
	};
}

void LevelController::_register_methods() {
	register_method("_init", &LevelController::_init);
}
