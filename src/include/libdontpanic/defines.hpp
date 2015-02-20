#ifndef DONTPANIC_DEFINES_HPP
#define DONTPANIC_DEFINES_HPP
// ---------------------------------------------------------------------------------
//dp includes
#include "dp_export.hpp"
#include "libdontpanic/success.hpp"
//KDE includes
#define TRANSLATION_DOMAIN "dontpanic"
#include <KLocalizedString>
//Qt includes
#include <QLoggingCategory>
// ---------------------------------------------------------------------------------
#ifdef __GNUC__
#undef __FUNCTION__
#define __FUNCTION__ __PRETTY_FUNCTION__
#endif //__GNUC__
// ---------------------------------------------------------------------------------
#ifdef __SUNCC__
#define __FUNCTION__ __func__
#endif // __SUNCC__
// ---------------------------------------------------------------------------------
//boost includes
//#include <boost/shared_ptr.hpp>
//#include <boost/weak_ptr.hpp>
// ---------------------------------------------------------------------------------
#define DECLARE_SMARTPOINTERS(clazz)
//  typedef QSharedPointer<clazz> clazz##_ptr;
//  typedef boost::weak_ptr<clazz> clazz##_weak_ptr
// ---------------------------------------------------------------------------------
#define FORWARD_DECL(clazz) \
  class clazz;\
  DECLARE_SMARTPOINTERS(clazz)
// ---------------------------------------------------------------------------------
#define TYPE(clazz) \
  typedef clazz type; 
//  typedef boost::shared_ptr<clazz> ptr; 
//  typedef boost::weak_ptr<clazz> weak_ptr
// ---------------------------------------------------------------------------------
#endif //DONTPANIC_DEFINES_HPP

