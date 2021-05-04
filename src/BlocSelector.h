//
// Created by bogdan on 03/05/2021.
//

#ifndef GODOT_NATIVE_BLOCSELECTOR_H
#define GODOT_NATIVE_BLOCSELECTOR_H

#include <Control.hpp>
#include <Godot.hpp>
#include <VBoxContainer.hpp>
#include <array>

#include "BlocTextureGenerator.h"
#include "BlocThumb.h"
#include "LevelConstants.h"
#include "Signals.h"

namespace godot {

using Bloc = std::array<std::array<uint8_t, COLUMNS>, ROWS>;

class BlocSelector : public Control {
	GODOT_CLASS(BlocSelector, Control);

	VBoxContainer *choiceContainer;

public:
	static void _register_methods();
	void _init();
	void _ready();

	void _connect_selection(Node *node);
	void _set_blocs(std::array<Bloc, 3> blocs);
};
} // namespace godot

#endif //GODOT_NATIVE_BLOCSELECTOR_H
