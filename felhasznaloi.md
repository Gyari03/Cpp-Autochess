# NHF - Felhasználói dokumentáció

>Gyarmathy Gábor(LW7L10)

## Rövid leírás a játékról
A sakk egy stratégiai játék, amelyben két játékos különböző bábukat mozgatva próbálja meg mattba szorítani az ellenfelét egy 8x8-as táblán. Ebben a változatban azonban a játékosok helyett két csapat automatikusan játszik egymás ellen. A játék a hagyományos sakk szabályai szerint zajlik, azzal a különbséggel, hogy a játék vége az ellenfél összes királyának leütésével ér véget. Sakkot itt nem lehet adni, csak a király leütése számít.

## A menük használata
Miután a felhasználó elindítja a játékot, a főmenüvel találkozik:
### Főmenü
>1) Play
>2) Exit

Ahhoz, hogy a felhasználó tudjon a menüpontok között lépkedni, be kell írnia a választott menüpontnak a számát.
Tehát ha ki szeretne lépni, akkor itt az **Exit** menüpontot kell választania, ha pedig játszani, akkor a **Play**-t kell választani.

### Játék menü
Miután a felhasználó kiválasztota a **Play**-t ez a menü fogja fogadni:
>1) New game
>2) Army editor

A **New Game** menüponttal a szimulációs játék indításához szükséges menü nyílik meg, míg az **Army Editor** menüponttal a felhasználó létrehozhat és szerkeszthet seregeket.

### Army editor menü
Az Army Editor menüben a felhasználó új seregeket hozhat létre, vagy szerkesztheti/törölheti a meglévőket.
>1) Create new army
>2) myArmy1
>3) myArmy2
>4) ... 

Ha a felhasználó egy meglévő sereget választ, a program szerkesztő módban megnyitja azt.

Ha a felhasználó új sereg létrehozását választja, egy üres táblával nyílik meg a szerkesztő.

###  New game menü

Itt tudja a Felhasználó kiválasztani a seregeket a csatára, majd elindítani a csatát.
>1) Army1
>2) Army2
>3) Start game

Ha a Felhasználó valamelyik Army gombot nyomja, meg akkor a program felsorolja az összes lementett sereget, és tud választani közülük, hogy melyiket akarja a csapatba berakni.

A felhasználó az Army gombok megnyomásával választhatja ki a mentett seregek közül, melyeket be szeretne rakni a csapatokba. Az army1-be betöltött csapat a fehér, az army2-be betöltött csapat pedig a fekete lesz.


## Army editor

Miután a felhasználó megnyitja a seregszerkesztőt, egy sakktábla egyik térfele jelenik meg előtte. Ha a felhasználó egy létező sereget választott, a seregben már létező bábu a táblán lesznek, egyébként üres tábla fogadja.

A felhasználó hozzáadhat, kitörölhet és felülírhat bábukat a seregben. Ezen kívül lehetőség van a sereg törlésére is.

### Bemenetek:

| Bemenet | Válasz                              |  
|---------|-------------------------------------|
| KXY     | Adott koordinátára király betöltése |     
| HXY     | Adott koordinátára ló betöltése     |    
| QXY     | Adott koordinátára királynő betöltése |     
| PXY     | Adott koordinátára paraszt betöltése |     
| RXY     | Adott koordinátára bástya betöltése |     
| BXY     | Adott koordinátára futó betöltése   |    
| DXY     | Adott koordinátán lévő bábu törlése | 
| delete  | Sereg törlése                       | 

Ha a felhasználó új sereget készített, a program megkérdezi, hogy el szeretné-e menteni, és ha igen, milyen névvel. A név nem lehet már létező, nem tartalmazhat szóközöket, és legfeljebb 35 karakter hosszú lehet.

Ha a sereg elkészült és sikeresen lementésre került, a felhasználó ki is próbálhatja azt a szimulátorban.

## Game

Miután a felhasználó elindítja a szimulációt, a játék nem fogad inputokat. A felhasználónak végig kell várnia, amíg a játék véget ér.

Mindkét csapatnak legalább egy királlyal kell rendelkeznie, különben az a csapat automatikusan veszít, mivel nincs, ki vezesse a sereget.