//
//  window.hpp
//  ComicBookReader
//
//  Created by Youssef Ben Cheikh on 29/1/2022.
//  Copyright © 2022 Youssef Ben Cheikh. All rights reserved.
//

#ifndef window_hpp
#define window_hpp
#include "ResourcePath.hpp"
#include <stdio.h>
#include <SFML/Graphics.hpp>
#include <iostream>
class Button
{
private:
    sf::RectangleShape shape;
    sf::Text text;
    
public:
    Button(float x, float y, float width, float height, std::string text);
    ~Button(){};
    void render(sf::RenderWindow target);
    bool is_pressed(float x, float y);
    sf::RectangleShape get_shape(){return shape;};
    sf::Text get_text(){return text;};
    void set_text(std::string ntext);
    
   
};




#endif /* window_hpp */
