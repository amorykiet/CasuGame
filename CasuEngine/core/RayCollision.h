#ifndef RAYLIB_CPP_INCLUDE_RAYCOLLISION_HPP_
#define RAYLIB_CPP_INCLUDE_RAYCOLLISION_HPP_

#include "raylib_cpp_utils.h"
#include "raylib_header.h"

namespace raylib {
    /**
     * Raycast hit information
     */
    class RayCollision : public ::RayCollision {
    public:
        RayCollision(const ::RayCollision& ray) : ::RayCollision(ray) {}

        RayCollision(bool hit, float distance, ::Vector3 point, ::Vector3 normal)
            : ::RayCollision{ hit, distance, point, normal } {
            // Nothing.
        }

        /**
         * Get collision info between ray and bounding box
         */
        RayCollision(const ::Ray& ray, const ::BoundingBox& box)
            : ::RayCollision(::GetRayCollisionBox(ray, box)) {
            // Nothing.
        }

        /**
         * Get collision info between ray and mesh
         */
        RayCollision(const ::Ray& ray, const ::Mesh& mesh, const ::Matrix& transform)
            : ::RayCollision(::GetRayCollisionMesh(ray, mesh, transform)) {
            // Nothing.
        }

        /**
         * Get collision info between ray and quad
         */
        RayCollision(const ::Ray& ray, ::Vector3 p1, ::Vector3 p2, ::Vector3 p3, ::Vector3 p4)
            : ::RayCollision(::GetRayCollisionQuad(ray, p1, p2, p3, p4)) {
            // Nothing.
        }

        /**
         * Get collision info between ray and sphere
         */
        RayCollision(const ::Ray& ray, ::Vector3 center, float radius)
            : ::RayCollision(::GetRayCollisionSphere(ray, center, radius)) {
            // Nothing.
        }

        /**
         * Get collision info between ray and triangle
         */
        RayCollision(const ::Ray& ray, ::Vector3 p1, ::Vector3 p2, ::Vector3 p3)
            : ::RayCollision(::GetRayCollisionTriangle(ray, p1, p2, p3)) {
            // Nothing.
        }

        RayCollision& operator=(const ::RayCollision& ray) {
            set(ray);
            return *this;
        }

        GETTERSETTER(bool, Hit, hit)
        GETTERSETTER(float, Distance, distance)
        GETTERSETTER(::Vector3, Position, point)
        GETTERSETTER(::Vector3, Normal, normal)
    protected:
        void set(const ::RayCollision& ray) {
            hit = ray.hit;
            distance = ray.distance;
            point = ray.point;
            normal = ray.normal;
        }
    };
} // namespace raylib

using RRayCollision = raylib::RayCollision;

#endif // RAYLIB_CPP_INCLUDE_RAYCOLLISION_HPP_
