#ifndef NHF_REFORMED_EDITOR_H
#define NHF_REFORMED_EDITOR_H
#include "../Game/Army.h"
#include "../File Management/Filemanagement.h"
#include <sstream>
#include <string>
/**
 * @brief A seregek létrehozásáért és szerkesztéséért felelős osztály.
 */
class Editor {
private:
    Army* army; /**< Pointer az éppen szerkesztett seregre. */
    bool exit; /**< Logikai érték arra, hogy a felhasználó végzett-e a sereg szerkesztésével. */
    bool toDelete; /**< Logikai érték arra, hogy ha a felhasználó szeretné törölni a sereget. */

public:
    /**
     * @brief Default constructor.
     * Creates a new Editor instance with an empty Army.
     */
    Editor();

    /**
     * @brief Destructor.
     */
    ~Editor();

    /**
     * @brief Constructor with parameter.
     * Creates an Editor instance with the provided Army for editing.
     * @param army Pointer to the Army object to be edited.
     */
    Editor(Army* army);

    /**
     * @brief Getter for the Army being edited.
     * @return Pointer to the Army being edited.
     */
    Army* getArmy() const;

    /**
     * @brief Searches for a Piece at the specified coordinates.
     * @param coordX X-coordinate of the Piece.
     * @param coordY Y-coordinate of the Piece.
     * @return Pointer to the Piece found at the specified coordinates, or nullptr if not found.
     */
    Piece* searchFor(int coordX, int coordY);

    /**
     * @brief Updates the exit flag to control editor termination.
     */
    void updateExit();

    /**
     * @brief Getter for the exit flag.
     * @return True if the editor should exit, false otherwise.
     */
    bool getExit() const;

    /**
     * @brief Updates the toDelete flag to indicate whether the Army should be deleted.
     */
    void updateDelete();

    /**
     * @brief Getter for the toDelete flag.
     * @return True if the Army should be deleted, false otherwise.
     */
    bool getDelete() const;

    /**
     * @brief Saves the newly created Army.
     * Saves the current state of the Army being created.
     */
    void saveArmy();

    /**
     * @brief Edits an existing Army.
     * Provides options to modify an existing Army.
     */
    void editArmy();

    /**
     * @brief Deletes an existing Army.
     * Deletes the Army currently being edited.
     */
    void deleteArmy();
};
#endif //NHF_REFORMED_EDITOR_H