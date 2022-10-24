#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

template<typename T>
struct DefaultConf
{
    static sf::Font FONT;
    const static size_t WIDTH, HEIGHT, CELL_WIDTH, FRAMERATELIMIT, START_X, START_Y, END_X, END_Y;
    const static sf::Color OUTLINE_COLOR, CELL_COLOR, WALL_COLOR, TEXT_COLOR, START_COLOR, END_COLOR, PATH_COLOR, VISITED_COLOR;
    const static std::string TITLE;
    const static std::string BFS, DIJKSTRA;
    
};
template<typename T>
sf::Font DefaultConf<T>::FONT;
template<typename T>
const size_t DefaultConf<T>::WIDTH = 1000;
template<typename T>
const size_t DefaultConf<T>::HEIGHT = 500;
template<typename T>
const size_t DefaultConf<T>::CELL_WIDTH = 50;
template<typename T>
const size_t DefaultConf<T>::FRAMERATELIMIT = 30;
template<typename T>
const size_t DefaultConf<T>::START_X = 0;
template<typename T>
const size_t DefaultConf<T>::START_Y = 0;
template<typename T>
const size_t DefaultConf<T>::END_X = WIDTH/CELL_WIDTH - 1;
template<typename T>
const size_t DefaultConf<T>::END_Y = HEIGHT/CELL_WIDTH - 1;
template<typename T>
const sf::Color DefaultConf<T>::OUTLINE_COLOR = sf::Color::Black;
template<typename T>
const sf::Color DefaultConf<T>::CELL_COLOR = sf::Color::White;
template<typename T>
const sf::Color DefaultConf<T>::WALL_COLOR = sf::Color(211, 211, 211);
template<typename T>
const sf::Color DefaultConf<T>::TEXT_COLOR = sf::Color::Black;
template<typename T>
const sf::Color DefaultConf<T>::START_COLOR = sf::Color(0, 255, 0);
template<typename T>
const sf::Color DefaultConf<T>::END_COLOR = sf::Color(255, 0, 0);
template<typename T>
const sf::Color DefaultConf<T>::PATH_COLOR = sf::Color(255, 255, 0);
template<typename T>
const sf::Color DefaultConf<T>::VISITED_COLOR = sf::Color(0, 0, 255);
template<typename T>
const std::string DefaultConf<T>::TITLE = "Path Finding";
template<typename T>
const std::string DefaultConf<T>::BFS = "bfs";
template<typename T>
const std::string DefaultConf<T>::DIJKSTRA = "dijkstra";

using Conf = DefaultConf<int>;