project(fleur_src)

set(HEADER_FILES
        include/Requete_parser.h
        include/RestHttp.h
        include/Http.h
        include/HttpException.h)

set(SOURCE_FILES
        src/Requete_parser.cpp
        src/RestHttp.cpp
        src/Http.cpp )

add_library(fleur_src STATIC ${SOURCE_FILES} ${HEADER_FILES})