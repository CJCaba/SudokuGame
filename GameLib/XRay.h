/**
 * @file XRay.h
 * @author linja
 *
 *
 */

#ifndef ARES_GAMELIB_XRAY_H
#define ARES_GAMELIB_XRAY_H

#include "Item.h"

class XRay : public Item
{
private:
    /// The max capacity of the X-Ray Container
    int mCapacity = 7;

public:
    /// Default constructor (disabled)
    XRay() = delete;
    
    /// Copy constructor (disabled)
    XRay(const XRay &) = delete;
    
    /// Assignment operator
    void operator=(const XRay &) = delete;

    /// Constructor
    XRay(Game *game, const std::wstring &filename);

    void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;

};

#endif //ARES_GAMELIB_XRAY_H
