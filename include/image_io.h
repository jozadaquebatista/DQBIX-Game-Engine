#ifndef STBIMAGE
#define STBIMAGE
#pragma once

#define DQBIX_USE_STB_IMAGE
#ifdef DQBIX_USE_STB_IMAGE
    #ifndef STB_IMAGE_IMPLEMENTATION
        #define STB_IMAGE_IMPLEMENTATION
        #include <stb_image.h>
    #else
        #error "STB_IMAGE already defined."
    #endif
#else
    #include <SOIL.h>
#endif

#endif // STBIMAGE

