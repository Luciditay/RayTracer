#include "glm/glm.hpp"
#include "strong_types.hpp"

struct colorParameter {};
using Color =
    NamedType<glm::vec3, colorParameter>; // Strong types cf article fluent cpp

struct colorRangeParameter {};
using ColorRange = NamedType<int, colorRangeParameter>;

void writeColor(std::ofstream &out, const ColorRange &colorRange,
                const Color &pixel_color);