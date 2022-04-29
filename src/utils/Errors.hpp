/**
 * @file Utils.hpp
 * @author Tarek Kunze(https://github.com/arxaqapi)
 * @version 0.1
 * @date 2022-02-02
 *
 * @copyright Copyright (c) 2022
 *
 * @brief
 */

#ifndef H_TEMPEST_GAME_INC_ERRORS_
#define H_TEMPEST_GAME_INC_ERRORS_

#include "types.hpp"
#include <stdexcept>

/**
 * @brief Erreurs personnalisées afin de faciliter le développement
 *
 */
namespace errors {
/**
 * @brief A utiliser dans le cas ou la méthode n'a pas encore été implémentée
 *
 */
struct NotImplemented : public std::exception
{
  const char* what() const throw();
};

/**
 * @brief A utiliser dans le cas ou la méthode ou un certain comportement
 * n'a pas encore été testée
 *
 */
struct NotTested : public std::exception
{
  const char* what() const throw();
};

/**
 * @brief A utiliser dans le cas ou le changement d'état demandé
 * n'est pas autorisée par la machine à état
 *
 */
struct NonValidStateSwitch : public std::exception
{
  const char* what() const throw();
};

/**
 * @brief A utiliser dans le cas ou le fichier n'a pas pu ou n'a pas été ouvert
 *
 */
struct FileNotOpened : public std::exception
{
  const char* what() const throw();
};

/**
 * @brief A utiliser dans le cas ou le caractère demandé
 * n'est pas supporté par la police d'écriture actuelle
 *
 */
struct NonValidCharacterRequested : public std::exception
{
  const char* what() const throw();
};

/**
 * @brief A utiliser afin de wrapper les messages d'érreurs de la SDL
 * ou pour exprimer une erreur propre à la SDL
 *
 */
struct SdlError : public std::exception
{
  std::string msg_;
  SdlError(const std::string& msg);
  const char* what() const throw();
};

}

#endif