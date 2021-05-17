//
// Created by bogdan on 29/04/2021.
//

#include "LevelController.h"

using namespace godot;

void LevelController::_init() {
	playerActionGenerator = PlayerActionGenerator();
	blocGenerator = BlocGenerator();
	actionTypeGenerator = ActionTypeGenerator();
	actions = actionTypeGenerator.generate_actions(10, 3);
	blocSelectedIndex = -1;
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
	player->connect(PLAYER_IS_ON_SPIKE, this, "end_level");
	add_child(player);

	playerController = cast_to<PlayerController>(get_node("PlayerController"));
	playerController->connect_player();
}

void LevelController::end_block() {
	emit_signal(PLAYER_PROGRESS, static_cast<int>(PlayerProgress::END));
	load_next_block_elements();
	player->set_position(Vector2(spawnPoint->get_position().x, player->get_position().y - SPAWN_PLAYER_ELEVATION));
}

void LevelController::load_next_block_tile() {
	Bloc bloc;
	map->clear();
	if(nextActionsArray.front().empty()){
		bloc = _generate_first_bloc();
	} else {
		bloc = _get_selected_block_tile();
	}
	emit_signal(NEXT_BLOC);
	map->_load_bloc(bloc);
}

void LevelController::load_next_block_action() {
	_clearActions();
	_addActions();
}

void LevelController::load_next_blocks_in_selector() {

	std::array<Bloc, 3> blocs;
	nextActionsArray = *std::next(actions.begin(), 1);
	std::shuffle(nextActionsArray.begin(), nextActionsArray.end(), std::default_random_engine(rand()));

	for (int i = 0; i < nextActionsArray.size(); i++) {
		blocs[i] = blocGenerator.generate_compat_bloc(ActionType::RUN, nextActionsArray[i]);
	}
	if (blocSelector != nullptr) {
		blocSelector->_set_blocs(blocs);
	}
}

Bloc LevelController::_get_selected_block_tile() {
	Bloc nextBloc = { { 0 } };
	if (blocSelectedIndex != -1) {
		nextBloc = blocGenerator.generate_compat_bloc(ActionType::RUN, nextActionsArray[blocSelectedIndex-1]);
	}
	blocSelectedIndex = -1;
	return nextBloc;
}

void LevelController::set_block_selected_index(int8_t m_block_selected_index) {
	blocSelectedIndex = m_block_selected_index;
	blocSelector->_hide_not_selected(m_block_selected_index);
}

void LevelController::load_next_block_player_action() {
	std::list<ActionsArray>::iterator actionsIterator = actions.begin();

	std::list<Action> nextActions = playerActionGenerator.generate_player_action(actions.begin()->front(), std::next(actionsIterator, 1)->front());
	playerController->fill_action_list(nextActions);
}

void LevelController::_exit_tree() {
	blocSelector->queue_free();
}

void LevelController::_addActions() {
	if (!actions.empty()) {
		auto nextBlock = std::next(actions.begin(), 1)->front();
		for (auto const &action : nextBlock) {
			auto actionInt = static_cast<int64_t>(action);
			emit_signal(ADD_ACTION, actionInt);
		}
	}
}

void LevelController::mid_block() {
	emit_signal(PLAYER_PROGRESS, static_cast<int>(PlayerProgress::MIDDLE));
}

void LevelController::_clearActions() {
	emit_signal(CLEAR_ACTION);
}

void LevelController::end_level() {
	emit_signal(END_LEVEL);
}

Bloc LevelController::_generate_first_bloc() {
	return blocGenerator.generate_compat_bloc(ActionType::RUN, actions.begin()->front());
}

void LevelController::_register_methods() {
	register_method("_init", &LevelController::_init);
	register_method("_ready", &LevelController::_ready);
	register_method("_exit_tree", &LevelController::_exit_tree);
	register_method("end_block", &LevelController::end_block);
	register_method("mid_block", &LevelController::mid_block);
	register_method("end_level", &LevelController::end_level);
	register_signal<LevelController>(ADD_ACTION, "action", GODOT_VARIANT_TYPE_INT);
	register_signal<LevelController>(CLEAR_ACTION);
	register_signal<LevelController>(NO_BLOC);
	register_signal<LevelController>(NEXT_BLOC);
	register_signal<LevelController>(END_LEVEL);
	register_signal<LevelController>(PLAYER_PROGRESS, "pos", GODOT_VARIANT_TYPE_INT);
}
