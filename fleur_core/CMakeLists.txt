project(fleur_static_lib)

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
        include/processing/Processing_wiki.h)

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
        src/processing/Processing_wiki.cpp)

#### Fleur Static Lib
add_library(fleur_static_lib STATIC ${SOURCE_FILES} ${HEADER_FILES})
target_link_libraries(fleur_static_lib ${Boost_LIBRARIES} curl ${CPR_LIBRARIES} gumbo_query_static twitcurl)