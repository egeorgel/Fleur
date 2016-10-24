project(fleur_src)

set(HEADER_FILES
        Requete_parser.h)

set(SOURCE_FILES
        Requete_parser.cpp )

add_library(fleur_src STATIC ${SOURCE_FILES} ${HEADER_FILES})