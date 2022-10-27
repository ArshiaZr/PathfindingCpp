#pragma once


bool djkstra(World& world, std::priority_queue<std::pair<int, std::pair<int, int>>> &q, std::vector<std::vector<bool>>& visited, std::vector<std::vector<std::pair<int, int>>>& path,bool &could_not_find){
    int size = q.size();
    if(size == 0){
        could_not_find = true;
        return false;
    }
    for(int i = 0; i < size; i++){
        std::pair<int, std::pair<int, int>> cur = q.top();
        q.pop();

        std::pair<int, int> pos = cur.second;

        int cur_w = cur.first;
        if(visited[pos.first][pos.second]){
            continue;
        }
        visited[pos.first][pos.second] = true;

        for(int j = 0; j < 4; j++){
            int x = cm[j] + pos.second;
            int y = rm[j] + pos.first;
            if(is_valid(Conf::WIDTH/Conf::CELL_WIDTH, Conf::HEIGHT/Conf::CELL_WIDTH, y, x)){
                if(!visited[y][x] && world.grid[y][x]->weight != -1){
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
                    world.grid[y][x]->change_color(Conf::VISITED_COLOR);
                    q.push(std::make_pair(cur_w + world.grid[y][x]->weight * -1, std::make_pair(y, x)));
                }
            }
        }
    }
    return false;
}