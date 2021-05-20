#include "TCImage.h"
#include "TCFile.h"
//#define STB_IMAGE_IMPLEMENTATION
//#include <stb/stb_image.h>

namespace Tce {

    ImageData Image::LoadPngFromFile(const String &path) {
//        ArrayList<uint8_t> fileBits;
//        if (!File::Open(path, fileBits)) {
//            throw std::runtime_error(
//                    String::Format("Cannot open texture file: %s\n", path.Data()).Data());
//        }
//        int32_t imgWidth, imgHeight, imgChannelCount;
//        stbi_set_flip_vertically_on_load(1);
//        uint8_t *imageBits = stbi_load_from_memory(
//                fileBits.Data(), (int)fileBits.Count(),
//                &imgWidth, &imgHeight, &imgChannelCount,
//                STBI_rgb_alpha);
//        auto totalBit = (size_t)(imgWidth * imgHeight);
//        ImageData data;
//        data.m_width = (uint32_t)imgWidth;
//        data.m_height = (uint32_t)imgHeight;
//        data.m_channelCount = (uint32_t)imgChannelCount;
//        data.m_data.SetCapacity(totalBit);
//
//        for (size_t k = 0; k < totalBit; k++) {
//            data.m_data.Add(imageBits[k]);
//        }
//
//        stbi_image_free(imageBits);
//
//        return data;
        return ImageData();
    }

}