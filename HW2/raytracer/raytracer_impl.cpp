#include "ray.hpp"
#include "math.hpp"
#include "scene.hpp"
#include "accel.hpp"
#include "config.hpp"

#include <cassert>

// TODO
Vec3 Scene::trace(const Ray &ray, int bouncesLeft, bool discardEmission) {
    if constexpr(DEBUG) {
        assert(ray.isNormalized());
    }
    if (bouncesLeft < 0) return {};

    // TODO...
    
    return {};
}

// TODO
Vec3 Random::randomHemisphereDirection(const Vec3 &normal) {
    /* 
        Uniformly generate a direction on the hemisphere oriented towards the positive y axis,
            represented by sphere coordinates
    */
    float azimuth = 0.0f;
    float elevation = 0.0f;

    // Convert spherical coordinates to Cartesian
    float x = cos(azimuth) * sin(elevation);
    float y = sin(azimuth) * sin(elevation);
    float z = cos(elevation);

    return localDirToWorld({x, y, z}, normal);
}

// TODO
Vec3 Random::cosWeightedHemisphere(const Vec3 &normal) {
    /* 
        Generate a direction on the hemisphere oriented towards the positive y axis, 
            cosine-weighted by the elevation angle.
    */
    float azimuth = 0.0f;
    float elevation = 0.0f;

    // Convert spherical coordinates to Cartesian
    float x = cos(azimuth) * sin(elevation);
    float y = sin(azimuth) * sin(elevation);
    float z = cos(elevation);

    return localDirToWorld({x, y, z}, normal);
}
