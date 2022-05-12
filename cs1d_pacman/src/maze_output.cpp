#include "maze_output.hpp"

void MazeOutput::_register_methods() {
	godot::register_method("_ready", &MazeOutput::_ready);
	godot::register_method("set_visible", &MazeOutput::set_visible);
	godot::register_method("_on_IsReversedButton_pressed", &MazeOutput::_on_IsReversedButton_pressed);
	godot::register_method("_on_BackButton_pressed", &MazeOutput::_on_BackButton_pressed);
	godot::register_method("_on_SubmitButton_pressed", &MazeOutput::_on_SubmitButton_pressed);
	godot::register_signal<MazeOutput>("set_path", godot::Dictionary());
}

void MazeOutput::_ready() {
	_control = get_node<godot::Control>("Control");
	_output_text = _control->get_node<godot::TextEdit>("OutputText");

	is_reversed = false;
}

void MazeOutput::set_visible(bool visible) {
	_control->set_visible(visible);
}

void MazeOutput::_on_IsReversedButton_pressed() {
	is_reversed = !is_reversed;
}

void MazeOutput::_on_BackButton_pressed() {
	set_visible(false);
}

void MazeOutput::_on_SubmitButton_pressed() {
	emit_signal("set_path", _output_text->get_text(), is_reversed);
}