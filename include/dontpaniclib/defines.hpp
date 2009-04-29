#ifndef DONTPANIC_DEFINES_HPP
#define DONTPANIC_DEFINES_HPP
// ---------------------------------------------------------------------------------
//boost includes
#include <boost/shared_ptr.hpp>
#include <boost/weak_ptr.hpp>
// ---------------------------------------------------------------------------------
#define DECLARE_SMARTPOINTERS(clazz)\
 typedef boost::shared_ptr<clazz> clazz##_ptr;\
 typedef boost::weak_ptr<clazz> clazz##_weak_ptr
// ---------------------------------------------------------------------------------
#define TYPE(clazz) \
 typedef clazz type; \
 typedef boost::shared_ptr<clazz> ptr; \
 typedef boost::weak_ptr<clazz> weak_ptr
// ---------------------------------------------------------------------------------
#endif //DONTPANIC_DEFINES_HPP

