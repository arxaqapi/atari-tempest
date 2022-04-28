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

  template<class GameObjectType>
  void handleCollisions(std::vector<GameObjectType>& enemies,
                        u32 associated_score);

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

template<class GameObjectType>
void
GameScene::handleCollisions(std::vector<GameObjectType>& enemies,
                            u32 associated_score)
{
  auto f = [](Bullet& bullet, GameObjectType& enemy) {return;};
  handleCollisions(enemies, associated_score, f);
}

template<class GameObjectType, typename Func>
void
GameScene::handleCollisions(std::vector<GameObjectType>& enemies,
                            u32 associated_score,
                            Func& on_bullet_collision)
{
  for (auto& enemy : enemies) {
    if (!enemy.isActive())
      continue;

    if (enemy.isColliding(player_)) {
      enemy.deactivate();
      player_.hit();
      spawn_manager_.clear();
    }

    for (auto& bullet : player_.getBullets()) {
      if (bullet.isActive() && bullet.isColliding(enemy)) {
        bullet.deactivate();
        enemy.hit();
        player_.addScore(associated_score);
        on_bullet_collision(bullet, enemy);
      }
    }
  }
}

#endif // TEMPEST_ATARI_GAMESCENE_HPP
