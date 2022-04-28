//
// Created by massimo on 16/03/2022.
//

#ifndef TEMPEST_ATARI_GAMESCENE_HPP
#define TEMPEST_ATARI_GAMESCENE_HPP

#include "../core/Blaster.hpp"
#include "../core/Bullet.hpp"
#include "../core/Data.hpp"
#include "../core/Flipper.hpp"
#include "../core/GameObjectPool.hpp"
#include "../core/Map.hpp"
#include "../core/SpawnManager.hpp"
#include "../utils/Vector2D.hpp"
#include "Scene.hpp"
#include <functional>
#include <string>
#include <vector>

class SceneManager;

/**
 * @brief Classe définissant la logique de la scène principale de jeu ainsi que
 * la gestion des différents niveaux
 *
 */
class GameScene : public Scene
{
private:
  Data level_data;
  /**
   * @brief Le numéro de la figure et le cycle courants définissent le niveau
   * courant
   */
  u8 current_figure_ = 0;
  u8 current_cycle_ = 0;
  Map map_;
  Blaster player_;
  SpawnManager spawn_manager_;

public:
  GameScene() = delete;
  GameScene(const GameScene& game_scene) = default;
  explicit GameScene(u8 level);

  /**
   * @brief Charge le niveau suivant. Les valeurs des membres de la classe sont
   * écrasées/réinitialisées.
   */
  void loadNextLevel();

  /**
   * @brief Teste si le jeu est terminé, ie il n'y a plus d'autres niveaux
   * @return Vrai si le jeu est terminé, faux sinon
   */
  bool gameOver() const;

  /**
   * @brief Renvoie le score maximal du niveau, ie le score nécessaire pour
   * terminer le niveau
   * @param cycle Numéro de cycle correspondant au niveau
   * @param figure Numéro de figure correspondant au niveau
   * @return Le score maximal du niveau
   */
  static u32 getLevelMaxScore(u8 cycle, u8 figure);

  /**
   * @brief Renvoie le score maxial du niveau courant, ie le score nécessaire
   * pour terminer le niveau courant
   * @return Le score maximal du niveau courant
   */
  u32 getCurrentLevelMaxScore() const;

  /**
   * @brief Renvoie le numéro du niveau courant à partir des membres `cycle_` et
   * `figure_` de la classe
   * @return Le numéro du niveau courant
   */
  u8 getCurrentLevelNum() const;

  /**
   * @brief Gère la collision entre le joueur et les ennemis, ainsi qu'entre les
   * balles du joueur et les ennemis. Attribue au joueur le score associé à la
   * destruction d'un ennemi. Appelle la fonction de même nom sans instructions
   * supplémentaires lors de la collision entre d'un ennemi avec une balle
   * @tparam GameObjectType Type enfant de GameObject. Type des ennemis dont il
   * faut gérer les collisions
   * @param enemies Ennemis dont il faut gérer la collision
   * @param associated_score Score à attribuer au joueur s'il a touché un ennemi
   * avec une balle
   */
  template<class GameObjectType>
  void handleCollisions(std::vector<GameObjectType>& enemies,
                        u32 associated_score);

  /**
   * @brief Gère la collision entre le joueur et les ennemis, ainsi qu'entre les
   * balles du joueur et les ennemis. Attribue au joueur le score associé à la
   * destruction d'un ennemi. Laisse la possibilité de fournir des instructions
   * supplémentaires en cas de collision d'un ennemi avec une balle
   * @tparam GameObjectType Type enfant de GameObject. Type des ennemis dont il
   * faut gérer les collisions
   * @tparam Func Type de la fonction utilisée pour fournir les instructions
   * supplémentaires en cas de collision d'un ennemi avec une balle. De la
   * forme `void f(GameObjectType &go)`
   * @param enemies Ennemis dont il faut gérer la collision
   * @param associated_score Score à attribuer au joueur s'il a touché un ennemi
   * avec une balle
   * @param on_bullet_collision Fonction de la forme
   * `void f(GameObjectType &go)`. Instructions à exécuter en cas de collision
   * d'un ennemi avec une balle
   */
  template<class GameObjectType, typename Func>
  void handleCollisions(std::vector<GameObjectType>& enemies,
                        u32 associated_score,
                        Func& on_bullet_collision);

  /**
   * @brief Fonction permettant la gestion des évènemment spécifique à la scène
   *
   * @param event Pointeur sur la structure de l'évènement
   * @param sm référence sur le gestionnaire de scène, permettant de
   * demander un changement d'état
   */
  void processEvent(SDL_Event* event, SceneManager& sm) override;
  /**
   * @brief Fonction permettant la mise à jour de l'état interne de la scène
   *
   * @param delta le temps delta issue du timer
   * @param sm référence sur le gestionnaire de scène, permettant de
   * demander et d'acter un changement d'état
   */
  void update(f64 delta, SceneManager& sm) override;
  /**
   * @brief Rend les différents éléments de la scène sur l'objet Renderer
   *
   * @param renderer Référence sur le Renderer courant
   */
  void render(SDLW::Renderer& renderer) const override;
};

#endif // TEMPEST_ATARI_GAMESCENE_HPP
