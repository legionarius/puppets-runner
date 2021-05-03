//
// Created by acroquelois on 28/04/2021.
//

#ifndef GODOT_NATIVE_MAINSCENE_H
#define GODOT_NATIVE_MAINSCENE_H

#include <Godot.hpp>
#include <Node.hpp>
#include <SceneTree.hpp>
#include <Viewport.hpp>

#include "BlocSelector.h"
#include "LevelController.h"

namespace godot {

class MainScene : public Node {
	GODOT_CLASS(MainScene, Node);

	BlocSelector *blocSelector;
	LevelController *levelController;

public:
	static void _register_methods();
	void _init();
	void _ready();
	void _exit();
	void _start();
	void _on_bloc_selected(int blocId);
	void _on_progress(int progressId);
};

} // namespace godot

#endif //GODOT_NATIVE_MAINSCENE_H
