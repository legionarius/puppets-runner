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
	_is_blocked = false;
	_is_on_spike = false;
}

void Player::_ready() {
	jumpPlayer = cast_to<AudioStreamPlayer>(get_node("JumpSnd"));
	playerAnimation = cast_to<AnimationPlayer>(get_node("AnimationPlayer"));
	deathPlayerSound = cast_to<AudioStreamPlayer>(get_node("DeathSnd"));
	animationPlayer = cast_to<AnimationPlayer>(get_node("AnimationPlayer"));
	idleTimer = cast_to<Timer>(get_node("IdleTimer"));
	idleTimer->connect(TIMEOUT, this, "_idle_time_exceed");
	animationPlayer->connect(ANIMATION_FINISHED, this, "_set_animation_death");
}

void Player::_physics_process(const real_t delta) {
	_detect_player_walk_on_spike();

	if (!is_on_floor()) {
		_motion.y += _gravity;
	} else {
		if (_current_action == ActionType::RUN) {
			if (!_is_on_spike) {
				_motion.y = 2;
			}
			_motion.x = _speed;
		} else {
			jumpPlayer->play();
			_motion.y = -_jump_speed;
			_motion.x = _speed;
			_current_action = ActionType::RUN;
		}
	}

	if (!_is_blocked) {
		if (is_on_wall()) {
			if (idleTimer->is_stopped()) {
				idleTimer->start();
			}
		} else {
			idleTimer->stop();
		}
	}

	move_and_slide(_motion, Vector2(0, -1));
}

void Player::_idle_time_exceed() {
	_is_blocked = true;
	playerAnimation->play("death");
	emit_signal(PLAYER_DEATH_WALL_START);
}

void Player::_detect_player_walk_on_spike() {
	int64_t nbCollision = get_slide_count();
	for (size_t i = 0; i < nbCollision; i++) {
		Ref<KinematicCollision2D> collisions = get_slide_collision(i);
		TileMap *tileMap = cast_to<TileMap>(collisions->get_collider());
		if (tileMap != nullptr) {
			auto cell = tileMap->world_to_map(collisions->get_position() - collisions->get_normal());
			if (tileMap->get_cellv(cell) == PIKE) {
				_is_on_spike = true;
				_speed = 10;
				_motion.y = -_jump_speed;
				deathPlayerSound->play();
				animationPlayer->play("death_on_spike");
			};
		}
	}
}

void Player::_set_animation_death() {
	emit_signal(PLAYER_IS_ON_SPIKE);
}

void Player::set_current_action_type(ActionType actionType) {
	_current_action = actionType;
}

void Player::_register_methods() {
	register_method("_init", &Player::_init);
	register_method("_ready", &Player::_ready);
	register_method("_physics_process", &Player::_physics_process);
	register_method("_idle_time_exceed", &Player::_idle_time_exceed);
	register_method("_set_animation_death", &Player::_set_animation_death);
	register_property("gravity", &Player::_gravity, 20.f);
	register_property("speed", &Player::_speed, 200.f);
	register_property("jump_speed", &Player::_jump_speed, 600.f);
	register_signal<Player>(PLAYER_DEATH_WALL_START);
	register_signal<Player>(PLAYER_IS_ON_SPIKE);
}
