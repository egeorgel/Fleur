//
// Created by Edgar on 20/11/2016.
//

#ifndef FLEUR_FILTEREXCEPTION_H
#define FLEUR_FILTEREXCEPTION_H

#include <exception>
#include <string>

namespace fleur {
    class FilterException : public std::exception {

    public:
        FilterException(std::string const& message="") throw()
                :
                _message(message)
        {}

        virtual const char* what() const throw() {
            return _message.c_str();
        }

        virtual ~FilterException() throw() {}

    private:
        std::string _message;
    };


}
#endif //FLEUR_FILTEREXCEPTION_H
