/**
 * @file Game.h
 * @brief A GameResult enumot és Game osztályt tartalmazó header
 */

#ifndef NHF_REFORMED_GAME_H
#define NHF_REFORMED_GAME_H
#include "Team.h"
#include "Army.h"
#include "Computer.h"

/**
 * @brief A játékeredmény lehetséges értékei
 * A játékban alapból DRAW-ként lesz inicializálva.
 */
enum GameResult {
    TEAM1_WIN,      /**< Első csapat nyertes  */
    TEAM2_WIN,      /**< Második csapat nyertes */
    DRAW            /**< Döntetlen */
};


/**
 * @brief A játék class. Ez van használatban amikor 2 csapat játszik.
 */
class Game {
private:
    Team* team[2];          /**< A két egymás ellen játszó csapatoknak a tömbje, ahol team[0]:White és team[1]:Black */
    Computer computer;      /**< A Computer, ami a csapat lépéseinek a kiszámolásáért lesz felelős */
    bool WhiteTurn;         /**< Egy logikai érték ami azt adja vissza, hogy jelenleg a fehér(team[0]) csapat jön-e */
    bool endOfGame;         /**< Egy logikai érték ami visszaadja, hogy vége van-e a játéknak. */
    GameResult result;      /**< A játék végeredménye. Alaphelyzetben döntetlenre van állítva. */

public:
    /**
     * @brief Game default konstruktor
     */
    Game();

    /**
     * @brief Game destruktor
     * Felszabadítja a 2 dinamikusan lefoglalt csapatot a játékban.
     */
    ~Game();

    /**
     * @brief Game konstruktor 2 paraméterként átadott sereggel.
     * Lemásolja magának a seregeket a 2 Team objektumon belül.
     * @param white Fehér csapat. Ez a csapat lesz a 0.-ás indexű csapat a team tömbben.
     * @param black Fekete csapat. Ez a csapat lesz az 1.-es indexű csapat a team tömbben. Ez a csapat még fel is lesz tükrözve a tábla túloldalára.
     */
    Game(Army* white,Army* black);

    /**
     * @brief Getter függvény a WhiteTurn bool-ra.
     * Bool érték annak az eldöntésére, hogy melyik csapat jön.
     * @return true: Fehér csapat jön 
     * @return false: Fekete csapat jön 
     */
    bool isWhiteTurn()const;

    /**
     * @brief Getter függvény a játék-végét eldöntő bool-ra.
     * Ha igaz, akkor nem lesz több lépés számolva, vége van a játéknak.
     * @return true: Vége a játéknak.
     * @return false: Folytatódik a játék. 
     */
    bool getEnd()const;

    /**
     * @brief Getter függvény a végeredményre.
     * @return A játék végeredménye
     */
    GameResult getResult()const;

    /**
     * @brief Átállítja az EndOfGame boolt az ellentetjére.
     * A kódban arra van használva, hogy véget vessen a játéknak.
     */
    void updateEnd();

    /**
     * @brief Megnézi, hogy van-e bábu az adott mezőn(x,y)
     * Ha megtalálja akkor visszatér egy bábupointerrel. Ha nincs semmi a mezőn akkor nullpointerrel.
     * @param x A keresett mező x koordinátája.
     * @param y A keresett mező y koordinátája.
     * @return Adott mezőn álló bábura mutató pointer.
     */
    Piece* searchFor(int x, int y);

    /**
     * @brief Getter csapat objektumra index alapján
     * 0-ás index idx fehér csapat, 1-es index idx fekete.
     * @param idx Keresett csapat indexe. 
     * @return Keresett csapatra mutató pointer.
     */
    Team* getTeam(size_t idx);

    /**
     * @brief Visszaadja egy paraméterként átadott bábunak a színét a játéban.
     * @param piece Bábu aminek keressük a színét.
     * @return A kérdéses bábunak a csapatszíne.
     */
    TeamColor getColorOfPiece(Piece* piece);

    /**
     * @brief Visszaadja, hogy van-e bármelyik csapatból is bábu az adott mezőn.
     * Mindkét csapaton átmegy és ha mindkettő nullptr-t ad vissza a getPiece(x,y)-ból, akkor a mezőn nincs egy bábu sem.
     * @param x Mező x koordinátája.
     * @param y Mező y koordinátája.
     * @return true: Van rajta bábu. 
     * @return false: Nincs rajta bábu.
     */
    bool occupied(int x,int y);

    /**
     * @brief Amikor lefut, akkor a játék megtesz egy lépést azzal a csapattal akinek a köre van.
     * Algoritmus leírása:
     * - Kiszámolja a csapat lépését a Computer objektum és rámutat a kiválasztott lépésre egy Move pointerrel
     * - A lépésből megkapja, hogy kivel kell lépnie, amiből pedig a csapat színét is.
     * - Megnézi, hogy a mező amire lép el van-e foglalva ellenséges bábuval, és ha igen akkor eltávolítja azt az ellenséges bábut
     * - Majd átállítja az új koordinátákra a bábunak a helyét.
     * - Felszabadítja az előbb jött csapatnak az összesített lépés-listáját.
     */
    void makeMove();

    /**
     * @brief Lejátszik egy darab kört a játékból.
     *  Ha vége lenne a játéknak, akkor egyből véget vet neki mielőtt megtenne egy lépést is.
     *  Ha meg nem lenne vége a játéknak, kiszámolja a lépést, megteszi, majd átadja a kört, azzal, hogy megváltoztatja a WhiteTurn bool-t az ellentetjére.
     */
    void playRound();

    /**
     * @brief Megállapítja, hogy vége van-e a játéknak.
     * Ha vége van a játéknak, akkor frissíti az endOfGame boolt, emellett eldönti, hogy mi a játék végeredménye és beállítja.
     * A játék végeredményének eldöntésének módja:
     * - Ha a jelenlegi körben következő csapatnak 0 legális lépése van, akkor automatikusan döntetlen lesz.
     * - Ha a jelenlegi körben következő csapatnak nincsen királya a táblán, akkor automatikusan a másik csapat nyer.
     * - Egyébként meg folytatódik a játék
     */
    void checkIfOver();

    /**
     * @brief Kitisztítja a csapat összesített lépés-listáját.
     * Annak a csapatnak szabadítja fel ezt a listáját akinek a köre most van(Természetesen a függvény ami ezt használja ezután adja át a kört).
     */
    void clearMovesBuffer();
};
#endif //NHF_REFORMED_GAME_H