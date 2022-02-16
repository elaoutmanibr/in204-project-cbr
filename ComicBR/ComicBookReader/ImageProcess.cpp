#include "ImageProcess.hpp"

sf::Image Cv_image::to_sfml(){
    sf::Image img;
    cv::Mat frameRGBA;
    cv::cvtColor(image, frameRGBA, cv::COLOR_BGR2RGBA);
    img.create(frameRGBA.cols, frameRGBA.rows, frameRGBA.ptr());
    return img;
}

void Cv_image::cv_resize(){
    cv::Mat resized;
    cv::resize(image, resized, cv::Size(), 0.9, 0.9, cv::INTER_LINEAR);
    image = resized;
}
