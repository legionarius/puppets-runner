//
// Created by bogdan on 29/04/2021.
//

#include "LevelController.h"

using namespace godot;

void LevelController::_init() {
	actions = generateActions();
}

void LevelController::_ready() {
	spawnPoint = Object::cast_to<Position2D>(get_node("SpawnPoint"));
	endBlock = Object::cast_to<Area2D>(get_node("EndBlock"));
	endBlock->connect("body_entered", this, "end_block");

	Ref<PackedScene> playerScene = ResourceLoader::get_singleton()->load("entity/Player/Player.tscn");
	player = Object::cast_to<Player>(playerScene->instance());
	player->set_position(spawnPoint->get_position());
	player->set_name("Player");
	add_child(player);

	playerController = Object::cast_to<PlayerController>(get_node("PlayerController"));
	playerController->connect_player();
}

std::list<std::list<ActionType>> LevelController::generateActions() {
	return std::list {
				std::list<ActionType>{ ActionType::RUN },
				std::list<ActionType>{ ActionType::RUN, ActionType::RUN, ActionType::JUMP },
	};
}

void LevelController::end_block() {
	std::vector<Action> mock_action_list;
	playerController->fill_action_list(mock_action_list);
	playerController->reset_delta_aggregator();
	player->set_position(spawnPoint->get_position());
}

void LevelController::_register_methods() {
	register_method("_init", &LevelController::_init);
	register_method("_ready", &LevelController::_ready);
	register_method("end_block", &LevelController::end_block);
}
