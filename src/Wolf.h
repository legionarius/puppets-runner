//
// Created by nahalu on 25/05/2021.
//

#ifndef GODOT_NATIVE_WOLF_H
#define GODOT_NATIVE_WOLF_H

#include "ActionType.h"
#include "LevelConstants.h"
#include "Player.h"
#include "Signals.h"

#include <AnimationPlayer.hpp>
#include <AudioStreamPlayer.hpp>
#include <Godot.hpp>
#include <KinematicBody2D.hpp>
#include <Vector2.hpp>

#define WOLF_VELOCITY 500

namespace godot {

class Wolf : public KinematicBody2D {
	GODOT_CLASS(Wolf, KinematicBody2D);
	real_t _gravity;
	real_t _speed;
	real_t _jump_speed;
	Vector2 _motion;

	AnimationPlayer *wolfAnimation;
	AudioStreamPlayer *wolfAudio;
	Player *player;

	void _random_bark();

public:
	static void _register_methods();
	void _init();
	void _ready();
	void _physics_process(const real_t delta);
	void _detect_walk_walk_on_spike();
	void _end_of_murder();
};

} // namespace godot

#endif //GODOT_NATIVE_WOLF_H
