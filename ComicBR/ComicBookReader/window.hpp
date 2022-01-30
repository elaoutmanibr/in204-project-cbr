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
public:
    sf::RectangleShape shape;
    sf::Text text;
    sf::Color color;
    
public:
    Button(float x, float y, float width, float height, std::string text);
    ~Button(){};
    void render(sf::RenderWindow target);
    
   
    
   
};

#endif /* window_hpp */
