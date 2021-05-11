//
// Created by bogdan on 29/04/2021.
//

#ifndef GODOT_NATIVE_LEVELCONTROLLER_H
#define GODOT_NATIVE_LEVELCONTROLLER_H

#include "Action.h"
#include "ActionType.h"
#include "ActionTypeGenerator.h"
#include "BlocGenerator.h"
#include "Level.h"
#include "Player.h"
#include "PlayerActionGenerator.h"
#include "PlayerController.h"
#include "PlayerProgress.h"
#include "Signals.h"

#include "BlocSelector.h"
#include <Area2D.hpp>
#include <Godot.hpp>
#include <Node.hpp>
#include <PackedScene.hpp>
#include <Position2D.hpp>
#include <Ref.hpp>
#include <ResourceLoader.hpp>
#include <TileMap.hpp>
#include <Viewport.hpp>
#include <iterator>
#include <list>

namespace godot {

using Bloc = std::array<std::array<uint8_t, COLUMNS>, ROWS>;

class LevelController : public Node {
	GODOT_CLASS(LevelController, Node);

	Area2D *endBlock;
	Area2D *midBlock;
	Area2D *voidBloc;
	Player *player;
	PlayerController *playerController;
	Position2D *spawnPoint;

	PlayerActionGenerator playerActionGenerator;
	BlocGenerator blocGenerator;
	ActionTypeGenerator actionTypeGenerator;

	Level *map;
	BlocSelector *blocSelector;
	int8_t blocSelectedIndex;

	std::list<std::array<std::list<ActionType>, 3>> actions;

	void _addActions();
	void _clearActions();
	Bloc _get_selected_block_tile();

public:
	static void _register_methods();
	void _init();
	void _ready();

	void end_block();
	void mid_block();
	void load_next_block_elements();
	void load_next_block_tile();
	void load_next_block_action();
	void load_next_blocks_in_selector();
	void load_player();
	void load_next_block_player_action();
	void set_block_selected_index(int8_t m_block_selected_index);
	void end_level();
	void start();
};
} // namespace godot

#endif //GODOT_NATIVE_LEVELCONTROLLER_H
