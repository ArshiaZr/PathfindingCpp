#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <queue>
#include <unordered_set>
#include <string>

#define TITLE "Path Finding"
#define WIDTH 500
#define HEIGHT 500
#define CELL_WIDTH 50
#define START_X 0
#define START_Y 0
#define END_X 9
#define END_Y 9
#define FRAMERATELIMIT 30

int cm[4] = {1, -1, 0, 0};
int rm[4] = {0, 0, 1, -1};

void init(sf::RenderWindow& window, std::vector<std::vector<sf::RectangleShape>>& grid, std::vector<std::vector<sf::Text>>& weight_titles, std::vector<std::vector<int>>& weights, std::queue<std::pair<int, int>>& q, std::priority_queue<std::pair<int, std::pair<int, int>>>& q_weight,std::vector<std::vector<bool>>& visited , std::vector<int> start, std::vector<int> end, int limit, int width, int height, int cell_width, sf::Font& font);
std::pair<int, int> get_pos(sf::RenderWindow& window, int cell_width);
bool is_valid(int width_size, int height_size, int i, int j);
void draw_grid(std::vector<std::vector<sf::RectangleShape>>& grid, std::vector<std::vector<int>>& weights, std::vector<std::vector<sf::Text>>& weight_titles, sf::RenderWindow& window, int cell_width);
void change_color(std::vector<std::vector<sf::RectangleShape>>& grid, int i, int j, std::vector<int> color);
bool bfs(std::vector<std::vector<sf::RectangleShape>>& grid, std::queue<std::pair<int, int>>& q, std::vector<std::vector<bool>>& visited, std::vector<std::vector<std::pair<int, int>>>& path, std::pair<int, int> windowSize, std::pair<int, int> target, std::pair<int, int> start, bool& found);
bool djkstra(std::vector<std::vector<sf::RectangleShape>>& grid, std::vector<std::vector<int>>& weights, std::priority_queue<std::pair<int, std::pair<int, int>>>& q, std::vector<std::vector<bool>>& visited, std::vector<std::vector<std::pair<int, int>>>& path, std::pair<int, int> windowSize, std::pair<int, int> target, std::pair<int, int> start, bool& found);

int main()
{
    int width_size = WIDTH/CELL_WIDTH;
    int height_size = HEIGHT/CELL_WIDTH;
    bool found = false;
    bool runing = false;
    sf::Font font;
    if (!font.loadFromFile("arial.ttf")){
        std::cout << "Font not loaded" << std::endl;
    }
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), TITLE);
    std::vector<std::vector<sf::RectangleShape>> grid(height_size, std::vector<sf::RectangleShape>(width_size));
    std::vector<std::vector<sf::Text>> weight_titles(height_size, std::vector<sf::Text>(width_size));
    std::queue<std::pair<int, int>> q;
    std::priority_queue<std::pair<int, std::pair<int, int>>> q_weight;
    std::vector<std::vector<bool>> visited(height_size, std::vector<bool>(width_size, false));
    std::vector<std::vector<std::pair<int, int>>> path(height_size, std::vector<std::pair<int, int>>(width_size));
    std::vector<std::vector<int>> weights(height_size, std::vector<int>(width_size, -1));
    
    init(window, grid, weight_titles, weights, q, q_weight, visited, {START_X, START_Y}, {END_X, END_Y}, FRAMERATELIMIT, WIDTH, HEIGHT, CELL_WIDTH, font);
    
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if(event.type == sf::Event::MouseButtonPressed){
                std::pair<int, int> pos = get_pos(window, CELL_WIDTH);
                if(event.mouseButton.button == sf::Mouse::Right){
                    if(is_valid(WIDTH, HEIGHT, pos.first, pos.second)){
                        if(weights[pos.first][pos.second] != 1)
                            weights[pos.first][pos.second] -= 1;
                    }
                }
                if(event.mouseButton.button == sf::Mouse::Left){
                    if(is_valid(WIDTH, HEIGHT, pos.first, pos.second)){
                        weights[pos.first][pos.second] = 1;
                    }
                }
                
            }
            if(event.type == sf::Event::KeyPressed){
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::P)){
                    runing = runing ? false : true;
                }
            }
            
        }

        window.clear();
        draw_grid(grid, weights, weight_titles, window, CELL_WIDTH);
        if(!found && runing){
            // if(!bfs(grid, q, visited, path, std::make_pair(width_size, height_size), std::make_pair(END_X, END_Y), std::make_pair(START_X, START_Y), found)){
            //     runing = false;
            // }
            if(!djkstra(grid, weights, q_weight, visited, path, std::make_pair(width_size, height_size), std::make_pair(END_X, END_Y), std::make_pair(START_X, START_Y), found)){
                runing = false;
            }
        }
        window.display();
    }

    return 0;
}

void init(sf::RenderWindow& window, std::vector<std::vector<sf::RectangleShape>>& grid, std::vector<std::vector<sf::Text>>& weight_titles, std::vector<std::vector<int>>& weights, std::queue<std::pair<int, int>>& q, std::priority_queue<std::pair<int, std::pair<int, int>>>& q_weight,std::vector<std::vector<bool>>& visited , std::vector<int> start, std::vector<int> end, int limit, int width, int height, int cell_width, sf::Font& font){
    window.setFramerateLimit(limit);
    for(int i = 0; i < grid.size(); i++){
        for(int j = 0; j < grid[0].size(); j++){
            grid[i][j].setSize(sf::Vector2f(cell_width, cell_width));
            grid[i][j].setPosition(sf::Vector2f(j * cell_width, i* cell_width));
            grid[i][j].setOutlineColor(sf::Color(0, 0, 0));
            grid[i][j].setOutlineThickness(1);
            weight_titles[i][j].setFont(font);
            weight_titles[i][j].setPosition(sf::Vector2f(j * cell_width, i* cell_width));
            weight_titles[i][j].setFillColor(sf::Color::Black);
            weight_titles[i][j].setCharacterSize(cell_width);
        }
    }
    change_color(grid, start[1], start[0], {255, 0, 0});
    change_color(grid, end[1], end[0], {0, 255, 0});
    q.push(std::make_pair(start[1], start[0]));
    q_weight.push(std::make_pair(weights[start[1]][start[0]], std::make_pair(start[1], start[0])));
    // visited[start[1]][start[0]] = true;
}

std::pair<int, int> get_pos(sf::RenderWindow& window, int cell_width){
    sf::Vector2i pos = sf::Mouse::getPosition(window);
    return std::make_pair(pos.y / cell_width, pos.x / cell_width);
}

void draw_grid(std::vector<std::vector<sf::RectangleShape>>& grid, std::vector<std::vector<int>>& weights, std::vector<std::vector<sf::Text>>& weight_titles, sf::RenderWindow& window, int cell_width){
    
    for(int i = 0; i < grid.size(); i++){
        for(int j = 0; j < grid[0].size(); j++){
            window.draw(grid[i][j]);
            if(weights[i][j] * -1 != 1 && weights[i][j] != 1){
                weight_titles[i][j].setString(std::to_string(weights[i][j] * -1));;
                window.draw(weight_titles[i][j]);
            }
            if(weights[i][j] == 1){
                change_color(grid, i, j, {211,211,211});
            }
        }
    }
}

void change_color(std::vector<std::vector<sf::RectangleShape>>& grid, int i, int j, std::vector<int> color){
    grid[i][j].setFillColor(sf::Color(color[0], color[1], color[2]));
}

bool is_valid(int width_size, int height_size, int i, int j){
    return i < height_size && i >= 0 && j < width_size && j >= 0;
}

bool bfs(std::vector<std::vector<sf::RectangleShape>>& grid, std::queue<std::pair<int, int>>& q, std::vector<std::vector<bool>>& visited, std::vector<std::vector<std::pair<int, int>>>& path, std::pair<int, int> windowSize, std::pair<int, int> target, std::pair<int, int> start, bool& found){
    int size = q.size();
    if(size == 0){
        return false;
    }
    for(int i = 0; i < size; i++){
        std::pair<int, int> pos = q.front();
        q.pop();

        for(int j = 0; j < 4; j++){
            int x = cm[j] + pos.second;
            int y = rm[j] + pos.first;
            if(is_valid(windowSize.first, windowSize.second, y, x)){
                if(!visited[y][x]){
                    visited[y][x] = true;
                    path[y][x] = pos;
                    if(x == target.first && y == target.second){
                        found = true;
                        std::vector<std::pair<int, int>> to_change;
                        std::pair<int, int> cur = path[y][x];

                        while(cur.first != start.second || cur.second != start.first){
                            change_color(grid, cur.first, cur.second, {255, 255, 0});
                            cur = path[cur.first][cur.second];
                        }
                        
                        return true;
                    }
                    change_color(grid, y, x, {0, 0, 255});
                    
                    q.push(std::make_pair(y, x));
                }
            }
        }
    }
    return true;
}

bool djkstra(std::vector<std::vector<sf::RectangleShape>>& grid, std::vector<std::vector<int>>& weights, std::priority_queue<std::pair<int, std::pair<int, int>>>& q, std::vector<std::vector<bool>>& visited, std::vector<std::vector<std::pair<int, int>>>& path, std::pair<int, int> windowSize, std::pair<int, int> target, std::pair<int, int> start, bool& found){
    int size = q.size();
    if(size == 0){
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
            if(is_valid(windowSize.first, windowSize.second, y, x)){
                if(!visited[y][x] && weights[y][x] != 1){
                    path[y][x] = pos;
                    if(x == target.first && y == target.second){
                        found = true;
                        std::vector<std::pair<int, int>> to_change;
                        std::pair<int, int> cur = path[y][x];

                        while(cur.first != start.second || cur.second != start.first){
                            change_color(grid, cur.first, cur.second, {255, 255, 0});
                            cur = path[cur.first][cur.second];
                        }
                        
                        return true;
                    }
                    change_color(grid, y, x, {0, 0, 255});
                    q.push(std::make_pair(cur_w + weights[y][x], std::make_pair(y, x)));
                }
            }
        }
    }
    return true;
}