if(CMAKE_CXX_COMPILER_ID MATCHES "MSVC" AND ${DEBUG})
   target_compile_options(${TARGET_NAME} PRIVATE /MDd)
   target_compile_options(${TARGET_NAME} PRIVATE /Zi)
   target_compile_options(${TARGET_NAME} PRIVATE /Ob0)
   target_compile_options(${TARGET_NAME} PRIVATE /Od)
   target_compile_options(${TARGET_NAME} PRIVATE /RTC1)

   # Tell linker to include symbol data
    set_target_properties(${TARGET_NAME} PROPERTIES 
        LINK_FLAGS "/INCREMENTAL:NO /DEBUG /OPT:REF /OPT:ICF"
    )

    # Set file name & location
    set_target_properties(${TARGET_NAME} PROPERTIES 
        COMPILE_PDB_NAME ${TARGET_NAME} 
        COMPILE_PDB_OUTPUT_DIR ${CMAKE_BINARY_DIR}
    )
endif()
