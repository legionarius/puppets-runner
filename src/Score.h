//
// Created by nahalu on 14/05/2021.
//

#ifndef GODOT_NATIVE_SCORE_H
#define GODOT_NATIVE_SCORE_H

#include "LevelController.h"
#include "Signals.h"

#include <Godot.hpp>
#include <Label.hpp>
#include <TextureRect.hpp>

namespace godot {
class Score : public TextureRect {
	GODOT_CLASS(Score, TextureRect);

private:
	LevelController *levelController;
	Label *labelScore;

public:
	static void _register_methods();
	void _init();
	void _ready();
	void _set_score_label(int64_t score);
};
} // namespace godot
#endif //GODOT_NATIVE_SCORE_H
