//
// Created by bogdan on 29/04/2021.
//

#include "LevelController.h"

using namespace godot;

void LevelController::_init() {
	actions = generateActions();
	blocGenerator = BlocGenerator();
}

void LevelController::_ready() {
	map = cast_to<Level>(get_node("TileMap"));
	spawnPoint = Object::cast_to<Position2D>(get_node("SpawnPoint"));
	endBlock = Object::cast_to<Area2D>(get_node("EndBlock"));
	endBlock->connect(BODY_ENTERED, this, "end_block");

	load_next_block();
	load_player();

	playerController = Object::cast_to<PlayerController>(get_node("PlayerController"));
	playerController->connect_player();
}

void LevelController::load_player() {
	Ref<PackedScene> playerScene = ResourceLoader::get_singleton()->load("entity/Player/Player.tscn");
	player = cast_to<Player>(playerScene->instance());
	player->set_position(spawnPoint->get_position());
	player->set_name("Player");
	add_child(player);
}

std::list<std::list<ActionType>> LevelController::generateActions() {
	return std::list{
		std::list<ActionType>{ ActionType::RUN, ActionType::RUN, ActionType::RUN },
		std::list<ActionType>{ ActionType::RUN, ActionType::RUN, ActionType::RUN },
		std::list<ActionType>{ ActionType::RUN, ActionType::RUN, ActionType::RUN },
		std::list<ActionType>{ ActionType::RUN, ActionType::JUMP, ActionType::JUMP_OVER, ActionType::JUMP },
	};
}

void LevelController::end_block() {
	load_next_block();
	std::vector<Action> mock_action_list;
	playerController->fill_action_list(mock_action_list);
	playerController->reset_delta_aggregator();
	auto position = player->get_position();
	player->set_position(Vector2(20.f, position.y));
}

void LevelController::load_next_block() {
	if (actions.size() > 0) {
		auto nextActions = actions.front();
		map->clear();
		auto bloc = blocGenerator.generate_compat_bloc(ActionType::RUN, nextActions);
		emit_signal(NEXT_BLOC);
		map->_load_bloc(bloc);
		actions.pop_front();
	} else {
		Godot::print("No more bloc to load");
		emit_signal(NO_BLOC);
	}
}

void LevelController::_register_methods() {
	register_method("_init", &LevelController::_init);
	register_method("_ready", &LevelController::_ready);
	register_method("end_block", &LevelController::end_block);
	register_signal<LevelController>(NO_BLOC);
	register_signal<LevelController>(NEXT_BLOC);
}
