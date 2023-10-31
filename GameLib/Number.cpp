/**
 * @file Number.cpp
 * @author Jaden Cabansag
 */

#include "pch.h"
#include "Number.h"

/**
 * Constructor
 * @param game The game class the item is a part of
 * @param dec Pointer to a Declartion node containing basic information
 * @param item Pointer to an Item node containing position information
 */
Number::Number(Game *game, wxXmlNode * dec, wxXmlNode* item) :
    Item(game, dec, item)
{
    dec->GetAttribute("value", "0").ToInt(&mValue);
}

