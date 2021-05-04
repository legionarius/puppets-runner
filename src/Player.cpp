//
// Created by acroquelois on 28/04/2021.
//

#include "Player.h"

using namespace godot;

void Player::_init() {
	_gravity = 20;
	_speed = PLAYER_VELOCITY;
	_jump_speed = 600;
	_current_action = ActionType::RUN;
}

void Player::_ready() {
	animation = Object::cast_to<AnimatedSprite>(get_node("Animation"));
}

void Player::_physics_process(const real_t delta) {
	;

	if (!is_on_floor()) {
		_motion.y += _gravity;
	} else {
		if(_current_action == ActionType::RUN) {
			animation->play("run");
			_motion.y = 2;
			_motion.x = _speed;
		} else {
			animation->play("jump");
			_motion.y = -_jump_speed;
			_motion.x = _speed;
			_current_action = ActionType::RUN;
		}
	}

	move_and_slide(_motion, Vector2(0, -1));
}

void Player::set_current_action_type(ActionType actionType) {
	_current_action = actionType;
}

void Player::_register_methods() {
	register_method("_init", &Player::_init);
	register_method("_ready", &Player::_ready);
	register_method("_physics_process", &Player::_physics_process);
	register_property("gravity", &Player::_gravity, 20.f);
	register_property("speed", &Player::_speed, 200.f);
	register_property("jump_speed", &Player::_jump_speed, 600.f);
}
