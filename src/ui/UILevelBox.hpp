/**
 * @file UILevelBox.hpp
 * @author Tarek Kunze(https://github.com/arxaqapi)
 * @version 0.1
 * @date 2022-04-14
 *
 * @copyright Copyright (c) 2022
 *
 * @brief
 */

#ifndef TEMPEST_ATARI_UILEVELBOX_HPP
#define TEMPEST_ATARI_UILEVELBOX_HPP

#include "../utils/types.hpp"
#include "UIElement.hpp"

class UILevelBox : public UIElement
{
private:
  /**
   * @brief Numéro du niveau correspondant
   *
   */
  u32 level_n_;

public:
  UILevelBox(i32 x, i32 y, i32 w, i32 h) = delete;
  /**
   * @brief Construction d'un nouvel objet UILevelBox de forme rectangulaire à
   * la position x, y et de taille w * y correspondant au niveau \b level
   *
   * @param level la niveau auquel l'élément fait référence
   * @param x position en x de l'élément
   * @param y position en y de l'élément
   * @param w largeur de l'élément
   * @param h hauteur de l'élément
   */
  UILevelBox(u32 level, i32 x, i32 y, i32 w, i32 h);
  ~UILevelBox();

  /**
   * @brief Fonction de mise à jour des données de l'élément
   *
   */
  void update() override;
  /**
   * @brief Fonction de rendu de l'élément sur le Renderer cible
   *
   * @param renderer la cible du rendu
   */
  void render(SDLW::Renderer& renderer) const override;
  /**
   * @brief Fonction de rendu de l'élément sur le Renderer cible,
   * dans le cas ou l'élément à été sélectionné
   *
   * @param renderer la cible du rendu
   * @param selected booléen indiquant si l'élément a été sélectionné
   */
  void render(SDLW::Renderer& renderer, bool selected) const;

  /**
   * @brief Setter mettant à jour le numéro du niveau
   *
   * @param new_level
   */
  void set_level_n(u32 new_level);
  /**
   * @brief Getter du numéro du niveau
   *
   * @return u32: valeur du niveau auquel l'élément fait référence
   */
  u32 get_level_n();
};

#endif // TEMPEST_ATARI_UILEVELBOX_HPP