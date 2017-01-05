#include <iostream>
#include <string>
#include <locale>
#include <boost/program_options.hpp>
#include <boost/exception/diagnostic_information.hpp>
#include <boost/exception_ptr.hpp>
#include "fleur.h"

#if defined(__APPLE__) || defined(__unix__)
    #define NOT_A_WINDOWS 1
    #include <sys/poll.h>
#elif
    #define NOT_A_WINDOWS 0
#endif

namespace po = boost::program_options;

void fleur_query(std::string requetes);
int poll_stdin();
int main(const int argc, const char *argv[]) {

    /* Declare Command Line Options */
    po::options_description cli_options("Fleur CLI Options");
    cli_options.add_options()
            ("help,h", "Display the help message")
            ("version,v", "Display the version number")
            ("execute,e", po::value<std::string>(), NOT_A_WINDOWS ?
                                                    "Execute a fleur Query - Queries can additionally be piped through STDIN"
                                                    : "Execute a fleur Query");


    /* Parse argv for command line options */
    po::variables_map vm;
    try {
        po::store(po::command_line_parser(argc, argv).options(cli_options).run(), vm);
        po::notify(vm);
    } catch(std::exception const&  ex) {
        std::cerr << ex.what() << std::endl << "Use fleur --help for usage information" << std::endl;
    }


    /* Help Option */
    if (vm.count("help")) {
        std::cout << cli_options;
    }

    /* Version Option */
    else if (vm.count("version")) {
        std::cout << fleur_version() << std::endl;
    }

    /* Execute Option */
    else if (vm.count("execute")) {
        fleur_query(vm["execute"].as<std::string>());
    }

    /* Query passed piped through stdin */
    #ifdef NOT_A_WINDOWS
    else if (poll_stdin()) {
        std::string line, input;
        while (std::getline(std::cin, line))
        {
            input += line;
        }
        fleur_query(input);
    }
    #endif

    /* REPL */
    else {

        /* Log in information */
        std::cout << "Fleur Interactive Shell - Version " << fleur_version() << std::endl;
        std::cout << "Type quit or exit to leave this shell" << std::endl << std::endl;

        /* REPL Loop */
        std::string line, line_tolower;
        std::locale locale;
        do {
            /* Ask for input */
            std::cout << "Fleur> ";
            std::getline(std::cin, line);

            /* To lower, to detect quit/exit in a case insensitive way */
            line_tolower = "";
            for(auto elem : line)
                line_tolower += std::tolower(elem,locale);
            if (line_tolower == "quit" || line_tolower == "exit") {
                std::cout << "Bye" << std::endl;
                break;
            }

            /* Execute fleur query */
            fleur_query(line);
        } while (true);
    }
    return 0;
}

void fleur_query(std::string requetes) {
    Processing processing(requetes);
    std::vector<std::string> results = processing.build();
    if (results.size())
        for (auto result : results)
            std::cout << result << std::endl;
}

int poll_stdin() {
    struct pollfd fds;
    int ret;
    fds.fd = 0; /* this is STDIN */
    fds.events = POLLIN;
    ret = poll(&fds, 1, 0);
    return ret;
}