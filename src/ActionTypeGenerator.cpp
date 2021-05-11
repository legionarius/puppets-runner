//
// Created by nahalu on 04/05/2021.
//

#include "ActionTypeGenerator.h"

using namespace godot;

ActionTypeGenerator::ActionTypeGenerator() {
	lastActionType = ActionType::RUN;
	difficulty = 1;
}

std::list<std::array<std::list<ActionType>, 3>> ActionTypeGenerator::generate_actions(size_t nbBloc, size_t nbAction) {
	std::list<std::array<std::list<ActionType>, 3>> listBlocs;

	for (int i = 0; i < nbBloc; i++) {
		if(i == 0){
			listBlocs.push_back(_generate_starting_blocs(nbAction));
		} else {
			listBlocs.push_back(_generate_blocs(nbAction));
		}
	}

	return listBlocs;
}

std::array<std::list<ActionType>, 3> ActionTypeGenerator::_generate_blocs(size_t nbAction) {
	std::array<std::list<ActionType>, 3> blocs;

	// Generate 1 valid bloc
	std::list<ActionType> validBloc = _generate_valid_bloc(nbAction);
	blocs[0] = validBloc;

	// Generate 2 wrong bloc
	for (int a = 1; a < 3; a++) {
		std::list<ActionType> wrongBloc = _generate_wrong_bloc(validBloc, nbAction);
		blocs[a] = wrongBloc;
	}

	return blocs;
}

std::array<std::list<ActionType>, 3> ActionTypeGenerator::_generate_starting_blocs(size_t nbAction){
	std::array<std::list<ActionType>, 3> blocs;
	std::list<ActionType> runBloc;

	for (int a = 0; a < nbAction; a++) {
		runBloc.push_back(ActionType::RUN);
	}
	return {runBloc, runBloc, runBloc};
}

std::list<ActionType> ActionTypeGenerator::_generate_valid_bloc(size_t nbAction) {
	std::list<ActionType> actionTypes;

	for (int i = 0; i < nbAction; i++) {
		lastActionType = _generate_next_valid_actiontype(lastActionType);
		actionTypes.push_back(lastActionType);
	}
	return actionTypes;
}

std::list<ActionType> ActionTypeGenerator::_generate_wrong_bloc(std::list<ActionType> validBloc, size_t nbAction) {
	std::list<ActionType> actionTypes;

	/*	for (auto const &actionType : validBloc) {
        auto nextActionType = _generate_next_wrong_actiontype(actionType);
        actionTypes.push_back(nextActionType);
    }*/

	return validBloc;
}

ActionType ActionTypeGenerator::_generate_next_valid_actiontype(ActionType lastActionType) {
	ActionType action;
	switch (lastActionType) {
		case ActionType::RUN:
			action = ActionType(rand() % 3);
			break;
		case ActionType::JUMP:
			action = ActionType::RUN;
			break;
		case ActionType::JUMP_OVER:
			action = ActionType::RUN;
			break;
	}
	return action;
}

ActionType ActionTypeGenerator::_generate_next_wrong_actiontype(ActionType nextActionType) {
	ActionType action;
	switch (nextActionType) {
		case ActionType::RUN:
			action = ActionType::RUN;
			break;
		case ActionType::JUMP:
			action = ActionType::RUN;
			break;
		case ActionType::JUMP_OVER:
			action = ActionType::RUN;
			break;
	}
	return action;
}

void ActionTypeGenerator::set_selected_bloc(std::list<ActionType> actions) {
	blocSelected = actions;
}

void ActionTypeGenerator::set_difficulty(int i) {
	difficulty = i;
}
