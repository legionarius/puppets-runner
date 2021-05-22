//
// Created by bogdan on 24/02/2021.
//

#ifndef GAMEJAM_TRAINING_TITLESCREEN_H
#define GAMEJAM_TRAINING_TITLESCREEN_H

#include <AnimationPlayer.hpp>
#include <TextureButton.hpp>
#include <Control.hpp>
#include <Godot.hpp>
#include <InputEvent.hpp>
#include <InputEventKey.hpp>
#include <InputMap.hpp>
#include <Ref.hpp>
#include <ResourceLoader.hpp>
#include <SceneTree.hpp>
#include <Viewport.hpp>

namespace godot {

class TitleScreen : public Control {
	GODOT_CLASS(TitleScreen, Control);

public:
	static void _register_methods();
	void _init();
	void _ready();
	void _exit();
	void _start();
	void _input(const Ref<InputEvent> event);
};

} // namespace godot
#endif //GAMEJAM_TRAINING_TITLESCREEN_H
