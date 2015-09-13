#ifndef ASSETPACKAGE_H
#define ASSETPACKAGE_H

#include <string>
#include <physfs.h>

#include "Texture.h"
#include "audio.h"
#include "font.h"

// Sizes
#define KB100 104857.6
#define HALF_MEG 524288
#define ONE_MEG 1048576

class AssetPackage
{
public:
    AssetPackage(string package_file = "") : m_filename(package_file)
    {
        PHYSFS_init(NULL);
    }
    ~AssetPackage()
    {
        this->DisposeTempFiles();
        PHYSFS_deinit();
    }

    void DisposeTempFiles();

    Texture* loadTexture(string filename);
    AudioClip* loadAudioClip(string filename);
    string loadText(string filename);
    Script* loadScript(string filename, LuaEngine* eng);
    Font* loadFont(string filename);

private:
    string m_filename;
    vector<string> m_tempfiles;

    void loadRAWDataFromArchive(const char* fname, PHYSFS_sint64* file_size, unsigned char** data);
    void AP_write(const char* file, const void* data, int size, int num);
};

#endif // ASSETPACKAGE_H
