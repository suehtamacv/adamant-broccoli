#include "include/RMSA/SpectrumAssignmentAlgorithms/ExactFit.h"
#include "include/RMSA/SpectrumAssignmentAlgorithms/FirstFit.h"
#include <Calls/Call.h>
#include <Structure/Link.h>
#include <Structure/Slot.h>

using namespace RMSA::SA;

ExactFit::ExactFit(std::shared_ptr<Topology> T) :
    SpectrumAssignmentAlgorithm(T, SpectrumAssignmentAlgorithm::EF)
{

}

mapSlots ExactFit::assignSlots(std::shared_ptr<Call> C, TransparentSegment Seg)
{

    int RequiredSlots = Seg.ModScheme.get_NumSlots(C->Bitrate);
    std::map<std::weak_ptr<Link>, std::vector<std::weak_ptr<Slot>>,
        std::owner_less<std::weak_ptr<Link>>> Slots;
    Slots.clear();

    bool SlotsAvailability[Link::NumSlots];

    for (int i = 0; i < Link::NumSlots; i++)
        {
        SlotsAvailability[i] = true;
        }

    for (auto &link : Seg.Links)
        {
        auto locklink = link.lock();

        for (auto &slot : locklink->Slots)
            {
            SlotsAvailability[slot->numSlot] &= slot->isFree;
            }
        }

    int CurrentFreeSlots = 0;
    int si = -1, sf = 0;

    for (sf = 0; sf < Link::NumSlots; sf++)
        {
        if (SlotsAvailability[sf])
            {
            CurrentFreeSlots++;
            }
        else
            {
            CurrentFreeSlots = 0;
            }

        //Found a "spectral hole" with exactly RequiredSlots slots.
        if ((CurrentFreeSlots == RequiredSlots) &&
                ((sf == Link::NumSlots - 1) || !SlotsAvailability[sf + 1]))
            {
            si = sf - RequiredSlots + 1;
            break;
            }
        }

    if (si != -1)
        {
#ifdef RUN_ASSERTIONS
        if (sf != si + RequiredSlots - 1)
            {
            std::cerr << "Error in Wavelength Assignment" << std::endl;
            abort();
            }
#endif
        for (auto &link : Seg.Links)
            {
            Slots.emplace(link, std::vector<std::weak_ptr<Slot>>
                          (link.lock()->Slots.begin() + si,
                           link.lock()->Slots.begin() + sf + 1));
            }
        return Slots;
        }
    else
        {
        //If there isn't an exact fit, then call First Fit.
        return FirstFit(T).assignSlots(C, Seg);
        }
}

void ExactFit::save(std::string SimConfigFileName)
{
    SpectrumAssignmentAlgorithm::save(SimConfigFileName);
}
