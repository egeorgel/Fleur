//
// Created by Edgar on 07/11/2016.
//

#ifndef FLEUR_HTTPEXCEPTION_H
#define FLEUR_HTTPEXCEPTION_H


#include <exception>
#include <string>

class HttpException : public std::exception {

public:
    HttpException(std::string const& message="") throw()
        :
            _message(message)
    {}

    virtual const char* what() const throw() {
        return _message.c_str();
    }

    virtual ~HttpException() throw() {}

private:
    std::string _message;
    std::string _url;
};


#endif //FLEUR_HTTPEXCEPTION_H
