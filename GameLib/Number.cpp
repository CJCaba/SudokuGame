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
Number::Number(Game *game, wxXmlNode * dec, wxXmlNode* item) :
    Item(game, dec, item)
{
    dec->GetAttribute("value", "0").ToInt(&mValue);
}

