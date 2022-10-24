#pragma once
#include <SFML/Graphics.hpp>
#include "../cell/cell.hpp"
#include <vector>
#include <iostream>
// #include <queue>
// #include <unordered_set>
// #include <string>


struct World{

    std::vector<std::vector<Cell*>> grid;
    std::pair<size_t, size_t> start, end;
    int cell_width;

    World(int width, int height, int cell_width){
        this->grid = std::vector<std::vector<Cell*>>(height, std::vector<Cell*>(width));
        this->cell_width = cell_width;
    }
    void init(){
        for(int i = 0; i < grid.size(); i++){
            for(int j = 0; j < grid[0].size(); j++){
                grid[i][j] = new Cell(j * cell_width, i* cell_width, cell_width, 1);
            }
        }
    }
    void set_start(std::pair<size_t, size_t> pos){
        start = pos;
        this->grid[pos.second][pos.first]->change_color(Conf::START_COLOR);
    }
    void set_end(std::pair<size_t, size_t> pos){
        end = pos;
        this->grid[pos.second][pos.first]->change_color(Conf::END_COLOR);
    }
    void add_wall(std::pair<size_t, size_t> pos){
        this->grid[pos.second][pos.first]->set_weight(-1);
        this->grid[pos.second][pos.first]->change_color(Conf::WALL_COLOR);
    }
    void remove_wall(std::pair<size_t, size_t> pos){
        this->grid[pos.second][pos.first]->set_weight(1);
        this->grid[pos.second][pos.first]->change_color(Conf::CELL_COLOR);
    }
    bool is_wall(std::pair<size_t, size_t> pos){
        return this->grid[pos.second][pos.first]->weight == -1;
    }
    void increase_weight(std::pair<size_t, size_t> pos){
        this->grid[pos.second][pos.first]->set_weight(this->grid[pos.second][pos.first]->weight + 1);
    }
    void decrease_weight(std::pair<size_t, size_t> pos){
        if(this->grid[pos.second][pos.first]->weight == 1){
            return;
        }
        this->grid[pos.second][pos.first]->set_weight(this->grid[pos.second][pos.first]->weight - 1);
    }
    bool is_start(std::pair<size_t, size_t> pos){
        return pos.first == this->start.second && pos.second == this->start.first;
    }
    bool is_end(std::pair<size_t, size_t> pos){
        return pos.first == this->end.second && pos.second == this->end.first;
    }
    void render(sf::RenderWindow& window){
        for(int i = 0; i < grid.size(); i++){
            for(int j = 0; j < grid[0].size(); j++){
                window.draw(grid[i][j]->shape);
                if(grid[i][j]->weight != 1 && grid[i][j]->weight != -1){
                    grid[i][j]->title.setString(std::to_string(grid[i][j]->weight));
                    window.draw(grid[i][j]->title);
                }
            }
        }
    }
    std::pair<int, int> get_pos(sf::RenderWindow& window, int cell_width){
        sf::Vector2i pos = sf::Mouse::getPosition(window);
        return std::make_pair(pos.y / cell_width, pos.x / cell_width);
    }
};