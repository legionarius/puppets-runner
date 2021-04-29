//
// Created by acroquelois on 28/04/2021.
//

#include "Player.h"

using namespace godot;

void Player::_init() {
	_gravity = 20;
	_speed = 200;
	_jump_speed = 600;
}

void Player::_ready() {
	animation = Object::cast_to<AnimatedSprite>(get_node("Animation"));
}

void Player::_physics_process(const real_t delta) {
	_apply_impulse = Input::get_singleton()->is_action_pressed("jump");
	_move_left = Input::get_singleton()->is_action_pressed("move_left");
	_move_right = Input::get_singleton()->is_action_pressed("move_right");
	if (_move_left || _move_right) {
		animation->play("run");
		motion.x = _move_left ? -_speed : _speed;
	} else {
		motion.x = 0;
		animation->play("idle");
	}

	if (!is_on_floor()){
		motion.y += _gravity;
	} else {
		if(_apply_impulse){
			motion.y = -_jump_speed;
		} else {
			motion.y = 2;
		}
	}

	move_and_slide(motion, Vector2(0, -1));
	
}


void Player::_register_methods() {
	register_method("_init", &Player::_init);
	register_method("_ready", &Player::_ready);
	register_method("_physics_process", &Player::_physics_process);
	register_property("gravity", &Player::_gravity, 20.f);
	register_property("speed", &Player::_speed, 200.f);
	register_property("jump_speed", &Player::_jump_speed, 600.f);


}
