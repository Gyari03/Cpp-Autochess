/**
 * @file filemanagement.h
 * @brief A fájlkezeléssel foglalkozó osztály és annak deklarációi.
 */


#ifndef NHF_REFORMED_FILEMANAGEMENT_H
#define NHF_REFORMED_FILEMANAGEMENT_H
#include <fstream>
#include "../List/List.hpp"
#include "../Game/Army.h"
#include "../Game/Piece.h"
#include <vector>
#include <string>
#include <sstream>

/**
 * @brief Fájlkezelő osztály.
 * Legfőkébb az elkészített seregek tárolását valósítja meg az armies.dat-ben.
 */
class Filemanagement{

public:

    /**
     * @brief A lementett seregek listájával visszatérő fv.
     * Kiolvassa az adott fájból(armies.dat) a seregeket. Ha nem létezik akkor létrehoz egyet 0 db sereggel.
     * @param filename Az olvasandó fájl neve
     * @return List<Army> A lementett seregek listája
     */
    static List<Army> ListofArmies(const char* filename);

    /**
     * @brief Sereg hozzáfűzése a fájlhoz.
     * A fájl legvégéhez odafűzi a paraméterként kapott sereget.
     * @param army A hozzáfűzendő seregre mutató pointer
     * @param filename A megnyitandó fájl neve
     */
    static void AppendArmy(Army* army,const char* filename);

    /**
     * @brief Sereg átszerkesztése fájlon belül.
     * Algoritmus leírása:
     * - Beolvassuk a sorokat.
     * - Név alapján kikeressük az Army-t, amit editelünk.
     * - Kiolvassuk, hogy hány bábu van az Army-ben.
     * - Ebből tudjuk, hogy hány sort kell majd ignorálni.
     * - A beolvasás második részét egy 2. stringvektorba tároljuk.
     * - Bezárjuk a beolvasást.
     * - Írásra megnyitjuk a fájlt.
     * - Beleírjuk az első stringvektor tartalmát, ami az editelendő Army előtt áll.
     * - Az Army* army alapján beleírjuk a fájlba az Army-t.
     * - Beleírjuk a második stringvektort a fájlba.
     * @param army A szerkesztendő sereg
     * @param filename Fájlnév
     */
    static void EditArmy(Army* army,const char* filename);

    /**
     * @brief 
     * - A overwriteline függvényt használva az első sort írjuk felül: 1-el csökkentjük a sorszámát.
     * - Ismételten létrehozunk lines1 és lines2 vektorokat.
     * - lines1 tartalmazza azokat a sorokat, amelyeket nem kell módosítanunk.
     * - Végigiterálunk lines1-en a kitörlendő névig.
     * - Kihagyjuk az Army-t.
     * - lines2-be olvassuk a fennmaradó sorokat.
     * - Kiírjuk lines1 és lines2 tartalmát 
     * @param army Kitörlendő sereg
     * @param filename Fájlnév
     */
    static void DeleteArmy(Army* army,const char* filename);

private:

    /**
     * @brief Ha az adott fájl nem létezik akkor létrehoz egyet.
     * Emellett használ egy bool visszatérési értéket, amit a ListofArmies fel is használ.
     * @param filename Fájlnév.
     * @return true: Ha nem létezik a keresett fájl. Ekkor ez egyben jelet ad arra, hogy a ListofArmies inicializálja az armies.dat első sorát.
     * @return false: Ha létezik a keresett fájl. Ezután nincs több teendő. 
     */
    static bool ifFileNonExistentCreate(const char* filename);

    /**
     * @brief Beolvasás egy ifstream adott pozíciójától egy adott sorig.
     * Miközben olvas addig a beolvasott sorokat folyamatosan menti kifele egy string tárolóba.
     * @param file Bemeneti filestream.
     * @param lines A sorokat ide tároljuk el.
     * @param boundary Eddig a sorig olvas, ha nincs paraméterként megadva akkor a fájl végéig olvas.
     */
    static void readTillLine(std::ifstream& file, std::vector<std::string>& lines,const std::string& boundary="");

    /**
     * @brief Sorok kihagyására használt metódus.
     * Adott számú sorral továbbtolja a filestreamet. Arra használjuk hogy kihagyhassuk őket.
     * @param file Bemeneti filestream.
     * @param numberofLines Kihagyandó sorok mennyisége.
     */
    static void skipLines(std::ifstream& file,int numberofLines);

    /**
     * @brief Sor-tárolóból beírás a fájlba.
     * Visszaírja egy stringtároló összes tagját a fájlba soronként.
     * @param file Kimeneti filestream.
     * @param lines A fájlba írandó sorok tárolója.
     */
    static void writeLines(std::ofstream& file,std::vector<std::string>& lines);

    /**
     * @brief Beleír egy adott sereget a fájlba.
     * A paraméterként megkapott helyre beírja a sereget a fájlba, majd a fájl elején lévő számot inkrementálja 1-el.
     * @param file Kimeneti filestream.
     * @param army A fájlba írandó seregre mutató pointer.
     */
    static void writeArmy(std::ofstream& file,Army* army);

    /**
     * @brief Felülír egy adott sort a fájlon belül.
     * Adott sorszámú sort felülír egy paraméterként kapott string-el.
     * Algoritmus leírása:
     * - Kiolvassa az egész fájlt egy string-tárolóba.
     * - Majd paraméterként kapott stringgel felülírja a tárolóban a kapott indexű kicserélendő sort.
     * - Visszaírja a fájlba az egészet. 
     * @param filename Fájlneve.
     * @param newLine A sornak az új tartalma.
     * @param lineNumber Helyettesített sor sorszáma.
     */
    static void overwriteline(const char* filename,std::string newLine,int lineNumber);

    /**
     * @brief Egy számot tároló string inkrementálása/dekrementálása
     * Átrakja a stringet egy int-be, majd azt inkrementálja/dekrementálja és visszarakja a stringbe.
     * @param string  Számot tároló string.
     * @param increment Ha igaz akkor megnöveli 1-el a stringben lévő számot, ha pedig hamis akkor 1-el csökkenti.
     */
    static void adjustStringNumber(std::string& string,bool increment);
};
#endif //NHF_REFORMED_FILEMANAGEMENT_H