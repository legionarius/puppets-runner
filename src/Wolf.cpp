//
// Created by nahalu on 25/05/2021.
//

#include "Wolf.h"

using namespace godot;

void Wolf::_init() {
	_gravity = 20;
	_speed = WOLF_VELOCITY;
	_jump_speed = 600;
	_current_action = ActionType::RUN;
}

void Wolf::_ready() {
	wolfAnimation = cast_to<AnimationPlayer>(get_node("AnimationPlayer"));
	wolfAudio = cast_to<AudioStreamPlayer>(get_node("BarkSnd"));
}

void Wolf::_physics_process(const real_t delta) {
	if (!is_on_floor()) {
		_motion.y += _gravity;
	} else {
		if (_current_action == ActionType::RUN) {
			_motion.y = 2;
			_motion.x = _speed;
		} else {
			wolfAnimation->play();
			_motion.y = -_jump_speed;
			_motion.x = _speed;
			_current_action = ActionType::RUN;
		}
	}

	move_and_slide(_motion, Vector2(0, -1));
}

void Wolf::_register_methods() {
	register_method("_init", &Wolf::_init);
	register_method("_ready", &Wolf::_ready);
	register_method("_physics_process", &Wolf::_physics_process);
	register_property("gravity", &Wolf::_gravity, 20.f);
	register_property("speed", &Wolf::_speed, 200.f);
	register_property("jump_speed", &Wolf::_jump_speed, 600.f);
}