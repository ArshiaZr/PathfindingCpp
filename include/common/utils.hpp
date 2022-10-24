#include <SFML/Graphics.hpp>

bool is_valid(int width, int height, int i, int j){
    return i < height && i >= 0 && j < width && j >= 0;
}