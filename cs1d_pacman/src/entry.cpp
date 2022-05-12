#include <Godot.hpp>

#include "main_menu.hpp"
#include "maze_settings.hpp"
#include "custom_maze_settings.hpp"
#include "maze_input.hpp"
#include "maze_output.hpp"
#include "main.hpp"
#include "pacman.hpp"
#include "pellet.hpp"

extern "C" void GDN_EXPORT godot_gdnative_init(godot_gdnative_init_options *o) {
	godot::Godot::gdnative_init(o);
}

extern "C" void GDN_EXPORT godot_gdnative_terminate(godot_gdnative_terminate_options *o) {
	godot::Godot::gdnative_terminate(o);
}

extern "C" void GDN_EXPORT godot_nativescript_init(void *handle) {
	godot::Godot::nativescript_init(handle);

	godot::register_class<MainMenu>();
	godot::register_class<MazeSettings>();
	godot::register_class<CustomMazeSettings>();
	godot::register_class<MazeInput>();
	godot::register_class<MazeOutput>();
    godot::register_class<Pacman>();
    godot::register_class<Pellet>();
    godot::register_class<Main>();
}
