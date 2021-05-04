//
// Created by bogdan on 28/04/2021.
//

#ifndef GODOT_NATIVE_BLOCTEXTUREGENERATOR_H
#define GODOT_NATIVE_BLOCTEXTUREGENERATOR_H

#include <Image.hpp>
#include <ImageTexture.hpp>
#include <array>
#include <vector>

#include "Action.h"
#include "LevelConstants.h"

namespace godot {

using Bloc = std::array<std::array<uint8_t, COLUMNS>, ROWS>;

class BlocTextureGenerator {
	Image *image;
	Color ground;
	Color obstacle;

private:
	void _add_tile(int x, int y, int tile, const Bloc &bloc);
	void addObstacle(int real_x, int real_y);
	void addStep(int x, int y, const Bloc &bloc, int real_x, int real_y);
	void addFloor(int x, int y, const Bloc &bloc, int real_x, int real_y);
	void addDirtTile(int real_x, int real_y);
	void addGrassCornerTile(int real_x, int real_y, int orientation);
	void addFloorTile(int real_x, int real_y);
	void set_cell(int x, int y, Color color);

public:
	BlocTextureGenerator();
	ImageTexture *_generate(Bloc bloc);
};
} // namespace godot

#endif //GODOT_NATIVE_BLOCTEXTUREGENERATOR_H
