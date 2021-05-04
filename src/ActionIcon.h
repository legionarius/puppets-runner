//
// Created by nahalu on 03/05/2021.
//

#ifndef GODOT_NATIVE_ACTIONICON_H
#define GODOT_NATIVE_ACTIONICON_H

#include "ActionType.h"

#include <Godot.hpp>
#include <ResourceLoader.hpp>
#include <Texture.hpp>
#include <TextureRect.hpp>

namespace godot {
class ActionIcon : public TextureRect {
	GODOT_CLASS(ActionIcon, TextureRect);

	Ref<Texture> iconTexture;

public:
	static void _register_methods();

	void _init();

	void _ready();

	void set_action_type(int64_t action);
};
}; // namespace godot
#endif //GODOT_NATIVE_ACTIONICON_H
