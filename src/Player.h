//
// Created by acroquelois on 28/04/2021.
//

#ifndef GODOT_NATIVE_PLAYER_H
#define GODOT_NATIVE_PLAYER_H

#include "ActionType.h"
#include "Signals.h"

#include <AnimatedSprite.hpp>
#include <Godot.hpp>
#include <Input.hpp>
#include <InputEventKey.hpp>
#include <InputMap.hpp>
#include <Timer.hpp>
#include <KinematicBody2D.hpp>
#include <Vector2.hpp>
#include <sstream>
#include <vector>

#define PLAYER_VELOCITY 300

namespace godot {

class Player : public KinematicBody2D {
	GODOT_CLASS(Player, KinematicBody2D);
	real_t _gravity;
	real_t _speed;
	real_t _jump_speed;
	Vector2 _motion;

	ActionType _current_action;
	AnimatedSprite *animation;
	Timer *idleTimer;

public:
	static void _register_methods();
	void _init();
	void _ready();
	void _physics_process(const real_t delta);
	void _exit();

	void set_current_action_type(ActionType actionType);
	void _idle_time_exceed();
};

} // namespace godot
#endif //GODOT_NATIVE_PLAYER_H
