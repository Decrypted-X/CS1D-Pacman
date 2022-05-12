#ifndef PELLET_H
#define PELLET_H

#include <Godot.hpp>
#include <AnimatedSprite.hpp>
#include <Area2D.hpp>

class Pellet : public godot::Area2D {
	GODOT_CLASS(Pellet, godot::Area2D)

	godot::AnimatedSprite* _animated_sprite;

public:
	void _init() {}
	void _ready();

	static void _register_methods();
};

#endif // PELLET_H