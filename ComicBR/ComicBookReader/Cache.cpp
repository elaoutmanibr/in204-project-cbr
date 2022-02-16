

#include "Cache.hpp"
void Cache::clean(int page){
    std::vector<Image> nv_images;
    for(Image image:images){
        if (image.get_num()<(page+3) && image.get_num()>(page-3)){
            nv_images.push_back(image);
        }
    }
    images.clear();
    images = nv_images;
}

void load_one(int page, Archive arch, Image * sf_image){
        cv::Mat a_image;
        arch.loadOneImage(page,a_image);
        Cv_image image = Cv_image(page,a_image);
        image.cv_resize();
        sf::Image sf_img = image.to_sfml();
        *sf_image = Image(page,sf_img);
}

void Cache::load(int page, Archive arch){
    clean(page);

    Image current; Image next; Image previous;
    load_one(page, arch, &current);
    if(page>1 && !isloaded(page-1)) load_one(page-1, arch, &previous);
    if(page<arch.getPageNumTotal() && !isloaded(page+1)) load_one(page+1, arch, &next);

    add(current); add(next); add(previous);
}

