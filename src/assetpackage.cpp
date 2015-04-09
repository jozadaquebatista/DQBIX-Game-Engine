#include "../include/assetpackage.h"

#include <fstream>

// Load RAW data of the file. Works with everything.
// Returns the file size and the file data
void AssetPackage::loadRAWDataFromArchive(const char* fname, PHYSFS_sint64* file_size, unsigned char** data)
{
    if (m_filename == "") return;

    PHYSFS_addToSearchPath(m_filename.c_str(), 1);

    if (!PHYSFS_exists(fname))
    {
        IXLOG("Package Error: ", LOG_ERROR, false);
        IXLOG(fname, LOG_INFO, false);
        IXLOG(" - No such file in ", LOG_PLAIN, false);
        IXLOG(m_filename.c_str(), LOG_PLAIN, true);
        return;
    }

    PHYSFS_file* m_file = PHYSFS_openRead(fname);
    if (m_file == NULL)
    {
        printf("AssetPackage Error: '%s' could not open file.\n", fname);
        return;
    }

    if (file_size)
    {
        *file_size = PHYSFS_fileLength(m_file);
        PHYSFS_sint64 max_file_size = ONE_MEG * 10; // 10 MB limit

        if (*file_size > max_file_size)
        {
            printf("AssetPackage Error: '%s' file is too big.\n", fname);
            return;
        }
    }

    if (data)
    {
        *data = new unsigned char[*file_size];
        PHYSFS_sint64 total_read = PHYSFS_read(m_file, *data, 1, *file_size);
        if (total_read != *file_size)
        {
            printf("AssetPackage Error: '%s' could not read file.\n", fname);
            SAFE_DELETE(*data);
            return;
        }
    }

    PHYSFS_close(m_file);

}

void AssetPackage::AP_write(const char* file, const void *data, int size, int num)
{
    PHYSFS_init(NULL);
    PHYSFS_addToSearchPath(m_filename.c_str(), 1);

    PHYSFS_file* handle = PHYSFS_openWrite(file);
    PHYSFS_sint64 rc = PHYSFS_write(handle, data, size, num);
    if (rc != num)
    {
        printf("AssetPackage Error: '%s' could not write file. Err: %d\n", file, (int)rc);
        return;
    }

    PHYSFS_close(handle);
    PHYSFS_deinit();
}

void AssetPackage::DisposeTempFiles()
{
    for (std::string& file : m_tempfiles)
    {
        char* filename = (char*)malloc(file.size()+1);
        strcpy(filename, file.c_str());

        remove(filename);
    }
}

Texture *AssetPackage::loadTexture(std::string filename)
{
    unsigned char* data;
    PHYSFS_sint64 file_size;
    loadRAWDataFromArchive(filename.c_str(), &file_size, &data);

    int w, h, comp;
    unsigned char* texture_data = ImageLoader::loadRawDataFromMemory(data, static_cast<int>(file_size),
                                                                     &w, &h, &comp, 4);

    Texture* ret = new Texture(w, h, texture_data,
                               GL_TEXTURE_2D, GL_NEAREST,
                               GL_RGBA, GL_RGBA, false,
                               GL_COLOR_ATTACHMENT0);

    ImageLoader::free_data(texture_data);

    PHYSFS_deinit();

    return ret;
}

AudioClip *AssetPackage::loadAudioClip(std::string filename)
{
    unsigned char* data;
    PHYSFS_sint64 file_size;
    loadRAWDataFromArchive(filename.c_str(), &file_size, &data);

    PHYSFS_deinit();

    return new AudioClip(data);
}

std::string AssetPackage::loadText(std::string filename)
{
    unsigned char* data;
    PHYSFS_sint64 file_size;
    loadRAWDataFromArchive(filename.c_str(), &file_size, &data);

    PHYSFS_deinit();

    return std::string(reinterpret_cast<char*>(data));
}

Script *AssetPackage::loadScript(std::string filename, LuaEngine* eng)
{
    unsigned char* data;
    PHYSFS_sint64 file_size;
    loadRAWDataFromArchive(filename.c_str(), &file_size, &data);

    PHYSFS_deinit();

    std::string txt(data, data+file_size);
    return new Script(txt, eng);
}

Font *AssetPackage::loadFont(std::string filename)
{
    unsigned char* data;
    PHYSFS_sint64 file_size;
    loadRAWDataFromArchive(filename.c_str(), &file_size, &data);

    PHYSFS_deinit();

    std::ofstream fout;
    try
    {
        fout.exceptions(std::ofstream::failbit | std::ofstream::badbit);
        fout.open(filename, std::ios::out|std::ios::binary);
        fout.write(reinterpret_cast<const char*>(data), file_size);
        fout.close();
        fout.exceptions(std::ofstream::goodbit);
        assert(!fout.fail());
    }
    catch (std::ofstream::failure const &ex)
    {
        std::cerr << ex.what() << std::endl;
    }

//    std::ofstream outputBuffer(filename, std::ios::out|std::ios::binary);
//    outputBuffer.write(reinterpret_cast<const char*>(data), file_size);
//    outputBuffer.close();

    free(data);

    Font* ret = new Font(filename, 12);

    m_tempfiles.push_back(filename);
    return ret;
}
