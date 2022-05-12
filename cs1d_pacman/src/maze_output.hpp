#ifndef MAZEOUTPUT_H
#define MAZEOUTPUT_H

#include <Godot.hpp>
#include <CanvasLayer.hpp>
#include <Control.hpp>
#include <TextEdit.hpp>

class MazeOutput : public godot::CanvasLayer {
	GODOT_CLASS(MazeOutput, godot::CanvasLayer)

	godot::Control* _control;
	godot::TextEdit* _output_text;

private:
	bool is_reversed;

public:
	void _init() {}
	void _ready();
	void set_visible(bool visible);
	void _on_IsReversedButton_pressed();
	void _on_BackButton_pressed();
	void _on_SubmitButton_pressed();

	static void _register_methods();
};

#endif