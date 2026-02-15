#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "../thirdparty/stb/stb_image_write.h"

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

    unsigned char imageData[width * height * 3];

    for (size_t y = 0; y < height; y++) {
        for (size_t x = 0; x < width; x++) {
            size_t i = (y * width + x) * 3;
            imageData[i + 0] = toLinear(image[y][x].x);
            imageData[i + 1] = toLinear(image[y][x].y);
            imageData[i + 2] = toLinear(image[y][x].z);
        }
    }

    std::cout << "Writing to PNG with resolution " << RESOLUTION << "\n";
    stbi_flip_vertically_on_write(true);
    
    int info;
    info = stbi_write_png(outPath.c_str(), width, height, 3, imageData, 0);
    if (!info)
        std::cerr << "Writing to " << outPath << ".png failed." << std::endl;
}
