//
// Created by acroquelois on 28/04/2021.
//

#include "MainScene.h"

using namespace godot;

void MainScene::_init() {
}

void MainScene::_ready() {
	blocSelector = cast_to<BlocSelector>(get_node("BlocSelector"));
	levelController = cast_to<LevelController>(get_node("Level"));
	blocSelector->_connect_selection(this);
	levelController->connect(PLAYER_PROGRESS, this, "_on_progress");
	levelController->connect(END_LEVEL, this, "_end_level");
	_start();
}

void MainScene::_exit() {
	get_tree()->quit();
}

void MainScene::_start() {
	levelController->start();
}

void MainScene::_on_bloc_selected(int blocId) {
	auto args = Array::make(blocId);
	levelController->set_block_selected_index(blocId);
}

void MainScene::_on_progress(int progressId) {
	auto progress = static_cast<PlayerProgress>(progressId);
	auto args = Array::make(progress);
	if (progress == PlayerProgress::MIDDLE) {
		blocSelector->show();
	} else {
		blocSelector->hide();
	}
}

void MainScene::_end_level() {
	Score *score = cast_to<Score>(levelController->get_node("Score"));
	String scoreText = score->get_text();
	levelController->queue_free();
	Ref<PackedScene> restartScene = ResourceLoader::get_singleton()->load("entity/EndScreen/EndScreen.tscn");
	Control *restartNode = cast_to<Control>(restartScene->instance());
	add_child(restartNode);
	TextureButton *button = cast_to<TextureButton>(restartNode->get_node("RestartButton"));
	Label *scoreLabel = cast_to<Label>(restartNode->get_node("Score"));
	scoreLabel->set_text(scoreText);
	button->connect(PRESSED, this, "_restart");
}

void MainScene::_restart() {
	get_tree()->change_scene("entity/MainScene/MainScene.tscn");
}

void MainScene::_register_methods() {
	register_method("_init", &MainScene::_init);
	register_method("_ready", &MainScene::_ready);
	register_method("_exit", &MainScene::_exit);
	register_method("_start", &MainScene::_start);
	register_method("_restart", &MainScene::_restart);
	register_method("_on_bloc_selected", &MainScene::_on_bloc_selected);
	register_method("_on_progress", &MainScene::_on_progress);
	register_method("_end_level", &MainScene::_end_level);
}
