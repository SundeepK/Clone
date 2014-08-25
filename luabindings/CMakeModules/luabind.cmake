###
# Helper macro that generates .pc and installs it.
# Argument: name - the name of the .pc package, e.g. "luabind.pc"
###
MACRO(LUABIND_GEN_PC name)
  IF(NOT WIN32)
    CONFIGURE_FILE(${name}.in "${CMAKE_CURRENT_BINARY_DIR}/${name}")
    INSTALL(FILES "${CMAKE_CURRENT_BINARY_DIR}/${name}" DESTINATION lib/pkgconfig)
  ENDIF(NOT WIN32)
ENDMACRO(LUABIND_GEN_PC)

###
#
###
MACRO(LUABIND_TARGET_LIB name)
  IF(WITH_STATIC)
    ADD_LIBRARY(${name} STATIC ${ARGN})
  ELSE(WITH_STATIC)
    ADD_LIBRARY(${name} SHARED ${ARGN})
  ENDIF(WITH_STATIC)
ENDMACRO(LUABIND_TARGET_LIB)

###
# Helper macro that sets the default library properties.
# Argument: name - the target name whose properties are being set
# Argument:
###
MACRO(LUABIND_DEFAULT_PROPS name label)
  GET_TARGET_PROPERTY(type ${name} TYPE)
  IF(${type} STREQUAL SHARED_LIBRARY)
    # Set versions only if target is a shared library
    SET_TARGET_PROPERTIES(${name} PROPERTIES
      VERSION ${LUABIND_VERSION} SOVERSION ${LUABIND_VERSION_MAJOR}
      INSTALL_NAME_DIR ${CMAKE_INSTALL_PREFIX}/lib
      PROJECT_LABEL ${label})
  ELSE(${type} STREQUAL SHARED_LIBRARY)
    SET_TARGET_PROPERTIES(${name} PROPERTIES
      PROJECT_LABEL ${label})
  ENDIF(${type} STREQUAL SHARED_LIBRARY)
ENDMACRO(LUABIND_DEFAULT_PROPS)

###
# Adds the target suffix on Windows.
# Argument: name - the library's target name.
###
MACRO(LUABIND_ADD_LIB_SUFFIX name)
  IF(WIN32)
    SET_TARGET_PROPERTIES(${name} PROPERTIES DEBUG_POSTFIX "_d" RELEASE_POSTFIX "_r")
  ENDIF(WIN32)
ENDMACRO(LUABIND_ADD_LIB_SUFFIX)

###
# Adds the runtime link flags for Win32 binaries and links STLport.
# Argument: name - the target to add the link flags to.
###
MACRO(LUABIND_ADD_RUNTIME_FLAGS name)
  IF(WIN32)
#    SET_TARGET_PROPERTIES(${name} PROPERTIES
#      LINK_FLAGS_DEBUG "${CMAKE_LINK_FLAGS_DEBUG}"
#      LINK_FLAGS_RELEASE "${CMAKE_LINK_FLAGS_RELEASE}")
  ENDIF(WIN32)
  IF(WITH_STLPORT)
    TARGET_LINK_LIBRARIES(${name} ${STLPORT_LIBRARIES})
  ENDIF(WITH_STLPORT)
ENDMACRO(LUABIND_ADD_RUNTIME_FLAGS)

###
# Checks build vs. source location. Prevents In-Source builds.
###
MACRO(CHECK_OUT_OF_SOURCE)
  IF(${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR})
    MESSAGE(FATAL_ERROR "

CMake generation for this project is not allowed within the source directory!
Remove the CMakeCache.txt file and try again from another folder, e.g.:

   rm CMakeCache.txt
   mkdir cmake
   cd cmake
   cmake -G \"Unix Makefiles\" ..
    ")
  ENDIF(${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR})

ENDMACRO(CHECK_OUT_OF_SOURCE)

MACRO(LUABIND_SETUP_DEFAULT_OPTIONS)
  OPTION(WITH_COVERAGE            "With Code Coverage Support"                    OFF)

  # Default to static building on Windows.
  IF(WIN32)
    OPTION(WITH_STATIC            "With static libraries."                        ON )
  ELSE(WIN32)
    OPTION(WITH_STATIC            "With static libraries."                        OFF)
  ENDIF(WIN32)

  ###
  # Optional support
  ###
  IF(WIN32)
    OPTION(WITH_STLPORT             "With STLport support."                       ON )
  ELSE(WIN32)
    OPTION(WITH_STLPORT             "With STLport support."                       OFF)
  ENDIF(WIN32)
ENDMACRO(LUABIND_SETUP_DEFAULT_OPTIONS)

MACRO(LUABIND_SETUP_BUILD)

  #-----------------------------------------------------------------------------
  # Setup the buildmode variables.
  SET(CMAKE_CONFIGURATION_TYPES "Debug;Release" CACHE STRING "" FORCE)

  IF(CMAKE_BUILD_TYPE MATCHES "Debug")
    SET(NL_BUILD_MODE "NL_DEBUG")
  ELSE(CMAKE_BUILD_TYPE MATCHES "Debug")
    IF(CMAKE_BUILD_TYPE MATCHES "Release")
      SET(NL_BUILD_MODE "NL_RELEASE")
    ELSE(CMAKE_BUILD_TYPE MATCHES "Release")
      SET(NL_BUILD_MODE "NL_RELEASE")
      # enforce release mode if it's neither Debug nor Release
      SET(CMAKE_BUILD_TYPE "Release" CACHE STRING "" FORCE)
    ENDIF(CMAKE_BUILD_TYPE MATCHES "Release")
  ENDIF(CMAKE_BUILD_TYPE MATCHES "Debug")

  IF(WIN32)
    # don't use a /O[012x] flag if you want custom optimizations
    SET(SPEED_OPTIMIZATIONS "/Ob2 /Oi /Ot /Oy /GT /GF /GS-")
    # without inlining it's unusable, use custom optimizations again
    SET(MIN_OPTIMIZATIONS "/Ob1")

    SET(PLATFORM_CFLAGS "/D_CRT_SECURE_NO_WARNINGS /DWIN32 /D_WINDOWS /W3")

    IF(WITH_STLPORT)
      # deactivate all global include paths
      SET(PLATFORM_CFLAGS "${PLATFORM_CFLAGS} /X")
    ENDIF(WITH_STLPORT)

	SET(PLATFORM_CXXFLAGS ${PLATFORM_CFLAGS})

    # Common link flags
    SET(PLATFORM_LINKFLAGS "/INCREMENTAL:NO")

    SET(LUABIND_DEBUG_CFLAGS "/MDd /RTC1 /D_DEBUG ${MIN_OPTIMIZATIONS}")
    SET(LUABIND_RELEASE_CFLAGS "/MD /D NDEBUG ${SPEED_OPTIMIZATIONS}")
    SET(LUABIND_DEBUG_LINKFLAGS "/NODEFAULTLIB:msvcrt")
    SET(LUABIND_RELEASE_LINKFLAGS "/OPT:REF /OPT:ICF")
  ELSE(WIN32)
    SET(PLATFORM_CFLAGS "-g -ftemplate-depth-48 -D_REENTRANT -Wall -ansi -W")
    IF(WITH_COVERAGE)
      SET(PLATFORM_CFLAGS "-fprofile-arcs -ftest-coverage ${PLATFORM_CFLAGS}")
    ENDIF(WITH_COVERAGE)
    SET(PLATFORM_CXXFLAGS ${PLATFORM_CFLAGS})

    # Equivalent is already used under Mac OS X
    IF(NOT APPLE)
      SET(PLATFORM_LINKFLAGS "-Wl,--as-needed -Wl,--no-undefined")
    ENDIF(NOT APPLE)

    SET(LUABIND_DEBUG_CFLAGS "-D_DEBUG")
    SET(LUABIND_RELEASE_CFLAGS "-DNDEBUG -O6")
  ENDIF(WIN32)

  # Determine host CPU
  IF(UNIX AND NOT WIN32)
    FIND_PROGRAM(CMAKE_UNAME uname /bin /usr/bin /usr/local/bin )
    IF(CMAKE_UNAME)
      EXEC_PROGRAM(uname ARGS -m OUTPUT_VARIABLE CMAKE_SYSTEM_PROCESSOR)
      SET(CMAKE_SYSTEM_PROCESSOR ${CMAKE_SYSTEM_PROCESSOR} CACHE INTERNAL "processor type (i386 and x86_64)")
      IF(CMAKE_SYSTEM_PROCESSOR MATCHES "x86_64")
        ADD_DEFINITIONS(-DHAVE_X86_64)
      ELSEIF(CMAKE_SYSTEM_PROCESSOR MATCHES "ia64")
        ADD_DEFINITIONS(-DHAVE_IA64)
      ELSE(CMAKE_SYSTEM_PROCESSOR MATCHES "x86_64")
        ADD_DEFINITIONS(-DHAVE_X86)
      ENDIF(CMAKE_SYSTEM_PROCESSOR MATCHES "x86_64")
    ELSE(CMAKE_UNAME)  # Assume that if uname is not found that we're x86.
      ADD_DEFINITIONS(-DHAVE_X86)
    ENDIF(CMAKE_UNAME)
  ENDIF(UNIX AND NOT WIN32)

ENDMACRO(LUABIND_SETUP_BUILD)

MACRO(LUABIND_SETUP_BUILD_FLAGS)
  #SET(CMAKE_DEBUG_POSTFIX "_d")
  #SET(CMAKE_RELEASE_POSTFIX "_r")

  SET(CMAKE_C_FLAGS ${PLATFORM_CFLAGS} CACHE STRING "" FORCE)
  SET(CMAKE_CXX_FLAGS ${PLATFORM_CXXFLAGS} CACHE STRING "" FORCE)

  ## Debug
  SET(CMAKE_C_FLAGS_DEBUG ${LUABIND_DEBUG_CFLAGS} CACHE STRING "" FORCE)
  SET(CMAKE_CXX_FLAGS_DEBUG ${LUABIND_DEBUG_CFLAGS} CACHE STRING "" FORCE)
  SET(CMAKE_EXE_LINKER_FLAGS_DEBUG "${PLATFORM_LINKFLAGS} ${LUABIND_DEBUG_LINKFLAGS}" CACHE STRING "" FORCE)
  SET(CMAKE_MODULE_LINKER_FLAGS_DEBUG "${PLATFORM_LINKFLAGS} ${LUABIND_DEBUG_LINKFLAGS}" CACHE STRING "" FORCE)
  SET(CMAKE_SHARED_LINKER_FLAGS_DEBUG "${PLATFORM_LINKFLAGS} ${LUABIND_DEBUG_LINKFLAGS}" CACHE STRING "" FORCE)

  ## Release
  SET(CMAKE_C_FLAGS_RELEASE ${LUABIND_RELEASE_CFLAGS} CACHE STRING "" FORCE)
  SET(CMAKE_CXX_FLAGS_RELEASE ${LUABIND_RELEASE_CFLAGS} CACHE STRING "" FORCE)
  SET(CMAKE_EXE_LINKER_FLAGS_RELEASE "${PLATFORM_LINKFLAGS} ${LUABIND_RELEASE_LINKFLAGS}" CACHE STRING "" FORCE)
  SET(CMAKE_MODULE_LINKER_FLAGS_RELEASE "${PLATFORM_LINKFLAGS} ${LUABIND_RELEASE_LINKFLAGS}" CACHE STRING "" FORCE)
  SET(CMAKE_SHARED_LINKER_FLAGS_RELEASE "${PLATFORM_LINKFLAGS} ${LUABIND_RELEASE_LINKFLAGS}" CACHE STRING "" FORCE)
ENDMACRO(LUABIND_SETUP_BUILD_FLAGS)

