#ifndef NONCOPYABLE_HPP
#define NONCOPYABLE_HPP

/// Interface for objects that are not copyable nor passable by value.
class NonCopyable
{
public:

	/// Default constructor (empty).
	NonCopyable() {}

	/// Default destructor (empty).
	virtual ~NonCopyable() {}

	/// Deleted copy-constructor.
	NonCopyable(NonCopyable &src) = delete;

	/// Deleted assignment operator.
	NonCopyable &operator=(const NonCopyable &src) = delete;
};

#endif
