/**
 * @file SudokuBoard.h
 * @author linja
 *
 *
 */

#ifndef ARES_GAMELIB_SUDOKUBOARD_H
#define ARES_GAMELIB_SUDOKUBOARD_H

#include "Item.h"

class SudokuBoard : public Item
{
private:

public:
    /// Default constructor (disabled)
    SudokuBoard() = delete;
    
    /// Copy constructor (disabled)
    SudokuBoard(const SudokuBoard &) = delete;
    
    /// Assignment operator
    void operator=(const SudokuBoard &) = delete;

    SudokuBoard(Game *game, const std::wstring &filename);
    
};

#endif //ARES_GAMELIB_SUDOKUBOARD_H
