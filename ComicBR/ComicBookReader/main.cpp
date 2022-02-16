
#include "ResourcePath.hpp"
#include <SFML/Graphics.hpp>
#include "Cache.hpp"
#include <string>
#include "Archive.hpp"
#include "Window.hpp"
#include <vector>

using namespace std;
using namespace cv;

int main(int argc, char * argv[])
{
    std::string path;
    Archive arch = Archive();
    
    //the path to the file
        TextBox txtbx = TextBox(1000,200,"enter path:");
        path = txtbx.get_text();
        if (!path.compare("none")) return EXIT_FAILURE;
    
    // load the file as Archive object
        
        while(!arch.loadArchivedFiles(path)){
            TextBox txtbx = TextBox(1000,200,"Try again:");
            path = txtbx.get_text();
            if (!path.compare("none")) return EXIT_FAILURE;
        }
   
    
    // Variable height and weight to fit all screens
    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
    auto height = desktop.height;
    auto width = desktop.width;
    
   
    // Create the main window
    sf::RenderWindow window(sf::VideoMode(sf::VideoMode(width, height)), "Comic Book Reader");
    sf::Image icon;
    if (!icon.loadFromFile(resourcePath()+"icon.png")) {
        return EXIT_FAILURE;
    }
    
    float window_y = (float)window.getSize().y;
    float window_x = (float)window.getSize().x;
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
    
    //Buttons
    std::vector<Button> buttons;
    Button prv_pg_btn = Button(0, 17*window_y/18, window_x/8-10, window_y/18, (std::string)"previous");
    Button nxt_pg_btn = Button(width/8, 17*window_y/18, window_x/8-10, window_y/18, (std::string)"next");
    Button zm_in_btn = Button(width/4, 17*window_y/18, window_x/8-10, window_y/18, (std::string)"zoom in");
    Button zm_out_btn = Button(3*window_x/8, 17*window_y/18, window_x/8-10, window_y/18, (std::string)"zoom out");
    Button one_two_btn = Button(window_x/2, 17*window_y/18, window_x/8-10, window_y/18, (std::string)"One/Two");
    Button go_to_btn = Button(5*window_x/8, 17*window_y/18, window_x/8-10, window_y/18, (std::string)"go to");
    Button sv_to_btn = Button(6*window_x/8, 17*window_y/18, window_x/8-10, window_y/18, (std::string)"save to");
    Button open_btn = Button(7*window_x/8, 17*window_y/18, window_x/8, window_y/18, (std::string)"open");
    buttons.insert(buttons.end(),{prv_pg_btn,nxt_pg_btn,zm_in_btn,zm_out_btn, one_two_btn, go_to_btn, sv_to_btn, open_btn});
    
    //Font
    sf::Font font;
    if (!font.loadFromFile(resourcePath() +"sansation.ttf")) {
        return EXIT_FAILURE;
    }
   
    
    
    //Display mode = 1 : One page ; =2 : Two pages
    int mode = 1;
    
    int page = 1; //current page

    int zoom = 1; //x1 x2 ou x4

    // coordonates of the center of the window
    int x_nav = 0; 
    int y_nav = 0;
    
    //Cache
    Cache cache;
    cache.load(page,arch); // load the current page, the next one and the previous one in the cache 


    //
    sf::Texture texture_1;
    sf::Texture texture_2;
    
    sf::Sprite sprite_1;
    sf::Sprite sprite_2;



    
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
                    if(zoom==1)page+=1;
                    else x_nav-=100;
                }
            
                if (event.key.code == sf::Keyboard::Left) {
                    if(zoom==1)page-=1;
                    else x_nav+=100;
                }
                if (event.key.code == sf::Keyboard::Up) {
                    if(zoom==1)page-=1;
                    else y_nav+=100;
                }
                if (event.key.code == sf::Keyboard::Down) {
                    if(zoom==1)page+=1;
                    else y_nav-=100;
                }
            }

            //mouse events
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left){
                if (nxt_pg_btn.is_pressed(event.mouseButton.x, event.mouseButton.y)){
                    page+=1;
                }
                else if (prv_pg_btn.is_pressed(event.mouseButton.x, event.mouseButton.y)){
                    page-=1;
                }
                else if (go_to_btn.is_pressed(event.mouseButton.x, event.mouseButton.y)){
                    TextBox txtbx = TextBox(500,200,"go to page:");
                    std::string npage = txtbx.get_text();
                    if (npage.compare("none")){
                        page = std::stoi(npage);
                    }
                }
                else if (open_btn.is_pressed(event.mouseButton.x, event.mouseButton.y)){
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
                }
                
                else if (sv_to_btn.is_pressed(event.mouseButton.x, event.mouseButton.y)){
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
            window.draw(sprite_1);
            if (mode == 2) window.draw(sprite_2);
            
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
            if (mode==1) texture_1.loadFromImage(cache.getpage(page));
            if (mode == 2) {
                int odd = 2*int((page+1)/2)-1;
                int even = odd + 1;
                texture_1.loadFromImage(cache.getpage(odd));
                texture_2.loadFromImage(cache.getpage(even));
            }
            oldpage=page;
        }
        sprite_1 = sf::Sprite(texture_1);
        if (mode == 2){
            sprite_2 = sf::Sprite(texture_2);
        }
        
        float scale2 = (11/12.f)*window_y/(float)cache.getpage(page).getSize().y;
        if (mode == 1) {
            sprite_1.setScale(zoom*scale2,zoom*scale2);
            if(zoom!=1) sprite_1.move(x_nav,y_nav);
        }
        if (mode == 2) {
            sprite_2.setScale(scale2,scale2);
            sprite_1.setScale(scale2,scale2);
        }
        if (mode == 1) sprite_1.move(window_x/2-sprite_1.getGlobalBounds().width/2.f,0);
        if (mode == 2){
            sprite_1.move(window_x/4-sprite_1.getGlobalBounds().width/2.f,0);
            sprite_2.move(window_x*3/4-sprite_2.getGlobalBounds().width/2.f,0);
        }
        
        }
    }
    
    //cache.clear();
    return EXIT_SUCCESS;
    
}
