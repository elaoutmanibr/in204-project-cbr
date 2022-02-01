//
//  window.cpp
//  ComicBookReader
//
//  Created by Youssef Ben Cheikh on 29/1/2022.
//  Copyright © 2022 Youssef Ben Cheikh. All rights reserved.
//

#include "window.hpp"

Button::Button(float x, float y, float width, float height, std::string text){
    this->shape.setPosition(sf::Vector2f(x,y));
    this->shape.setSize(sf::Vector2f(width,height));
    this->shape.setFillColor(sf::Color::Cyan);
    this->text.setString(text);
    this->text.setFillColor(sf::Color::Black);
    this->text.setCharacterSize(30);
    sf::Font font;
    font.loadFromFile(resourcePath() +"sansation.ttf");
    this->text.setFont(font);
    this->text.setPosition(
                           x+width/2.f-this->text.getGlobalBounds().width/2.f,
                           y+height/2.f-this->text.getGlobalBounds().height/2.f);
}

void Button::render(sf::RenderWindow target){
    target.draw(this->shape);
}

bool Button::is_pressed(float x, float y){
    sf::Rect<float> rect = sf::Rect<float>(shape.getPosition(),shape.getSize());
    return rect.contains(x,y);
}
void Button::set_text(std::string ntext){
    this->text.setString(ntext);
}
