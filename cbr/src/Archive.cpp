
#include "Archive.hpp"

Archive::Archive()
{
}


Archive::~Archive()
{
}

bool Archive::loadArchivedFiles(std::string file_path)
{
    archive_path = file_path;
    char *path = &archive_path[0];
    stream = ar_open_file(path);
    if (stream == NULL) return false;
    ar = ar_open_any_archive(stream, strrchr(path, '.'));
    if (!ar) return false;
    int count = 0;
    while (ar_parse_entry(ar)) {
            size_t offset = ar_entry_get_offset(ar);
            offset_cache.push_back(offset);
            count++;
        }
    page_num_total = count;
    return true;
}


ar_archive * Archive::ar_open_any_archive(ar_stream * stream, const char * fileext)
{
    ar_archive *ar = ar_open_rar_archive(stream);
    if (!ar)
        ar = ar_open_zip_archive(stream, fileext && (strcmp(fileext, ".xps") == 0 || strcmp(fileext, ".epub") == 0));
    if (!ar)
        ar = ar_open_7z_archive(stream);
    if (!ar)
        ar = ar_open_tar_archive(stream);
    return ar;
}

bool Archive::loadOneImage(int num, cv::Mat &a_image){
    if (num > page_num_total || num < 1) return false;
    if(!ar_parse_entry_at(ar, offset_cache[num-1])) return false;
    size_t size = ar_entry_get_size(ar);
    //std::cout<<ar_entry_get_name(ar)<<'\n';
    read_buffer.resize(size);
    unsigned char *buffer = &read_buffer[0];
    if(!ar_entry_uncompress(ar, buffer, size)) return false;
        a_image = cv::imdecode(read_buffer, cv::IMREAD_COLOR);
    return true;
}


