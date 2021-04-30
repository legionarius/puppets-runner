//
// Created by bogdan on 29/04/2021.
//

#ifndef GODOT_NATIVE_LEVELCONTROLLER_H
#define GODOT_NATIVE_LEVELCONTROLLER_H

#include "ActionType.h"
#include "Player.h"
#include "PlayerController.h"

#include <Area2D.hpp>
#include <Godot.hpp>
#include <Node.hpp>
#include <PackedScene.hpp>
#include <Position2D.hpp>
#include <Ref.hpp>
#include <ResourceLoader.hpp>
#include <Viewport.hpp>
#include <list>

namespace godot {
class LevelController : public Node {
	GODOT_CLASS(LevelController, Node);


	Area2D *endBlock;
	Player *player;
	PlayerController *playerController;
	Position2D *spawnPoint;

	std::list<std::list<ActionType>> actions;
	std::list<std::list<ActionType>> generateActions();

public:
	static void _register_methods();
	void _init();
	void _ready();

	void end_block();
};
} // namespace godot

#endif //GODOT_NATIVE_LEVELCONTROLLER_H
