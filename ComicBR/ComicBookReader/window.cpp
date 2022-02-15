
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



std::string TextBox::get_text(){
    sf::Font font;
    font.loadFromFile(resourcePath() +"sansation.ttf");
    sf::RenderWindow gotopagewind(sf::VideoMode(x, y), this->text);
    std::string typed = "";
    while (gotopagewind.isOpen()){
            sf::Event event;
            while (gotopagewind.pollEvent(event))
            {
                // Close window: exit
                if (event.type == sf::Event::Closed) {
                    gotopagewind.close();
                    return (std::string)"none";
                    
                }

                // Escape pressed: exit
                if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                    gotopagewind.close();
                    return (std::string)"none";
                    
                }
                if (event.type == sf::Event::TextEntered) {
                    if (event.text.unicode == '\b'){
                        if(!typed.empty())
                            typed.pop_back();}
                    else if (event.text.unicode == '\n'){
                        //page = std::stoi(npage);
                        gotopagewind.close();
                        return typed;
                    }
                    else if (event.text.unicode && event.text.unicode < 123)
                        typed+=static_cast<char>(event.text.unicode);
                    
                }
            }
            
            sf::Text npg(typed.data(), font, 30);
            npg.setPosition(50.f,50.f);
            gotopagewind.clear();
            gotopagewind.draw(npg);
            // Update the window
            gotopagewind.display();
        }
    return (std::string)"none";
}
