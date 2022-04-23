//
// Created by massimo on 16/04/2022.
//

#include "Tanker.hpp"
#include <iostream>

Tanker::Tanker()
{
  deactivate();
}

void
Tanker::render(SDL_Renderer* renderer, const Map& map) const
{
  if (!active_)
    return;

  SDL_SetRenderDrawColor(renderer, 230, 0, 0, 255);

  const Band& band = map.getBand(band_num_);

  f32 fraction =
    utils::easeOutQuad(front_progression_, 1 - map.getFocal()) - map.getFocal();

  f32 inner_size = (30 * (1 - fraction)) / 2;
  f32 outer_size = (60 * (1 - fraction)) / 2;

  Vector2D u = {1,0};
  Vector2D v = {0,1};
  Vector2D position = band.getExterCenter().vec_to(map.getOrigin()) * fraction;

  Vector2D inner_left = band.getExterCenter() + (u * .7f * inner_size ) + position;
  Vector2D inner_right = band.getExterCenter() + (u * (-.7f*inner_size))+ position;
  Vector2D inner_top = band.getExterCenter() + (v * inner_size) + position;
  Vector2D inner_bottom = band.getExterCenter() + (v * -inner_size) + position;
  Vector2D outer_left = band.getExterCenter() + (u * (.7f*outer_size)) + position;
  Vector2D outer_right = band.getExterCenter() + (u * (-.7f*outer_size))+ position;
  Vector2D outer_top = band.getExterCenter() + (v * outer_size) + position;
  Vector2D outer_bottom = band.getExterCenter() + (v * -outer_size) + position;

  SDL_RenderDrawLineF(renderer,
                      inner_left.getX(),
                      inner_left.getY(),
                      inner_top.getX(),
                      inner_top.getY());
  SDL_RenderDrawLineF(renderer,
                      inner_top.getX(),
                      inner_top.getY(),
                      inner_right.getX(),
                      inner_right.getY());
  SDL_RenderDrawLineF(renderer,
                      inner_right.getX(),
                      inner_right.getY(),
                      inner_bottom.getX(),
                      inner_bottom.getY());
  SDL_RenderDrawLineF(renderer,
                      inner_bottom.getX(),
                      inner_bottom.getY(),
                      inner_left.getX(),
                      inner_left.getY());
  SDL_RenderDrawLineF(renderer,
                      outer_left.getX(),
                      outer_left.getY(),
                      outer_top.getX(),
                      outer_top.getY());
  SDL_RenderDrawLineF(renderer,
                      outer_top.getX(),
                      outer_top.getY(),
                      outer_right.getX(),
                      outer_right.getY());
  SDL_RenderDrawLineF(renderer,
                      outer_right.getX(),
                      outer_right.getY(),
                      outer_bottom.getX(),
                      outer_bottom.getY());
  SDL_RenderDrawLineF(renderer,
                      outer_bottom.getX(),
                      outer_bottom.getY(),
                      outer_left.getX(),
                      outer_left.getY());
  SDL_RenderDrawLineF(renderer,
                      outer_top.getX(),
                      outer_top.getY(),
                      inner_left.getX(),
                      inner_left.getY());
  SDL_RenderDrawLineF(renderer,
                      outer_right.getX(),
                      outer_right.getY(),
                      inner_top.getX(),
                      inner_top.getY());
  SDL_RenderDrawLineF(renderer,
                      outer_bottom.getX(),
                      outer_bottom.getY(),
                      inner_right.getX(),
                      inner_right.getY());
  SDL_RenderDrawLineF(renderer,
                      outer_left.getX(),
                      outer_left.getY(),
                      inner_bottom.getX(),
                      inner_bottom.getY());
}

void
Tanker::update(f64 delta, const Map& map)
{
  if (!active_)
    return;

  if (front_progression_ == 0) {
    split_ = true;
    active_ = false;
  }

  move(delta, map);
}
