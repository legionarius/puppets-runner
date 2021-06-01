//
// Created by nahalu on 25/05/2021.
//

#include "Wolf.h"

using namespace godot;

void Wolf::_init() {
	_gravity = 20;
	_speed = WOLF_VELOCITY;
	_jump_speed = 600;
}

void Wolf::_ready() {
	wolfAnimation = cast_to<AnimationPlayer>(get_node("AnimationPlayer"));
	wolfAudio = cast_to<AudioStreamPlayer>(get_node("BarkSnd"));
	player = cast_to<Player>(get_parent()->get_node("Player"));
	wolfAnimation->connect(ANIMATION_FINISHED, this, "_end_of_murder");
}

void Wolf::_physics_process(const real_t delta) {
	_detect_walk_walk_on_spike();
	_random_bark();

	if (!is_on_floor()) {
		_motion.y += _gravity;
	} else {
		_motion.y = 2;
		_motion.x = _speed;
	}

	if (get_position().x > player->get_position().x) {
		wolfAnimation->set_current_animation("attack");
		wolfAnimation->play();
		_motion.x = 0;
		move_and_slide(_motion, Vector2(0, -1));
	} else {
		if (is_on_wall()) {
			_motion.y = -_jump_speed;
			_motion.x = _speed;
		}
		move_and_slide(_motion, Vector2(0, -1));
	}
}

void Wolf::_detect_walk_walk_on_spike() {
	int64_t nbCollision = get_slide_count();
	for (size_t i = 0; i < nbCollision; i++) {
		Ref<KinematicCollision2D> collisions = get_slide_collision(i);
		TileMap *tileMap = cast_to<TileMap>(collisions->get_collider());
		if (tileMap != nullptr) {
			auto cell = tileMap->world_to_map(collisions->get_position() - collisions->get_normal());
			if (tileMap->get_cellv(cell) == PIKE) {
				_motion.y = -_jump_speed;
				_motion.x = _speed;
			};
		}
	}
}

void Wolf::_random_bark() {
	if (rand() % 200 + 1 == 1) {
		wolfAudio->play();
	}
}

void Wolf::_end_of_murder() {
	wolfAnimation->set_current_animation("attack");
	if (wolfAnimation->get_current_animation() == "attack") {
		emit_signal(PLAYER_IS_BLOCKED);
	}
}

void Wolf::_register_methods() {
	register_method("_init", &Wolf::_init);
	register_method("_ready", &Wolf::_ready);
	register_method("_physics_process", &Wolf::_physics_process);
	register_method("_end_of_murder", &Wolf::_end_of_murder);
	register_method("_random_bark", &Wolf::_random_bark);
	register_property("gravity", &Wolf::_gravity, 20.f);
	register_property("speed", &Wolf::_speed, 200.f);
	register_property("jump_speed", &Wolf::_jump_speed, 600.f);
	register_signal<Wolf>(PLAYER_IS_BLOCKED);
}