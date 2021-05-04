//
// Created by nahalu on 30/04/2021.
//

#include "Partition.h"

using namespace godot;
using namespace std;

void Partition::_init() {}

void Partition::_ready() {
	levelController = cast_to<LevelController>(get_tree()->get_root()->get_node("MainScene/Level"));
	levelController->connect("add_action", this, "_addActionIcon");
	levelController->connect("clear_actions", this, "_clearActionIcons");
}

void Partition::_addActionIcon(int64_t action) {
	ActionIcon *actionIcon = ActionIcon::_new();
	actionIcon->set_action_type(action);
	add_child(actionIcon);
}

void Partition::_clearActionIcons() {
	Array actionIcons = get_children();
	for (size_t i = 0; i < get_child_count(); i++) {
		Node *node = cast_to<Node>(actionIcons[i]);
		node->queue_free();
	}
}

void Partition::_register_methods() {
	register_method("_init", &Partition::_init);
	register_method("_ready", &Partition::_ready);
	register_method("_addActionIcon", &Partition::_addActionIcon);
	register_method("_clearActionIcons", &Partition::_clearActionIcons);
}
