#include "color.hpp"
#include "glm/glm.hpp"
#include "strong_types.hpp"
#include <fstream>
#include <iostream>

struct widthParameter {};
struct heightParameter {};
struct aspect_ratioParameter {};
struct point3DParameter {};

using Width = NamedType<int, widthParameter>;
using Height = NamedType<int, widthParameter>;
using Aspect_ratio = NamedType<double, aspect_ratioParameter>;
// using point3D = NamedType<glm::vec3, point3DParameter>;

struct Result_Window {
  Height _height;
  Aspect_ratio _aspect_ratio;
  Width _width;

  Result_Window(const Height &height, const Aspect_ratio &aspect_ratio)
      : _height(height), _aspect_ratio(aspect_ratio),
        _width(aspect_ratio.get() * height.get()) {}
};

typedef glm::vec3 point3D;

class Ray {
private:
  point3D _origin;
  glm::vec3 _direction;

public:
  Ray(const point3D &origin, const glm::vec3 &direction)
      : _origin(origin), _direction(direction) {}

  point3D at(float t) { return (_direction * t) + _origin; }

  point3D origin() { return _origin; }

  glm::vec3 direction() { return _direction; }
};

void create_image(std::ofstream output_stream, int width, int height,
                  int color_range);

void create_ppm_file(const std::string &file_name, const Width &width,
                     const Height &height, const ColorRange &color_range) {

  std::ofstream image_out(file_name.c_str());

  if (!image_out) {
    std::cerr << "failed to open " << file_name << std::endl;
  } else {
    image_out << "P3" << std::endl;
    image_out << width.get() << ' ' << height.get() << std::endl;
    image_out << color_range.get() << std::endl;

    for (int j = 0; j < height.get(); j++) {
      std::cerr << "\rlines remaining: " << height.get() - j << ' '
                << std::flush;
      for (int i = 0; i < width.get(); i++) {
        auto r = double(i) / (width.get() - 1);
        auto g = double(j) / (height.get() - 1);
        auto b = 0.25;
        Color color_pixel(glm::vec3(r, g, b));

        writeColor(image_out, ColorRange(256), color_pixel);
      }
    }
  }
}

int main() {
  const ColorRange color_range(256);
  const Width image_width(400);
  const Aspect_ratio aspect_ratio((16.0 / 9.0));
  const Height image_height(
      static_cast<int>(image_width.get() / aspect_ratio.get()));

  // Viewport
  auto viewport_height = 2.;
  auto viewport_width = aspect_ratio.get() * viewport_height;

  // Camera
  point3D camera_origin(0., 0., 0.);
  float distance_camera_to_viewport = 1.0;
  glm::vec3 horizontal(viewport_width, 0, 0);
  glm::vec3 vertical(0, viewport_height, 0);
  glm::vec3 lower_left_corner(camera_origin - horizontal / 2.f -
                              vertical / 2.f -
                              glm::vec3(0, 0, distance_camera_to_viewport));

  const std::string fileName("../../out/test.ppm");
  create_ppm_file(fileName, image_width, image_height, color_range);
}