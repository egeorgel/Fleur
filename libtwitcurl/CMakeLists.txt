cmake_minimum_required(VERSION 3.6)
project(libtwitcurl)

set(HEADER_FILES_LIBTWIT
        include/curl/curl.h
        include/curl/curlbuild.h
        include/curl/curlrules.h
        include/curl/curlver.h
        include/curl/easy.h
        include/curl/mprintf.h
        include/curl/multi.h
        include/curl/stdcheaders.h
        include/curl/typecheck-gcc.h
        include/oauthlib.h
        include/twitcurl.h
        include/base64.h
        include/HMAC_SHA1.h
        include/SHA1.h
        include/twitcurlurls.h include/OAuthLibDefaults.h)

set(SOURCE_FILES_LIBTWIT
        include/base64.cpp
        include/HMAC_SHA1.cpp
        include/SHA1.cpp
        include/urlencode.cpp
        include/oauthlib.cpp
        include/twitcurl.cpp)

add_library(libtwitcurl STATIC ${SOURCE_FILES_LIBTWIT} ${HEADER_FILES_LIBTWIT})