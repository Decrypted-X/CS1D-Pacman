#ifndef PACMAN_H
#define PACMAN_H

#include <AudioStreamPlayer.hpp>
#include <AnimatedSprite.hpp>
#include <Godot.hpp>
#include <KinematicBody2D.hpp>
#include <Vector2.hpp>

class Pacman : public godot::KinematicBody2D {
	GODOT_CLASS(Pacman, godot::KinematicBody2D)

	godot::AudioStreamPlayer* _eat_sound;
	godot::AudioStreamPlayer* _death_sound;
	godot::AnimatedSprite* _animated_sprite;

private:
	godot::Vector2 target;
	bool signal_emitted;

public:
	real_t speed = 100;

	void _init() {}
	void _ready();
	void _process(const double delta);
	void set_target(godot::Vector2 target);
	void stop_anim();
	void play_eat();
	void play_death();
	void reset(godot::Vector2 start_pos);

	static void _register_methods();
};

#endif // PACMAN_H