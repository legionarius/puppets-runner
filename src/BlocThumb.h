//
// Created by bogdan on 04/05/2021.
//

#ifndef GODOT_NATIVE_BLOCTHUMB_H
#define GODOT_NATIVE_BLOCTHUMB_H

#include <ColorRect.hpp>
#include <Godot.hpp>
#include <TextureButton.hpp>

#include "Signals.h"

namespace godot {

class BlocThumb : public TextureButton {
	GODOT_CLASS(BlocThumb, TextureButton);

	ColorRect *selectedTexture;

public:
	static void _register_methods();
	void _init();
	void _ready();
	void _on_selected();
	void _reset_selected();
};
} // namespace godot

#endif //GODOT_NATIVE_BLOCTHUMB_H
