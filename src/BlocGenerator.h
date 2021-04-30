//
// Created by bogdan on 28/04/2021.
//

#ifndef GODOT_NATIVE_BLOCGENERATOR_H
#define GODOT_NATIVE_BLOCGENERATOR_H

#include <Godot.hpp>
#include <array>
#include <list>
#include <vector>

#include "ActionType.h"
#include "LevelConstants.h"

namespace godot {

using Bloc = std::array<std::array<uint8_t, COLUMNS>, ROWS>;

class BlocGenerator {
	int chunkSize;
	int elevation;

public:
	BlocGenerator();
	Bloc generate_compat_bloc(ActionType lastAction, std::list<ActionType> actions);
	void addJumpChunk(const int chunkIdx, Bloc &bloc) const;
	void addRunChunk(const int chunkIdx, Bloc &bloc) const;
	void addPadding(Bloc &bloc, unsigned long padding) const;
};
} // namespace godot

#endif //GODOT_NATIVE_BLOCGENERATOR_H
