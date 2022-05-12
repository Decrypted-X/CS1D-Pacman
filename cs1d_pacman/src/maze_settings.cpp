#include "maze_settings.hpp"

void MazeSettings::_register_methods() {
	godot::register_method("_ready", &MazeSettings::_ready);
	godot::register_method("set_visible", &MazeSettings::set_visible);
	godot::register_method("_on_CreateCustomButton_pressed", &MazeSettings::_on_CreateCustomButton_pressed);
	godot::register_method("_on_ContinueButton_pressed", &MazeSettings::_on_ContinueButton_pressed);
	godot::register_signal<MazeSettings>("open_custom", godot::Dictionary());
	godot::register_signal<MazeSettings>("start_game", godot::Dictionary());
}

void MazeSettings::_ready() {
	_control = get_node<godot::Control>("Control");
	_maze_size_input = _control->get_node<godot::LineEdit>("MazeSizeInput");
}

void MazeSettings::set_visible(bool visible) {
	_control->set_visible(visible);
}

void MazeSettings::_on_CreateCustomButton_pressed() {
	emit_signal("open_custom");
}

void MazeSettings::_on_ContinueButton_pressed() {
	int maze_size = (int)_maze_size_input->get_text().to_int();

	if (maze_size >= 10 && maze_size <= 50) {
		emit_signal("start_game", maze_size, maze_size); // min: 10  max: 50
		set_visible(false);
	}
}