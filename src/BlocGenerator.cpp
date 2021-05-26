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
				addRunChunk(i, bloc);
				break;
			case ActionType::JUMP:
				addJumpChunk(i, bloc);
				break;
			case ActionType::JUMP_OVER:
				addJumpOverChunk(i, bloc);
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
	auto start = chunkIdx * chunkSize;
	auto end = start + chunkSize;
	auto elevationStart = ROWS - JUMP_ELEVATION - elevation;

	for (int y = elevationStart; y < ROWS; y++) {
		for (int x = start; x < end; x++) {
			if (y == elevationStart) {
				bloc[y][x] = STEP;
			} else {
				bloc[y][x] = FLOOR;
			}
		}
	}
}

void BlocGenerator::addRunChunk(const int chunkIdx, Bloc &bloc) const {
	auto start = chunkIdx * chunkSize;
	auto end = start + chunkSize;

	for (int y = ROWS - elevation; y < ROWS; y++) {
		for (int x = start; x < end; x++) {
			bloc[y][x] = FLOOR;
		}
	}
}

void BlocGenerator::addPadding(Bloc &bloc, unsigned long padding) const {
	if (padding > 0) {
		for (int y = 0; y < ROWS; y++) {
			for (int x = COLUMNS - padding; x < COLUMNS; x++) {
				if(bloc[y][x - 1] == OBSTACLE){
					bloc[y][x] = FLOOR;
				}
				else {
					bloc[y][x] = bloc[y][x - 1];
				}
			}
		}
	}
}

void BlocGenerator::addJumpOverChunk(const int chunkIdx, Bloc &bloc) {
	auto start = chunkIdx * chunkSize;
	auto end = start + chunkSize;

	if (chunkSize < OBSTACLE_SIZE) {
		for (int y = ROWS - elevation; y < ROWS; y++) {
			for (int x = start; x < end; x++) {
				bloc[y][x] = OBSTACLE;
			}
		}
	} else {
		auto paddingStartIdx = start + OBSTACLE_SIZE;
		for (int y = ROWS - elevation; y < ROWS; y++) {
			for (int x = start; x < end; x++) {
				if (x > start && x < paddingStartIdx) {
					bloc[y][x] = OBSTACLE;
				} else {
					bloc[y][x] = FLOOR;
				}
			}
		}
	}
}

BlocGenerator::BlocGenerator() {
	elevation = 1;
}
