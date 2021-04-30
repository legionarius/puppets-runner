//
// Created by acroquelois on 28/04/2021.
//

#ifndef GODOT_NATIVE_MAINSCENE_H
#define GODOT_NATIVE_MAINSCENE_H

#include <Godot.hpp>
#include <Node.hpp>
#include <SceneTree.hpp>
#include <Viewport.hpp>

namespace godot {

class MainScene : public Node {
	GODOT_CLASS(MainScene, Node);

public:
	static void _register_methods();
	void _init();
	void _ready();
	void _exit();
	void _start();
};

}

#endif //GODOT_NATIVE_MAINSCENE_H
