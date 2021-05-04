//
// Created by bogdan on 28/04/2021.
//

#include "BlocTextureGenerator.h"

using namespace godot;

ImageTexture *BlocTextureGenerator::_generate(const Bloc bloc) {
	auto texture = ImageTexture::_new();
	image = Image::_new();
	image->create(256, 144, false, Image::FORMAT_RGBA8);
	image->fill(Color(0, 0, 0, 1));
	image->lock();
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
	texture->create_from_image(image);
	return texture;
}

void BlocTextureGenerator::_add_tile(int x, int y, int tile, const Bloc &bloc) {
	auto real_x = x * 16;
	auto real_y = y * 16;
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
			Godot::print("[BlocTextureGenerator] Tile value unknown !");
			break;
	}
}
void BlocTextureGenerator::addFloor(int x, int y, const Bloc &bloc, int real_x, int real_y) {
	addFloorTile(real_x, real_y);
}

void BlocTextureGenerator::addStep(int x, int y, const Bloc &bloc, int real_x, int real_y) {
	// If we don't have a bloc above the current one
	// we add the ground layer.
	if (bloc[y - 1][x] == NOTHING) {
		// If we don't have a bloc previous to the current one
		// we add the ground corner layer.
		if (bloc[y][x - 1] == NOTHING) {
			addGrassCornerTile(real_x, real_y, -1);
		} else if (x + 1 < COLUMNS && bloc[y][x + 1] == NOTHING) {
			addGrassCornerTile(real_x, real_y, 1);
		} else {
			addFloorTile(real_x, real_y);
		}
	} else { // We have a full ground bloc
		addDirtTile(real_x, real_y);
	}
}

void BlocTextureGenerator::addObstacle(int real_x, int real_y) {
	for (int i = 0; i < 2; i++) {
		set_cell(real_x + i, real_y, obstacle);
		set_cell(real_x + i, real_y + 1, obstacle);
	}
}

void BlocTextureGenerator::addDirtTile(int real_x, int real_y) {
	for (int i = 0; i < 2; i++) {
		set_cell(real_x + i, real_y, ground);
		set_cell(real_x + i, real_y + 1, ground);
	}
}

void BlocTextureGenerator::addFloorTile(int real_x, int real_y) {
	for (int i = 0; i < 2; i++) {
		set_cell(real_x + i, real_y, ground);
		set_cell(real_x + i, real_y + 1, ground);
	}
}

void BlocTextureGenerator::addGrassCornerTile(int real_x, int real_y, int orientation) {
	if (orientation == -1) {
		set_cell(real_x, real_y, ground);
		set_cell(real_x + 1, real_y, ground);
		set_cell(real_x, real_y + 1, ground);
		set_cell(real_x + 1, real_y + 1, ground);
	} else {
		set_cell(real_x, real_y, ground);
		set_cell(real_x + 1, real_y, ground);
		set_cell(real_x, real_y + 1, ground);
		set_cell(real_x + 1, real_y + 1, ground);
	}
}

void BlocTextureGenerator::set_cell(int x, int y, Color color) {
	auto real_x = x;
	auto real_y = y;
	for (int i = real_x; i < real_x + 12; i++) {
		for (int j = real_y; j < real_y + 12; j++) {
			image->set_pixel(i, j, color);
		}
	}
}
BlocTextureGenerator::BlocTextureGenerator() {
	obstacle = Color(255, 0, 0, 1);
	ground = Color(1, 1, 1, 1);
}
