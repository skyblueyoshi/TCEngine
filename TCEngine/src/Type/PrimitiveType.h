#pragma once

namespace Tce {
    enum class PrimitiveType {
        // Renders the specified vertices as a sequence of isolated triangles. Each group of three vertices defines a separate triangle. Back-face culling is affected by the current winding-order render state.
        TriangleList,
        // Renders the vertices as a triangle strip. The back-face culling flag is flipped automatically on even-numbered triangles.
        TriangleStrip,
        // Renders the vertices as a list of isolated straight line segments; the count may be any positive integer.
        LineList,
        // Renders the vertices as a single polyline; the count may be any positive integer.
        LineStrip
    };
}
