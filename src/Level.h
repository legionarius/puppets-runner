//
// Created by bogdan on 28/04/2021.
//

#ifndef GODOT_NATIVE_LEVEL_H
#define GODOT_NATIVE_LEVEL_H

#include <Godot.hpp>
#include <TileMap.hpp>
#include <TileSet.hpp>
#include <array>
#include <vector>

#include "Action.h"
#include "LevelConstants.h"

namespace godot {

using Bloc = std::array<std::array<uint8_t, COLUMNS>, ROWS>;

class Level : public TileMap {
	GODOT_CLASS(Level, TileMap);

private:
	void _add_tile(int x, int y, int tile, const Bloc &bloc);

public:
	static void _register_methods();
	void _ready();

	void _init();
	void _load_bloc(Bloc bloc);
	void addObstacle(int real_x, int real_y);
	void addStep(int x, int y, const Bloc &bloc, int real_x, int real_y);
	void addFloor(int x, int y, const Bloc &bloc, int real_x, int real_y);
	void addDirtTile(int real_x, int real_y);
	void addGrassCornerTile(int real_x, int real_y, int orientation);
	void addFloorTile(int real_x, int real_y);
};
} // namespace godot

#endif //GODOT_NATIVE_LEVEL_H
