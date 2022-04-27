#include "Pen.hpp"
#include "../core/Game.hpp"
#include "../utils/Errors.hpp"

i32
Pen::index_of_ascii(const u8 c)
{
  return static_cast<i32>(c) - 32;
}

void
Pen::draw_edge(SDLW::Renderer& renderer,
               const f32 x1,
               const f32 y1,
               const f32 x2,
               const f32 y2,
               const i32 xoffset,
               const i32 yoffset)
{
  renderer.SetRenderDrawColor(0xFF, 0xFF, 0xFF, SDL_ALPHA_OPAQUE);
  renderer.RenderDrawLineF(
    x1 + xoffset, -y1 + yoffset, x2 + xoffset, -y2 + yoffset);
}

i32
Pen::draw_character(SDLW::Renderer& renderer,
                    const u8 c,
                    const i32 xoffset,
                    const i32 yoffset,
                    const f32 multiplier)
{
  i32 char_index = Pen::index_of_ascii(c);
  if (char_index < 0 || char_index >= 95) {
    throw errors::non_valid_character_requested();
  }

  i32 i = 2;
  while ((i + 3) < 112) {
    if (Pen::hershey_table[char_index][i] == -1 ||
        Pen::hershey_table[char_index][i + 2] == -1) {
      i += 2;
    } else {
      draw_edge(renderer,
                multiplier * Pen::hershey_table[char_index][i],
                multiplier * Pen::hershey_table[char_index][i + 1],
                multiplier * Pen::hershey_table[char_index][i + 2],
                multiplier * Pen::hershey_table[char_index][i + 3],
                xoffset,
                yoffset);
      i += 2;
    }
  }
  return multiplier * Pen::hershey_table[char_index][1];
}

// Public

void
Pen::draw_string(std::string const& s,
                 i32 xpos,
                 i32 ypos,
                 SDLW::Renderer& renderer)
{
  for (auto& c : s) {
    xpos += Pen::draw_character(renderer, c, xpos, ypos, 1) + Pen::space_size;
  }
}

void
Pen::draw_string_centered_x(std::string const& s,
                            i32 ypos,
                            SDLW::Renderer& renderer)
{
  draw_string(
    s, Game::get_width() / 2 - get_string_width(s) / 2, ypos, renderer);
}

void
Pen::draw_string(std::string const& s,
                 i32 xpos,
                 i32 ypos,
                 SDLW::Renderer& renderer,
                 f32 size)
{
  for (auto& c : s) {
    xpos +=
      Pen::draw_character(renderer, c, xpos, ypos, size) + Pen::space_size;
  }
}

void
Pen::draw_string_centered_x(std::string const& s,
                            i32 ypos,
                            SDLW::Renderer& renderer,
                            f32 size)
{
  draw_string(s,
              Game::get_width() / 2 - get_string_width(s, size) / 2,
              ypos,
              renderer,
              size);
}

i32
Pen::get_string_width(std::string const& s)
{
  i32 total_width = 0;
  for (auto& c : s) {
    total_width += Pen::hershey_table[Pen::index_of_ascii(c)][1];
  }
  return total_width + (s.size() - 1) * Pen::space_size;
}

i32
Pen::get_string_width(std::string const& s, f32 size)
{
  i32 total_width = 0;
  for (auto& c : s) {
    total_width += size * Pen::hershey_table[Pen::index_of_ascii(c)][1];
  }
  return total_width + (s.size() - 1) * Pen::space_size;
}