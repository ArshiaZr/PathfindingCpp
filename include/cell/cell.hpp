#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
// #include "../config.hpp"
#include <iostream>
#include <string>

#pragma once
struct Cell
{
   sf::RectangleShape shape;
   sf::Text title;
   int weight = 1;
   
   Cell(int x, int y, int width, int weight){
      this->shape.setPosition(sf::Vector2f(x, y));
      this->weight = weight;
      this->shape.setFillColor(Conf::CELL_COLOR);
      this->shape.setSize(sf::Vector2f(width, width));
      this->shape.setOutlineColor(Conf::OUTLINE_COLOR);
      this->shape.setOutlineThickness(1);
      this->title.setPosition(sf::Vector2f(x, y));
      this->title.setFillColor(Conf::TEXT_COLOR);
      this->title.setCharacterSize(width);
      this->title.setFont(Conf::FONT);
   }
   void change_color(const sf::Color color){
      this->shape.setFillColor(color);
   }
   void update_color(){
      if(this->weight == -2){
         this->shape.setFillColor(Conf::START_COLOR);
      }else if(this->weight == -3){
         this->shape.setFillColor(Conf::END_COLOR);
      }else if(this->weight == -1){
         this->shape.setFillColor(Conf::WALL_COLOR);
      }else{
         this->shape.setFillColor(Conf::CELL_COLOR);
      }
   }
   void set_weight(int weight){
      this->weight = weight;
   }
};