
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

class TextBox
{
public:
    TextBox(int x, int y, std::string text){
        this->x = x;
        this->y = y;
        this->text = text;
    }
public:
    std::string get_text();
private:
    int x; int y;
    std::string text;;
   
};



#endif /* window_hpp */
