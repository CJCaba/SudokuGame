/**
 * @file InteractiveItems.h
 * @author Jason Lin
 *
 *
 */

#ifndef ARES_GAMELIB_INTERACTIVEITEMS_H
#define ARES_GAMELIB_INTERACTIVEITEMS_H

#include "Visitor.h"
#include "InteractNumber.h"

/**
 * Visitor for Interactive Numbers
 */
class InteractiveItems : public Visitor
{
private:
    /// Vector of InteractNumber pointers
    std::vector<InteractNumber*> mFoundItems;
public:
    /**
     * Function for when an interact number is visited
     * @param interact The current InteractNumber* we are visiting
     */
    void VisitInteract(InteractNumber* interact) override
    {
        mFoundItems.push_back(interact);
    }

    /**
     * Return the vector of InteractNumber pointers
     * @return mFoundItems
     */
    std::vector<InteractNumber*> InteractFound()
    {
        return mFoundItems;
    }
};

#endif //ARES_GAMELIB_INTERACTIVEITEMS_H
