/**
 * @file Vector2D.hpp
 * @author Tarek Kunze(https://github.com/arxaqapi)
 * @version 0.1
 * @date 2022-02-17
 *
 * @copyright Copyright (c) 2022
 *
 * @brief
 */

#ifndef H_TEMPEST_GAME_INC_VECTOR_2D_
#define H_TEMPEST_GAME_INC_VECTOR_2D_

#include "types.hpp"
#include <cmath>
#include <utility>

class Vector2D
{

private:
  f32 x_ = 0.f;
  f32 y_ = 0.f;

public:
  Vector2D() = default;
  Vector2D(const Vector2D& vector) = default;
  Vector2D(f32 x, f32 y)
    : x_(x)
    , y_(y){};
  ~Vector2D() = default;

  /**
   * @brief Calcule la magnitude du vecteur
   * @return Magnitude du vecteur
   */
  inline f32 magnitude() const { return sqrtf32(x_ * x_ + y_ * y_); };

  /**
   * @brief Renvoie le vecteur depuis la position courante vers la position du
   * point en paramètre
   * @param point Le point à atteindre
   * @return Le vecteur directeur
   */
  inline Vector2D vec_to(const Vector2D& point) const
  {
    return { point.x_ - x_, point.y_ - y_ };
  };

  /**
   * @brief Renvoie le point médian pondéré depuis la position courante vers la
   * position du point en paramètre
   * @param point Le point à atteindre
   * @param weight La pondération
   * @return Le point médian pondéré
   */
  inline Vector2D weightedMidPointTo(const Vector2D& point, f32 weight) const
  {
    return { (1 - weight) * x_ + weight * point.x_,
             (1 - weight) * y_ + weight * point.y_ };
  }

  /**
   * @brief Renvoie le vecteur unitaire du vecteur
   * @return Le vecteur unitaire du vecteur
   */
  inline Vector2D unit() const
  {
    return { x_ / magnitude(), y_ / magnitude() };
  };

  /**
   * @brief Retourne un vecteur orthogonal au vecteur
   * @return Vecteur orthogonal au vecteur
   */
  inline Vector2D orthogonalVector() const { return { y_, -x_ }; }

  /**
   * @brief Addition avec un vecteur composante par composante
   * @param vector Vecteur avec lequel faire l'addition
   * @return Vecteur résultant
   */
  inline Vector2D operator+(const Vector2D& vector) const
  {
    return { x_ + vector.x_, y_ + vector.y_ };
  };

  /**
   * @brief Multiplication des composantes du vecteur par un scalaire
   * @param lambda Scalaire avec lequel faire la multiplication
   * @return Vecteur résultant
   */
  inline Vector2D operator*(f32 lambda) const
  {
    return { x_ * lambda, y_ * lambda };
  };

  /**
   * Setters
   */
  inline void setX(f32 x) { x_ = x; }
  inline void setY(f32 y) { y_ = y; };

  /**
   * Getters
   */
  inline f32 getX() const { return x_; };
  inline f32 getY() const { return y_; };
};

#endif