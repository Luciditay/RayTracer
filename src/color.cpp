#include "color.hpp"
#include <fstream>
#include <iostream>

void writeColor(std::ofstream &out, const ColorRange &colorRange,
                const Color &pixel_color) {
  out << static_cast<int>((colorRange.get() - 0.001) * pixel_color.get().x)
      << ' '
      << static_cast<int>((colorRange.get() - 0.001) * pixel_color.get().y)
      << ' '
      << static_cast<int>((colorRange.get() - 0.001) * pixel_color.get().z)
      << std::endl;
}