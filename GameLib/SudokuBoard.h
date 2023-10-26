/**
 * @file SudokuBoard.h
 * @author linja
 *
 *
 */

#ifndef ARES_GAMELIB_SUDOKUBOARD_H
#define ARES_GAMELIB_SUDOKUBOARD_H

#include "Container.h"

class SudokuBoard : public Container
{
private:

public:
    /// Default constructor (disabled)
    SudokuBoard() = delete;
    
    /// Copy constructor (disabled)
    SudokuBoard(const SudokuBoard &) = delete;
    
    /// Assignment operator
    void operator=(const SudokuBoard &) = delete;
    
};

#endif //ARES_GAMELIB_SUDOKUBOARD_H
