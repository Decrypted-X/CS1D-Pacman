#include "pellet.hpp"

void Pellet::_register_methods() {
	godot::register_method("_ready", &Pellet::_ready);
}

void Pellet::_ready() {
	_animated_sprite = get_node<godot::AnimatedSprite>("AnimatedSprite");
	_animated_sprite->play();
}