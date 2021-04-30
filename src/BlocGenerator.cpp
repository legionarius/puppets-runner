//
// Created by bogdan on 28/04/2021.
//

#include "BlocGenerator.h"
#include <list>

using namespace godot;

Bloc BlocGenerator::generate_compat_bloc(const ActionType lastAction, std::list<ActionType> actions) {
	auto bloc = Bloc();
	auto row_index = 0;
	auto max_elevation = 5; // Can be a preprocessor var
	int chunks = actions.size();
	chunkSize = COLUMNS / chunks;
	int paddingSize = COLUMNS % chunks;

	ActionType currentAction;
	ActionType previousAction = lastAction;

	for (int i = 0; i < chunks; i++) {
		currentAction = actions.front();
		actions.pop_front();
		switch (currentAction) {
			case ActionType::RUN:
				Godot::print("Generating RUN chunk...");
				addRunChunk(i, bloc);
				break;
			case ActionType::JUMP:
				Godot::print("Generating JUMP chunk...");
				addJumpChunk(i, bloc);
				break;
			default:
				break;
		}
		previousAction = currentAction;
	}

	addPadding(bloc, paddingSize);

	return bloc;
}

void BlocGenerator::addJumpChunk(const int chunkIdx, Bloc &bloc) const {
	for (int y = ROWS - JUMP_ELEVATION - elevation; y < ROWS; y++) {
		for (int x = chunkIdx * chunkSize; x < chunkIdx * chunkSize + chunkSize; x++) {
			bloc[y][x] = 1;
		}
	}
}

void BlocGenerator::addRunChunk(const int chunkIdx, Bloc &bloc) const {
	for (int y = ROWS - elevation; y < ROWS; y++) {
		for (int x = chunkIdx * chunkSize; x < chunkIdx * chunkSize + chunkSize; x++) {
			bloc[y][x] = 1;
		}
	}
}

void BlocGenerator::addPadding(Bloc &bloc, unsigned long padding) const {
	if (padding > 0) {
		Godot::print("Add padding...");
		for (int y = 0; y < ROWS; y++) {
			for (int x = COLUMNS - padding; x < COLUMNS; x++) {
				bloc[y][x] = bloc[y][x - 1];
			}
		}
	}
}

BlocGenerator::BlocGenerator() {
	elevation = 1;
}
