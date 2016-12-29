project(fleur_src)

set(HEADER_FILES
        include/Requete_parser.h
        include/Http.h
        include/HttpException.h
        include/Filter.h
        include/FilterException.h
        include/Processing.h
        include/Xml_parser.h
        include/Include_parser.h
        include/Twitter_parser.h
        include/Twitter.h)

set(SOURCE_FILES
        src/Requete_parser.cpp
        src/Http.cpp
        src/Filter.cpp
        src/Processing.cpp
        src/Xml_parser.cpp
        src/Twitter.cpp)

add_library(fleur_src STATIC ${SOURCE_FILES} ${HEADER_FILES})