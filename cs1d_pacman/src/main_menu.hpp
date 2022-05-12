#ifndef MAINMENU_H
#define MAINMENU_H

#include <Godot.hpp>
#include <CanvasLayer.hpp>
#include <Button.hpp>
#include <AudioStreamPlayer.hpp>
#include <Control.hpp>

class MainMenu : public godot::CanvasLayer {
	GODOT_CLASS(MainMenu, godot::CanvasLayer)

	godot::Control* _control;
	godot::AudioStreamPlayer* _start_music;
	godot::Button* _continue_button;

public:
	void _init() {}
	void _ready();
	void set_visible(bool visible);
	void _on_StartMusic_finished();
	void _on_ContinueButton_pressed();

	static void _register_methods();
};

#endif