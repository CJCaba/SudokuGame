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
    XRay* mXRay = nullptr;
public:
    void VisitXRay(XRay* xray)
    {
        mXRay = xray;
    }

    XRay* XRayFound()
    {
        return mXRay;
    }
};

#endif //ARES_GAMELIB_XRAYVISITOR_H
