#include "../include/imageloader.h"
#include "../include/image_io.h"

unsigned char* ImageLoader::loadRawDataFromFile(const char *filename, int* w, int *h, int* comp)
{
    unsigned char* data = 0;
#ifdef DQBIX_USE_STB_IMAGE
    data = stbi_load(filename, w, h, comp, 4);
#else
    data = SOIL_load_image(filename, w, h, comp, 4);
#endif
    return data;
}

unsigned char *ImageLoader::loadRawDataFromMemory(const void *data, int len, int *w, int *h, int *comp, int req_comp)
{
    const unsigned char* buffer = static_cast<const unsigned char*>(data);
    unsigned char* texdata = 0;
#ifdef DQBIX_USE_STB_IMAGE
    texdata = stbi_load_from_memory(buffer, len, w, h, comp, req_comp);
#else
    texdata = SOIL_load_image_from_memory(buffer, len, w, h, comp, req_comp);
#endif
    return texdata;
}

void ImageLoader::free_data(void* data)
{
#ifdef DQBIX_USE_STB_IMAGE
    stbi_image_free(data);
#else
    SOIL_free_image_data((unsigned char*)data);
#endif
}
