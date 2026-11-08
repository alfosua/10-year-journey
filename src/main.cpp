#include "journey/game.hpp"

int main() {
  constexpr int screenWidth = 256;
  constexpr int screenHeight = 224;

  raylib::Window window(screenWidth, screenHeight, "The 10-Year Journey");
  window.SetTargetFPS(60);

  auto bg_color = raylib::Color::RayWhite();
  auto text_color = raylib::Color::DarkGray();

  raylib::Texture himmel_texture("assets/himmel.png");
  raylib::Vector2 himmel_pos(32, 32);

  float move_speed = 64.0f;
  float move_time = 0.0f;
  raylib::Vector2 current_facing(0, 1); // faces down initially

  while (!window.ShouldClose()) {
    float dt = GetFrameTime();

    raylib::Vector2 move_dir(0, 0);
    if (raylib::Keyboard::IsKeyDown(KEY_RIGHT))
      move_dir.x += 1;
    if (raylib::Keyboard::IsKeyDown(KEY_LEFT))
      move_dir.x -= 1;
    if (raylib::Keyboard::IsKeyDown(KEY_DOWN))
      move_dir.y += 1;
    if (raylib::Keyboard::IsKeyDown(KEY_UP))
      move_dir.y -= 1;
    move_dir = move_dir.Normalize();

    raylib::Rectangle himmel_src_rect;
    if (move_dir.LengthSqr() != 0.0f) {
      himmel_pos += move_dir * move_speed * dt;
      current_facing = move_dir;
      himmel_src_rect =
          game::chara_atlas::walk::get_frame_rect(move_time, current_facing);
      move_time += dt;
    } else {
      himmel_src_rect = game::chara_atlas::idle::get_frame_rect(current_facing);
      move_time = 0;
    }

    window.BeginDrawing();
    window.ClearBackground(bg_color);

    auto himmel_dest_rect =
        game::chara_atlas::calc_chara_rect_by_pos(himmel_pos);
    himmel_texture.Draw(himmel_src_rect, himmel_dest_rect,
                        raylib::Vector2::Zero(), 0.0f, raylib::Color::White());
    text_color.DrawText("The 10-Year Journey", 10, 10, 16);

    window.EndDrawing();
  }

  return 0;
}
