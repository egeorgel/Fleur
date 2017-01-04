//
// Created by Edgar on 02/01/2017.
//

#ifndef FLEUR_PROCESSINGEXCEPTION_H
#define FLEUR_PROCESSINGEXCEPTION_H

#include <exception>
#include <string>

class ProcessingException : public std::exception {

public:
    ProcessingException(std::string const& message="") throw()
            :
            _message(message)
    {}

    virtual const char* what() const throw() {
        return _message.c_str();
    }

    virtual ~ProcessingException() throw() {}

private:
    std::string _message;
};

#endif //FLEUR_PROCESSINGEXCEPTION_H
