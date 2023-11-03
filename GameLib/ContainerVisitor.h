/**
 * @file ContainerVisitor.h
 * @author Jason Lin
 *
 * Visit and Collect all Containers
 */

#ifndef ARES_GAMELIB_CONTAINERVISITOR_H
#define ARES_GAMELIB_CONTAINERVISITOR_H

#include "Visitor.h"

/**
 * Visitor Class for Containers
 */
class ContainerVisitor : public Visitor
{
private:
    /// Vector of pointers to Container Items
    std::vector<Container*> mContainers;
public:

    /**
     *
     * @param container Pointer to a container
     */
    void VisitContainer(Container* container) override
    {
        mContainers.push_back(container);
    }

    /**
     * Return the vector of Containers
     * @return The vector of Containers
     */
    std::vector<Container*> ContainerFound()
    {
        return mContainers;
    }
};

#endif //ARES_GAMELIB_CONTAINERVISITOR_H
