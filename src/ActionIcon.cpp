//
// Created by nahalu on 03/05/2021.
//

#include "ActionIcon.h"

#define RUN_TEXTURE "asset/sprite/player/adventurer_walk1.png"
#define JUMP_TEXTURE "asset/sprite/player/adventurer_jump.png"
#define JUMP_OVER_TEXTURE "asset/sprite/player/adventurer_slide.png"

using namespace godot;

void ActionIcon::_init() {
}

void ActionIcon::_ready() {
}

void ActionIcon::set_action_type(int64_t action) {
	auto actionType = static_cast<ActionType>(action);

	switch (actionType) {
		case ActionType::RUN:
			iconTexture = ResourceLoader::get_singleton()->load(RUN_TEXTURE);
			break;
		case ActionType::JUMP:
			iconTexture = ResourceLoader::get_singleton()->load(JUMP_TEXTURE);
			break;
		case ActionType::JUMP_OVER:
			iconTexture = ResourceLoader::get_singleton()->load(JUMP_OVER_TEXTURE);
			break;
	}

	set_texture(iconTexture);
}

void ActionIcon::_register_methods() {
	register_method("_init", &ActionIcon::_init);
	register_method("_ready", &ActionIcon::_ready);
	register_method("set_action_type", &ActionIcon::set_action_type);
}
