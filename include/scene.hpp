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


    bool waiting_for_start;
    bool waiting_for_end;

    World *world;
    std::string alg;
    sf::RenderWindow *window;
    PathFinding pathfinding;
    
    bool show_alert;
    size_t frame_alert_showed;
    sf::Text alert_text;
    sf::RectangleShape alert_text_box;

    bool show_warning;
    size_t frame_warning_showed;
    sf::Text warning_text;
    sf::RectangleShape warning_text_box;

    Scene(sf::RenderWindow* window){
        this->window = window;
        
        this->show_alert = false;
        this->frame_alert_showed = 0;
        this->alert_text.setFont(Conf::FONT);
        this->alert_text.setCharacterSize(Conf::ALERT_TEXT_SIZE);

        this->show_warning = false;
        this->frame_warning_showed = 0;
        this->warning_text.setFont(Conf::FONT);
        this->warning_text.setCharacterSize(Conf::WARNING_TEXT_SIZE);
    }
    void init(){
        this->world = new World(Conf::WIDTH/Conf::CELL_WIDTH, Conf::HEIGHT/Conf::CELL_WIDTH, Conf::CELL_WIDTH);
        
        this->found = false;
        this->running = false;
        this->could_not_find = false;
        this->is_alg_set = false;

        this->waiting_for_start = false;
        this->waiting_for_end = false;
        
        this->world->init();
        //this->world->set_start(std::make_pair(Conf::START_X, Conf::START_Y));
        //this->world->set_end(std::make_pair(Conf::END_X, Conf::END_Y));
        
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
                if(this->waiting_for_start){
                    if(is_valid(Conf::WIDTH, Conf::HEIGHT, pos.first, pos.second)){
                        this->world->set_start(std::make_pair(pos.first, pos.second));
                        this->waiting_for_start = false;
                        this->pathfinding.set_starting_point(*this->world);
                    }
                    break;
                }else if(this->waiting_for_end){
                    if(is_valid(Conf::WIDTH, Conf::HEIGHT, pos.first, pos.second)){
                        this->world->set_end(std::make_pair(pos.first, pos.second));
                        this->waiting_for_end = false;
                    }
                    break;
                }
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
                if(!this->world->is_start_set){
                    this->set_warning(Conf::SET_START);
                    break;
                }
                if(!this->world->is_end_set){
                    this->set_warning(Conf::SET_END);
                    break;
                }
                if(this->is_alg_set){
                    this->set_warning(Conf::ALG_ALR_SET);
                    break;
                }
                this->set_alert(Conf::BFS);
                this->set_alg(Conf::BFS);
                break;

            case 2:
                this->set_alert(Conf::CLEAR_TEXT);
                this->pathfinding.init();
                this->pathfinding.set_starting_point(*this->world);
                this->found = false;
                this->running = false;
                this->could_not_find = false;
                this->world->clear();
                break;
            case 3:
                if(!this->world->is_start_set){
                    this->set_warning(Conf::SET_START);
                    break;
                }
                if(!this->world->is_end_set){
                    this->set_warning(Conf::SET_END);
                    break;
                }
                if(this->is_alg_set){
                    this->set_warning(Conf::ALG_ALR_SET);
                    break;
                }
                this->set_alert(Conf::DIJKSTRA);
                set_alg(Conf::DIJKSTRA);
                
                break;
            case 4:
                if(this->world->is_end_set){
                    this->set_warning(Conf::END_ALR_SET);
                    break;
                }
                if(this->waiting_for_start){
                    this->set_warning(Conf::SET_START);
                    break;
                }
                this->set_alert(Conf::SET_END_TEXT);
                this->waiting_for_end = true;
                break;
            case 15:
                if(!this->world->is_start_set){
                    this->set_warning(Conf::SET_START);
                    break;
                }
                if(!this->world->is_end_set){
                    this->set_warning(Conf::SET_END);
                    break;
                }
                if(!this->is_alg_set){
                    this->set_warning(Conf::SET_ALG);
                    break;
                }
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
                break;
            case 18:
                if(this->world->is_start_set){
                    this->set_warning(Conf::START_ALR_SET);
                    break;
                }
                if(this->waiting_for_end){
                    this->set_warning(Conf::SET_END);
                    break;
                }
                this->set_alert(Conf::SET_START_TEXT);
                this->waiting_for_start = true;
                break;
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
            this->alert_text.setString(msg);
            this->show_alert = true;
        }
    }
    void render_alert(){
        unsigned int alpha = this->frame_alert_showed <= Conf::ALERT_DURATION / 4 ? 255 : map_value(this->frame_alert_showed, Conf::ALERT_DURATION / 4, Conf::ALERT_DURATION - 1, 255, 0);

        size_t padding =  Conf::ALERT_TEXT_SIZE * 2;

        sf::FloatRect textRect = this->alert_text.getLocalBounds();
        this->alert_text.setOrigin(textRect.left + textRect.width/2.0f, textRect.top  + textRect.height/2.0f);
        this->alert_text.setPosition(sf::Vector2f(Conf::WIDTH / 2.0, Conf::HEIGHT/2.0));
        this->alert_text.setFillColor(sf::Color(255, 255, 255, alpha));
        
        float box_width = textRect.width + padding;
        float box_height = (float)padding / 4.0 + textRect.height;

        this->alert_text_box.setSize(sf::Vector2f(box_width, box_height));
        this->alert_text_box.setFillColor(sf::Color(51, 51, 51, alpha));
        this->alert_text_box.setPosition(sf::Vector2f(Conf::WIDTH / 2 - box_width / 2, Conf::HEIGHT / 2 - box_height / 2));

        this->window->draw(this->alert_text_box);
        this->window->draw(this->alert_text);
    }
    bool is_warning_finished(){
        return frame_warning_showed >= Conf::WARNING_DURATION;
    }
    void set_warning(std::string msg){
        if(!this->show_warning){
            this->warning_text.setString(msg);
            this->show_warning = true;
        }
    }
    void render_warning(){
        unsigned int alpha = this->frame_warning_showed <= Conf::WARNING_DURATION / 4 ? 255 : map_value(this->frame_warning_showed, Conf::WARNING_DURATION / 4, Conf::WARNING_DURATION - 1, 255, 0);

        size_t margin_bottom = Conf::WARNING_TEXT_SIZE;
        size_t padding =  Conf::WARNING_TEXT_SIZE * 2;

        sf::FloatRect textRect = this->warning_text.getLocalBounds();
        
        this->warning_text.setOrigin(textRect.left + textRect.width/2.0f, textRect.top  + textRect.height / 2.0f);
        this->warning_text.setPosition(sf::Vector2f(Conf::WIDTH / 2.0, Conf::HEIGHT - margin_bottom));
        this->warning_text.setFillColor(sf::Color(0, 0, 0, alpha));
        
        float box_width = textRect.width + padding;
        float box_height = (float)padding / 4.0 + textRect.height;
        
        this->warning_text_box.setSize(sf::Vector2f(box_width, box_height));
        this->warning_text_box.setFillColor(sf::Color(255, 204, 0, alpha));
        this->warning_text_box.setPosition(sf::Vector2f(Conf::WIDTH / 2 - box_width / 2, Conf::HEIGHT - (box_height / 2 + margin_bottom)));

        this->window->draw(this->warning_text_box);
        this->window->draw(this->warning_text);
    }
};