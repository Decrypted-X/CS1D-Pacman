#include "main_menu.hpp"

void MainMenu::_register_methods() {
	godot::register_method("_ready", &MainMenu::_ready);
	godot::register_method("set_visible", &MainMenu::set_visible);
	godot::register_method("_on_StartMusic_finished", &MainMenu::_on_StartMusic_finished);
	godot::register_method("_on_ContinueButton_pressed", &MainMenu::_on_ContinueButton_pressed);
}

void MainMenu::_ready() {
	_control = get_node<godot::Control>("Control");
	_start_music = _control->get_node<godot::AudioStreamPlayer>("StartMusic");
	_continue_button = _control->get_node<godot::Button>("ContinueButton");
	_start_music->play();
}

void MainMenu::set_visible(bool visible) {
	_control->set_visible(visible);
}

void MainMenu::_on_StartMusic_finished() {
	_continue_button->show();
}

void MainMenu::_on_ContinueButton_pressed() {
	set_visible(false);
}