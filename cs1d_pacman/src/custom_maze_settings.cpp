#include "custom_maze_settings.hpp"

void CustomMazeSettings::_register_methods() {
	godot::register_method("_ready", &CustomMazeSettings::_ready);
	godot::register_method("set_visible", &CustomMazeSettings::set_visible);
	godot::register_method("_on_BackButton_pressed", &CustomMazeSettings::_on_BackButton_pressed);
	godot::register_method("_on_SubmitButton_pressed", &CustomMazeSettings::_on_SubmitButton_pressed);
	godot::register_signal<CustomMazeSettings>("set_maze", godot::Dictionary());
}

void CustomMazeSettings::_ready() {
	_control = get_node<godot::Control>("Control");
	_start_y_input = _control->get_node<godot::LineEdit>("StartYInput");
	_start_x_input = _control->get_node<godot::LineEdit>("StartXInput");
	_maze_input = _control->get_node<godot::TextEdit>("MazeInput");
}

void CustomMazeSettings::set_visible(bool visible) {
	_control->set_visible(visible);
}

void CustomMazeSettings::_on_BackButton_pressed() {
	set_visible(false);
}

void CustomMazeSettings::_on_SubmitButton_pressed() {
	emit_signal("set_maze", _start_y_input->get_text(), _start_x_input->get_text(), _maze_input->get_text());
}