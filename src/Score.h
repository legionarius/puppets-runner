//
// Created by nahalu on 14/05/2021.
//

#ifndef GODOT_NATIVE_SCORE_H
#define GODOT_NATIVE_SCORE_H

#include "LevelController.h"
#include "Signals.h"

#include <Godot.hpp>
#include <Label.hpp>

namespace godot {
class Score : public Label {
	GODOT_CLASS(Score, Label);

private:
	LevelController *levelController;

public:
	static void _register_methods();
	void _init();
	void _ready();
	void _set_score_label(int64_t score);
};
} // namespace godot
#endif //GODOT_NATIVE_SCORE_H
