set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/build/bin/")
set(FLEUR_CLI_SOURCE_FILES main.cpp)
add_executable(fleur_cli ${FLEUR_CLI_SOURCE_FILES})
target_link_libraries(fleur_cli ${Boost_LIBRARIES} fleur_static)


#### Install
add_custom_target(
        fleur_cli-install
        COMMAND
            cp -f build/bin/fleur_cli /usr/local/bin/fleur
        COMMAND
            echo 'Installed fleur command line to /usr/local/bin/fleur'
        WORKING_DIRECTORY
            "${PROJECT_SOURCE_DIR}"
)
add_custom_target(
        fleur_cli-uninstall
        COMMAND
            rm /usr/local/bin/fleur
        COMMAND
            echo 'Uninstalled fleur command line'
        WORKING_DIRECTORY
            "${PROJECT_SOURCE_DIR}"
)