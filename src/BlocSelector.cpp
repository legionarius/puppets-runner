//
// Created by bogdan on 03/05/2021.
//

#include "BlocSelector.h"

using namespace godot;

void BlocSelector::_init() {
}

void BlocSelector::_ready() {
	choiceContainer = cast_to<VBoxContainer>(get_node("ItemList"));
	connect(VISIBILITY_CHANGED, this, "_reset_selection");
}

void BlocSelector::_register_methods() {
	register_method("_init", &BlocSelector::_init);
	register_method("_ready", &BlocSelector::_ready);
	register_method("_reset_selection", &BlocSelector::_reset_selection);
}

void BlocSelector::_connect_selection(Node *node) {
	auto size = choiceContainer->get_child_count();
	for (int i = 0; i < size; i++) {
		auto button = cast_to<BlocThumb>(choiceContainer->get_child(i));
		button->connect(BLOC_SELECTED, node, "_on_bloc_selected");
	}
}

void BlocSelector::_hide_not_selected(int8_t block_selected_index) {
	auto size = choiceContainer->get_child_count();
	for (int8_t i = 1; i < size + 1; i++) {
		if (i != block_selected_index) {
			BlocThumb *button = cast_to<BlocThumb>(choiceContainer->get_child(i - 1));
			button->set_disabled(true);
			button->set_default_cursor_shape(0);
		}
	}
}

void BlocSelector::_reset_selection() {
	auto size = choiceContainer->get_child_count();
	for (int i = 0; i < size; i++) {
		BlocThumb *button = cast_to<BlocThumb>(choiceContainer->get_child(i));
		button->_reset_selected();
	}
}

void BlocSelector::_set_blocs(std::array<Bloc, 3> blocs) {
	auto size = choiceContainer->get_child_count();
	auto textureGenerator = BlocTextureGenerator();
	for (int i = 0; i < size; i++) {
		auto button = cast_to<BlocThumb>(choiceContainer->get_child(i));
		auto texture = textureGenerator._generate(blocs[i]);
		button->set_normal_texture(texture);
	}
}
