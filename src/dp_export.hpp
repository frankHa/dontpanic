#ifndef DP_EXPORT_HPP
#define DP_EXPORT_HPP
/* needed for KDE_EXPORT and KDE_IMPORT macros */
#include <kdemacros.h>
// ---------------------------------------------------------------------------------
#ifndef DP_EXPORT
# if defined(MAKE_DPPRIVATE_LIB)
   /* We are building this library */
#  define DP_EXPORT KDE_EXPORT
# else
   /* We are using this library */
#  define DP_EXPORT KDE_IMPORT
# endif
#endif
// ---------------------------------------------------------------------------------
#endif //DP_EXPORT_HPP