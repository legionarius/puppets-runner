//
// Created by bogdan on 29/04/2021.
//

#ifndef GODOT_NATIVE_LEVELCONTROLLER_H
#define GODOT_NATIVE_LEVELCONTROLLER_H

#include "Action.h"
#include "ActionType.h"
#include "BlocGenerator.h"
#include "Level.h"
#include "Player.h"
#include "PlayerActionGenerator.h"
#include "PlayerController.h"
#include "PlayerProgress.h"
#include "Signals.h"

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

#include "BlocSelector.h"

namespace godot {
class LevelController : public Node {
	GODOT_CLASS(LevelController, Node);

	Area2D *endBlock;
	Area2D *midBlock;
	Player *player;
	PlayerController *playerController;
	Position2D *spawnPoint;

	PlayerActionGenerator playerActionGenerator;
	BlocGenerator blocGenerator;

	Level *map;
	BlocSelector *blocSelector;

	std::list<std::list<ActionType>> actions;
	std::list<std::list<ActionType>> generateActions();

	std::list<std::list<Action>> playerActions;

	void _addActions();
	void _clearActions();

public:
	static void _register_methods();
	void _init();
	void _ready();

	void end_block();
	void mid_block();
	void load_next_block_elements();
	void load_next_block_tile();
	void load_player();
	void load_next_block_player_action();
	void start();
};
} // namespace godot

#endif //GODOT_NATIVE_LEVELCONTROLLER_H
