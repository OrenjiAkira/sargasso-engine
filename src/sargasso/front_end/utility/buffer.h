#ifndef SARGASSO_ENGINE_BUFFER_H
#define SARGASSO_ENGINE_BUFFER_H

#include <glad/glad.h>

#include <sml/vector3.h>
#include <vector>

namespace SargassoEngine {
namespace FrontEnd {
namespace Utility {

using namespace SML;

class Buffer {
   public:
    Buffer(const std::vector<Vec3>& points);
    ~Buffer();
    void render() const;
    GLuint get_id() const;
    size_t get_buffer_size() const;

   private:
    GLuint _buffer_id;
    size_t _point_count;
};

}  // namespace Utility
}  // namespace FrontEnd
}  // namespace SargassoEngine

#endif
