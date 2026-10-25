#include <print>
#include "raylib-cpp.hpp"

int main() {
    constexpr int screenWidth = 800;
    constexpr int screenHeight = 600;

    raylib::Window window(screenWidth, screenHeight, "The 10-Year Journey");
    window.SetTargetFPS(60);

    raylib::Color bgColor = raylib::Color::RayWhite();
    raylib::Color textColor = raylib::Color::DarkGray();

    std::println("Initialized window: {}x{}", screenWidth, screenHeight);

    while (!window.ShouldClose()) {
        window.BeginDrawing();

        window.ClearBackground(bgColor);
        textColor.DrawText("The 10-Year Journey", 190, 200, 20);

        window.EndDrawing();
    }

    return 0;
}
