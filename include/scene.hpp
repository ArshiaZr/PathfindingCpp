#pragma once
#include <SFML/Graphics.hpp>

#include "environment/world.hpp"
//#include "common/utils.hpp"
#include "config.hpp"
#include <string>
#include "algorithms/algorithm.hpp"

struct Scene{
    bool found;
    bool running;
    bool could_not_find;
    bool is_alg_set;
    World *world;
    std::string alg;
    sf::RenderWindow *window;
    PathFinding pathfinding;

    Scene(sf::RenderWindow* window){
        this->window = window;
        //this->world = new World(Conf::WIDTH/Conf::CELL_WIDTH, Conf::HEIGHT/Conf::CELL_WIDTH, Conf::CELL_WIDTH);
    }
    void init(){
        this->world = new World(Conf::WIDTH/Conf::CELL_WIDTH, Conf::HEIGHT/Conf::CELL_WIDTH, Conf::CELL_WIDTH);
        this->found = false;
        this->running = false;
        this->could_not_find = false;
        this->is_alg_set = false;
        this->world->init();
        this->world->set_start(std::make_pair(Conf::START_X, Conf::START_Y));
        this->world->set_end(std::make_pair(Conf::END_X, Conf::END_Y));
        if(!Conf::FONT.loadFromFile("res/font.ttf")){
            std::cout << "Could not find some of resourses: font" << std::endl;
        }
        this->window->setFramerateLimit(Conf::FRAMERATELIMIT);
        pathfinding.init();
    }
    World* get_world(){
        return this->world;
    }
    void toggle_run(){
        if(this->is_alg_set){
            this->running = !this->running;
        }else{
            this->running = false;
        }
        
    }
    bool is_path_found(){
        return found;
    }
    bool is_paused(){
        return !this->running;
    }
    void set_alg(std::string alg){
        this->alg = alg;
        this->is_alg_set = true;
    }
    void handle_input(int code){
        sf::Vector2i posV = sf::Mouse::getPosition(*this->window);
        std::pair<int, int> pos = std::make_pair(posV.x / Conf::CELL_WIDTH, posV.y / Conf::CELL_WIDTH);
        switch(code){
            case -1:
                if(is_valid(Conf::WIDTH, Conf::HEIGHT, pos.first, pos.second)){
                    if(!this->world->is_start(pos) && !this->world->is_end(pos)){
                        if(this->world->is_wall(pos)){
                            this->world->remove_wall(pos);
                        }else{
                            this->world->add_wall(pos);
                        }
                    }
                }
                break;
            case -2:
                if(is_valid(Conf::WIDTH, Conf::HEIGHT, pos.first, pos.second)){
                    int cur_weight = this->world->grid[pos.second][pos.first]->weight;
                    if(!this->world->is_wall(pos) && !this->world->is_start(pos) && !this->world->is_end(pos)){
                        this->world->increase_weight(pos);
                    }
                }
                break;
            case 1:
                set_alg(Conf::BFS);
                break;
            case 3:
                set_alg(Conf::DIJKSTRA);
                break;
            case 15:
                this->toggle_run();
                break;
            case 17:
                this->init();
            default:
                break;
        }
    }
    void run_algo(){
        pathfinding.run(this->alg, *this->world, this->found, this->could_not_find);
    }
    bool impossible(){
        return this->could_not_find;
    }
};