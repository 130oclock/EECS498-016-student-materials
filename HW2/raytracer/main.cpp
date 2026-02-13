#include "scene.hpp"
#include "config.hpp"

#include <filesystem>
#include <fstream>
#include <algorithm>
#include <chrono>

constexpr float GAMMA = 0.6f;

inline float toneMap(float x) {
    return (x * (2.51f * x + 0.03f)) / (x * (2.43f * x + 0.59f) + 0.14f);
}

unsigned char toLinear(float sRGB) {
    return 255 * std::pow(std::clamp(sRGB, 0.0f, 1.0f), GAMMA);
}

int main() {
    using namespace std::chrono;
    auto startTime = high_resolution_clock::now();

    Scene scene;
    scene.addObjects(OBJ_PATH, MTL_SEARCH_DIR);
    scene.constructBVH();
    
    auto timeAfterVBVH = high_resolution_clock::now();
    std::cout << "BVH Construction time in seconds: " << duration_cast<seconds>(timeAfterVBVH - startTime).count() << '\n';
    int width = RESOLUTION, height = RESOLUTION;
    std::vector<std::vector<Vec3>> image(height, std::vector<Vec3>(width));
    Vec3 cameraPos = {
        0.0f, 1.0f, 4.0f
    };

    if constexpr(!DEBUG) {
        std::cout << "Debug mode disabled. Progress output will be in brief." <<  '\n';
    }

    spawnRays(width, height, cameraPos, scene, image);
    std::cout << std::endl;

    auto finishTime = high_resolution_clock::now();
    std::cout << "Rendering time in seconds: " << duration_cast<seconds>(finishTime - timeAfterVBVH).count() << '\n';

    std::filesystem::path outPath = std::filesystem::absolute(OUTPUT_PATH);

    FILE* fp = fopen(outPath.string().c_str(), "wb");
    (void)fprintf(fp, "P6\n%d %d\n255\n", width, height);
    for (size_t y = 0; y < height; y++) {
        for (size_t x = 0; x < width; x++) {
            static unsigned char color[3];
            size_t invY = height - 1 - y;
            color[0] = toLinear(image[invY][x].x);
            color[1] = toLinear(image[invY][x].y);
            color[2] = toLinear(image[invY][x].z);
            fwrite(color, 1, 3, fp);
        }
    }
    fclose(fp);
    std::cout << "Output image written to " << outPath << '\n';
}