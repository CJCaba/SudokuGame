/**
 * @file VisitorNumbers.h
 * @author Jaden Cabansag
 *
 * Visitor to collect all Numbers, Given and Interactive
 */

#ifndef ARES_GAMELIB_VISITORNUMBERS_H
#define ARES_GAMELIB_VISITORNUMBERS_H

#include "Visitor.h"
#include "GivenNumber.h"
#include "InteractNumber.h"

/**
 * Base class for Visitor Numebers
 */
class VisitorNumbers : public Visitor
{
private:
    std::vector<Number*> mFoundItems;
public:

    void VisitInteract(InteractNumber* interact) override{
        mFoundItems.push_back(interact);
    }

    void VisitGiven(GivenNumber* given) override{
        mFoundItems.push_back(given);
    }

    std::vector<Number*> FoundItems() { return mFoundItems; }
};

#endif //ARES_GAMELIB_VISITORNUMBERS_H
