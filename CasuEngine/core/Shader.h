#ifndef RAYLIB_CPP_INCLUDE_SHADER_HPP_
#define RAYLIB_CPP_INCLUDE_SHADER_HPP_

#include <string>

#include "ShaderUnmanaged.h"
#include "Texture.h"
#include "raylib_cpp_utils.h"
#include "raylib_header.h"

namespace raylib {
    /**
     * Shader type (generic)
     */
    class Shader : public ShaderUnmanaged {
    public:
        using ShaderUnmanaged::ShaderUnmanaged;

        Shader(const Shader&) = delete;

        Shader(Shader&& other) noexcept {
            set(other);

            other.id = 0;
            other.locs = nullptr;
        }

        Shader& operator=(const Shader&) = delete;

        Shader& operator=(Shader&& other) noexcept {
            if (this == &other) {
                return *this;
            }

            Unload();
            set(other);

            other.id = 0;
            other.locs = nullptr;

            return *this;
        }

        /**
         * Unload shader from GPU memory (VRAM)
         */
        ~Shader() { Unload(); }

        /**
         * Unload shader from GPU memory (VRAM)
         */
        void Unload() {
            if (locs != nullptr) {
                ::UnloadShader(*this);
            }
        }
    };
} // namespace raylib

using RShader = raylib::Shader;

#endif // RAYLIB_CPP_INCLUDE_SHADER_HPP_
