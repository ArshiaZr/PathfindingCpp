#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <queue>
#include <unordered_set>
#include <string>

#include "include/config.hpp"
#include "include/scene.hpp"

int main()
{
    sf::RenderWindow window(sf::VideoMode(Conf::WIDTH, Conf::HEIGHT), Conf::TITLE);
    
    Scene scene = Scene(&window);
    scene.init();
    
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if(event.type == sf::Event::MouseButtonPressed){                
                scene.handle_input(event.key.code * -1 - 1);
            }
            if(event.type == sf::Event::KeyPressed){
                scene.handle_input(event.key.code);
            }
            
        }
        window.clear();
        scene.get_world()->render(window);
        if(scene.show_alert){
            //std::cout << scene.frame_alert_showed << std::endl;
            
            scene.render_alert();
            scene.frame_alert_showed++;
            if(scene.is_alert_finished()){
                scene.show_alert = false;
                scene.frame_alert_showed = 0;
            }
        }
        if(!scene.is_path_found() && !scene.is_paused()){
            if(scene.impossible()){
                //TODO
                continue;
            }
            scene.run_algo();
        }
        window.display();
    }

    return 0;
}
