//
// Created by bogdan on 29/04/2021.
//

#ifndef GODOT_NATIVE_LEVELCONTROLLER_H
#define GODOT_NATIVE_LEVELCONTROLLER_H

#include "Action.h"
#include "ActionType.h"
#include "ActionTypeGenerator.h"
#include "BlocGenerator.h"
#include "BlocSelector.h"
#include "Level.h"
#include "Player.h"
#include "PlayerActionGenerator.h"
#include "PlayerController.h"
#include "PlayerProgress.h"
#include "Signals.h"
#include "Wolf.h"

#include <Area2D.hpp>
#include <Godot.hpp>
#include <Node.hpp>
#include <PackedScene.hpp>
#include <ParallaxBackground.hpp>
#include <Position2D.hpp>
#include <Ref.hpp>
#include <ResourceLoader.hpp>
#include <TileMap.hpp>
#include <Timer.hpp>
#include <Viewport.hpp>
#include <algorithm>
#include <iterator>
#include <list>
#include <random>

#define SPAWN_PLAYER_ELEVATION 20
#define PARALLAX_SCROLL 200

#define NB_BLOC_LENGTH_3 10
#define NB_BLOC_LENGTH_4 20
#define NB_BLOC_LENGTH_5 300

namespace godot {

using Bloc = std::array<std::array<uint8_t, COLUMNS>, ROWS>;
using ActionsArray = std::array<std::list<ActionType>, 3>;

class LevelController : public Node {
	GODOT_CLASS(LevelController, Node);

	Area2D *endBlock;
	Area2D *midBlock;
	Area2D *voidBloc;
	ParallaxBackground *parallax;
	real_t scrollOffset;
	Player *player;
	Wolf *wolf;
	PlayerController *playerController;
	Position2D *spawnPoint;

	PlayerActionGenerator playerActionGenerator;
	BlocGenerator blocGenerator;
	ActionTypeGenerator *actionTypeGenerator;

	Level *map;
	BlocSelector *blocSelector;
	int8_t blocSelectedIndex;
	int64_t score;

	std::list<std::array<std::list<ActionType>, 3>> actions;
	ActionsArray nextActionsArray;

	void _addActions();
	void _clearActions();
	Bloc _get_selected_block_tile();

public:
	static void _register_methods();
	void _init();
	void _ready();
	void _process(const real_t delta);
	void _exit_tree();

	void end_block();
	void mid_block();
	void load_action_type();
	void load_next_block_elements();
	void load_next_block_tile();
	void load_next_block_action();
	void load_next_blocks_in_selector();
	void load_player();
	void load_wolf();
	void load_next_block_player_action();
	void set_block_selected_index(int8_t m_block_selected_index);
	void end_level();
	void start();
	void _set_wolf_spawn();
	Bloc _generate_first_bloc();

	~LevelController();
};
} // namespace godot

#endif //GODOT_NATIVE_LEVELCONTROLLER_H
