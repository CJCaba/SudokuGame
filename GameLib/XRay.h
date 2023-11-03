/**
 * @file XRay.h
 * @author linja
 *
 * Class for Xray item
 */

#ifndef ARES_GAMELIB_XRAY_H
#define ARES_GAMELIB_XRAY_H

#include "Item.h"
#include "InteractNumber.h"

class Sparty;

/**
 * Base class for XRay Item
 */
class XRay : public Item
{
private:
    /// The max capacity of the X-Ray
    int mCapacity = 7;

    /// Items held in X-Ray, Sparty's Stomach
    std::vector<InteractNumber*> mStomachItems;

public:
    /// Default constructor (disabled)
    XRay() = delete;

    /// Copy constructor (disabled)
    XRay(const XRay &) = delete;

    /// Assignment operator
    void operator=(const XRay &) = delete;

    /// Constructor
    XRay(Game *game, wxXmlNode * dec, wxXmlNode* item);

    void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;

    void Add(InteractNumber* interact);

    void Remove(InteractNumber* item);

    InteractNumber* Find(int value);

    bool Check(InteractNumber* item);

    /**
     * Checks if the XRay is full
     * @return true if full, else return false
     */
    bool IsFull() { return mStomachItems.size() == mCapacity; }

    /**
     * Accept a visitor
     * @param visitor The visitor we accept
     */
    void Accept(Visitor* visitor) override {visitor->VisitXRay(this); };
};

#endif //ARES_GAMELIB_XRAY_H
