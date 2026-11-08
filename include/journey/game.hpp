#include "raylib-cpp.hpp"
#include <array>
#include <cmath>
#include <utility>

namespace game::chara_atlas {
inline constexpr raylib::Rectangle x();
inline constexpr raylib::Rectangle rect(0, 0, 16, 24);
inline constexpr int row_length = 3;

enum class Facing {
  Down,
  Up,
  Left,
  Right,
};

constexpr Facing calc_facing_by_axes(raylib::Vector2 axes) {
  using enum Facing;
  if (axes.x > 0) {
    return Right;
  } else if (axes.x < 0) {
    return Left;
  } else if (axes.y < 0) {
    return Up;
  } else {
    return Down;
  }
}

constexpr raylib::Rectangle calc_chara_rect_by_pos(raylib::Vector2 pos) {
  return raylib::Rectangle(pos.x, pos.y, rect.width, rect.height);
}

constexpr raylib::Rectangle calc_rect_by_frame_index(int index) {
  int col = index % row_length;
  int row = index / row_length;
  float x = col * rect.width;
  float y = row * rect.height;
  return raylib::Rectangle(x, y, rect.width, rect.height);
}

namespace idle {
  namespace frame_indices {
    inline constexpr int down = 1;
    inline constexpr int up = 4;
    inline constexpr int side = 7;
  } // namespace frame_indices

  constexpr int get_frame_index(Facing facing) {
    using enum Facing;
    switch (facing) {
    case Down:
      return frame_indices::down;
    case Up:
      return frame_indices::up;
    case Left:
    case Right:
      return frame_indices::side;
    default:
      std::unreachable();
    }
  }

  constexpr raylib::Rectangle get_frame_rect(Facing facing) {
    auto target_index = get_frame_index(facing);
    auto target_rect = calc_rect_by_frame_index(target_index);
    if (facing == Facing::Right)
      target_rect.width = -target_rect.width;
    return target_rect;
  }

  constexpr raylib::Rectangle get_frame_rect(raylib::Vector2 facing_axes) {
    auto facing = calc_facing_by_axes(facing_axes);
    return get_frame_rect(facing);
  }
} // namespace idle

namespace walk {
  inline constexpr int frame_count = 4;
  inline constexpr int fps = 4;

  namespace frame_indices {
    inline constexpr std::array<int, frame_count> down = {0, 1, 2, 1};
    inline constexpr std::array<int, frame_count> up = {3, 4, 5, 4};
    inline constexpr std::array<int, frame_count> side = {6, 7, 8, 7};
  } // namespace frame_indices

  constexpr int calc_index_by_time(float time) pre(time >= 0) {
    return static_cast<int>(time * fps) % frame_count;
  }

  constexpr const std::array<int, frame_count> &get_frame_set(Facing facing) {
    using enum Facing;
    switch (facing) {
    case Down:
      return frame_indices::down;
    case Up:
      return frame_indices::up;
    case Left:
    case Right:
      return frame_indices::side;
    default:
      std::unreachable();
    }
  }

  constexpr int get_frame_index(int index, Facing facing)
      pre(index >= 0 && index < frame_count) {
    auto frame_set = get_frame_set(facing);
    return frame_set[index];
  }

  constexpr raylib::Rectangle get_frame_rect(int index, Facing facing)
      pre(index >= 0 && index < frame_count) {
    auto target_index = get_frame_index(index, facing);
    auto target_rect = calc_rect_by_frame_index(target_index);
    if (facing == Facing::Right)
      target_rect.width = -target_rect.width;
    return target_rect;
  }

  constexpr raylib::Rectangle get_frame_rect(float time,
                                             raylib::Vector2 facing_axes) {
    auto index = calc_index_by_time(time);
    auto facing = calc_facing_by_axes(facing_axes);
    return get_frame_rect(index, facing);
  }
} // namespace walk
} // namespace game::chara_atlas
