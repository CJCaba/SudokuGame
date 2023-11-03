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
class Spotlight;
class Sparty;
class AudioPlayer;

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

    /**
     * Visit an InteractNumber item
     * @param interact Pointer to an InteractNumber
     */
    virtual void VisitInteract(InteractNumber* interact) {}

    /**
     * Visit an GivenNumber item
     * @param given Pointer to a GivenNumber
     */
    virtual void VisitGiven(GivenNumber* given) {}

    /**
     * Visit a background item
     * @param background Pointer to a Background
     */
    virtual void VisitBackground(Background* background) {}

    /**
     * Visit a Container Item
     * @param container Pointer to a Container
     */
    virtual void VisitContainer(Container* container) {}

    /**
     * Visit an XRay Item
     * @param xray Pointer to an XRay
     */
    virtual void VisitXRay(XRay* xray) {}

    /**
     * Visit a Sparty Item
     * @param sparty Pointer to a Sparty item
     */
    virtual void VisitSparty(Sparty* sparty) {}

    virtual void VisitAudioPlayer(AudioPlayer* audio) {}

    /**
     * Visit a Spotlight Item
     * @param spotlight Pointer to a Spotlight
     */
    virtual void VisitSpotlight(Spotlight* spotlight) {}
};

#endif //ARES_GAMELIB_VISITOR_H
