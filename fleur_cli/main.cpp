#include <iostream>
#include <string>
#include <locale>
#include <boost/program_options.hpp>
#include <boost/exception/diagnostic_information.hpp>
#include <boost/exception_ptr.hpp>
#include "fleur.h"
#include <readline/readline.h>
#include <readline/history.h>
#include <sys/poll.h>

#ifndef __APPLE__
    #define LOG_QUERY 1
#endif


namespace po = boost::program_options;
int poll_stdin();
std::vector<std::string> fleur_query_ex(std::string);

int main(const int argc, const char *argv[]) {

    /* Declare Command Line Options */
    po::options_description cli_options("Fleur CLI Options");
    cli_options.add_options()
            ("help,h", "Displays the help message")
            ("version,v", "Displays the version number")
            ("execute,e", po::value<std::string>(), "Executes a Fleur Query - Queries can additionally be piped through STDIN")
            ("silent,s", "Strips verbosity to minimum - Only outputs query results  - Useful when used with socat to create a server")
            ("no-rlwrap", "Will use standard getline instead of readline - Useful when used with socat to create a server");


    /* Parse argv for command line options */
    po::variables_map vm;
    try {
        po::store(po::command_line_parser(argc, argv).options(cli_options).run(), vm);
        po::notify(vm);
    } catch(std::exception const&  ex) {
        std::cerr << ex.what() << std::endl << "Use fleur --help for usage information" << std::endl;
        return EXIT_FAILURE;
    }

    /* Poll STDIN */
    int polled_stdin = poll_stdin();

    /* Help Option */
    if (vm.count("help")) {
        std::cout << cli_options;
    }

    /* Version Option */
    else if (vm.count("version")) {
        std::cout << "Fleur Version: " << fleur_version() << std::endl;
        std::cout << "Bundled with modules: " << fleur_installed_modules() << std::endl;
    }

    /* Execute Option */
    else if (vm.count("execute")) {
        fleur_query_ex(vm["execute"].as<std::string>());
    }

    /* Query passed piped through stdin */
    else if (polled_stdin) {
        std::string line, input;
        while (std::getline(std::cin, line))
        {
            input += line;
        }
        for (auto const& c : fleur_query_ex(input))
            std::cout << c << std::endl;
    }

    /* REPL */
    else {

        /* Log in information */
        if (!vm.count("silent")) {
            std::cout << "Fleur Interactive Shell: Version " << fleur_version() << std::endl;
            std::cout << "Bundled with modules: " << fleur_installed_modules() << std::endl;
            std::cout << "Type quit or exit to leave this shell" << std::endl << std::endl;
        }

        /* REPL Loop */
        char * line_readline;
        std::string line, line_tolower;
        std::locale locale;
        do {
            /* Ask for input with read*/
            if (vm.count("no-rlwrap")) {
                if (!vm.count("silent"))
                    std::cout << "Fleur" + (fleur_current_module() != "" ? " (" + fleur_current_module() + ")" : "") +
                                 "> ";
                std::getline(std::cin, line);
            }

            else {
                if (!vm.count("silent")) {
                    std::string prompt =
                            "Fleur" + (fleur_current_module() != "" ? " (" + fleur_current_module() + ")" : "") + "> ";
                    line_readline = readline(prompt.c_str());
                } else {
                    line_readline = readline("");
                }
                add_history(line_readline);
                line = std::string(line_readline);
                free(line_readline); // Sneaky memory leak
            }


            /* To lower, to detect quit/exit in a case insensitive way */
            line_tolower = "";
            for(auto elem : line)
                line_tolower += std::tolower(elem,locale);
            if (line_tolower == "quit" || line_tolower == "quit;" || line_tolower == "exit" || line_tolower == "exit;") {
                if (!vm.count("silent"))
                    std::cout << "Bye" << std::endl;
                break;
            }

            /* Execute fleur query */
            for (auto const& c : fleur_query_ex(line))
                std::cout << c << std::endl;
        } while (true);
    }
    return EXIT_SUCCESS;
}

int poll_stdin() {
    struct pollfd fds;
    int ret;
    fds.fd = 0; /* this is STDIN */
    fds.events = POLLIN;
    ret = poll(&fds, 1, 0);
    return ret;
}


std::vector<std::string> fleur_query_ex(std::string line) {
    #ifdef LOG_QUERY
        std::string influx_curl = "curl -i -XPOST 'http://localhost:8086/write?db=fleur' --data-binary 'fleur_queries,"
                                  + fleur_current_module() + "=1 value=1 '\"$(date +%s%N)\"";
        system(&influx_curl[0u]);
    #endif
    return fleur_query(line);
}
