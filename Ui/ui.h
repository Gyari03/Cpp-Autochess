/**
 * @file ui.h
 * @brief Ez a header tárolja a ui(user interface) absztrakt osztályt.
 */

#ifndef NHF_REFORMED_UI_H
#define NHF_REFORMED_UI_H


/**
 * @brief ui absztakt osztály
 * Ebből származik a uiGame, uiEditor, uiMenu.
 * Ezek az osztályok tartják fent a kapcsolatot a felhasználó és számítógép között.
 */
class ui {
public:
    ui(){}                              /**< Default konstruktor */
    
    /**
     * @brief Tisztán virtuális tag függvény a képernyőre való megjelenítésért.
     * Ez mutatja meg a felhasználónak a program válaszreakcióját a felhasználó bemenetére.
     */
    virtual void display()=0;           


    virtual bool handleInput()=0;       /**< Tisztán virtuális tagfgv. Ez felelős a bemenetek kezeléséért. */
    
    /**
     * @brief Tisztán virtuális tagfgv. Ez felelős a display() és handleInput() egymással való kommunkiációjának kialakítására.
     * Minden ebből származó osztályban az idle() úgy néz ki, hogy egymás után következik a display() és handleInput() és ezek vannak egy while ciklusban amiből akkor lép ki, ha parancsot kapott a kilépésre a handleInput()-on keresztül.
     */
    virtual void idle()=0;

    /**
     * @brief Letisztítja a képernyőt.
     * Letörli a képernyőn kiírt adatokat, hogy az újakat "tiszta lapra" lehessen kiírni.
     * A tagfüggvény van arra is kezelve ha windows-ról van futtatva vagy linuxról.
     */
    static void clearScreen();

    /**
     * @brief Függvény adott milliszekundum-nyi késleltetésre.
     * Hasznos arra, hogy egy sakk meccs ne egyből fusson le, hanem mindig várjon a gép lépésenként, hogy legyen ideje felfognia a felhasználónak.
     * A tagfüggvény van arra is kezelve ha windows-ról van futtatva vagy linuxról.
     * @param ms milliszekundum-nyi késleltetés
     */
    static void delayMilliseconds(unsigned int ms);
};
#endif //NHF_REFORMED_UI_H