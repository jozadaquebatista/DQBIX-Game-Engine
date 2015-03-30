#ifndef IMAGELOADER_H
#define IMAGELOADER_H

class ImageLoader
{
public:
    static unsigned char *loadRawDataFromFile(const char* filename, int* w, int *h, int* comp);
    static unsigned char *loadRawDataFromMemory(const void* data, int len, int* w, int *h, int* comp, int req_comp);
    static void free_data(void* data);
};

#endif // IMAGELOADER_H
