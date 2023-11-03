/**
 * @file XRayVisitor.h
 * @author linja
 *
 *
 */

#ifndef ARES_GAMELIB_XRAYVISITOR_H
#define ARES_GAMELIB_XRAYVISITOR_H

#include "Visitor.h"
#include "XRay.h"

class XRayVisitor : public Visitor
{
private:
    /// Pointer to XRay
    XRay* mXRay = nullptr;
public:
    /**
     * Visit an XRay item
     * @param xray Pointer to an XRay
     */
    void VisitXRay(XRay* xray)
    {
        mXRay = xray;
    }

    /**
     * Return the XRay Item
     * @return Pointer to XRay
     */
    XRay* XRayFound()
    {
        return mXRay;
    }
};

#endif //ARES_GAMELIB_XRAYVISITOR_H
