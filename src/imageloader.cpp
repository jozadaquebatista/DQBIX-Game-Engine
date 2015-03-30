#include "../include/imageloader.h"
#include "../include/stbimage.h"

unsigned char* ImageLoader::loadRawDataFromFile(const char *filename, int* w, int *h, int* comp)
{
    unsigned char* data = stbi_load(filename, w, h, comp, 4);
    return data;
}

unsigned char *ImageLoader::loadRawDataFromMemory(const void *data, int len, int *w, int *h, int *comp, int req_comp)
{
    const unsigned char* buffer = static_cast<const unsigned char*>(data);
    unsigned char* texdata = stbi_load_from_memory(buffer, len, w, h, comp, req_comp);
    return texdata;
}

void ImageLoader::free_data(void* data)
{
    stbi_image_free(data);
}
