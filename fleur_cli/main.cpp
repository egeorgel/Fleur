#include <iostream>
#include <boost/program_options.hpp>
#include <boost/exception/diagnostic_information.hpp>
#include <boost/exception_ptr.hpp>
#include "fleur.h"

namespace po = boost::program_options;

int main(const int argc, const char *argv[]) {


    po::options_description cli_options("Fleur CLI Options");
    cli_options.add_options()
            ("help,h", "Display the help message")
            ("version,v", "Display the version number")
            ("execute,e", po::value<std::string>()->implicit_value("stdin"), "Execute a fleur Query");


    po::variables_map vm;
    try {
        po::store(po::command_line_parser(argc, argv).options(cli_options).run(), vm);
        po::notify(vm);
    } catch(std::exception const&  ex) {
        std::cerr << ex.what() << std::endl << "Use fleur --help for usage information" << std::endl;
    }

    if (vm.count("help")) {
        std::cout << cli_options;
    }

    if (vm.count("version")) {
        std::cout << fleur_version();
    }

    if (vm.count("execute")) {
        std::string requettes(vm["execute"].as<std::string>());
        Processing processing(requettes);
        std::vector<std::string> results = processing.build();
        if (results.size())
            std::cout << results[0];
        else
            std::cout << "No results found.";
    }

    return 0;
}