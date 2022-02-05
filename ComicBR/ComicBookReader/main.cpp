
#include "ResourcePath.hpp"
#include <SFML/Graphics.hpp>
#include "display.hpp"
#include <string>
#include <filesystem>
#include "archivereader.hpp"
#include "window.hpp"
#include <vector>

using namespace std;
using namespace cv;

int main(int, char const**)
{

    // Create the main window
    sf::RenderWindow window(sf::VideoMode(sf::VideoMode(1600, 1200)), "Comic Book Reader");
    
    sf::Image icon;
    if (!icon.loadFromFile(resourcePath()+"icon.png")) {
        return EXIT_FAILURE;
    }
    
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
    
    //Buttons
    std::vector<Button> buttons;
    Button prv_pg_btn = Button(0, 1100, 190, 100, (std::string)"previous");
    Button nxt_pg_btn = Button(200, 1100, 190, 100, (std::string)"next");
    Button zm_in_btn = Button(400, 1100, 190, 100, (std::string)"zoom in");
    Button zm_out_btn = Button(600, 1100, 190, 100, (std::string)"zoom out");
    Button one_two_btn = Button(800, 1100, 190, 100, (std::string)"One/Two");
    Button go_to_btn = Button(1000, 1100, 190, 100, (std::string)"go to");
    Button sv_to_btn = Button(1200, 1100, 190, 100, (std::string)"save to");
    Button open_btn = Button(1400, 1100, 200, 100, (std::string)"open");
    buttons.insert(buttons.end(),{prv_pg_btn,nxt_pg_btn,zm_in_btn,zm_out_btn, one_two_btn, go_to_btn, sv_to_btn, open_btn});
    
    //Font
    sf::Font font;
    if (!font.loadFromFile(resourcePath() +"sansation.ttf")) {
        return EXIT_FAILURE;
    }
    //Affichage des buttons
    sf::Text text;
    for (Button button:buttons){
        window.draw(button.get_shape());
        text = button.get_text();
        text.setFont(font);
        window.draw(text);
    }
    
    
    
    
    //the path to the file
    std::string path = "Users/youssefbencheikh/Desktop/Archive.cbz";
    Archive arch = Archive();
    arch.loadArchivedFiles(path);
    cv::Mat a_image;
    arch.loadOneImage(2,a_image);
    
    
    //current page
    int page = 1;
    //la Cache
    CACHE cache(10);
    
    cache.load(page,arch);
    cache.load(2,arch);
    cache.load(3,arch);
    
    
    sf::Texture texture;
    
    // Start the loop
    while (window.isOpen())
    {
        
        // Process events
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Close window: exit
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            // Escape pressed: exit
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                window.close();
            }
            
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Right) {
                page+=1;
                if (!texture.loadFromImage(cache.getpage(page))) {
                    return EXIT_FAILURE;
                }
            }
            
                if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Left) {
                    page+=-1;
                    if (!texture.loadFromImage(cache.getpage(page))) {
                        return EXIT_FAILURE;
                    }
                }
            //mouse events
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left){
                if (nxt_pg_btn.is_pressed(event.mouseButton.x, event.mouseButton.y)){
                    page+=1;
                    if (!texture.loadFromImage(cache.getpage(page))) {
                        return EXIT_FAILURE;
                    }
                }
                if (prv_pg_btn.is_pressed(event.mouseButton.x, event.mouseButton.y)){
                    page-=1;
                    if (!texture.loadFromImage(cache.getpage(page))) {
                        return EXIT_FAILURE;
                    }
                }
                if (go_to_btn.is_pressed(event.mouseButton.x, event.mouseButton.y)){
                    TextBox txtbx = TextBox(500,200,"go to page:");
                    std::string npage = txtbx.get_text();
                    if (npage.compare("none")){
                        page = std::stoi(npage);
                    }
                    if (!texture.loadFromImage(cache.getpage(page))) {
                        return EXIT_FAILURE;
                    }
                }
                if (open_btn.is_pressed(event.mouseButton.x, event.mouseButton.y)){
                    TextBox txtbx = TextBox(1000,200,"enter path:");
                    std::string npath = txtbx.get_text();
                    if (npath.compare("none")){
                        path = npath;
                        arch.loadArchivedFiles(path);
                        page=1;
                        cache.load(page,arch);
                    }
                    if (!texture.loadFromImage(cache.getpage(page))) {
                        return EXIT_FAILURE;
                    }
                }
            }
        }
        
        // Load a sprite to display
        
        texture.loadFromImage(cache.getpage(page));
        
        sf::Sprite sprite(texture);
        float scale2 = (11/12.f)*(float)window.getSize().y/(float)cache.getpage(page).getSize().y;
        sprite.setScale(scale2,scale2);
        sprite.move(800-sprite.getGlobalBounds().width/2.f,0);
        // Clear screen
        window.clear();

        // Draw the sprite
        window.draw(sprite);
        
        sf::Text text("Welcome to ComicBookReader, type the path to your CB, or choose one among the recent:", font, 50);
        text.setFillColor(sf::Color::White);
        // Draw the string
        //window.draw(text);
        buttons[5].set_text(std::to_string(page)+"/"+std::to_string(arch.getPageNumTotal()));
        for (Button button:buttons){
        window.draw(button.get_shape());
        text = button.get_text();
        text.setFont(font);
        window.draw(text);
        }
        // Update the window
        window.display();
    }
    
    //cache.clear();
    return EXIT_SUCCESS;
    
}
