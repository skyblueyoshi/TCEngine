#include "File.h"

namespace Tce {

    AAssetManager *File::m_pAssetManager = nullptr;

    bool File::Open(const std::string &path, std::vector<uint8_t> &buffer) {
        assert(m_pAssetManager);
        auto pAsset = AAssetManager_open(m_pAssetManager, path.c_str(), AASSET_MODE_BUFFER);
        if (pAsset) {
            buffer.resize(AAsset_getLength(pAsset), '\0');
            AAsset_read(pAsset, &buffer[0], buffer.size());
            AAsset_close(pAsset);
            return true;
        }
        return false;
    }

    bool File::Open(const std::string &path, std::string &readContent) {
        std::vector<uint8_t> buffer;
        if (Open(path, buffer)) {
            size_t size = buffer.size();
            readContent.reserve(size + 1);
            for (size_t i = 0; i < size; i++)
                readContent[i] = (char) buffer[i];
            readContent[size] = '\0';
            return true;
        }
        return false;
    }
}