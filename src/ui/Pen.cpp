/**
 * @file Pen.cpp
 * @author Tarek Kunze (https://github.com/arxaqapi)
 * @version 0.1
 * @date 2022-04-29
 *
 * @copyright Copyright (c) 2022
 *
 * @brief
 */
#include "Pen.hpp"
#include "../core/Game.hpp"
#include "../utils/Errors.hpp"

i32
Pen::indexOfAscii(const u8 c)
{
  return static_cast<i32>(c) - 32;
}

void
Pen::drawEdge(SDLW::Renderer& renderer,
              const f32 x1,
              const f32 y1,
              const f32 x2,
              const f32 y2,
              const i32 xoffset,
              const i32 yoffset,
              const color& render_color)
{
  renderer.SetRenderDrawColor(std::get<0>(render_color),
                              std::get<1>(render_color),
                              std::get<2>(render_color),
                              SDL_ALPHA_OPAQUE);
  renderer.RenderDrawLineF(
    x1 + xoffset, -y1 + yoffset, x2 + xoffset, -y2 + yoffset);
}

i32
Pen::drawCharacter(SDLW::Renderer& renderer,
                   const u8 c,
                   const i32 xoffset,
                   const i32 yoffset,
                   const f32 multiplier,
                   const color& render_color)
{
  i32 char_index = Pen::indexOfAscii(c);
  if (char_index < 0 || char_index >= 95) {
    throw errors::NonValidCharacterRequested();
  }

  i32 i = 2;
  while ((i + 3) < 112) {
    if (Pen::hershey_table[char_index][i] == -1 ||
        Pen::hershey_table[char_index][i + 2] == -1) {
      i += 2;
    } else {
      drawEdge(renderer,
               multiplier * Pen::hershey_table[char_index][i],
               multiplier * Pen::hershey_table[char_index][i + 1],
               multiplier * Pen::hershey_table[char_index][i + 2],
               multiplier * Pen::hershey_table[char_index][i + 3],
               xoffset,
               yoffset,
               render_color);
      i += 2;
    }
  }
  return multiplier * Pen::hershey_table[char_index][1];
}

// Public

void
Pen::drawString(std::string const& s,
                i32 xpos,
                i32 ypos,
                SDLW::Renderer& renderer)
{
  drawString(s, xpos, ypos, renderer, Pen::base_color);
}

void
Pen::drawString(std::string const& s,
                i32 xpos,
                i32 ypos,
                SDLW::Renderer& renderer,
                const color& render_color)
{
  for (auto& c : s) {
    xpos += Pen::drawCharacter(renderer, c, xpos, ypos, 1, render_color) +
            Pen::space_size;
  }
}

void
Pen::drawString(std::string const& s,
                i32 xpos,
                i32 ypos,
                SDLW::Renderer& renderer,
                f32 size)
{
  for (auto& c : s) {
    xpos += Pen::drawCharacter(renderer, c, xpos, ypos, size, Pen::base_color) +
            Pen::space_size;
  }
}

void
Pen::drawString(std::string const& s,
                i32 xpos,
                i32 ypos,
                SDLW::Renderer& renderer,
                f32 size,
                const color& render_color)
{
  for (auto& c : s) {
    xpos += Pen::drawCharacter(renderer, c, xpos, ypos, size, render_color) +
            Pen::space_size;
  }
}

void
Pen::drawStringCenteredInX(std::string const& s,
                           i32 ypos,
                           SDLW::Renderer& renderer)
{
  drawString(s, Game::getWidth() / 2 - getStringWidth(s) / 2, ypos, renderer);
}

void
Pen::drawStringCenteredInX(std::string const& s,
                           i32 ypos,
                           SDLW::Renderer& renderer,
                           const color& render_color)
{
  drawString(s,
             Game::getWidth() / 2 - getStringWidth(s) / 2,
             ypos,
             renderer,
             render_color);
}

void
Pen::drawStringCenteredInX(std::string const& s,
                           i32 ypos,
                           SDLW::Renderer& renderer,
                           f32 size)
{
  drawString(s,
             Game::getWidth() / 2 - getStringWidth(s, size) / 2,
             ypos,
             renderer,
             size);
}

void
Pen::drawStringCenteredInX(std::string const& s,
                           i32 ypos,
                           SDLW::Renderer& renderer,
                           f32 size,
                           const color& render_color)
{
  drawString(s,
             Game::getWidth() / 2 - getStringWidth(s, size) / 2,
             ypos,
             renderer,
             size,
             render_color);
}

i32
Pen::getStringWidth(std::string const& s)
{
  i32 total_width = 0;
  for (auto& c : s) {
    total_width += Pen::hershey_table[Pen::indexOfAscii(c)][1];
  }
  return total_width + (s.size() - 1) * Pen::space_size;
}

i32
Pen::getStringWidth(std::string const& s, f32 size)
{
  i32 total_width = 0;
  for (auto& c : s) {
    total_width += size * Pen::hershey_table[Pen::indexOfAscii(c)][1];
  }
  return total_width + (s.size() - 1) * Pen::space_size;
}