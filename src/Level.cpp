//
// Created by bogdan on 28/04/2021.
//

#include "Level.h"

using namespace godot;

void Level::_init() {
}

void Level::_ready() {
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
				_add_tile(x, y, tile, bloc);
			}
		}
	}
}

void Level::_add_tile(int x, int y, int tile, const Bloc &bloc) {
	auto real_x = x * CELLS_PER_BLOCK;
	auto real_y = y * CELLS_PER_BLOCK;
	switch (tile) {
		case FLOOR:
			addFloor(x, y, bloc, real_x, real_y);
			break;
		case STEP:
			addStep(x, y, bloc, real_x, real_y);
			break;
		case OBSTACLE:
			addObstacle(real_x, real_y);
			break;
		default:
			Godot::print("[Level] Tile value unknown !");
			break;
	}
}
void Level::addFloor(int x, int y, const Bloc &bloc, int real_x, int real_y) {
	// If we don't have a bloc above the current one
	// we add the grass layer.
	if (bloc[y - 1][x] == NOTHING) {
		addFloorTile(real_x, real_y);
	} else { // We have a full dirt bloc
		if (bloc[y - 1][x - 1] == NOTHING) {
			set_cell(real_x, real_y, SMALL_GRASS_CORNER_L);
			set_cell(real_x + 1, real_y, DIRT);
			set_cell(real_x, real_y + 1, DIRT);
			set_cell(real_x + 1, real_y + 1, DIRT);
		} else if (x + 1 < COLUMNS && bloc[y - 1][x + 1] == NOTHING) {
			set_cell(real_x, real_y, DIRT);
			set_cell(real_x + 1, real_y, SMALL_GRASS_CORNER_R);
			set_cell(real_x, real_y + 1, DIRT);
			set_cell(real_x + 1, real_y + 1, DIRT);
		} else {
			addDirtTile(real_x, real_y);
		}
	}
}

void Level::addStep(int x, int y, const Bloc &bloc, int real_x, int real_y) {
	// If we don't have a bloc above the current one
	// we add the grass layer.
	if (bloc[y - 1][x] == NOTHING) {
		// If we don't have a bloc previous to the current one
		// we add the grass corner layer.
		if (bloc[y][x - 1] == NOTHING) {
			addGrassCornerTile(real_x, real_y, -1);
		} else if (x + 1 < COLUMNS && bloc[y][x + 1] == NOTHING) {
			addGrassCornerTile(real_x, real_y, 1);
		} else {
			addFloorTile(real_x, real_y);
		}
	} else { // We have a full dirt bloc
		addDirtTile(real_x, real_y);
	}
}

void Level::addObstacle(int real_x, int real_y) {
	for (int i = 0; i < 2; i++) {
		set_cell(real_x + i, real_y, PIKE);
		set_cell(real_x + i, real_y + 1, DIRT);
	}
}

void Level::addDirtTile(int real_x, int real_y) {
	for (int i = 0; i < 2; i++) {
		set_cell(real_x + i, real_y, DIRT);
		set_cell(real_x + i, real_y + 1, DIRT);
	}
}

void Level::addFloorTile(int real_x, int real_y) {
	for (int i = 0; i < 2; i++) {
		set_cell(real_x + i, real_y, GRASS);
		set_cell(real_x + i, real_y + 1, DIRT);
	}
}

void Level::addGrassCornerTile(int real_x, int real_y, int orientation) {
	if (orientation == -1) {
		set_cell(real_x, real_y, GRASS_CORNER_L);
		set_cell(real_x + 1, real_y, GRASS);
		set_cell(real_x, real_y + 1, VERT_GRASS_L);
		set_cell(real_x + 1, real_y + 1, DIRT);
	} else {
		set_cell(real_x, real_y, GRASS);
		set_cell(real_x + 1, real_y, GRASS_CORNER_R);
		set_cell(real_x, real_y + 1, DIRT);
		set_cell(real_x + 1, real_y + 1, VERT_GRASS_R);
	}
}
