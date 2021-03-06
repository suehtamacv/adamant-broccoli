#ifndef SIMULATION_FFE_OPTIMIZATION_H
#define SIMULATION_FFE_OPTIMIZATION_H

#include "SimulationType.h"
#include "RMSA.h"

namespace RMSA
{
namespace SA
{
namespace FFE
{
class FFE_GA;
}
}
}

namespace Simulations
{
class Simulation_FFE_Optimization : public SimulationType
{
public:
    Simulation_FFE_Optimization();

    void help();
    void run();
    void load();
    void save(std::string);
    void load_file(std::string);
    void print();

    bool hasLoaded;
    double NumCalls;
    double OptimizationLoad;

    std::string CoefficientsFilename;
    std::string LogFilename;

    RMSA::ROUT::RoutingAlgorithm::RoutingAlgorithms Routing_Algorithm;
    RMSA::ROUT::RoutingCost::RoutingCosts Routing_Cost;
    RMSA::RP::RegeneratorPlacementAlgorithm::RegeneratorPlacementAlgorithms
    RegPlacement_Algorithm;
    RMSA::RA::RegeneratorAssignmentAlgorithm::RegeneratorAssignmentAlgorithms
    RegAssignment_Algorithm;

    void place_Regenerators(std::shared_ptr<Topology> T);

private:
    std::shared_ptr<RMSA::SA::FFE::FFE_GA> FFE_GA_Optimization;
    void printCoefficients(std::string);
};
}

#endif // SIMULATION_FFE_OPTIMIZATION_H
