/**
 * @file UIElement.hpp
 * @author Tarek Kunze(https://github.com/arxaqapi)
 * @version 0.1
 * @date 2022-04-14
 *
 * @copyright Copyright (c) 2022
 *
 * @brief
 */

#ifndef TEMPEST_ATARI_UIELEMENT_HPP
#define TEMPEST_ATARI_UIELEMENT_HPP

#include "../sdlw/SDLW.hpp"
#include "../utils/types.hpp"

/**
 * @brief Classe de base des element de l'interface utilisateur
 *
 */
class UIElement
{
protected:
  /**
   * @brief Boite englobante délimitant l'élément
   *
   */
  SDLW::Rect_T<i32> bounding_box_;

public:
  UIElement();
  /**
   * @brief Construction d'un nouvel objet UIElement de forme rectangulaire à la
   * position x, y et de taille w * y
   *
   * @param x position en x de l'élément
   * @param y position en y de l'élément
   * @param w largeur de l'élément
   * @param h hauteur de l'élément
   */
  UIElement(i32 x, i32 y, i32 w, i32 h);
  ~UIElement();

  /**
   * @brief Fonction purement virtuelle de mise à jour des données de l'élément
   *
   */
  virtual void update() = 0;
  /**
   * @brief Fonction purement virtuelle de rendu de l'élément sur le Renderer
   * cible
   *
   * @param renderer la cible du rendu
   */
  virtual void render(SDLW::Renderer& renderer) const = 0;
};

#endif // TEMPEST_ATARI_UIELEMENT_HPP