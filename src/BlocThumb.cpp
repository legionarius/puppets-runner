//
// Created by bogdan on 04/05/2021.
//

#include "BlocThumb.h"

using namespace godot;

void BlocThumb::_init() {
}

void BlocThumb::_ready() {
	connect(PRESSED, this, "_on_selected");
}

void BlocThumb::_on_selected() {
	auto id = get_name().substr(3, 4).to_int();
	emit_signal(BLOC_SELECTED, id);
}

void BlocThumb::_register_methods() {
	register_method("_init", &BlocThumb::_init);
	register_method("_ready", &BlocThumb::_ready);
	register_method("_on_selected", &BlocThumb::_on_selected);
	register_signal<BlocThumb>(BLOC_SELECTED, "id", GODOT_VARIANT_TYPE_INT);
}
