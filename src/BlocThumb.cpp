//
// Created by bogdan on 04/05/2021.
//

#include "BlocThumb.h"

using namespace godot;

void BlocThumb::_init() {
}

void BlocThumb::_ready() {
	connect(PRESSED, this, "_on_selected");
	texture = cast_to<TextureRect>(get_node("TextureRect"));
}

void BlocThumb::_on_selected() {
	auto id = get_name().substr(3, 4).to_int();
	Ref<ShaderMaterial> material = get_material();
	material->set_shader_param("bright_amount", 0.1);
	emit_signal(BLOC_SELECTED, id);
}

void BlocThumb::_reset_selected() {
	Ref<ShaderMaterial> material = get_material();
	material->set_shader_param("bright_amount", 0);
	set_disabled(false);
	set_default_cursor_shape(2);
}

void BlocThumb::_register_methods() {
	register_method("_init", &BlocThumb::_init);
	register_method("_ready", &BlocThumb::_ready);
	register_method("_on_selected", &BlocThumb::_on_selected);
	register_signal<BlocThumb>(BLOC_SELECTED, "id", GODOT_VARIANT_TYPE_INT);
}
TextureRect *BlocThumb::get_texture() {
	return texture;
}

void BlocThumb::set_disabled(const bool disabled) {
	if (disabled) {
		texture->hide();
	} else {
		texture->show();
	}
	BaseButton::set_disabled(disabled);
}
