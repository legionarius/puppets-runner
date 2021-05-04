//
// Created by nahalu on 30/04/2021.
//

#ifndef GODOT_NATIVE_PARTITION_H
#define GODOT_NATIVE_PARTITION_H

#include "ActionIcon.h"
#include "ActionType.h"
#include "LevelController.h"

#include <Godot.hpp>
#include <HBoxContainer.hpp>
#include <TextureRect.hpp>

namespace godot {
class Partition : public HBoxContainer {
	GODOT_CLASS(Partition, HBoxContainer);

private:
	void _addActionIcon(int64_t action);
	void _clearActionIcons();

	LevelController *levelController;

public:
	static void _register_methods();
	void _init();
	void _ready();
};
} // namespace godot

#endif //GODOT_NATIVE_PARTITION_H
