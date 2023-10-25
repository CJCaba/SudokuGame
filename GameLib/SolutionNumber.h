/**
 * @file SolutionNumber.h
 * @author Daniel Flanagan
 *
 *
 */

#ifndef ARES_GAMELIB_SOLUTIONNUMBER_H
#define ARES_GAMELIB_SOLUTIONNUMBER_H

class SolutionNumber
{
private:
    int mValue;
    double mColumn;
    double mRow;

public:
    /// Default constructor (disabled)
    SolutionNumber() = delete;

    /// Constructor to initialize mValue, mColumn, and mRow
    SolutionNumber(int value, double column, double row);

    /// Get number's value
    int GetValue() { return mValue; }

    /// Get the column
    double GetColumn() { return mColumn; }

    /// Get the row
    double GetRow() { return mRow; }

};

#endif //ARES_GAMELIB_SOLUTIONNUMBER_H
