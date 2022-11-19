#include <iostream>
#include <iomanip>
#include "Parser.h"

using std::cout;
using std::endl;

int main(int argc, char **argv)
{

    if (argc != 2)
    {
        cout << "usage: " << argv[0] << " <config_path>" << endl;
        return -1;
    }

    // read simulation from config file
    const string config_path = argv[1];
    Simulation simulation = Parser::readSimulation(argv[1]);

    // run simulation and store json state after each iteration
    vector<json> outPerIter = {Parser::makeJson(simulation)};
    std::cout << "----------------Simulation Started!" << std::endl; /// to remove
    int i = 0;
    while (!simulation.shouldTerminate())
    {
        std::cout << "start of iteration " << i << std::endl;
        simulation.step();
        outPerIter.push_back(Parser::makeJson(simulation));
        std::cout << "end of iteration " << i << std::endl;
        std::cout << "--------------- "<< std::endl;
        i++;
        if (i > 9){
            std::cout << "failed" << std::endl;
            break;
        }
    }
    std::cout << "----------------Simulation Ended!" << std::endl;
    // writing the outputs list to a file
    const string output_path = config_path.substr(0, config_path.find_last_of('.')) + ".out";
    std::ofstream outputFile(output_path);
    outputFile << std::setw(4) << json(outPerIter) << endl;

    return 0;
}