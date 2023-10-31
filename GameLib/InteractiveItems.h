/**
 * @file InteractiveItems.h
 * @author linja
 *
 *
 */

#ifndef ARES_GAMELIB_INTERACTIVEITEMS_H
#define ARES_GAMELIB_INTERACTIVEITEMS_H

#include "Visitor.h"
#include "InteractNumber.h"

class InteractiveItems : public Visitor
{
private:
    std::vector<InteractNumber*> mFoundItems;
public:
    void VisitInteract(InteractNumber* interact) override
    {
        mFoundItems.push_back(interact);
    }
    std::vector<InteractNumber*> InteractFound()
    {
        return mFoundItems;
    }
};

#endif //ARES_GAMELIB_INTERACTIVEITEMS_H
