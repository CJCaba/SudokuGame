/**
 * @file GivenNumber.cpp
 * @author Jaden Cabansag
 */

#include "pch.h"
#include "GivenNumber.h"

using namespace std;

/**
 * Constructor
 * @param game
 * @param filename
 */
GivenNumber::GivenNumber(Game *game, wxXmlNode * dec, wxXmlNode* item) :
    Number(game, dec, item)
{
}