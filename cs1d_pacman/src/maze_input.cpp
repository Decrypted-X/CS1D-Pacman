#include "maze_input.hpp"

void MazeInput::_register_methods() {
	godot::register_method("_ready", &MazeInput::_ready);
	godot::register_method("set_visible", &MazeInput::set_visible);
	godot::register_method("set_input", &MazeInput::set_input);
	godot::register_method("_on_ContinueButton_pressed", &MazeInput::_on_ContinueButton_pressed);
	godot::register_signal<MazeInput>("start_game", godot::Dictionary());
}

void MazeInput::_ready() {
	_control = get_node<godot::Control>("Control");
	_input_text = _control->get_node<godot::TextEdit>("InputText");
}

void MazeInput::set_visible(bool visible) {
	_control->set_visible(visible);
}

void MazeInput::set_input(godot::String input_text) {
	_input_text->set_text(input_text);
}

void MazeInput::_on_ContinueButton_pressed() {
	set_visible(false);
}