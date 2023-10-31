/**
 * @file Visitor.h
 * @author Jason Lin
 *
 * Item visitor base class.
 */

#ifndef ARES_GAMELIB_VISITOR_H
#define ARES_GAMELIB_VISITOR_H

/// Forward references to all items
class InteractNumber;
class GivenNumber;
class Background;
class Container;
class XRay;
class Sparty;

/**
 * Item visitor base class
 */
class Visitor
{
protected:
    /// Abstract Constructor
    Visitor() {}

public:
    /// Destructor
    virtual ~Visitor() {}

    virtual void VisitInteract(InteractNumber* interact) {}

    virtual void VisitGiven(GivenNumber* given) {}

    virtual void VisitBackground(Background* background) {}

    virtual void VisitContainer(Container* container) {}

    virtual void VisitXRay(XRay* xray) {}

    virtual void VisitSparty(Sparty* sparty) {}
};

#endif //ARES_GAMELIB_VISITOR_H
