//
// Created by nahalu on 14/05/2021.
//

#include "Score.h"

using namespace godot;

void Score::_init() {
}

void Score::_ready() {
	labelScore = cast_to<Label>(get_node("Label"));
	levelController = cast_to<LevelController>(get_tree()->get_root()->get_node("MainScene/Level"));
	levelController->connect(SET_LABEL_SCORE, this, "_set_score_label");
}

void Score::_set_score_label(int64_t score) {
	labelScore->set_text(String("SCORE:  " + String::num_int64(score)));
}

void Score::_register_methods() {
	register_method("_init", &Score::_init);
	register_method("_ready", &Score::_ready);
	register_method("_set_score_label", &Score::_set_score_label);
}