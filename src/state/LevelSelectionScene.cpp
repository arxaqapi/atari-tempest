#include "LevelSelectionScene.hpp"
#include "../core/LevelData.hpp"
#include "../ui/Pen.hpp"
#include "../ui/UILevelBox.hpp"
#include "SceneManager.hpp"
#include <filesystem>
#include <regex>

namespace fs = std::filesystem;

LevelSelectionScene::LevelSelectionScene()
{
  std::regex r{ "level-[0-9]+" };
  // Get all available scenes
  if (fs::exists(LevelData::LEVELS_DATA_DIR_) &&
      fs::is_directory(LevelData::LEVELS_DATA_DIR_)) {
    for (const auto& file :
         fs::directory_iterator(LevelData::LEVELS_DATA_DIR_)) {
      if (std::regex_match(file.path().filename().string(), r)) {
        available_levels_.push_back(file.path());
      }
    }
  }

  std::sort(available_levels_.begin(),
            available_levels_.end(),
            [](fs::path p1, fs::path p2) {
              return std::stoi(p1.filename().string().substr(6)) <
                     std::stoi(p2.filename().string().substr(6));
            });

  for (size_t i = 0; i < available_levels_.size(); i++) {
    UILevelBox b{ 40 + ((int)i * 40), 400, 30, 30 };
    ui_elements_.push_back(b);
  }
}

LevelSelectionScene::~LevelSelectionScene() {}

void
LevelSelectionScene::update(f64 delta, SceneManager& sm)
{}

void
LevelSelectionScene::render(SDL_Renderer* renderer) const
{
  SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, SDL_ALPHA_OPAQUE);
  SDL_RenderClear(renderer);

  // Draw UI
  for (size_t i = 0; i < ui_elements_.size(); i++) {
    bool selected = selected_level_ == (int)i;
    ui_elements_[i].render(renderer, selected);
  }

  // Draw text
  Pen::draw_string_centered_x("Level selection scene", 100, renderer);
  Pen::draw_string_centered_x("Press space", 250, renderer);

  for (size_t i = 0; i < available_levels_.size(); i++) {
    Pen::draw_string(
      available_levels_[i].string(), 200, 400 + (i * 25), renderer);
  }
}

void
LevelSelectionScene::processEvent(SDL_Event event, SceneManager& sm)
{
  if (event.type == SDL_KEYDOWN) {
    switch (event.key.keysym.sym) {
      case SDLK_SPACE:
        sm.set_next_state(STATE_GAME_SCENE, selected_level_);
        break;
      case SDLK_RIGHT:
        selected_level_ = selected_level_ < (int)available_levels_.size() - 1
                            ? selected_level_ + 1
                            : selected_level_;
        break;
      case SDLK_LEFT:
        selected_level_ =
          selected_level_ > 0 ? selected_level_ - 1 : selected_level_;
        break;
      default:
        break;
    }
  }
}
