#include "main.hpp"

void Main::_register_methods() {
	godot::register_method("_ready", &Main::_ready);
	godot::register_method("create_maze", &Main::create_maze);
	godot::register_method("show_maze", &Main::show_maze);
	godot::register_method("traverse_maze", &Main::traverse_maze);
	godot::register_method("maze_won", &Main::maze_won);
	godot::register_method("maze_lost", &Main::maze_lost);
	godot::register_method("reset_maze", &Main::reset_maze);
	godot::register_method("_on_CooldownTimer_timeout", &Main::_on_CooldownTimer_timeout);
	godot::register_method("_on_MazeSettingsButton_pressed", &Main::_on_MazeSettingsButton_pressed);
	godot::register_method("_on_MazeInputButton_pressed", &Main::_on_MazeInputButton_pressed);
	godot::register_method("_on_MazeOutputButton_pressed", &Main::_on_MazeOutputButton_pressed);
	godot::register_method("_on_RunButton_pressed", &Main::_on_RunButton_pressed);
	godot::register_method("_on_MazeSettings_open_custom", &Main::_on_MazeSettings_open_custom);
	godot::register_method("_on_CustomMazeSettings_set_maze", &Main::_on_CustomMazeSettings_set_maze);
	godot::register_method("_on_MazeOutput_set_path", &Main::_on_MazeOutput_set_path);
	godot::register_property("empty_cell_scene", &Main::empty_cell_scene, (godot::Ref<godot::PackedScene>)nullptr);
	godot::register_property("wall_scene", &Main::wall_scene, (godot::Ref<godot::PackedScene>)nullptr);
	godot::register_property("pellet_scene", &Main::pellet_scene, (godot::Ref<godot::PackedScene>)nullptr);
}

void Main::_ready() {
	_maze_settings = get_node<MazeSettings>("MazeSettings");
	_custom_maze_settings = get_node<CustomMazeSettings>("CustomMazeSettings");
	_maze_input = get_node<MazeInput>("MazeInput");
	_maze_output = get_node<MazeOutput>("MazeOutput");
	_pacman = get_node<Pacman>("Pacman");
	_maze_settings_button = get_node<godot::Button>("MazeSettingsButton");
	_maze_input_button = get_node<godot::Button>("MazeInputButton");
	_maze_output_button = get_node<godot::Button>("MazeOutputButton");
	_run_button = get_node<godot::Button>("RunButton");
	_maze_node = get_node<godot::Node>("Maze");
	_start_pos_node = get_node<godot::Node2D>("StartPos");
	_end_pos_node = get_node<godot::Node2D>("EndPos");
	_cooldown_timer = get_node<godot::Timer>("CooldownTimer");
	_random = (godot::Ref<godot::RandomNumberGenerator>)godot::RandomNumberGenerator::_new();
    _random->randomize();

    is_reversed = false;
    is_game_over = false;
}

Main::~Main() {
	current_maze.clear();
	saved_path.clear();
	path.clear();
	cells.clear();
}

bool Main::in_bounds(int y, int x) {
	return (y >= 0 && x >= 0 && y < m && x < n);
}

void Main::get_walls(int y, int x, std::vector<std::vector<int>>& maze, std::vector<std::pair<int, int>>& walls) {
	for (int i = 0; i < 4; ++i) {
		int ty = y + dy[i], tx = x + dx[i];
		if (in_bounds(ty, tx) && maze[ty][tx] == 3)
			walls.push_back(std::make_pair(ty, tx));
	}
}

// Maze Values
// 0 - not visited (visited for creating maze)
// 1 - wall        (visited wall for creating maze)
// 2 - goal
// 3 - not visited spot (for creating maze)
void Main::create_maze(int m, int n) {
	this->m = m;
	this->n = n;

	std::vector<std::vector<int>> maze(this->m, std::vector<int>(this->n, 3));
	std::vector<std::pair<int, int>> walls, empty_spots;

	start_y = (int) _random->randi_range(0, m - 1);
	start_x = (int) _random->randi_range(0, n - 1);

	maze[start_y][start_x] = 0;
	get_walls(start_y, start_x, maze, walls);

	while (!walls.empty()) {
		int spot_index = (int) _random->randi_range(0, walls.size() - 1);
		std::pair<int, int> random_spot = walls[spot_index];
		int y = random_spot.first, x = random_spot.second;

		int visited_count = 0;
		for (int i = 0; i < 4; ++i) {
			int ty = y + dy[i], tx = x + dx[i];
			if (in_bounds(ty, tx) && maze[ty][tx] == 0)
				visited_count++;
		}

		if (visited_count == 1) {
			maze[y][x] = 0;
			empty_spots.push_back(std::make_pair(y, x));
			get_walls(y, x, maze, walls);
		}
		else
			maze[y][x] = 1;

		walls.erase(walls.begin() + spot_index);
	}

	int spot_index = (int) _random->randi_range(0, empty_spots.size() - 1);
	std::pair<int, int> spot = empty_spots[spot_index];
	end_y = spot.first;
	end_x = spot.second;
	maze[end_y][end_x] = 2;

	for (int y = 0; y < m; ++y)
		for (int x = 0; x < n; ++x)
			if (maze[y][x] == 3)
				maze[y][x] = 1;

	current_maze = maze;

	start_cell = nullptr;
	cells.clear();
	path.clear();

	show_maze();
}

void Main::add_cell(double y_pos, double x_pos, double y_scale, double x_scale, int cell_type) {
	godot::Node* cell = nullptr;

	switch (cell_type) {
		case 1:
			cell = wall_scene->instance();
			break;
		case 2:
			cell = pellet_scene->instance();
			break;
		default:
			cell = empty_cell_scene->instance();
	}

	godot::Vector2 scale_vector = godot::Vector2((real_t)x_scale, (real_t)y_scale);
	cell->set("scale", scale_vector);
	
	godot::Vector2 position_vector = godot::Vector2((real_t)x_pos, (real_t)y_pos);
	cell->set("position", position_vector);
	
	cells.push_back((godot::Node2D*)cell);

	_maze_node->call_deferred("add_child", cell);
}

void Main::show_maze() {
	double y_scale = CELL_CONST / (double)m;
	double x_scale = CELL_CONST / (double)n;
	godot::Vector2 spos = _start_pos_node->get_position();

	for (int y = 0; y < m; ++y) {
		for (int x = 0; x < n; ++x) {
			double y_pos = spos[1] + CELL_SIZE / 2 * y_scale + (CELL_SIZE * y_scale * y);
			double x_pos = spos[0] + CELL_SIZE / 2 * x_scale + (CELL_SIZE * x_scale * x);

			add_cell(y_pos, x_pos, y_scale, x_scale, current_maze[y][x]);
		}
	}

	start_cell = cells[start_x + start_y * n];

	godot::Vector2 scale_vector = godot::Vector2((real_t)x_scale, (real_t)y_scale);
	_pacman->set("scale", scale_vector);
	_pacman->reset(start_cell->get_position());
}

void Main::traverse_maze() {
	if (!is_game_over) {
		if (!path.empty()) {
			std::vector<int> spot = (is_reversed ? path.back() : path.front());
			int y = spot[0], x = spot[1];

			int y_dist = std::abs(y - prev_y), x_dist = std::abs(x - prev_x);
			if (!in_bounds(y, x) || current_maze[y][x] == 1 || y_dist > 1 || x_dist > 1 || (y_dist == 1 && x_dist == 1) || (y_dist == 0 && x_dist == 0)) {
				is_game_over = true;
				maze_lost();
			}
			else {
				if (y == end_y && x == end_x)
					_pacman->play_eat();

				_pacman->set_target(cells[x + y * n]->get_position());

				prev_y = y;
				prev_x = x;

				path.erase((is_reversed ?  path.end() - 1 : path.begin()));
			}
		}
		else {
			is_game_over = true;

			if (end_y == prev_y && end_x == prev_x)
				maze_won();
			else
				maze_lost();
		}
	}
}

void Main::maze_won() {
	_cooldown_timer->start();
	get_tree()->call_group("walls", "play");
	_pacman->stop_anim();
}

void Main::maze_lost() {
	_cooldown_timer->start();
	_pacman->stop_anim();
	_pacman->play_death();
}

void Main::reset_maze() {
	get_tree()->call_group("walls", "stop");
	get_tree()->call_group("walls", "set_frame", 0);

	is_game_over = false;
}

void Main::_on_CooldownTimer_timeout() {
	reset_maze();
}

void Main::_on_MazeSettingsButton_pressed() {
	_maze_settings->set_visible(true);
	get_tree()->call_group("maze_objects", "queue_free");
}

void Main::_on_MazeInputButton_pressed() {
	std::string s = "std::vector<std::vector<int>> maze = {\n";

	for (int y = 0; y < m; ++y) {
		s += "\t{";
		for (int x = 0; x < n; ++x) {
			s += std::to_string(current_maze[y][x]);
			s += (x < n - 1 ? "," : "");
		}
		s += "}";
		s += (y < m - 1 ? ",\n" : "\n");
	}

	s += "};\nint startY = ";
	s += std::to_string(start_y);
	s += ", startX = ";
	s += std::to_string(start_x);
	s += ";\nstd::vector<std::vector<int>> path;  // TODO GET PATH HERE (i.e. path = dfs(maze, startY, startX);)\nstd::cout << \"{\";\nfor (int i = 0; i < path.size(); ++i) {\n\tstd::cout << \"{\" << path[i][0] << \",\" << path[i][1] << \"}\" << (i == path.size() - 1 ? \"\" : \",\");\n}\nstd::cout << \"}\\n\";";
	godot::String input_text(s.c_str());
	_maze_input->set_input(input_text);
	_maze_input->set_visible(true);
}

std::vector<std::vector<int>> Main::convert_to_matrix(godot::String text) {
	std::vector<std::vector<int>> matrix;
	std::vector<int> current_row;
	int text_length = text.length(), current_num = -1;
	bool outer_first = false, outer_last = false, inner_first = false, inner_last = false;
	// {{0,0},{0,1},{1,1}}
	for (int i = 0; i < text_length; ++i) {
		char c = (char)text[i];

		if (c == '{') {
			if (outer_last)
				return {};
			else if (!outer_first)
				outer_first = true;
			else if (!inner_first) {
				inner_first = true;
				inner_last = false;
			}
			else
				return {};
		}
		else if (c == '}') {
			if (!inner_last) {
				inner_last = true;
				inner_first = false;

				if (current_num != -1) {
					current_row.push_back(current_num);
					current_num = -1;
				}

				if (current_row.size() == 0)
					return {};

				matrix.push_back(current_row);
				current_row.clear();
			}
			else if (!outer_last)
				outer_last = true;
			else
				return {};
		}
		else if (c == ',' && current_num != -1) {
			current_row.push_back(current_num);
			current_num = -1;
		}
		else if (c - '0' >= 0 && c - '0' <= 9) {
			if (current_num > 0) {
				current_num *= 10;
				current_num += c - '0';
			}
			else
				current_num = c - '0';
		}
	}

	return matrix;
}

void Main::_on_MazeOutputButton_pressed() {
	_maze_output->set_visible(true);
}

void Main::_on_RunButton_pressed() {
	_run_button->set_disabled(true);
	
	if (_run_button->get_text() == "Reset") {
		_pacman->reset(start_cell->get_position());
		reset_maze();
		_maze_settings_button->set_disabled(false);
		_maze_input_button->set_disabled(false);
		_maze_output_button->set_disabled(false);
		_run_button->set_text("Run");
	}
	else if (saved_path.size() > 0) {
		_maze_settings_button->set_disabled(true);
		_maze_input_button->set_disabled(true);
		_maze_output_button->set_disabled(true);
		path = saved_path;
		prev_y = start_y;
		prev_x = start_x;
		path.erase((is_reversed ? path.end() - 1 : path.begin()));
		traverse_maze();
		_run_button->set_text("Reset");
	}

	_run_button->set_disabled(false);
}

void Main::_on_MazeSettings_open_custom() {
	_custom_maze_settings->set_visible(true);
}

void Main::_on_CustomMazeSettings_set_maze(godot::String y_str, godot::String x_str, godot::String maze_str) {
	int temp_y = (int)y_str.to_int(), temp_x = (int)x_str.to_int();
	std::vector<std::vector<int>> maze = convert_to_matrix(maze_str);

	if (maze.size() >= 10 && maze.size() <= 50 && maze[0].size() == maze.size() && temp_y >= 0 && temp_y < maze.size() && temp_x >= 0 && temp_x < maze.size() && maze[temp_y][temp_x] == 0) {
		bool found_goal = false;
		for (int y = 0; y < maze.size(); ++y) {
			for (int x = 0; x < maze[y].size(); ++x) {
				if (maze[y][x] == 2 && !found_goal)
					found_goal = true;
				else if (maze[y][x] != 0 && maze[y][x] != 1)
					return;	
			}
		}

		m = (int)maze.size();
		n = (int)maze[0].size();

		start_y = temp_y;
		start_x = temp_x;

		current_maze = maze;

		start_cell = nullptr;
		cells.clear();
		path.clear();

		show_maze();

		_maze_settings->set_visible(false);
		_custom_maze_settings->set_visible(false);
	}
}

void Main::_on_MazeOutput_set_path(godot::String output, bool is_reversed) {
	std::vector<std::vector<int>> p = convert_to_matrix(output);

	if (p.size() > 0) {
		saved_path = p;
		this->is_reversed = is_reversed;

		_maze_output->set_visible(false);
	}
}