/**
 * @file Map.hpp
 * @author massimo
 * @version 0.1
 * @date 2022-03-15
 *
 * @copyright Copyright (c) 2022
 */

#ifndef TEMPEST_ATARI_MAP_HPP
#define TEMPEST_ATARI_MAP_HPP

#include "Band.hpp"
#include <vector>

/**
 * @brief Représente la carte d'un niveau
 */
class Map
{
private:
  std::vector<Band> bands_;
  bool is_continuous_ = false;
  u8 selected_band_num_ = 0;
  f32 avg_band_with_ = 0;
  f32 focal_;
  Vector2D origin_;

  /**
   * @brief Créé les bandes en fonction des coordonnées des points extérieurs.
   * Les membres `is_continuous`, `selected_band_num_`, `focal` et `origin`
   * doivent être initialisés.
   * @param exterior Coordonnées des points extérieurs de la carte
   */
  void makeBands(const std::vector<Vector2D>& exterior);

public:
  Map() = default;
  Map(const Map& map) = default;
  Map(const std::vector<Vector2D>& exterior,
      bool is_continuous,
      f32 focal,
      Vector2D origin);
  ~Map() = default;

  /**
   * Renvoie le nombre de bandes de la carte
   * @return Le nombre de bandes de la carte
   */
  inline u8 size() const { return bands_.size(); };

  u8 getLeftBandNum(u8 num_band) const;
  u8 getRightBandNum(u8 num_band) const;
  const Band& getBand(u8 num_band) const;

  /**
   * @brief Réalise le rendu de la carte. Appelle la fonction `render` sur
   * chaque bande
   * @param renderer Wrapper du renderer SDL
   * @param standard_color Couleur standard des bandes
   * @param accent_color Couleur de la bande sélectionnée
   */
  void render(SDLW::Renderer& renderer,
              const color& standard_color,
              const color& accent_color) const;

  /**
   * @brief Appelle la fonction `select` sur la bande
   * @param num_band Numéro de la bande à sélectionner
   */
  void select(u8 num_band);

  /**
   * @brief Charge une carte. Les anciennes valeurs des membres de la classe
   * sont écrasés.
   * @param exterior Coordonnées des points extérieurs de la carte
   * @param is_continuous Booléen indiquant si la carte est fermée ou non
   * @param focal Indique le rapport entre l'intérieur et l'extérieur de la
   * carte
   * @param origin Point d'origine vers lesquels sont orientées les bandes
   */
  void load(const std::vector<Vector2D>& exterior,
            bool is_continuous,
            f32 focal,
            Vector2D origin);

  /**
   * Getters
   */
  inline const Vector2D& getOrigin() const { return origin_; };
  inline f32 getFocal() const { return focal_; }
  inline f32 getAvgBandWith() const { return avg_band_with_; }
  inline u8 getSelectedBandNum() const { return selected_band_num_; };
};

#endif // TEMPEST_ATARI_MAP_HPP
