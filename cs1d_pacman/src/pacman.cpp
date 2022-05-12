#include "pacman.hpp"

void Pacman::_register_methods() {
	godot::register_method("_ready", &Pacman::_ready);
	godot::register_method("_process", &Pacman::_process);
	godot::register_method("set_target", &Pacman::set_target);
	godot::register_method("stop_anim", &Pacman::stop_anim);
	godot::register_method("play_eat", &Pacman::play_eat);
	godot::register_method("play_death", &Pacman::play_death);
	godot::register_method("reset", &Pacman::reset);
	godot::register_property("speed", &Pacman::speed, (real_t)100.0);
	godot::register_signal<Pacman>("target_reached", godot::Dictionary());
}

void Pacman::_ready() {
	_eat_sound = get_node<godot::AudioStreamPlayer>("EatSound");
	_death_sound = get_node<godot::AudioStreamPlayer>("DeathSound");
	_animated_sprite = get_node<godot::AnimatedSprite>("AnimatedSprite");

	signal_emitted = true;
	target = get_position();
}

void Pacman::_process(const double delta) {
	godot::Vector2 position = get_position();

	if (position.distance_to(target) > (real_t)3) {
		godot::Vector2 velocity = target - position;

		if (velocity.length() > 0)
			velocity = velocity.normalized() * speed;

		position += velocity * (real_t)delta;
		set_position(position);

		if (velocity.x != 0) {
			_animated_sprite->set_animation("right");
			_animated_sprite->set_flip_v(false);
			_animated_sprite->set_flip_h(velocity.x < 0);
		}
		else if (velocity.y != 0) {
			_animated_sprite->set_animation("down");
			_animated_sprite->set_flip_h(false);
			_animated_sprite->set_flip_v(velocity.y < 0);
		}
		
		if (position.distance_to(target) <= (real_t)3) {
			position = target;
			set_position(position);

			if (!signal_emitted) {
				signal_emitted = true;
				emit_signal("target_reached");
			}
		}
	}
}

void Pacman::set_target(godot::Vector2 target) {
	signal_emitted = false;
	this->target = target;
	_animated_sprite->play();
}

void Pacman::stop_anim() {
	set_position(target);
	_animated_sprite->stop();
	_animated_sprite->set_frame(0);
}

void Pacman::play_eat() {
	_eat_sound->play();
}

void Pacman::play_death() {
	_animated_sprite->set_animation("death");
	_animated_sprite->set_frame(0);
	_animated_sprite->play();
	_death_sound->play();
}

void Pacman::reset(godot::Vector2 start_pos) {
	signal_emitted = true;
	target = start_pos;
	_animated_sprite->set_animation("right");
	stop_anim();
	_animated_sprite->set_flip_v(false);
	_animated_sprite->set_flip_v(false);
}