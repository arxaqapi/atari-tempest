#include "Pen.hpp"
#include "../utils/Utils.hpp"

int
Pen::index_of_ascii(const char c)
{
  return static_cast<int>(c) - 32;
}

void
Pen::draw_edge(SDL_Renderer* const r,
               const int x1,
               const int y1,
               const int x2,
               const int y2,
               const int xoffset,
               const int yoffset)
{
  SDL_SetRenderDrawColor(r, 0xFF, 0xFF, 0xFF, SDL_ALPHA_OPAQUE);
  SDL_RenderDrawLine(
    r, x1 + xoffset, -y1 + yoffset, x2 + xoffset, -y2 + yoffset);
}

int
Pen::draw_character(SDL_Renderer* const r,
                    const char c,
                    const int xoffset,
                    const int yoffset)
{
  int char_index = Pen::index_of_ascii(c);
  if (char_index < 0 || char_index >= 95) {
    throw utils::non_valid_character_requested();
  }

  int i = 2;
  while ((i + 3) < 112) {
    if (Pen::hershey_table[char_index][i] == -1 ||
        Pen::hershey_table[char_index][i + 2] == -1) {
      i += 2;
    } else {
      draw_edge(r,
                Pen::hershey_table[char_index][i],
                Pen::hershey_table[char_index][i + 1],
                Pen::hershey_table[char_index][i + 2],
                Pen::hershey_table[char_index][i + 3],
                xoffset,
                yoffset);
      i += 2;
    }
  }
  return Pen::hershey_table[char_index][1];
}

void
Pen::draw_string(std::string s, int xpos, int ypos, SDL_Renderer* const r)
{
  for (auto& c : s) {
    xpos += Pen::draw_character(r, c, xpos, ypos) + 2;
  }
}
