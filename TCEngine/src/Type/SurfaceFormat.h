#pragma once

namespace Tce {

    // 表面格式
    // 这里使用UNITY全部表面格式
    enum class EnumSurfaceFormat {

        /// Unsigned 32-bit ARGB pixel format for store 8 bits per channel.
        Color,

        /// Unsigned 16-bit BGR pixel format for store 5 bits for blue, 6 bits for green, and 5 bits for red.
        Bgr565,

        /// Unsigned 16-bit BGRA pixel format where 5 bits reserved for each color and last bit is reserved for alpha.
        Bgra5551,

        /// Unsigned 16-bit BGRA pixel format for store 4 bits per channel.
        Bgra4444,

        /// DXT1. Texture format with compression. Surface dimensions must be a multiple 4.
        Dxt1,

        /// DXT3. Texture format with compression. Surface dimensions must be a multiple 4.
        Dxt3,

        /// DXT5. Texture format with compression. Surface dimensions must be a multiple 4.
        Dxt5,

        /// Signed 16-bit bump-map format for store 8 bits for <c>u</c> and <c>v</c> data.
        NormalizedByte2,

        /// Signed 32-bit bump-map format for store 8 bits per channel.
        NormalizedByte4,

        /// Unsigned 32-bit RGBA pixel format for store 10 bits for each color and 2 bits for alpha.
        Rgba1010102,

        /// Unsigned 32-bit RG pixel format using 16 bits per channel.
        Rg32,

        /// Unsigned 64-bit RGBA pixel format using 16 bits per channel.
        Rgba64,

        /// Unsigned A 8-bit format for store 8 bits to alpha channel.
        Alpha8,

        /// IEEE 32-bit R float format for store 32 bits to red channel.
        Single,

        /// IEEE 64-bit RG float format for store 32 bits per channel.
        Vector2,

        /// IEEE 128-bit RGBA float format for store 32 bits per channel.
        Vector4,

        /// Float 16-bit R format for store 16 bits to red channel.
        HalfSingle,

        /// Float 32-bit RG format for store 16 bits per channel.
        HalfVector2,

        /// Float 64-bit ARGB format for store 16 bits per channel.
        HalfVector4,

        /// Float pixel format for high dynamic range data.
        HdrBlendable,

        /// For compatibility with WPF D3DImage.
        Bgr32 = 20,     // B8G8R8X8

        /// For compatibility with WPF D3DImage.
        Bgra32 = 21,    // B8G8R8A8


        /// Unsigned 32-bit RGBA sRGB pixel format that supports 8 bits per channel.
        ColorSRgb = 30,

        /// Unsigned 32-bit sRGB pixel format that supports 8 bits per channel. 8 bits are unused.
        Bgr32SRgb = 31,

        /// Unsigned 32-bit sRGB pixel format that supports 8 bits per channel.
        Bgra32SRgb = 32,

        /// DXT1. sRGB texture format with compression. Surface dimensions must be a multiple of 4.
        Dxt1SRgb = 33,

        /// DXT3. sRGB texture format with compression. Surface dimensions must be a multiple of 4.
        Dxt3SRgb = 34,

        /// DXT5. sRGB texture format with compression. Surface dimensions must be a multiple of 4.
        Dxt5SRgb = 35,

        /// PowerVR texture compression format (iOS and Android).
        RgbPvrtc2Bpp = 50,

        /// PowerVR texture compression format (iOS and Android).
        RgbPvrtc4Bpp = 51,

        /// PowerVR texture compression format (iOS and Android).
        RgbaPvrtc2Bpp = 52,

        /// PowerVR texture compression format (iOS and Android).
        RgbaPvrtc4Bpp = 53,

        /// Ericcson Texture Compression (Android)
        RgbEtc1 = 60,

        /// DXT1 version where 1-bit alpha is used.
        Dxt1a = 70,

        /// ATC/ATITC compression (Android)
        RgbaAtcExplicitAlpha = 80,

        /// ATC/ATITC compression (Android)
        RgbaAtcInterpolatedAlpha = 81,

        /// Etc2 RGB8 (Android/iOS withh OpenglES 3.0)
        Rgb8Etc2 = 90,

        /// Etc2 SRGB8 (Android/iOS withh OpenglES 3.0)
        Srgb8Etc2 = 91,

        /// Etc2 RGB8A1 (Android/iOS withh OpenglES 3.0)
        Rgb8A1Etc2 = 92,

        /// Etc2 SRGB8A1 (Android/iOS withh OpenglES 3.0)
        Srgb8A1Etc2 = 93,

        /// Etc2 RGBA8 EAC (Android/iOS withh OpenglES 3.0)
        Rgba8Etc2 = 94,

        /// Etc2 SRGB8A8 EAC (Android/iOS withh OpenglES 3.0)
        SRgb8A8Etc2 = 95
    };

}