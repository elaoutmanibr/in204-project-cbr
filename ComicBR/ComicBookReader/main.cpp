
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
    //the path to the file
    TextBox txtbx = TextBox(1000,200,"enter path:");
    std::string path = txtbx.get_text();
    if (!path.compare("none")) return EXIT_FAILURE;
    //archive
    Archive arch = Archive();
    while(!arch.loadArchivedFiles(path)){
        TextBox txtbx = TextBox(1000,200,"Try again:");
        std::string path = txtbx.get_text();
        std::cout<<path<<"\n";
        if (!path.compare("none")) return EXIT_FAILURE;
    }
    
    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
    auto height = desktop.height;
    auto width = desktop.width;
    //int height = 1200;
    
   
    // Create the main window
    sf::RenderWindow window(sf::VideoMode(sf::VideoMode(width, height)), "Comic Book Reader");
    //std::cout<<resourcePath()<<"\n";
    sf::Image icon;
    if (!icon.loadFromFile(resourcePath()+"icon.png")) {
        return EXIT_FAILURE;
    }
    
    float window_y = (float)window.getSize().y;
    float window_x = (float)window.getSize().x;
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
    
    //Buttons
    std::vector<Button> buttons;
    Button prv_pg_btn = Button(0, window_y-100, window_x/8-10, 100, (std::string)"previous");
    Button nxt_pg_btn = Button(width/8, window_y-100, window_x/8-10, 100, (std::string)"next");
    Button zm_in_btn = Button(width/4, window_y-100, window_x/8-10, 100, (std::string)"zoom in");
    Button zm_out_btn = Button(3*window_x/8, window_y-100, window_x/8-10, 100, (std::string)"zoom out");
    Button one_two_btn = Button(window_x/2, window_y-100, window_x/8-10, 100, (std::string)"One/Two");
    Button go_to_btn = Button(5*window_x/8, window_y-100, window_x/8-10, 100, (std::string)"go to");
    Button sv_to_btn = Button(6*window_x/8, window_y-100, window_x/8-10, 100, (std::string)"save to");
    Button open_btn = Button(7*window_x/8, window_y-100, window_x/8, 100, (std::string)"open");
    buttons.insert(buttons.end(),{prv_pg_btn,nxt_pg_btn,zm_in_btn,zm_out_btn, one_two_btn, go_to_btn, sv_to_btn, open_btn});
    
    //Font
    sf::Font font;
    if (!font.loadFromFile(resourcePath() +"sansation.ttf")) {
        return EXIT_FAILURE;
    }
   
    
    
    //mode d'affichage
    int mode = 1;
    //current page
    int page = 1;
    //zoom
    int zoom = 1; //x1 x2 ou x4
    int x_nav = 0;
    int y_nav = 0;
    
    //la Cache
    CACHE cache;
    cache.load(page,arch);
    
    sf::Texture texture_odd;
    sf::Texture texture_even;
    
    sf::Sprite sprite_odd;
    sf::Sprite sprite_even;
    
    // Start the loop
    while (window.isOpen())
    {
    
        
        
        int oldpage = 0;
        // Process events
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Close window: exit
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::KeyPressed){
            // Escape pressed: exit
                if (event.key.code == sf::Keyboard::Escape) {
                window.close();
                }
            
                if (event.key.code == sf::Keyboard::Right) {
                    if(zoom==1)page+=1;//+(mode-1);
                    else x_nav-=100;
                //texture.load_texture(mode, cache, page);
                }
            
                if (event.key.code == sf::Keyboard::Left) {
                    if(zoom==1)page-=1;//+(mode-1);
                    else x_nav+=100;
                    //texture.load_texture(mode, cache, page);
                }
                if (event.key.code == sf::Keyboard::Up) {
                    if(zoom==1)page-=1;//+(mode-1);
                    else y_nav+=100;
                }
                if (event.key.code == sf::Keyboard::Down) {
                    if(zoom==1)page+=1;//+(mode-1);
                    else y_nav-=100;
                }
            }
            //mouse events
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left){
                if (nxt_pg_btn.is_pressed(event.mouseButton.x, event.mouseButton.y)){
                    page+=1;
                    //texture.load_texture(mode, cache, page);
                }
                if (prv_pg_btn.is_pressed(event.mouseButton.x, event.mouseButton.y)){
                    page-=1;
                    //texture.load_texture(mode, cache, page);
                }
                if (go_to_btn.is_pressed(event.mouseButton.x, event.mouseButton.y)){
                    TextBox txtbx = TextBox(500,200,"go to page:");
                    std::string npage = txtbx.get_text();
                    if (npage.compare("none")){
                        page = std::stoi(npage);
                    }
                    //texture.load_texture(mode, cache, page);
                }
                if (open_btn.is_pressed(event.mouseButton.x, event.mouseButton.y)){
                    TextBox txtbx = TextBox(1000,200,"enter path:");
                    std::string npath = txtbx.get_text();
                    if (npath.compare("none")){
                        path = npath;
                        arch.loadArchivedFiles(path);
                        page=1;
                        mode=1;
                        x_nav = 0;
                        y_nav = 0;
                        cache.load(page,arch);
                    }
                    //texture.load_texture(mode, cache, page);
                }
                
                if (sv_to_btn.is_pressed(event.mouseButton.x, event.mouseButton.y)){
                    TextBox txtbx = TextBox(1000,200,"enter path/Name:");
                    std::string spath = txtbx.get_text();
                    cv::Mat image;
                    arch.loadOneImage(page,image);
                    
                    imwrite(spath, image);
                    
                    
                    
                }
                
                if (one_two_btn.is_pressed(event.mouseButton.x, event.mouseButton.y)){
                    mode = ((mode)%2)+1;
                }
                if (zm_in_btn.is_pressed(event.mouseButton.x, event.mouseButton.y)){
                    zoom += 1;
                    if (zoom>3) zoom = 3;
                    //texture.load_texture(mode, cache, page);
                }
                if (zm_out_btn.is_pressed(event.mouseButton.x, event.mouseButton.y)){
                    zoom -= 1;
                    if (zoom<1) zoom = 1;
                }
            }
            
            if (page<1) page = 1;
            if (page>arch.getPageNumTotal()) page = arch.getPageNumTotal();
            
            // Clear screen
            window.clear();

            // Draw the sprite
            window.draw(sprite_odd);
            if (mode == 2) window.draw(sprite_even);
            
            sf::Text text;
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
        
        // Load a sprite to display
        if (oldpage!=page){
            cache.load(page,arch);
            if (mode==1) texture_odd.loadFromImage(cache.getpage(page));
            if (mode == 2) {
                int odd = 2*int((page+1)/2)-1;
                int even = odd + 1;
                texture_odd.loadFromImage(cache.getpage(odd));
                texture_even.loadFromImage(cache.getpage(even));
            }
            oldpage=page;
        }
        sprite_odd = sf::Sprite(texture_odd);
        if (mode == 2){
            sprite_even = sf::Sprite(texture_even);
        }
        
        float scale2 = (11/12.f)*window_y/(float)cache.getpage(page).getSize().y;
        if (mode == 1) {
            sprite_odd.setScale(zoom*scale2,zoom*scale2);
            if(zoom!=1) sprite_odd.move(x_nav,y_nav);
        }
        if (mode == 2) {
            sprite_even.setScale(scale2,scale2);
            sprite_odd.setScale(scale2,scale2);
        }
        if (mode == 1) sprite_odd.move(window_x/2-sprite_odd.getGlobalBounds().width/2.f,0);
        if (mode == 2){
            sprite_odd.move(window_x/4-sprite_odd.getGlobalBounds().width/2.f,0);
            sprite_even.move(window_x*3/4-sprite_even.getGlobalBounds().width/2.f,0);
        }
        
        }
    }
    
    //cache.clear();
    return EXIT_SUCCESS;
    
}
