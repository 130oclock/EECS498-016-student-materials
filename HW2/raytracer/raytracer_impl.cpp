#include "ray.hpp"
#include "math.hpp"
#include "scene.hpp"
#include "accel.hpp"
#include "config.hpp"

// TODO
void spawnRays(size_t width, size_t height, Vec3 cameraPosition, Scene &scene, std::vector<std::vector<Vec3>> &image) {
    for (size_t y = 0; y < height; y++) {
        for (size_t x = 0; x < width; x++) {
            Vec3 pixel = {(float)x + 0.5f, (float)y + 0.5f, 0.0f};
            Vec3 color;

            // TODO...

            image[y][x] = color;
            UpdateProgress((float)(y * width + x) / (width * height));
        }
    }
}

// TODO
float Triangle::timeOfIntersection(const Ray& ray) {

    // TODO...
    
    return 0.0f;
}

// TODO
Vec3 Scene::trace(const Ray &ray, int bouncesLeft, bool discardEmission) {

    // TODO...
    
    return {};
}

// TODO
Vec3 Random::randomHemisphereDirection(const Vec3 &normal) {
    /* 
        Uniformly generate a direction on the hemisphere oriented towards the positive y axis,
            represented by sphere coordinates
    */
    float azimuth =   0.0f;
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
    float azimuth =   0.0f;
    float elevation = 0.0f;

    // Convert spherical coordinates to Cartesian
    float x = cos(azimuth) * sin(elevation);
    float y = sin(azimuth) * sin(elevation);
    float z = cos(elevation);

    return localDirToWorld({x, y, z}, normal);
}
