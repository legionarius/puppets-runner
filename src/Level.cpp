//
// Created by bogdan on 28/04/2021.
//

#include "Level.h"

using namespace godot;

void Level::_init() {
}

void Level::_ready() {
	//	_load_bloc(Bloc());
}

void Level::_register_methods() {
	register_method("_init", &Level::_init);
	register_method("_ready", &Level::_ready);
}

void Level::_load_bloc(const Bloc bloc) {
	for (int y = 0; y < ROWS; y++) {
		for (int x = 0; x < COLUMNS; x++) {
			auto tile = bloc[y][x];
			if (tile == 0) {
				continue;
			} else {
				_add_tile(x, y, tile);
			}
		}
	}
}

void Level::_add_tile(int x, int y, int tile) {
	auto real_x = x * CELLS_PER_BLOCK;
	auto real_y = y * CELLS_PER_BLOCK;
	switch (tile) {
		case FLOOR:
			for (int i = 0; i < 2; i++) {
				set_cell(real_x+i, real_y, GRASS);
				set_cell(real_x+i, real_y+1, DIRT);
			}
			break;
		case STEP:
			break;
		case OBSTACLE:
			break;
		default:
			break;
	}
}
