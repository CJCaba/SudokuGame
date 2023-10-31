/**
 * @file ContainerVisitor.h
 * @author linja
 *
 *
 */

#ifndef ARES_GAMELIB_CONTAINERVISITOR_H
#define ARES_GAMELIB_CONTAINERVISITOR_H

#include "Visitor.h"

class ContainerVisitor : public Visitor
{
private:
    std::vector<Container*> mContainers;
public:
    void VisitContainer(Container* container) override
    {
        mContainers.push_back(container);
    }

    std::vector<Container*> ContainerFound()
    {
        return mContainers;
    }
};

#endif //ARES_GAMELIB_CONTAINERVISITOR_H
