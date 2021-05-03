//
// Created by bogdan on 03/05/2021.
//

#include "BlocSelector.h"

using namespace godot;

void BlocSelector::_init() {
}

void BlocSelector::_ready() {
	choiceContainer = cast_to<VBoxContainer>(get_node("ItemList"));
}

void BlocSelector::_register_methods() {
	register_method("_init", &BlocSelector::_init);
	register_method("_ready", &BlocSelector::_ready);
}

void BlocSelector::_connect_selection(Node *node) {
	auto size = choiceContainer->get_child_count();
	for (int i = 0; i < size; i++) {
		auto button = cast_to<BlocThumb>(choiceContainer->get_child(i));
		button->connect(BLOC_SELECTED, node, "_on_bloc_selected");
	}
}
