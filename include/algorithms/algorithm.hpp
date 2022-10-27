#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <queue>
#include <string>

#include "bfs.hpp"
#include "dijkstra.hpp"

struct PathFinding{
    std::priority_queue<std::pair<int, std::pair<int, int>>> q_weighted;
    std::queue<std::pair<int, int>> q;
    std::vector<std::vector<bool>> visited;
    std::vector<std::vector<std::pair<int, int>>> path;

    void init(){
        this->visited = std::vector<std::vector<bool>>(Conf::HEIGHT, std::vector<bool>(Conf::WIDTH, false));
        this->path = std::vector<std::vector<std::pair<int, int>>>(Conf::HEIGHT, std::vector<std::pair<int, int>>(Conf::WIDTH));
        clear_queue(this->q);
        clear_queue(this->q_weighted);
        
        //this->visited[Conf::START_Y][Conf::START_X] = true;
    }

    void set_starting_point(World& world){
        this->q.push(std::make_pair(world.start.second, world.start.first));
        this->q_weighted.push(std::make_pair(0 , std::make_pair(world.start.second, world.start.first)));
    }

    void clear_queue(std::queue<std::pair<int, int>> &q){
        std::queue<std::pair<int, int>> empty;
        std::swap(q, empty);
    }
    void clear_queue(std::priority_queue<std::pair<int, std::pair<int, int>>> &q){
        std::priority_queue<std::pair<int, std::pair<int, int>>> empty;
        std::swap(q, empty);
    }
    void run(std::string alg, World& world, bool& found, bool& could_not_find){
        if(alg == Conf::BFS){
            if(bfs(world, this->q, this->visited, this->path, could_not_find)){
                found = true;
            }
        }else if(alg == Conf::DIJKSTRA){
            if(djkstra(world, this->q_weighted, this->visited, this->path, could_not_find)){
                found = true;
            }
        }
    }
};