/**
 * @file SDLW.hpp
 * @author Tarek Kunze(https://github.com/arxaqapi)
 * @version 0.1
 * @date 2022-04-15
 *
 * @copyright Copyright (c) 2022
 *
 * @brief
 */
#ifndef TEMPEST_ATARI_SDLW_HPP
#define TEMPEST_ATARI_SDLW_HPP

#include "../utils/types.hpp"
#include "SDL2/SDL.h"
#include <string>

/**
 * @brief spécifique à l'implémentation du Rectangle paramétré par T
 *
 */
namespace impl {
template<typename T, typename Enable = void>
class base_Rect;

template<typename T>
class base_Rect<T, std::enable_if_t<std::is_same<T, f32>::value>>
{
protected:
  SDL_FRect r_;
};

template<typename T>
class base_Rect<T, std::enable_if_t<std::is_same<T, i32>::value>>
{
protected:
  SDL_Rect r_;
};
}

/**
 * @brief Wrapper autour de la SDL avec gestion des erreurs et de la mémoire
 * (RAII)
 *
 */
namespace SDLW {

/// Forward declaration
class Renderer;

/**
 * \~english @brief Class template allowing float or integer parametrized
 * Rectangles
 *
 * \~english @tparam T parameter is either float (f32) or int (i32)
 */
template<typename T>
class Rect_T : public impl::base_Rect<T>
{
  friend class Renderer;

public:
  Rect_T() = delete;
  /**
   * \~french @brief Construit un objet Rectangle paramétré par T
   *
   * \~french @param x position en x du rectangle
   * \~french @param y position en y du rectangle
   * \~french @param w largeur du rectangle
   * \~french @param h hauteur du rectangle
   */
  Rect_T(T x, T y, T w, T h)
  {
    impl::base_Rect<T>::r_.x = x;
    impl::base_Rect<T>::r_.y = y;
    impl::base_Rect<T>::r_.w = w;
    impl::base_Rect<T>::r_.h = h;
  };
  ~Rect_T(){};

  /**
   * \~french @brief Renvoie la valeur x du rectanlge
   *
   * \~french @return T valeur issue du Rectangle
   */
  T x() const { return impl::base_Rect<T>::r_.x; };
  /**
   * \~french @brief Renvoie la valeur y du rectanlge
   *
   * \~french @return T valeur issue du Rectangle
   */
  T y() const { return impl::base_Rect<T>::r_.y; };
  /**
   * \~french @brief Renvoie la valeur w du rectanlge
   *
   * \~french @return T valeur issue du Rectangle
   */
  T w() const { return impl::base_Rect<T>::r_.w; };
  /**
   * \~french @brief Renvoie la valeur h du rectanlge
   *
   * \~french @return T valeur issue du Rectangle
   */
  T h() const { return impl::base_Rect<T>::r_.h; };
};

//// Window
/**
 * \~french @brief Classe Window encapsulant la structure SDL sous-jacente
 * et exposant les fonctions de rendu utilisée
 *
 */
class Window
{
  friend class Renderer;

private:
  /**
   * \~french @brief Le pointeur sur la structure SDL sous-jacente
   * \~english @brief the pointer on the underlying structure
   *
   */
  SDL_Window* w_;

public:
  Window() = delete;
  Window(const SDLW::Window&) = delete;
  /**
   * \~english @brief Create a window with the specified position, dimensions,
   * and flags.
   *
   * `flags` may be any of the following OR'd together:
   *
   * - `SDL_WINDOW_FULLSCREEN`: fullscreen window
   * - `SDL_WINDOW_FULLSCREEN_DESKTOP`: fullscreen window at desktop resolution
   * - `SDL_WINDOW_OPENGL`: window usable with an OpenGL context
   * - `SDL_WINDOW_VULKAN`: window usable with a Vulkan instance
   * - `SDL_WINDOW_METAL`: window usable with a Metal instance
   * - `SDL_WINDOW_HIDDEN`: window is not visible
   * - `SDL_WINDOW_BORDERLESS`: no window decoration
   * - `SDL_WINDOW_RESIZABLE`: window can be resized
   * - `SDL_WINDOW_MINIMIZED`: window is minimized
   * - `SDL_WINDOW_MAXIMIZED`: window is maximized
   * - `SDL_WINDOW_INPUT_GRABBED`: window has grabbed input focus
   * - `SDL_WINDOW_ALLOW_HIGHDPI`: window should be created in high-DPI mode if
   *   supported (>= SDL 2.0.1)
   *
   * \~english @param title the title of the window, in UTF-8 encoding
   * \~english @param x the x position of the window, `SDL_WINDOWPOS_CENTERED`,
   * or `SDL_WINDOWPOS_UNDEFINED`
   * \~english @param y the y position of the window, `SDL_WINDOWPOS_CENTERED`,
   * or `SDL_WINDOWPOS_UNDEFINED`
   * \~english @param w the width of the window, in screen coordinates
   * \~english @param h the height of the window, in screen coordinates
   * \~english @param flags 0, or one or more SDL_WindowFlags OR'd together
   */
  Window(const std::string& title, i32 x, i32 y, i32 w, i32 h, u32 flags);
  ~Window();
};

//// Renderer
/**
 * \~french @brief Classe Renderer encapsulant la structure SDL sous-jacente
 * et exposant les fonctions de rendu utilisée
 *
 */
class Renderer
{
private:
  /**
   * \~french @brief Le pointeur sur la structure SDL sous-jacente
   * \~english @brief the pointer on the underlying structure
   *
   */
  SDL_Renderer* r_;

public:
  Renderer() = delete;
  Renderer(const SDLW::Renderer&) = delete;
  /**
   * \~french @brief Construit l'objet Renderer avec un contexte de rendu 2D
   * \~english @brief Create a 2D rendering context for a window.
   *
   * \~french @param window La fenêtre sur laquelle le rendu sera affiché
   * \~french @param index
   * \~french @param flags 0, ou plusieurs SDL_RendererFlags réduite par
   * l'opérateur OU
   *
   * \~english @param window the window where rendering is displayed
   * \~english @param index the index of the rendering driver to initialize, or
   * -1 to initialize the first one supporting the requested flags
   * \~english @param flags 0, or one or more SDL_RendererFlags OR'd together
   */
  Renderer(SDLW::Window& window, i32 index, u32 flags);
  /**
   * \~french @brief Destruction de l'objet et de la mémoire allouée
   * dynamiquement
   *
   */
  ~Renderer();

  /**
   * \~english @brief Draw a rectangle on the current rendering target.
   *
   * \~english @param rect A reference to a wrapped `Rect_T` object
   */
  void RenderDrawRect(const SDLW::Rect_T<i32>& rect);
  /**
   * \~english @brief Fill a rectangle on the current rendering target with the
   * drawing color. The current drawing color is set by
   * SDL_SetRenderDrawColor(), and the color's alpha value is ignored unless
   * blending is enabled with the appropriate call to
   * SDL_SetRenderDrawBlendMode().
   *
   * \~english @param rect A reference to a wrapped `Rect_T` object
   */
  void RenderFillRect(const SDLW::Rect_T<i32>& rect);
  /**
   * \~english @brief Fill a rectangle on the current rendering target with the
   * drawing color at subpixel precision.
   *
   * \~english @param rect A reference to a wrapped `Rect_T` object
   */
  void RenderFillRectF(const SDLW::Rect_T<f32>& rect);

  /**
   * \~english @brief Draw a line on the current rendering target at subpixel
   * precision.
   *
   * \~english @param x1 the x coordinate of the start point
   * \~english @param y1 the y coordinate of the start point
   * \~english @param x2 the x coordinate of the end point
   * \~english @param y2 the y coordinate of the end point
   */
  void RenderDrawLineF(f32 x1, f32 y1, f32 x2, f32 y2);
  /**
   * \~english @brief Draw a line on the current rendering target.
   * SDL_RenderDrawLine() draws the line to include both end points.
   *
   * \~english @param x1 the x coordinate of the start point
   * \~english @param y1 the y coordinate of the start point
   * \~english @param x2 the x coordinate of the end point
   * \~english @param y2 the y coordinate of the end point
   */
  void RenderDrawLine(i32 x1, i32 y1, i32 x2, i32 y2);

  /**
   * \~english @brief Set the color used for drawing operations (Rect, Line and
   * Clear). Set the color for drawing or filling rectangles, lines, and points,
   * and for SDL_RenderClear().
   *
   * \~english @param r the red value used to draw on the rendering target
   * \~english @param g the green value used to draw on the rendering target
   * \~english @param b the blue value used to draw on the rendering target
   * \~english @param a the alpha value used to draw on the rendering target;
   * usually `SDL_ALPHA_OPAQUE` (255)
   */
  void SetRenderDrawColor(u8 r, u8 g, u8 b, u8 a);
  /**
   * \~english @brief Update the screen with any rendering performed since the
   * previous call.
   *
   * SDL's rendering functions operate on a backbuffer; that is, calling a
   * rendering function such as SDL_RenderDrawLine() does not directly put a
   * line on the screen, but rather updates the backbuffer. As such, you compose
   * your entire scene and *present* the composed backbuffer to the screen as a
   * complete picture.
   *
   * Therefore, when using SDL's rendering API, one does all drawing intended
   * for the frame, and then calls this function once per frame to present the
   * final drawing to the user.
   *
   * The backbuffer should be considered invalidated after each present; do not
   * assume that previous contents will exist between frames. You are strongly
   * encouraged to call SDL_RenderClear() to initialize the backbuffer before
   * starting each new frame's drawing, even if you plan to overwrite every
   * pixel.
   *
   */
  void RenderPresent();
  /**
   * \~english @brief Clear the current rendering target with the drawing color.
   *
   * This function clears the entire rendering target, ignoring the viewport and
   * the clip rectangle.
   *
   */
  void RenderClear();
};

/**
 * \~english @brief Initialize the SDL library.
 *
 * The file I/O (for example: SDL_RWFromFile)
 * and threading (SDL_CreateThread) subsystems are initialized by default.
 *
 * `flags` may be any of the following OR'd together:
 *
 * - `SDL_INIT_TIMER`: timer subsystem
 * - `SDL_INIT_AUDIO`: audio subsystem
 * - `SDL_INIT_VIDEO`: video subsystem; automatically initializes the events
 *   subsystem
 * - `SDL_INIT_JOYSTICK`: joystick subsystem; automatically initializes the
 *   events subsystem
 * - `SDL_INIT_HAPTIC`: haptic (force feedback) subsystem
 * - `SDL_INIT_GAMECONTROLLER`: controller subsystem; automatically
 *   initializes the joystick subsystem
 * - `SDL_INIT_EVENTS`: events subsystem
 * - `SDL_INIT_EVERYTHING`: all of the above subsystems
 * - `SDL_INIT_NOPARACHUTE`: compatibility; this flag is ignored
 *
 * \~english @param flags subsystem initialization flags
 */
void
Init(u32 flags);

/**
 *  \~english @brief Clean up all initialized subsystems.
 *
 */
void
Quit();

// Time

/**
 * \~english @brief Get the number of milliseconds since SDL library
 * initialization.
 *
 * \~english @return u64 a value value representing the number of milliseconds
 * since the SDL library initialized.
 */
u64
GetTicks64();

/**
 * \~english @brief Get the current value of the high resolution counter. This
 * function is typically used for profiling. The counter values are only
 * meaningful relative to each other. Differences between values can be
 * converted to times by using SDL_GetPerformanceFrequency().
 *
 * \~english @return u64 the current counter value.
 */
u64
GetPerformanceCounter();

/**
 * \~english @brief Wait a specified number of milliseconds before returning.
 * This function waits a specified number of milliseconds before returning. It
 * waits at least the specified time, but possibly longer due to OS scheduling.
 *
 * \~english @param ms the number of milliseconds to delay
 */
void
Delay(u32 ms);

/**
 * \~english @brief Get the count per second of the high resolution counter.
 *
 * \~english @return u64 a platform-specific count per second.
 */
u64
GetPerformanceFrequency();

class Event
{
  friend i32 PollEvent(SDLW::Event& e);

private:
  SDL_Event event_;

public:
  Event();
  ~Event();

  u32 getType() const;
  SDL_Keycode getKeycode() const;
};

i32
PollEvent(SDLW::Event& e);
i32
PollEvent();

} // namespace SDLW

#endif