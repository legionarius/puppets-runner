//
// Created by acroquelois on 28/04/2021.
//

#ifndef GODOT_NATIVE_MAINSCENE_H
#define GODOT_NATIVE_MAINSCENE_H

#include "Player.h"

#include <Godot.hpp>
#include <Node.hpp>
#include <Ref.hpp>
#include <ResourceLoader.hpp>
#include <PackedScene.hpp>
#include <Position2D.hpp>
#include <SceneTree.hpp>
#include <Viewport.hpp>
#include <sstream>

namespace godot {

class MainScene : public Node {
	GODOT_CLASS(MainScene, Node);

	Player *player;

public:
	static void _register_methods();
	void _init();
	void _ready();
	void _exit();
	void _start();
};

}

#endif //GODOT_NATIVE_MAINSCENE_H
