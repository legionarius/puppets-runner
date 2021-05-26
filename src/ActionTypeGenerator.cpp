//
// Created by nahalu on 04/05/2021.
//

#include "ActionTypeGenerator.h"

using namespace godot;

ActionTypeGenerator::ActionTypeGenerator() {
	lastActionType = ActionType::RUN;
	rng = RandomNumberGenerator()._new();
	rng->randomize();
}

ActionTypeGenerator::~ActionTypeGenerator() {
	rng->free();
}

std::list<std::array<std::list<ActionType>, 3>> ActionTypeGenerator::generate_actions(size_t nbBloc, size_t nbAction) {
	std::list<std::array<std::list<ActionType>, 3>> listBlocs;
	for (int i = 0; i < nbBloc; i++) {
		listBlocs.push_back(_generate_blocs(nbAction));
	}
	return listBlocs;
}

std::array<std::list<ActionType>, 3> ActionTypeGenerator::_generate_blocs(size_t nbAction) {
	std::array<std::list<ActionType>, 3> blocs;
	blocs[0] = _generate_valid_bloc(nbAction);
	while (blocs[1] == blocs[2] || blocs[0] == blocs[1] || blocs[0] == blocs[2]) {
		blocs[1] = _generate_bad_bloc(blocs[0]);
		blocs[2] = _generate_bad_bloc(blocs[0]);
	}
	return blocs;
}

std::array<std::list<ActionType>, 3> ActionTypeGenerator::generate_starting_actions() {
	std::list<ActionType> runBloc = { ActionType::RUN, ActionType::RUN, ActionType::RUN };
	return { runBloc, runBloc, runBloc };
}

std::list<ActionType> ActionTypeGenerator::_generate_valid_bloc(size_t nbAction) {
	std::list<ActionType> actionTypes;

	for (int i = 0; i < nbAction; i++) {
		lastActionType = _generate_next_valid_actiontype(lastActionType, nbAction);
		actionTypes.push_back(lastActionType);
	}
	return actionTypes;
}

std::list<ActionType> ActionTypeGenerator::_generate_bad_bloc(std::list<ActionType> bloc) {
	std::list<ActionType>::iterator blocIterator = bloc.begin();
	for (size_t i = 0; i < bloc.size(); i++) {
		if (need_to_change_action_type_at_index(i, bloc.size())) {
			*std::next(blocIterator, i) = _generate_next_bad_actiontype(*std::next(blocIterator, i));
		}
	}
	return bloc;
}

ActionType ActionTypeGenerator::_generate_next_valid_actiontype(ActionType lastActionType, int64_t nbActionInBloc) {
	ActionType action;
	// Exclude JUMP ActionType
	int actionTypeChoices[2] = { 0, 2 };

	// Prevent succession of JUMP generation
	if(nbActionInBloc >= 5 && (lastActionType == ActionType::JUMP || lastActionType == ActionType::JUMP_OVER)){
		action = ActionType(actionTypeChoices[0]);
	}
	else if (lastActionType == ActionType::JUMP) {
		action = ActionType(actionTypeChoices[0]);
	}else {
		action = ActionType(rng->randi_range(0, 2));
	}

	return action;
}

ActionType ActionTypeGenerator::_generate_next_bad_actiontype(ActionType actionType) {
	ActionType action;
	int64_t actionTypeIndex;
	switch (actionType) {
		case ActionType::RUN:
			actionTypeIndex = rng->randi_range(1, 2);
			action = ActionType(actionTypeIndex);
			break;
		case ActionType::JUMP:
			action = ActionType::JUMP_OVER;
			break;
		case ActionType::JUMP_OVER:
			action = ActionType::JUMP;
			break;
	}
	return action;
}

bool ActionTypeGenerator::need_to_change_action_type_at_index(int64_t index, int64_t nbActionInBloc) {
	real_t randomPercentage = rng->randi_range(1, 100);
	return randomPercentage <= exp(normalize_to_specific_range(weight_formula(index, nbActionInBloc)));
}

real_t ActionTypeGenerator::weight_formula(int64_t index, int64_t nbActionInBloc) {
	return 3/nbActionInBloc + index;
}

real_t ActionTypeGenerator::normalize_to_specific_range(real_t value) {
	real_t max_action_in_bloc = 5;
	real_t min_action_in_bloc = 3;
	real_t desired_min = 2;
	real_t desired_max = 4;
	real_t actual_max = weight_formula(max_action_in_bloc-1, max_action_in_bloc);
	real_t actual_min = weight_formula(0, min_action_in_bloc);
	return desired_min + (value - actual_min) * (desired_max - desired_min) / (actual_max - actual_min);
}
