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
GivenNumber::GivenNumber(Game *game, const std::wstring &filename) :
    Item(game, filename)
{
}