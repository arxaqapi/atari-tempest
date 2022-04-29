/**
 * @file RenderHandler.hpp
 * @author Tarek Kunze(https://github.com/arxaqapi)
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

/**
 * @brief Classe permettant l'initialisation de la SDL, de la fenêtre ainsi que
 * le contexte de rendu
 *
 */
class RenderHandler
{
private:
  /**
   * @brief Pointeur unique sur la fenêtre
   *
   */
  std::unique_ptr<SDLW::Window> w_;
  /**
   * @brief Pointeur unique sur le contexte de Rendu
   *
   */
  std::unique_ptr<SDLW::Renderer> r_;

public:
  /**
   * @brief Construction d'un objet de type RenderHandler avec une fenêtre de
   * taille w_width * w_height
   *
   * @param w_width largeur de la fenêtre
   * @param w_height hauteur de la fenêtre
   */
  RenderHandler(u16 w_width, u16 w_height);
  ~RenderHandler();

  /**
   * @brief Efface la cible de rendu actuelle avec la couleur noire
   *
   */
  void clear();
  /**
   * @brief Met à jour la fenêtre actuelle avec le contexte de rendu du Renderer
   *
   */
  void draw();

  /**
   * @brief Retourne une référence sur l'objet Renderer sous-jacent
   *
   * @return SDLW::Renderer& pointeur sur le contexte de rendu
   */
  SDLW::Renderer& get_renderer();
};

#endif