#pragma once

#include "../environment/world.hpp"
#include "../common/utils.hpp"

int cm[4] = {1, -1, 0, 0};
int rm[4] = {0, 0, 1, -1};

bool bfs(World& world, std::queue<std::pair<int, int>>& q, std::vector<std::vector<bool>>& visited, std::vector<std::vector<std::pair<int, int>>>& path, bool &could_not_find){
    int size = q.size();
    if(size == 0){
        could_not_find = true;
        return false;
    }
    for(int i = 0; i < size; i++){
        std::pair<int, int> pos = q.front();
        q.pop();
        
        for(int j = 0; j < 4; j++){
            int x = cm[j] + pos.second;
            int y = rm[j] + pos.first;
            if(is_valid(Conf::WIDTH/Conf::CELL_WIDTH, Conf::HEIGHT/Conf::CELL_WIDTH, y, x)){
                if(!visited[y][x] && !world.is_wall(std::make_pair(x, y))){
                    visited[y][x] = true;
                    path[y][x] = pos;
                    if(world.is_end(std::make_pair(y, x))){
                        std::vector<std::pair<int, int>> to_change;
                        std::pair<int, int> cur = path[y][x];
                        
                        while(!world.is_start(std::make_pair(cur.first, cur.second))){
                            world.grid[cur.first][cur.second]->change_color(Conf::PATH_COLOR);
                            cur = path[cur.first][cur.second];
                        }
                        return true;
                    }
                    if(!world.is_start(std::make_pair(y, x))){
                        world.grid[y][x]->change_color(Conf::VISITED_COLOR);
                    }
                    
                    q.push(std::make_pair(y, x));
                }
            }
        }
    }
    return false;
}