project(fleur_src)

set(HEADER_FILES
        include/parser/Requete_parser.h
        include/service/Http.h
        include/HttpException.h
        include/Filter.h
        include/FilterException.h
        include/processing/Processing_http.h
        include/parser/Xml_parser.h
        include/parser/Include_parser.h
        include/parser/Twitter_parser.h
        include/service/Twitter.h
        include/processing/Processing_twitter.h
        include/processing/Processing.h)

set(SOURCE_FILES
        src/parser/Requete_parser.cpp
        src/service/Http.cpp
        src/Filter.cpp
        src/processing/Processing_http.cpp
        src/parser/Xml_parser.cpp
        src/service/Twitter.cpp
        src/processing/Processing_twitter.cpp
        src/processing/Processing.cpp )

add_library(fleur_src STATIC ${SOURCE_FILES} ${HEADER_FILES})