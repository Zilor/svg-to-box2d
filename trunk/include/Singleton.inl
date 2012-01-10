
template <typename T> T* Singleton<T>::_singleton = 0;

template <class T>
    Singleton<T>::Singleton() {
}

template <class T>
    Singleton<T>::~Singleton() {
}

template <class T>
        T* Singleton<T>::getInstance () {
  if ( ! _singleton ) {
      _singleton = new T;
  }

  return (static_cast<T*> (_singleton));
}


template <class T>
        void Singleton<T>::kill () {
  if ( _singleton )
    {
      delete _singleton;
      _singleton = 0;
    }
}
