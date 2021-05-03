//
// Created by bogdan on 03/05/2021.
//

#ifndef GODOT_NATIVE_BLOCSELECTOR_H
#define GODOT_NATIVE_BLOCSELECTOR_H

#include <Control.hpp>
#include <Godot.hpp>
#include <VBoxContainer.hpp>

#include "BlocThumb.h"
#include "Signals.h"
namespace godot {
class BlocSelector : public Control {
	GODOT_CLASS(BlocSelector, Control);

	VBoxContainer *choiceContainer;

public:
	static void _register_methods();
	void _init();
	void _ready();

	void _connect_selection(Node *node);
};
} // namespace godot

#endif //GODOT_NATIVE_BLOCSELECTOR_H
