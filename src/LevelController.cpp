//
// Created by bogdan on 29/04/2021.
//

#include "LevelController.h"

using namespace godot;

void LevelController::_init() {
	actions = generateActions();
	playerActionGenerator = PlayerActionGenerator();
	blocGenerator = BlocGenerator();
}

void LevelController::_ready() {
	map = cast_to<Level>(get_node("TileMap"));
	spawnPoint = cast_to<Position2D>(get_node("SpawnPoint"));
	endBlock = cast_to<Area2D>(get_node("EndBlock"));
	endBlock->connect(BODY_ENTERED, this, "end_block");
	midBlock = Object::cast_to<Area2D>(get_node("MidBlock"));
	midBlock->connect(BODY_ENTERED, this, "mid_block");
	_addActions();

	load_player();
	load_next_block_elements();
}

void LevelController::load_next_block_elements() {
	if (actions.size() > 1) {
		load_next_block_player_action();
		load_next_block_tile();
		_clearActions();
		_addActions();
		actions.pop_front();
	} else {
		Godot::print("No more bloc to load");
		emit_signal(NO_BLOC);
	}
}

void LevelController::load_player() {
	Ref<PackedScene> playerScene = ResourceLoader::get_singleton()->load("entity/Player/Player.tscn");
	player = cast_to<Player>(playerScene->instance());
	player->set_position(spawnPoint->get_position());
	player->set_name("Player");
	add_child(player);

	playerController = cast_to<PlayerController>(get_node("PlayerController"));
	playerController->connect_player();
}

std::list<std::list<ActionType>> LevelController::generateActions() {
	return std::list{
		std::list<ActionType>{ ActionType::RUN, ActionType::JUMP, ActionType::JUMP },
		std::list<ActionType>{ ActionType::RUN, ActionType::JUMP_OVER, ActionType::RUN },
		std::list<ActionType>{ ActionType::RUN, ActionType::JUMP, ActionType::RUN },
		std::list<ActionType>{ ActionType::RUN, ActionType::JUMP, ActionType::RUN, ActionType::JUMP },
		std::list<ActionType>{ ActionType::RUN, ActionType::JUMP, ActionType::RUN, ActionType::JUMP },
	};
}

void LevelController::end_block() {
	emit_signal(PLAYER_PROGRESS, static_cast<int>(PlayerProgress::END));
	load_next_block_elements();
	player->set_position(Vector2(spawnPoint->get_position().x, player->get_position().y));
}

void LevelController::load_next_block_tile() {
	auto nextActions = actions.front();
	map->clear();
	auto bloc = blocGenerator.generate_compat_bloc(ActionType::RUN, nextActions);
	emit_signal(NEXT_BLOC);
	map->_load_bloc(bloc);
}

void LevelController::load_next_block_player_action() {
	std::list<std::list<ActionType>>::iterator actionsIterator = actions.begin();
	std::list<Action> nextActions = playerActionGenerator.generate_player_action(actions.front(), *std::next(actionsIterator, 1));
	playerController->fill_action_list(nextActions);
}

void LevelController::_addActions() {
	if (!actions.empty()) {
		auto nextBlock = std::next(actions.begin(), 1);

		for (auto const &action : *nextBlock) {
			auto actionInt = static_cast<int64_t>(action);
			emit_signal("add_action", actionInt);
		}
	}
}

void LevelController::mid_block() {
	emit_signal(PLAYER_PROGRESS, static_cast<int>(PlayerProgress::MIDDLE));
}

void LevelController::_clearActions() {
	emit_signal("clear_actions");
}

void LevelController::_register_methods() {
	register_method("_init", &LevelController::_init);
	register_method("_ready", &LevelController::_ready);
	register_method("end_block", &LevelController::end_block);
	register_signal<LevelController>("add_action", "action", GODOT_VARIANT_TYPE_INT);
	register_signal<LevelController>("clear_actions");
	register_method("mid_block", &LevelController::mid_block);
	register_signal<LevelController>(NO_BLOC);
	register_signal<LevelController>(NEXT_BLOC);
	register_signal<LevelController>(PLAYER_PROGRESS, "pos", GODOT_VARIANT_TYPE_INT);
}
