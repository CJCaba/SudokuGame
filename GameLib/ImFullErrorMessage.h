/**
 * @file ImFullErrorMessage.h
 * @author Gerald Hoskins
 *
 *
 */

#ifndef ARES_GAMELIB_IMFULLERRORMESSAGE_H
#define ARES_GAMELIB_IMFULLERRORMESSAGE_H

/**
 * Class used to display I'm Full error message
 */
class ImFullErrorMessage
{
private:
    wxPoint mPosition; ///< Centered location of the error message
    bool mDeleteMeFlag = false; ///< Flag for delete

public:
    /// Default constructor (disabled)
    ImFullErrorMessage() = delete;

    /// Constructor
    ImFullErrorMessage(wxPoint position);

    /**
     * Whether the message should be deleted.
     * @return Boolean representing yes/no.
     */
    bool ShouldBeDeleted() const { return mDeleteMeFlag; }

    void Update(double elapsed);
    void Draw(std::shared_ptr<wxGraphicsContext> graphics);
};

#endif //ARES_GAMELIB_IMFULLERRORMESSAGE_H
