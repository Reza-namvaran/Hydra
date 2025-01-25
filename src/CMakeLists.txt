set (PROJECT_SOURCES
    main.c
    ${CORE_SOURCES}
)

add_executable(${PROJECT_NAME}
    ${PROJECT_SOURCES}
)

include_directories(
    ${PROJECT_SOURCE_DIR}/include
)

target_include_directories(${PROJECT_NAME} PRIVATE
    ${PROJECT_SOURCE_DIR}/include
)

set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)