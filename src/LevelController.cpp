//
// Created by bogdan on 29/04/2021.
//

#include "LevelController.h"

using namespace godot;

void LevelController::_init() {
	actions = generateActions();
	playerActionGenerator = PlayerActionGenerator();
	blocGenerator = BlocGenerator();
	blocSelectedIndex = 1;
}

void LevelController::_ready() {
	map = cast_to<Level>(get_node("TileMap"));
	spawnPoint = cast_to<Position2D>(get_node("SpawnPoint"));
	endBlock = cast_to<Area2D>(get_node("EndBlock"));
	endBlock->connect(BODY_ENTERED, this, "end_block");
	midBlock = Object::cast_to<Area2D>(get_node("MidBlock"));
	midBlock->connect(BODY_ENTERED, this, "mid_block");
	blocSelector = cast_to<BlocSelector>(get_parent()->get_node("BlocSelector"));
	voidBloc = Object::cast_to<Area2D>(get_node("VoidBlock"));
	voidBloc->connect(BODY_ENTERED, this, "end_level");
}

void LevelController::start() {
	load_player();
	load_next_block_elements();
	load_next_block_action();
}

void LevelController::load_next_block_elements() {
	if (actions.size() > 1) {
		load_next_block_player_action();
		load_next_block_tile();
		load_next_block_action();
		load_next_blocks_in_selector();
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
	player->connect(PLAYER_IS_BLOCKED, this, "end_level");
	add_child(player);

	playerController = cast_to<PlayerController>(get_node("PlayerController"));
	playerController->connect_player();
}

std::list<std::list<ActionType>> LevelController::generateActions() {
	return std::list{
		std::list<ActionType>{ ActionType::RUN, ActionType::JUMP, ActionType::JUMP },
		std::list<ActionType>{ ActionType::JUMP_OVER, ActionType::JUMP_OVER, ActionType::RUN },
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
	map->clear();
	auto bloc = _get_selected_block_tile();
	emit_signal(NEXT_BLOC);
	map->_load_bloc(bloc);
}

void LevelController::load_next_block_action() {
	_clearActions();
	_addActions();
}

void LevelController::load_next_blocks_in_selector() {
	// TODO : Create function to generate a shuffled array
	//  containing the good bloc & 2 bad blocs.
	auto nextActions = std::next(actions.begin(), 1);
	Bloc nextBloc = blocGenerator.generate_compat_bloc(ActionType::RUN, *nextActions);
	if (blocSelector != nullptr) {
		std::array<Bloc, 3> blocs = { nextBloc };
		blocSelector->_set_blocs(blocs);
	}
}

Bloc LevelController::_get_selected_block_tile() {
	Bloc nextBloc = {{0}};
	if (blocSelectedIndex != -1){
		// Force correct selection to index 2
		if(blocSelectedIndex == 1) {
			auto nextActions = actions.front();
			nextBloc = blocGenerator.generate_compat_bloc(ActionType::RUN, nextActions);
		}
	}
	blocSelectedIndex = -1;
	return nextBloc;
}

void LevelController::set_block_selected_index(int8_t m_block_selected_index) {
	blocSelectedIndex = m_block_selected_index;
	blocSelector->_hide_not_selected(m_block_selected_index);
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

void LevelController::end_level() {
	emit_signal(END_LEVEL);
}

void LevelController::_register_methods() {
	register_method("_init", &LevelController::_init);
	register_method("_ready", &LevelController::_ready);
	register_method("end_block", &LevelController::end_block);
	register_method("mid_block", &LevelController::mid_block);
	register_method("end_level", &LevelController::end_level);
	register_signal<LevelController>("add_action", "action", GODOT_VARIANT_TYPE_INT);
	register_signal<LevelController>("clear_actions");
	register_signal<LevelController>(NO_BLOC);
	register_signal<LevelController>(NEXT_BLOC);
	register_signal<LevelController>(END_LEVEL);
	register_signal<LevelController>(PLAYER_PROGRESS, "pos", GODOT_VARIANT_TYPE_INT);
}
