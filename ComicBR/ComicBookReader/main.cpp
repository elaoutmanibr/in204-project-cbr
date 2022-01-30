
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

/*
    //sf::RenderWindow prewindow(sf::VideoMode(sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height), "Comic Book Reader");
    sf::RenderWindow prewindow(sf::VideoMode(1600, 1200), "Comic Book Reader");
    
    sf::Font font;
    if (!font.loadFromFile(resourcePath() +"sansation.ttf")) {
        return EXIT_FAILURE;
    }
    sf::Text text("Welcome to ComicBookReader, type the path to your CB, or choose one among the recent:", font, 50);
    text.setFillColor(sf::Color::White);
    std::string path("/");
    while (prewindow.isOpen()){
        sf::Event event;
        while (prewindow.pollEvent(event))
        {
            // Close window: exit
            if (event.type == sf::Event::Closed) {
                prewindow.close();
                return EXIT_SUCCESS;
            }

            // Escape pressed: exit
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                prewindow.close();
                return EXIT_SUCCESS;
            }
            if (event.type == sf::Event::TextEntered) {
                if (event.text.unicode == '\b'){
                    if(!path.empty())
                        path.pop_back();}
                else if (event.text.unicode == '\n'){
                    prewindow.close();
                }
                else if (event.text.unicode < 128)
                    path+=static_cast<char>(event.text.unicode);
                
            }
        }
        
        sf::Text pth(path.data(), font, 50);
        pth.setPosition(200.f,200.f);
        prewindow.clear();
        // Draw the string
        prewindow.draw(text);
        prewindow.draw(pth);
        // Update the window
        prewindow.display();
    }
 */
    
    std::string path = "Users/youssefbencheikh/Desktop/Archive.cbz";
    Archive arch = Archive();
    if(arch.loadArchivedFiles(path)) std::cout<<"hey\n";
    std::cout<<"total pages: "<<arch.getPageNumTotal()<<"\n";
    cv::Mat a_image;
    std::cout<<arch.loadOneImage(5,a_image)<<"\n";

    /*cv::namedWindow("Car",cv::WINDOW_AUTOSIZE);

    cv::imshow("Car",a_image);
    cv::waitKey(0);
    cv::destroyWindow("Car");*/
    
    // Create the main window
    sf::RenderWindow window(sf::VideoMode(sf::VideoMode(1600, 1200)), "Comic Book Reader");
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
    //sf::RenderWindow window(sf::VideoMode(800, 600), "Comic Book Reader");
    // Set the Icon
    sf::Image icon;
    if (!icon.loadFromFile(resourcePath()+"icon.png")) {
        return EXIT_FAILURE;
    }
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
    cv::Mat resized;
    
    float scale = (float)(window.getSize().x)/(float)(a_image.size().width);
    std::cout<<"here: "<<sf::VideoMode::getDesktopMode().height<<"\n";
    std::cout<<"here: "<<a_image.size().height<<"\n";
    std::cout<<"here: "<<scale<<"\n";
    resize(a_image, resized, Size(), 0.5, 0.5, INTER_LINEAR);

    
    CACHE cache(20);
    int page = 0;
    sf::Texture texture;
    /*
    for (const auto & entry : std::__fs::filesystem::directory_iterator(path)){
    sf::Image simg;
    if (!simg.loadFromFile(entry.path())) {
        return EXIT_FAILURE;
    }

   
    
    IMAGE img(page++,simg);
    cache.add(img);
    
    }

    page = 1;
    if (!texture.loadFromImage(cache.getpage(page))) {
        return EXIT_FAILURE;
    }
 */

    //Archive arch = Archive();
    //arch.loadArchivedFiles(path);
    //std::cout<<"nombre total "<< arch.getPageNumTotal()<<"\n";
    //cv::Mat image;
    //arch.loadOneImage(1, image);
    CV_IMAGE cv_im = CV_IMAGE(1, resized);
    
    IMAGE img = IMAGE(cv_im);
    // Start the game loop
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
            
        }
        
        // Load a sprite to display
        
        texture.loadFromImage(img.get_img());
        
        sf::Sprite sprite(texture);
        float scale2 = (11/12.f)*(float)window.getSize().y/(float)img.get_img().getSize().y;
        sprite.setScale(scale2,scale2);
        sprite.move(800-sprite.getGlobalBounds().width/2.f,0);
        // Clear screen
        window.clear();

        // Draw the sprite
        window.draw(sprite);
        sf::Font font;
        if (!font.loadFromFile(resourcePath() +"sansation.ttf")) {
            return EXIT_FAILURE;
        }
        sf::Text text("Welcome to ComicBookReader, type the path to your CB, or choose one among the recent:", font, 50);
        text.setFillColor(sf::Color::White);
        // Draw the string
        //window.draw(text);
        for (Button button:buttons){
        window.draw(button.shape);
        text = button.text;
        text.setFont(font);
        window.draw(text);
        }
        // Update the window
        window.display();
    }
    
    //cache.clear();
    return EXIT_SUCCESS;
    
}
