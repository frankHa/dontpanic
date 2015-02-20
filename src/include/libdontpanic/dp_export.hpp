#ifndef DP_EXPORT_HPP
#define DP_EXPORT_HPP
#define __DP_HAVE_GCC_VISIBILITY
// ---------------------------------------------------------------------------------
#ifndef DP_EXPORT
# ifdef __DP_HAVE_GCC_VISIBILITY
#  define DP_NO_EXPORT __attribute__ ((visibility("hidden")))
#  define DP_EXPORT __attribute__ ((visibility("default")))
#  define DP_IMPORT __attribute__ ((visibility("default")))
# elif defined(_WIN32) || defined(_WIN64)
#  define DP_NO_EXPORT
#  define DP_EXPORT __declspec(dllexport)
#  define DP_IMPORT __declspec(dllimport)
# else
#  define DP_NO_EXPORT
#  define DP_EXPORT
#  define DP_IMPORT
# endif
#endif
// ---------------------------------------------------------------------------------
#endif //DP_EXPORT_HPP
