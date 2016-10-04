project(fleur_src)

set(HEADER_FILES
        Parseur.h
        )

set(SOURCE_FILES
        Parseur.cpp
        )

add_library(fleur_src STATIC ${SOURCE_FILES} ${HEADER_FILES})