/**
 * @file Number.cpp
 * @author jadec
 */

#include "pch.h"
#include "Number.h"

/**
 * Constructor
 * @param game
 * @param filename
 */
Number::Number(Game *game, wxXmlNode * dec) :
    Item(game, dec)
{
    dec->GetAttribute("value", "0").ToInt(&mValue);
}

