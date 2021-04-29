//
// Created by acroquelois on 28/04/2021.
//

#include "MainScene.h"

using namespace godot;

void MainScene::_init() {
}

void MainScene::_ready() {
	Position2D *spawnPoint = Object::cast_to<Position2D>(get_node("Level/SpawnPoint"));
	Ref<PackedScene> playerScene = ResourceLoader::get_singleton()->load("entity/Player/Player.tscn");
	player = Object::cast_to<Player>(playerScene->instance());
	player->set_position(spawnPoint->get_position());
	add_child(player);
}

void MainScene::_exit() {
	get_tree()->quit();
}

void MainScene::_start() {
}

void MainScene::_register_methods() {
	register_method("_init", &MainScene::_init);
	register_method("_ready", &MainScene::_ready);
	register_method("_exit", &MainScene::_exit);
	register_method("_start", &MainScene::_start);
}
