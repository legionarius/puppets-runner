//
// Created by bogdan on 11/02/2021.
//

#include "ActionIcon.h"
#include "Level.h"
#include "LevelController.h"
#include "MainScene.h"
#include "Partition.h"
#include "Player.h"
#include "PlayerController.h"
#include "TitleScreen.h"

extern "C" void GDN_EXPORT godot_gdnative_init(godot_gdnative_init_options *o) {
	godot::Godot::gdnative_init(o);
}

extern "C" void GDN_EXPORT
godot_gdnative_terminate(godot_gdnative_terminate_options *o) {
	godot::Godot::gdnative_terminate(o);
}

extern "C" void GDN_EXPORT godot_nativescript_init(void *handle) {
	godot::Godot::nativescript_init(handle);

	godot::register_class<godot::LevelController>();
	godot::register_class<godot::Level>();
	godot::register_class<godot::MainScene>();
	godot::register_class<godot::LevelController>();
	godot::register_class<godot::TitleScreen>();
	godot::register_class<godot::Player>();
	godot::register_class<godot::PlayerController>();
	godot::register_class<godot::Partition>();
	godot::register_class<godot::ActionIcon>();
}