//
// Created by acroquelois on 28/04/2021.
//

#ifndef GODOT_NATIVE_PLAYER_H
#define GODOT_NATIVE_PLAYER_H

#include <AnimatedSprite.hpp>
#include <Godot.hpp>
#include <KinematicBody2D.hpp>
#include <InputEventKey.hpp>
#include <InputMap.hpp>
#include <Input.hpp>
#include <Vector2.hpp>
#include <sstream>

namespace godot {

class Player : public KinematicBody2D {
	GODOT_CLASS(Player, KinematicBody2D);
	real_t _gravity;
	real_t _speed;
	real_t _jump_speed;
	Vector2 motion;

	bool _move_left = false;
	bool _move_right = false;
	bool _apply_impulse = false;

	AnimatedSprite *animation;

public:
	static void _register_methods();
	void _init();
	void _ready();
	void _physics_process(const real_t delta);
	void _exit();
};

} // namespace godot
#endif //GODOT_NATIVE_PLAYER_H
