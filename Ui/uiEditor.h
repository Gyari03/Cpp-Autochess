/**
 * @file uiEditor.h
 * @brief uiEditor osztályt tartalmazó header
 */

#ifndef NHF_REFORMED_UIEDITOR_H
#define NHF_REFORMED_UIEDITOR_H
#include "../Editor/Editor.h"
#include "ui.h"
#include <iostream>
#include "../File Management/Filemanagement.h"


/**
 * @brief uiEditor osztály, ami az editor megjelenítéséért felelős.
 */
class uiEditor:public ui {
private:
    Editor* editor;                         /**<Az editor, amit meg szeretnénk jeleníteni */
public:
    uiEditor(Editor* editor);               /**<Konstruktor editorrel paraméterként */
    ~uiEditor();                            /**<Destruktor */
    
    /**
     * @brief A szerkesztő megjelenítőfüggvénye.
     * Ez 2 másik függvényt foglal magába.
     * - clearScreen() : letisztítja az előző táblát a képernyőről
     * - renderTable() : visszarajzolja a táblát, de már az új állapotában.
     */
    void display() override;

    /**
     * @brief A szerkesztőnek az inputkezelésével foglalkozó függvény.
     * - Mivel a menüben is megszokott volt, hogy a [0].-ás gomb az a kilépést szolgálja, itt is ha a felhasználó 0-át ad be inputnak akkor kilép az szerkesztőből.
     * - Egyébként meg, ha nem 0-át ad a felhasználó mint input, akkor az első betű egy létező bábutípusnak a betűjele kell, hogy legyen, vagy nem fog hozzáadódni a táblához.
     * - A második-harmadik karaktert pedig átkonvertálja int-re, hogy tudjon vele dolgozni a Bábuhozzáadásnál
     * - Ha a felhasználó bábubetűjel helyett 'D'-t ad meg, akkor az azon a koordinátán lévő bábut próbálja törölni a fv.
     * - Ha pedig a felhasználó azt írja be, hogy "delete" akkor törli az éppen szerkesztett sereget a lemenett seregek közül.
     * @return Ebben a visszatérési értéke nincsen felhasználva.
     */
    bool handleInput() override;

    /**
     * @brief A tábla lerendereléséért felelős függvény.
     * Ez csak egy fél táblát fog kiírni, hiszen csak 1 térfelet akarunk szerkeszteni nem többet.
     * Emellett minden mezőben leellenőrzi, hogy lenne-e benne bábu, mert ha igen akkor beleírja a bábu betűjelét. Egyébként meg üresen hagyja.
     */
    void renderTable();

    /**
     * @brief A szerkesztő inaktív állapota lényegében.(várja a választ a felektől egymás fele)
     * Felhasználó és program közötti kommunikáció a szerkesztőben amik kilépésre nem kap jelet a program.
     */
    void idle()override;

    /**
     * @brief Újonnan lementett seregek mentésére szolgáló protokol.
     * Ha a felhasználó egy újonnan létrehozott sereget el szeretne menteni, akkor kilépéskor ezen keresztül tudja kimenteni a fájlba.
     */
    void saveSequence();

    /**
     * @brief Futtatja a paraméterként kapott szerkesztőt
     * Létrehoz neki egy uiEditor-t és azt berakja idle() pozícióba.
     * A fv. tudni fogja, hogyha újonnan készített(Onnan hogy nincs neve a seregnek) a sereg és kilépésnél automatikusan felajánlja a lementését.
     * Ha egy már alapból létrehozott seregből lépünk ki akkor az automatikusan mentésre kerül.
     * @param editorptr Az editorre mutató pointer
     */
    static void Run(Editor* editorptr);
};
#endif //NHF_REFORMED_UIEDITOR_H