//
// Created by nahalu on 04/05/2021.
//

#ifndef GODOT_NATIVE_ACTIONTYPEGENERATOR_H
#define GODOT_NATIVE_ACTIONTYPEGENERATOR_H

#include "ActionType.h"

#include <Godot.hpp>
#include <array>
#include <list>
#include <sstream>

namespace godot {
class ActionTypeGenerator {
	std::list<ActionType> blocSelected;

	int difficulty;
	ActionType lastActionType;

private:
	ActionType _generate_next_valid_actiontype(ActionType actionType);

	ActionType _generate_next_wrong_actiontype(ActionType actionType);

	std::list<ActionType> _generate_valid_bloc(size_t nbAction);

	std::list<ActionType> _generate_wrong_bloc(std::list<ActionType> validBloc, size_t nbAction);

	std::array<std::list<ActionType>, 3> _generate_blocs(size_t nbAction);

public:
	void set_selected_bloc(std::list<ActionType> actionTypeList);

	void set_difficulty(int i);

	std::list<std::array<std::list<ActionType>, 3>> generate_actions(size_t nbBloc, size_t nbAction);

	ActionTypeGenerator();
};
} // namespace godot

#endif //GODOT_NATIVE_ACTIONTYPEGENERATOR_H
