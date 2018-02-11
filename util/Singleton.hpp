#ifndef SINGLETON_HPP
#define SINGLETON_HPP

#include "util/Error.hpp"
#include "util/Exception.hpp"
#include "util/NonCopyable.hpp"

/**
* Base class for classes that only exist in one instance.
*/
template <typename T>
class Singleton : public virtual NonCopyable
{
protected:

	/**
	* Pointer to the single instance of the object, or null if none exists.
	*/
	static Singleton<T>* theInstance;

public:

	/**
	* Returns a pointer to the single existing instance of the object,
	* or null if none exists.
	*/
	T *the() { return static_cast<T*>(theInstance); }

	/**
	* Constructor.
	* Automatically sets the sole instance pointer to this object.
	*
	* \throws BadObjectState if another instance of the singleton
	* already exists.
	*/
	Singleton();

	/**
	* Destructor.
	* Resets the instance pointer to null.
	*/
	~Singleton();
};

template <typename T>
Singleton<T>* Singleton<T>::theInstance = nullptr;

template <typename T>
Singleton<T>::Singleton()
{
	if (theInstance) {
		Throw(BadObjectState, "another instance already exists");
	}
	theInstance = this;
}

template <typename T>
Singleton<T>::~Singleton()
{
	if (theInstance != this) {
		panic(THIS_FN, "destructor called for an unregistered instance");
	}
	theInstance = nullptr;
}

#endif
