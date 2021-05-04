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
	Godot::print(String("Bloc {0} selected").format(args));
}

void MainScene::_on_progress(int progressId) {
	auto progress = static_cast<PlayerProgress>(progressId);
	auto args = Array::make(progress);
	Godot::print(String("Player progress is {0}").format(args));
	if (progress == PlayerProgress::MIDDLE) {
		blocSelector->show();
	} else {
		blocSelector->hide();
	}
}

void MainScene::_register_methods() {
	register_method("_init", &MainScene::_init);
	register_method("_ready", &MainScene::_ready);
	register_method("_exit", &MainScene::_exit);
	register_method("_start", &MainScene::_start);
	register_method("_on_bloc_selected", &MainScene::_on_bloc_selected);
	register_method("_on_progress", &MainScene::_on_progress);
}
