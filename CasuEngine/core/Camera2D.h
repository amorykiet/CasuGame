#ifndef RAYLIB_CPP_INCLUDE_CAMERA2D_HPP_
#define RAYLIB_CPP_INCLUDE_CAMERA2D_HPP_

#include "Vector2.h"
#include "raylib_cpp_utils.h"
#include "raylib_header.h"

namespace raylib {
    /**
     * Camera2D type, defines a 2d camera
     */
    class Camera2D : public ::Camera2D {
    public:
        Camera2D(const ::Camera2D& camera)
            : ::Camera2D(camera) {
            // Nothing.
        }

        Camera2D() : ::Camera2D() {}
        Camera2D(::Vector2 offset, ::Vector2 target, float rotation = 0.0f, float zoom = 1.0f)
            : ::Camera2D{ offset, target, rotation, zoom } {}

        Camera2D& BeginMode() {
            ::BeginMode2D(*this);
            return *this;
        }

        Camera2D& EndMode() {
            ::EndMode2D();
            return *this;
        }

        GETTERSETTER(::Vector2, Offset, offset)
        GETTERSETTER(::Vector2, Target, target)
        GETTERSETTER(float, Rotation, rotation)
        GETTERSETTER(float, Zoom, zoom)

        Camera2D& operator=(const ::Camera2D& camera) {
            set(camera);
            return *this;
        }

        /**
         * Returns camera 2d transform matrix
         */
        [[nodiscard]] Matrix GetMatrix() const { return ::GetCameraMatrix2D(*this); }

        /**
         * Returns the world space position for a 2d camera screen space position
         */
        [[nodiscard]] Vector2 GetScreenToWorld(::Vector2 position) const { return ::GetScreenToWorld2D(position, *this); }

        /**
         * Returns the screen space position for a 2d world space position
         */
        [[nodiscard]] Vector2 GetWorldToScreen(::Vector2 position) const { return ::GetWorldToScreen2D(position, *this); }
    protected:
        void set(const ::Camera2D& camera) {
            offset = camera.offset;
            target = camera.target;
            rotation = camera.rotation;
            zoom = camera.zoom;
        }
    };
} // namespace raylib

using RCamera2D = raylib::Camera2D;

#endif // RAYLIB_CPP_INCLUDE_CAMERA2D_HPP_