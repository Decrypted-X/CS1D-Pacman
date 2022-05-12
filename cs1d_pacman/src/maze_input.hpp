#ifndef MAZEINPUT_H
#define MAZEINPUT_H

#include <Godot.hpp>
#include <CanvasLayer.hpp>
#include <Control.hpp>
#include <TextEdit.hpp>
#include <Button.hpp>

class MazeInput : public godot::CanvasLayer {
	GODOT_CLASS(MazeInput, godot::CanvasLayer)

	godot::Control* _control;
	godot::TextEdit* _input_text;

public:
	void _init() {}
	void _ready();
	void set_visible(bool visible);
	void set_input(godot::String input_text);
	void _on_ContinueButton_pressed();

	static void _register_methods();
};

#endif