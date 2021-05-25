//
// Created by bogdan on 04/05/2021.
//

#ifndef GODOT_NATIVE_BLOCTHUMB_H
#define GODOT_NATIVE_BLOCTHUMB_H

#include <CanvasModulate.hpp>
#include <Godot.hpp>
#include <ShaderMaterial.hpp>
#include <TextureButton.hpp>
#include <TextureRect.hpp>

#include "Signals.h"

namespace godot {

class BlocThumb : public TextureButton {
	GODOT_CLASS(BlocThumb, TextureButton);

	CanvasModulate *selectedTexture;
	TextureRect *texture;

public:
	static void _register_methods();
	void _init();
	void _ready();
	void _on_selected();
	void _reset_selected();
	void set_disabled(const bool disabled);
	TextureRect *get_texture();
};
} // namespace godot

#endif //GODOT_NATIVE_BLOCTHUMB_H
