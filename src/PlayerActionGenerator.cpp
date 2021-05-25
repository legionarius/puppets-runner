//
// Created by acroquelois on 30/04/2021.
//

#include "PlayerActionGenerator.h"

using namespace godot;

std::list<Action> PlayerActionGenerator::generate_player_action(std::list<ActionType> actions, std::list<ActionType> nextBlocActionType) {
	std::list<Action> playerActionsBloc;
	std::list<ActionType>::iterator playerActionsBlocIt;
	real_t actionIndex = 1;
	for (playerActionsBlocIt = actions.begin(); playerActionsBlocIt != actions.end(); ++playerActionsBlocIt) {
		ActionType nextActionType;
		real_t actionWidth;
		if (std::next(playerActionsBlocIt, 1) == actions.end()) {
			nextActionType = nextBlocActionType.front();
			actionWidth = WIDTH / nextBlocActionType.size();
		} else {
			nextActionType = *std::next(playerActionsBlocIt, 1);
			actionWidth = WIDTH / actions.size();
		}

		switch (nextActionType) {
			case ActionType::JUMP:
				playerActionsBloc.push_front(Action{ nextActionType, (actionWidth * actionIndex) - 120 });
				break;
			case ActionType::JUMP_OVER:
				playerActionsBloc.push_front(Action{ nextActionType, (actionWidth * actionIndex) - 20 });
				break;
			case ActionType::RUN:
				playerActionsBloc.push_front(Action{ nextActionType, (actionWidth * actionIndex) - 20 });
				break;
		}
		++actionIndex;
	}
	return playerActionsBloc;
}