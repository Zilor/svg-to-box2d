#ifndef SINGLETON_HPP_INCLUDED
#define SINGLETON_HPP_INCLUDED

/*!
*   \file Singleton.hpp
*   \brief The singleton template header
*   \version 0.1
*   \author Bastien (Bigz) Cramillet
*/

#include "../Constants.hpp"

template <typename T>
class Singleton
{
protected:
  //! Constructeur/destructeur
  Singleton ();
  ~Singleton ();

public:
  //! Interface publique
  static T *getInstance ();

  static void kill ();


private:
  //! Unique instance
  static T *_singleton;

};

#include "Singleton.inl"

#endif // SINGLETON_HPP_INCLUDED
