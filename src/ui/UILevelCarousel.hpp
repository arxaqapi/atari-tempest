/**
 * @file UILevelCarousel.hpp
 * @author Tarek Kunze(https://github.com/arxaqapi)
 * @version 0.1
 * @date 2022-04-17
 *
 * @copyright Copyright (c) 2022
 *
 * @brief
 */

#ifndef TEMPEST_ATARI_UILEVELCAROUSEL_HPP
#define TEMPEST_ATARI_UILEVELCAROUSEL_HPP

#include "../state/SceneManager.hpp"
#include "UIElement.hpp"
#include "UILevelBox.hpp"
#include <filesystem>
#include <string>
#include <vector>

/**
 * @brief Classe gérant le rendu des différents niveau
 * auquel il est possible de jouer dans une interface
 * de type carousel.
 *
 */
class UILevelCarousel : public UIElement
{
  friend inline void setup_ui_elements(std::vector<UILevelBox>& ui_elements);

private:
  /**
   * @brief Nombre maximum de boîte à afficher avant décalage de tout les
   * éléments
   *
   */
  static constexpr u8 AMOUNT_OF_BOXES_ = 4;
  /**
   * @brief le numéro du niveau en cours de sélection
   *
   */
  i32 selected_level_ = 0;
  /**
   * @brief Les boîtes des différents éléments
   *
   */
  std::vector<UILevelBox> ui_elements_;
  /**
   * @brief la valeur du décalage afin de gérer l'affichage des éléments
   * dnas une interface de type carousel
   *
   */
  u16 offset_ = 0;

  /**
   * @brief Décale les éléments à gauche, afin de visualiser les éléments
   * restants à droite
   *
   */
  void cycle_right();
  /**
   * @brief Décale les éléments à droite, afin de visualiser les éléments
   * restants à gauche
   *
   */
  void cycle_left();

public:
  UILevelCarousel();
  /**
   * @brief Construction d'un nouvel objet UILevelBox de forme rectangulaire à
   * la position x, y et de taille w * y
   *
   * @param x position en x de l'élément
   * @param y position en y de l'élément
   * @param w largeur de l'élément
   * @param h hauteur de l'élément
   */
  UILevelCarousel(i32 x, i32 y, i32 w, i32 h);
  ~UILevelCarousel();

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
   * @brief Déplace le curseur à droite
   *
   */
  void go_right();
  /**
   * @brief Déplace le curseur à gauche
   *
   */
  void go_left();
  /**
   * @brief Charge la scène de jeux au niveau désiré
   *
   * @param sm L'objet de gestion des scènes
   */
  void select(SceneManager& sm);
};

#endif // TEMPEST_ATARI_UILEVELCAROUSEL_HPP