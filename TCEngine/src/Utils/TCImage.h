#pragma once

#include "TCArrayList.h"

namespace Tce {

    class ImageData {
    public:
        uint32_t m_width{};
        uint32_t m_height{};
        uint32_t m_channelCount{};
        ArrayList<uint8_t> m_data;
    };

    class Image {
    public:
        static ImageData LoadPngFromFile(const String &path);
    };

}