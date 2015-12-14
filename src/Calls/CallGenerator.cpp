#include <Calls/CallGenerator.h>
#include <Calls/Call.h>
#include <boost/assert.hpp>

std::default_random_engine CallGenerator::generator;

CallGenerator::CallGenerator(std::shared_ptr<Topology> T,
                             long double h,
                             std::vector<TransmissionBitrate> Bitrates) :
    T(T), h(h), simulationTime(0), Bitrates(Bitrates) {

    UniformNodeDistribution = std::uniform_int_distribution<int>
                              (0, T->Nodes.size() - 1);
    UniformBitrateDistribution = std::uniform_int_distribution<int>
                                 (0, Bitrates.size() - 1);
    ExponentialDistributionMu = std::exponential_distribution<long double>
                                (1.0L / mu);
    ExponentialDistributionH = std::exponential_distribution<long double>(h);

}

std::shared_ptr<Call> CallGenerator::generate_Call() {
    long double ArrivalTime = simulationTime + ExponentialDistributionH(generator);
    long double EndingTime = ArrivalTime + ExponentialDistributionMu(generator);
    simulationTime = ArrivalTime;

    int Origin = UniformNodeDistribution(generator);
    int Destination = UniformNodeDistribution(generator);

    while (Origin == Destination) {
        Destination = UniformNodeDistribution(generator);
    }

    int Bitrate = UniformBitrateDistribution(generator);

    std::shared_ptr<Call> C(new Call(std::weak_ptr<Node>(T->Nodes[Origin]),
                                     std::weak_ptr<Node>(T->Nodes[Destination]),
                                     Bitrates[Bitrate]));

    std::shared_ptr<Event> CallRequisition(new Event(ArrivalTime,
                                           Event::CallRequisition, C));
    std::shared_ptr<Event> CallEnding(new Event(EndingTime,
                                      Event::CallEnding, C));

    Events.push(CallRequisition);
    Events.push(CallEnding);

    C->CallRequisition = CallRequisition;
    C->CallEnding = CallEnding;

    return C;
}

void CallGenerator::set_Load(long double h) {
    BOOST_ASSERT_MSG(h >= 0, "Network loads must be positive.");
    this->h = h;
    ExponentialDistributionH = std::exponential_distribution<long double>(h);
}
