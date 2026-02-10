#pragma once

#include "../thirdparty/tinyobj/tiny_obj_loader.h"
#include "accel.hpp"

#include <string>
#include <vector>

class Scene {
public:
    static tinyobj::ObjReader reader;
    std::vector<Object*> objects;
    std::vector<Object*> lights;
    BVH bvh;

    float lightArea = 0;

    void addObjects(std::string_view modelPath, std::string_view searchPath);
    void constructBVH();
    Intersection getIntersection(const Ray& ray);
    /**
     * @brief sample a point from the first object in the light vector
     * @todo add support for multiple light objects
    */
    Intersection sampleLight() const;

    /**
     * Trace the ray until it intersects an object and returns the color.
     * @param ray             contains the position and direction of the ray
     * @param bouncesLeft     the number of bounces until the ray ends
     * @param discardEmission whether to discard the emission (direct radiance) from objects
     */
    Vec3 trace(const Ray& ray, int bouncesLeft = 2, bool discardEmission = false);
    ~Scene();
};