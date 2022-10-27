#pragma once
#include <SFML/Graphics.hpp>

#include "environment/world.hpp"
//#include "common/utils.hpp"
#include "config.hpp"
#include <string>
#include "algorithms/algorithm.hpp"

int map_value(int input, int input_start, int input_end, int output_start, int output_end){
    return output_start + ((output_end - output_start) / (input_end - input_start)) * (input - input_start);
}

struct Scene{
    bool found;
    bool running;
    bool could_not_find;
    bool is_alg_set;
    World *world;
    std::string alg;
    sf::RenderWindow *window;
    PathFinding pathfinding;
    bool show_alert;
    size_t frame_alert_showed;
    std::string alert_msg;
    sf::Text alert_text;
    sf::RectangleShape alert_text_box;

    Scene(sf::RenderWindow* window){
        this->window = window;
        this->frame_alert_showed = 0;
        this->show_alert = false;
        this->alert_text.setFont(Conf::FONT);
        this->alert_text.setCharacterSize(Conf::ALERT_TEXT_SIZE);
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
                this->set_alert(Conf::BFS);
                set_alg(Conf::BFS);
                break;
            case 3:
                this->set_alert(Conf::DIJKSTRA);
                set_alg(Conf::DIJKSTRA);
                break;
            case 15:
                if(this->running){
                    this->set_alert(Conf::PAUSE_TEXT);
                }else{
                    this->set_alert(Conf::PLAY_TEXT);
                }
                this->toggle_run();
                break;
            case 17:
                this->set_alert(Conf::RESET_TEXT);
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
    bool is_alert_finished(){
        return frame_alert_showed >= Conf::ALERT_DURATION;
    }
    void set_alert(std::string msg){
        if(!this->show_alert){
            this->alert_msg = msg;
            this->show_alert = true;
        }
    }
    void render_alert(){
        this->alert_text.setString(this->alert_msg);
        unsigned int alpha = this->frame_alert_showed <= Conf::ALERT_DURATION / 4 ? 255 : map_value(this->frame_alert_showed, Conf::ALERT_DURATION / 4, 29, 255, 0);

        sf::FloatRect textRect = this->alert_text.getLocalBounds();
        this->alert_text.setOrigin(textRect.left + textRect.width/2.0f, textRect.top  + textRect.height/2.0f);
        this->alert_text.setPosition(sf::Vector2f(Conf::WIDTH / 2.0, Conf::HEIGHT/2.0));
        this->alert_text.setFillColor(sf::Color(255, 255, 255, alpha));
        
        
        size_t padding =  Conf::ALERT_TEXT_SIZE * 2;
        float box_width = textRect.width + padding;
        float box_height = (float)padding / 4.0 + textRect.height;
        

        this->alert_text_box.setSize(sf::Vector2f(box_width, box_height));
        this->alert_text_box.setFillColor(sf::Color(51, 51, 51, alpha));
        this->alert_text_box.setPosition(sf::Vector2f(Conf::WIDTH / 2 - box_width / 2, Conf::HEIGHT / 2 - box_height / 2));

        this->window->draw(this->alert_text_box);
        this->window->draw(this->alert_text);
    }
};