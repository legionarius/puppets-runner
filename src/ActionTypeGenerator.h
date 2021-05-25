//
// Created by nahalu on 04/05/2021.
//

#ifndef GODOT_NATIVE_ACTIONTYPEGENERATOR_H
#define GODOT_NATIVE_ACTIONTYPEGENERATOR_H

#include "ActionType.h"

#include <math.h>
#include <Godot.hpp>
#include <RandomNumberGenerator.hpp>
#include <array>
#include <iterator>
#include <list>
#include <sstream>

namespace godot {
class ActionTypeGenerator {
	ActionType lastActionType;
	RandomNumberGenerator *rng;

private:
	ActionType _generate_next_valid_actiontype(ActionType actionType);
	ActionType _generate_next_bad_actiontype(ActionType actionType);

	std::list<ActionType> _generate_valid_bloc(size_t nbAction);
	std::list<ActionType> _generate_bad_bloc(std::list<ActionType> validBloc);

	std::array<std::list<ActionType>, 3> _generate_blocs(size_t nbAction);

	bool need_to_change_action_type_at_index(int64_t index, int64_t nbActionInBloc);
	real_t normalize_to_specific_range(real_t value);
	real_t weight_formula(int64_t index, int64_t nbActionInBloc);

public:
	std::array<std::list<ActionType>, 3> generate_starting_actions();
	std::list<std::array<std::list<ActionType>, 3>> generate_actions(size_t nbBloc, size_t nbAction);

	ActionTypeGenerator();
	~ActionTypeGenerator();
};
} // namespace godot

#endif //GODOT_NATIVE_ACTIONTYPEGENERATOR_H
