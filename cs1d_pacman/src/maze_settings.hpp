#ifndef MAZESETTINGS_H
#define MAZESETTINGS_H

#include <Godot.hpp>
#include <CanvasLayer.hpp>
#include <LineEdit.hpp>
#include <Control.hpp>

class MazeSettings : public godot::CanvasLayer {
	GODOT_CLASS(MazeSettings, godot::CanvasLayer)

	godot::Control* _control;
	godot::LineEdit* _maze_size_input;

public:
	void _init() {}
	void _ready();
	void set_visible(bool visible);
	void _on_CreateCustomButton_pressed();
	void _on_ContinueButton_pressed();

	static void _register_methods();
};

#endif