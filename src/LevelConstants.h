//
// Created by bogdan on 30/04/2021.
//

#ifndef GODOT_NATIVE_LEVELCONSTANTS_H
#define GODOT_NATIVE_LEVELCONSTANTS_H

// Level structure
#define ROWS 9
#define COLUMNS 16
#define CELLS_PER_BLOCK 2
#define JUMP_ELEVATION 1
#define OBSTACLE_SIZE 3
#define WIDTH 1280

// Type of blocs (4x4 tiles of 40)
#define NOTHING 0
#define FLOOR 1
#define STEP 2
#define OBSTACLE 3

// Tiles identifiers
#define DIRT 2
#define PIKE 8
#define GRASS 3
#define GRASS_CORNER_R 5
#define GRASS_CORNER_L 4
#define SMALL_GRASS_CORNER_R 6
#define SMALL_GRASS_CORNER_L 7
#define VERT_GRASS_R 11
#define VERT_GRASS_L 10


#endif //GODOT_NATIVE_LEVELCONSTANTS_H
