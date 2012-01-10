#ifndef SINGLETON_HPP_INCLUDED
#define SINGLETON_HPP_INCLUDED

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
