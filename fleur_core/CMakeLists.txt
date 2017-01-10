set(HEADER_FILES
        include/parser/Requete_parser.h
        include/service/Http.h
        include/HttpException.h
        include/Filter.h
        include/FilterException.h
        include/processing/Processing_http.h
        include/parser/Include_parser.h
        include/parser/Twitter_parser.h
        include/service/Twitter.h
        include/processing/Processing_twitter.h
        include/processing/Processing.h
        include/ProcessingException.h
        include/parser/Wiki_parser.h
        include/service/Wiki.h
        include/utils/sha1.h
        include/processing/Processing_wiki.h
        include/parser/WolframAlpha_parser.h
        include/service/WolframAlpha.h
        include/processing/Processing_wolframalpha.h)

set(SOURCE_FILES
        src/parser/Requete_parser.cpp
        src/service/Http.cpp
        src/parser/Filter.cpp
        src/processing/Processing_http.cpp
        src/service/Twitter.cpp
        src/processing/Processing_twitter.cpp
        src/processing/Processing.cpp
        src/entrypoint.cpp
        src/processing/Processing.cpp
        src/service/Wiki.cpp
        src/utils/sha1.cpp
        src/processing/Processing_wiki.cpp src/service/WolframAlpha.cpp src/processing/Processing_wolframalpha.cpp)

add_library(fleur_static STATIC ${SOURCE_FILES} ${HEADER_FILES})
target_link_libraries(fleur_static ${Boost_LIBRARIES} curl ${CPR_LIBRARIES} gumbo_query_static twitcurl)


#### Install
add_custom_target(
        fleur_static-install
        COMMAND
            cp build/lib/libfleur_static.a /usr/local/lib/fleur.a
        COMMAND
            echo 'Installed fleur static library to /usr/local/lib/fleur.a'
        COMMAND
            cp fleur_cli/fleur.h /usr/local/include/fleur.h
        COMMAND
            echo 'Installed fleur.h header to /usr/local/include/fleur.h'
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