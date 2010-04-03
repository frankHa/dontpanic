##################################################################
# Checks for libuuid headers/library
####################################################################

MESSAGE(STATUS "checking for libuuid")

SET(libuuid_INCLUDES STLPort_INCLUDES-NOTFOUND)
SET(libuuid_LIB STLPort_LIB-NOTFOUND)

FIND_PATH(libuuid_INCLUDES uuid/uuid.h
          PATHS
          /usr/include/
          /usr/local/include/
          ENV PREFIX
         )

FIND_LIBRARY( libuuid_LIB
     NAMES uuid
     PATHS
     /usr/lib
     /usr/local/lib
     ENV PREFIX
)

MARK_AS_ADVANCED(
                 libuuid_LIB
                 libuuid_INCLUDES
                )

IF(libuuid_INCLUDES AND libuuid_LIB)
        SET(libuuid_FOUND "YES")
ELSE(libuuid_INCLUDES AND libuuid_LIB)
  SET( libuuid_FOUND "NO")
ENDIF(libuuid_INCLUDES AND libuuid_LIB)

IF(libuuid_FOUND)
        MESSAGE(STATUS "checking for libuuid - found")
        INCLUDE_DIRECTORIES( BEFORE ${libuuid_INCLUDES} )
ELSE (libuuid_FOUND)
        IF(libuuid_FIND_REQUIRED)
             MESSAGE(FATAL_ERROR "checking for libuuid - not found...")
        ELSE(libuuid_FIND_REQUIRED)
             MESSAGE(STATUS "*****************************************")
             MESSAGE(STATUS "checking for libuuid - not found")
             MESSAGE(STATUS "falling back to your Qt's default Uuid generator")
             MESSAGE(STATUS "*****************************************")
             SET( libuuid_LIB "")
             SET( libuuid_INCLUDES "")
        ENDIF(libuuid_FIND_REQUIRED)
ENDIF(libuuid_FOUND)

IF(libuuid_FOUND)
  SET(HAVE_LIBUUID TRUE)
ENDIF(libuuid_FOUND)
