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
	playerAnimation = cast_to<AnimationPlayer>(get_parent()->get_node("Player")->get_node("AnimationPlayer"));
	playerAnimation->connect(ANIMATION_STARTED, this, "_attack_player");
}

void Wolf::_physics_process(const real_t delta) {
	if (!is_on_floor()) {
		_motion.y += _gravity;
	} else {
		_motion.y = 2;
		_motion.x = _speed;
	}

	_random_bark();
	move_and_slide(_motion, Vector2(0, -1));
}

void Wolf::_attack_player() {
	if (playerAnimation->get_current_animation() == "death") {
		wolfAnimation->play("attack");
	}
}

void Wolf::_random_bark() {
	if (rand() % 200 + 1 == 1) {
		wolfAudio->play();
	}
}

void Wolf::_register_methods() {
	register_method("_init", &Wolf::_init);
	register_method("_ready", &Wolf::_ready);
	register_method("_physics_process", &Wolf::_physics_process);
	register_method("_attack_player", &Wolf::_attack_player);
	register_method("_random_bark", &Wolf::_random_bark);
	register_property("gravity", &Wolf::_gravity, 20.f);
	register_property("speed", &Wolf::_speed, 200.f);
	register_property("jump_speed", &Wolf::_jump_speed, 600.f);
}