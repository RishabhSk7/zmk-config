target_include_directories(app PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/include
)

target_sources(app PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/src/main.c
    ${CMAKE_CURRENT_LIST_DIR}/src/scuba_cat_frames.c
)
