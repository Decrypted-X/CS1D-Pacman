#ifndef MAIN_H
#define MAIN_H

#include <Godot.hpp>
#include <Node.hpp>
#include <Node2D.hpp>
#include <RandomNumberGenerator.hpp>
#include <PackedScene.hpp>
#include <SceneTree.hpp>
#include <Timer.hpp>
#include <Button.hpp>

#include <vector>
#include <utility>
#include <string>

#include "maze_settings.hpp"
#include "custom_maze_settings.hpp"
#include "maze_input.hpp"
#include "maze_output.hpp"
#include "pacman.hpp"

class Main : public godot::Node {
	GODOT_CLASS(Main, godot::Node)

	MazeSettings* _maze_settings;
	CustomMazeSettings* _custom_maze_settings;
	MazeInput* _maze_input;
	MazeOutput* _maze_output;
	Pacman* _pacman;
	godot::Button* _maze_settings_button;
	godot::Button* _maze_input_button;
	godot::Button* _maze_output_button;
	godot::Button* _run_button;
	godot::Node* _maze_node;
	godot::Node2D* _start_pos_node;
	godot::Node2D* _end_pos_node;
	godot::Timer* _cooldown_timer;
	godot::Ref<godot::RandomNumberGenerator> _random;

private:
	const int CELL_SIZE = 16; // the default size of a cell
	const double CELL_CONST = 30.5; // number of cells that can normally fit within the start and end positions
	int m, n, start_y, start_x, end_y, end_x, prev_y, prev_x;
	int dy[4] = {1, -1, 0, 0}, dx[4] = {0, 0, 1, -1};
	std::vector<std::vector<int>> current_maze;
	godot::Node2D* start_cell;
	std::vector<std::vector<int>> saved_path, path;
	std::vector<godot::Node2D*> cells;
	bool is_reversed, is_game_over;
	bool in_bounds(int y, int x);
	void get_walls(int y, int x, std::vector<std::vector<int>>& maze, std::vector<std::pair<int, int>>& walls);
	void add_cell(double y_pos, double x_pos, double y_scale, double x_scale, int cell_type);
	std::vector<std::vector<int>> convert_to_matrix(godot::String text);

public:
	godot::Ref<godot::PackedScene> empty_cell_scene;
	godot::Ref<godot::PackedScene> wall_scene;
	godot::Ref<godot::PackedScene> pellet_scene;

	void _init() {}
	void _ready();
	~Main();
	void create_maze(int m, int n);
	void show_maze();
	void traverse_maze();
	void maze_won();
	void maze_lost();
	void reset_maze();
	void _on_CooldownTimer_timeout();
	void _on_MazeSettingsButton_pressed();
	void _on_MazeInputButton_pressed();
	void _on_MazeOutputButton_pressed();
	void _on_RunButton_pressed();
	void _on_MazeSettings_open_custom();
	void _on_CustomMazeSettings_set_maze(godot::String y_str, godot::String x_str, godot::String maze_str);
	void _on_MazeOutput_set_path(godot::String output, bool is_reversed);

	static void _register_methods();
};

#endif // MAIN_H