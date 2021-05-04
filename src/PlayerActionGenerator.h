//
// Created by acroquelois on 30/04/2021.
//

#ifndef GODOT_NATIVE_PLAYERACTIONGENERATOR_H
#define GODOT_NATIVE_PLAYERACTIONGENERATOR_H

#include "Action.h"
#include "LevelConstants.h"

#include <iterator>
#include <list>
#include <sstream>


namespace godot {

class PlayerActionGenerator {
public:
	std::list<Action> generate_player_action(std::list<ActionType> actions, std::list<ActionType> nextBlocFirstActionType);
};
}

#endif //GODOT_NATIVE_PLAYERACTIONGENERATOR_H
