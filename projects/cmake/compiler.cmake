set(COMPILER_MSVC 0)
set(COMPILER_GCC 1)
set(COMPILER_EMCC 2)
set(COMPILER_UNKNOWN 3)

if(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    set(COMPILER ${COMPILER_MSVC})
    message("Compiler is set to MSVC...")
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    set(COMPILER ${COMPILER_GCC})
    message("Compiler is set to GNU...")
elseif(CMAKE_CXX_COMPILER MATCHES "/em\\+\\+(-[a-zA-Z0-9.])?")
    set(COMPILER ${COMPILER_EMCC})
    message("Compiler is set to EMCC...")
else()
    set(COMPILER ${COMPILER_UNKNOWN})
    message(FATAL_ERROR "Compiler could not be determined!")
endif()
