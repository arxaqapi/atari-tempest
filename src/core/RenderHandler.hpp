/**
 * @file RenderHandler.hpp
 * @author arxaqapi (https://github.com/arxaqapi)
 * @version 0.1
 * @date 2022-01-30
 *
 * @copyright Copyright (c) 2022
 *
 * @brief
 */
#ifndef H_TEMPEST_GAME_INC_RENDERHANDLER_
#define H_TEMPEST_GAME_INC_RENDERHANDLER_

#include "../sdlw/SDLW.hpp"
#include "../utils/types.hpp"
#include <memory>

class RenderHandler
{
private:
  std::unique_ptr<SDLW::Window> w_;
  std::unique_ptr<SDLW::Renderer> r_;

public:
  RenderHandler(u16 w_width, u16 w_height);
  ~RenderHandler();

  void clear();
  void draw();

  SDLW::Renderer& get_renderer();
};

#endif