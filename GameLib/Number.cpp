/**
 * @file Number.cpp
 * @author Jaden Cabansag
 */

#include "pch.h"
#include "Number.h"

using namespace std;

/**
 * Constructor
 * @param game
 * @param filename
 */
Number::Number(Game *game, const std::wstring &filename) :
    Item(game, filename)
{
}