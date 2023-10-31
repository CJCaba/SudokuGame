/**
 * @file GivenNumber.cpp
 * @author Jaden Cabansag
 */

#include "pch.h"
#include "GivenNumber.h"

using namespace std;

/**
 * Constructor
 * @param game The game class the item is a part of
 * @param dec Pointer to a Declartion node containing basic information
 * @param item Pointer to an Item node containing position information
 */
GivenNumber::GivenNumber(Game *game, wxXmlNode * dec, wxXmlNode* item) :
    Number(game, dec, item)
{
}