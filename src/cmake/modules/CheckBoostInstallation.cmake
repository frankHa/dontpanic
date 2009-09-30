MESSAGE(STATUS "checking for required boost libs")

SET(Boost_ADDITIONAL_VERSIONS "1.38" "1.38.0" "1.37" "1.37.0")

IF(_SOLARIS)
  #using cmake 2.4 on Solaris, which is unable to detect 
  #the boost version by itself 
  SET(Boost_LIB_VERSION 1_38)
ELSE(_SOLARIS)
  SET(BOOST_ROOT "/usr/local")
ENDIF(_SOLARIS)

IF(BOOST_LINK_STATIC)
  SET(Boost_USE_STATIC_LIBS ON)
ENDIF(BOOST_LINK_STATIC)

IF(_WIN)
  #SET(BOOST_ROOT ${CMAKE_CURRENT_SOURCE_DIR}/dependencies)
  #MESSAGE(STATUS "Setting BOOST_ROOT to ${BOOST_ROOT}")
ENDIF(_WIN)
FIND_PACKAGE(Boost REQUIRED)

IF(Boost_FOUND)
  #--------------------------------------------------------------------------------------------
  #for some reason we need to do this here again (copied from FindBoost.cmake)
  #in order to detect the boost version in use reliably
  SET(BOOST_VERSION 0)
  SET(BOOST_LIB_VERSION "")
  FILE(READ "${Boost_INCLUDE_DIR}/boost/version.hpp" _boost_VERSION_HPP_CONTENTS)
  
  STRING(REGEX REPLACE ".*#define BOOST_VERSION ([0-9]+).*" "\\1" Boost_VERSION "${_boost_VERSION_HPP_CONTENTS}")
  STRING(REGEX REPLACE ".*#define BOOST_LIB_VERSION \"([0-9_]+)\".*" "\\1" Boost_LIB_VERSION "${_boost_VERSION_HPP_CONTENTS}")
    
  SET(Boost_LIB_VERSION ${Boost_LIB_VERSION} CACHE INTERNAL "The library version string for boost libraries")
  SET(Boost_VERSION ${Boost_VERSION} CACHE INTERNAL "The version number for boost libraries")
  #--------------------------------------------------------------------------------------------
  MESSAGE(STATUS "checking for required boost libs - found")
  IF(NOT Boost_LIBRARY_DIRS)
	IF(_WIN)
                SET(_x64)
                IF(_WIN64)
                  SET(_x64 "x64")
                ENDIF(_WIN64)
		SET(Boost_LIBRARY_DIRS ${Boost_INCLUDE_DIRS}/../../lib/${_x64})
		MESSAGE(STATUS "Boost lib dir: ${Boost_LIBRARY_DIRS}")
      ENDIF(_WIN)
  ENDIF(NOT Boost_LIBRARY_DIRS)

  INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIRS})
  LINK_DIRECTORIES(${Boost_LIBRARY_DIRS})

  SET(_THREAD "boost_thread")
  SET(_SYSTEM "boost_system")
  SET(_FILESYSTEM "boost_filesystem")

  SET(_PREFIX "")
  SET(_VERSION "-${Boost_LIB_VERSION}")
  SET(_ABI "")

  IF(_WIN)
    IF(BOOST_LINK_STATIC)
      SET(_PREFIX "lib")
    ENDIF(BOOST_LINK_STATIC)
    IF(MSVC90)
      SET(_ABI "-vc90-mt")
    ELSE(MSVC90)
      SET(_ABI "-vc80-mt")
    ENDIF(MSVC90)
  ELSE(_WIN)
   IF(_SOLARIS)
    IF(__SUNCC__)
    	SET(_ABI "-sw-mt")
    ELSE(__SUNCC__)
    	SET(_ABI "-gcc34-mt")
    ENDIF(__SUNCC__)
   ELSE(_SOLARIS)
    IF(_LINUX)
     SET(_ABI "-gcc43-mt")
    ENDIF(_LINUX)
   ENDIF(_SOLARIS)
  ENDIF(_WIN)

  SET(BOOST_LIB_THREAD "${_PREFIX}${_THREAD}${_ABI}${_VERSION}")
  SET(BOOST_LIB_SYSTEM "${_PREFIX}${_SYSTEM}${_ABI}${_VERSION}")
  SET(BOOST_LIB_FILESYSTEM "${_PREFIX}${_FILESYSTEM}${_ABI}${_VERSION}")
  MESSAGE (STATUS boost thread:  ${BOOST_LIB_THREAD})

ENDIF(Boost_FOUND)

