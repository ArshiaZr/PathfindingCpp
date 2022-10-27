#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

template<typename T>
struct DefaultConf
{
    static sf::Font FONT;
    const static size_t WIDTH, HEIGHT, CELL_WIDTH, FRAMERATELIMIT
    , START_X, START_Y, END_X, END_Y, ALERT_DURATION, ALERT_TEXT_SIZE, WARNING_TEXT_SIZE, WARNING_DURATION;
    const static sf::Color OUTLINE_COLOR, CELL_COLOR, WALL_COLOR
    , TEXT_COLOR, START_COLOR, END_COLOR, PATH_COLOR, VISITED_COLOR;
    const static std::string TITLE;
    const static std::string BFS, DIJKSTRA;
    const static std::string PLAY_TEXT, PAUSE_TEXT, RESET_TEXT, CLEAR_TEXT;
    const static std::string ALG_ALR_SET, SET_START, SET_END, SET_ALG, START_ALR_SET, END_ALR_SET, SET_START_TEXT, SET_END_TEXT;
};
template<typename T>
sf::Font DefaultConf<T>::FONT;
template<typename T>
const size_t DefaultConf<T>::WIDTH = 1000;
template<typename T>
const size_t DefaultConf<T>::HEIGHT = 500;
template<typename T>
const size_t DefaultConf<T>::CELL_WIDTH = 10;
template<typename T>
const size_t DefaultConf<T>::FRAMERATELIMIT = 30;
template<typename T>
const size_t DefaultConf<T>::ALERT_DURATION = 1 * 30;
template<typename T>
const size_t DefaultConf<T>::ALERT_TEXT_SIZE = 30;
template<typename T>
const size_t DefaultConf<T>::WARNING_TEXT_SIZE = 15;
template<typename T>
const size_t DefaultConf<T>::WARNING_DURATION = 3 * 30;
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
const std::string DefaultConf<T>::BFS = "Breadth First Search";
template<typename T>
const std::string DefaultConf<T>::DIJKSTRA = "Dijkstra";
template<typename T>
const std::string DefaultConf<T>::PLAY_TEXT = "Play";
template<typename T>
const std::string DefaultConf<T>::PAUSE_TEXT = "Pause";
template<typename T>
const std::string DefaultConf<T>::RESET_TEXT = "Reset";
template<typename T>
const std::string DefaultConf<T>::CLEAR_TEXT = "Clear";
template<typename T>
const std::string DefaultConf<T>::ALG_ALR_SET = "Algorithm is already set. You can rest if you want to change the algorithm";
template<typename T>
const std::string DefaultConf<T>::SET_START = "You should first set start point";
template<typename T>
const std::string DefaultConf<T>::SET_END = "You should first set end point";
template<typename T>
const std::string DefaultConf<T>::SET_ALG = "You should first set algorithm";
template<typename T>
const std::string DefaultConf<T>::START_ALR_SET = "Starting point is already set";
template<typename T>
const std::string DefaultConf<T>::END_ALR_SET = "Ending point is already set";
template<typename T>
const std::string DefaultConf<T>::SET_START_TEXT = "Start";
template<typename T>
const std::string DefaultConf<T>::SET_END_TEXT = "End";
using Conf = DefaultConf<int>;