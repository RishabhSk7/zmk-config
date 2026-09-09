# Only the split central (left) half gets the custom Scuba Cat screen.
if (CONFIG_ZMK_SPLIT AND CONFIG_ZMK_SPLIT_ROLE_CENTRAL)
    target_include_directories(app PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/include
    )

    target_sources(app PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/src/scuba_cat.c
        ${CMAKE_CURRENT_LIST_DIR}/src/scuba_cat_frames.c
    )
endif()
