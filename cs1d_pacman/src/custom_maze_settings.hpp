#ifndef CUSTOMMAZESETTINGS_H
#define CUSTOMMAZESETTINGS_H

#include <Godot.hpp>
#include <CanvasLayer.hpp>
#include <Control.hpp>
#include <LineEdit.hpp>
#include <TextEdit.hpp>

class CustomMazeSettings : public godot::CanvasLayer {
	GODOT_CLASS(CustomMazeSettings, godot::CanvasLayer)

	godot::Control* _control;
	godot::LineEdit* _start_y_input;
	godot::LineEdit* _start_x_input;
	godot::TextEdit* _maze_input;

public:
	void _init() {}
	void _ready();
	void set_visible(bool visible);
	void _on_BackButton_pressed();
	void _on_SubmitButton_pressed();

	static void _register_methods();
};

#endif