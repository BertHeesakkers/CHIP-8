## copy assets
#if(CMAKE_HOST_WIN32)
#    add_custom_command(TARGET ${PROJECT_NAME}
#            POST_BUILD COMMAND python ${SCRIPT_DIR}/CopyAssets.py
#            ${ASSET_DIR}
#            ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Debug/assets/)
#
#    add_custom_command(TARGET ${PROJECT_NAME}
#            POST_BUILD COMMAND python ${SCRIPT_DIR}/CopyAssets.py
#            ${ASSET_DIR}
#            ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Release/assets/)
#else()
#    add_custom_command(TARGET ${PROJECT_NAME}
#            POST_BUILD COMMAND python ${SCRIPT_DIR}/CopyAssets.py
#            ${ASSET_DIR}
#            ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/assets/)
#endif()
