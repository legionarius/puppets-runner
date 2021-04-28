//
// Created by bogdan on 28/04/2021.
//

#ifndef GODOT_NATIVE_LEVEL_H
#define GODOT_NATIVE_LEVEL_H

#include <Godot.hpp>
#include <array>
#include <vector>

#include "Action.h"

namespace godot {
class Level {
private:
	std::vector<std::vector<Action>> blocs;

public:
	Level();
};
} // namespace godot

#endif //GODOT_NATIVE_LEVEL_H
