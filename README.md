# NHF - Autochess

>Gyarmathy Gábor(LW7L10)


## A programról röviden
* C++ 03-as standardjában íródott a program.
* A program konzolos felületű.
* A program mindenhol angol nyelvet használ a felhasználói felületen.

## Rövid leírás a játékról
A sakk egy stratégiai játék, melyben két játékos különböző bábukat mozgatva próbálja meg mattba szorítani az ellenfelét 
felváltva lépegetve egy 8x8-as táblán. Ebben a változatban viszont a nevéből fakadóan automatikusan fog egymással játszani a 2 csapat.
A játék a hagyományos sakk szabályaival fog játszódni annyi különbséggel, hogy a játék végét vagy az ellenfél összes bábujának a leütésével szerzi egy csapat, vagy ha a királyt üti le. Sakkot itt majd nem lehet adni, csak a király leütése válik fontossá(vagy ha a csapaton belül nincs király, akkor az ellenséges sereg teljes elpusztítása).

## Eltérések az általános sakktól
* A játékban lehetőség van egy saját térfél létrehozására, egy 8x4-es területen ahol egy sereget lehet létrehozni akármilyen bábukombinációból.
* Egy csapat addig nem veszt ameddig le nem ütik az összes királyát, vagy ha nincsen király a seregben az összes bábut.
* A külön létrehozott seregeket szabadon rakhatjuk be egymás ellen.
* A seregek automatikusan el fogják dönteni, hogy mit fognak lépni egy _félig_-random módon, mivel amikor lehetőségük van egy ellenséges bábu leütésére, akkor az kap prioritást.

## Menük leírása
A menükben tud majd navigálni a felhasználó azzal kapcsolatban, hogy mit szeretne csinálni. A felhasználó a megfelelő menüt a sorszámának a kiválasztásával tudja aktiválni. Visszalépni az előzőbe a 0.-dik sorszám beírásával tudja.

### Főmenü
>1) Play
>2) Exit

### Játék menü
>1) New game
>2) Army editor

### New game menü
Itt kiválaszthatja a felhasználó, hogy melyik két sereget akarja egymás ellen harcolni és elindíthatja a játékot.

### Army editor menü
Itt tudja majd a felhasználó létrehozni új seregeket vagy szerkeszteni/törölni.
>1) Create new army
>2) myArmy1
>3) myArmy2
>4) ...

## Sereg készítése/szerkesztése
Ha a felhasználó sereget szeretne készíteni, az army editoron belül tudja.
A szerkesztőn belül egy 8x4-es tábla fogadja a felhasználót ahol a megfelelő koordináták és egy adott betűnek a leírásával létre tud hozni egy bábut a seregen belül az alábbi formátumban:
**K54**, ahol 'K' az angol King szóból a királyt jelenti, az '5' x koordináta, '4' pedig y koordináta.
### Bábuk jelölése:
* King: **K**
* Queen: **Q**
* Horse: **H**
* Rook: **R**
* Bishop: **B**
* Pawn : **P**

Ha esetleg egy bábut törölni szeretnénk, akkor egy bábutípusnak a betűjele helyett a **D** jelzővel lehet bábut törölni(Az angol *delete* szóból).

Ha ki szeretnénk belőle lépni, akkor inputnak bábutípus helyett **0**-át kell megadni. Ilyenkor a program megkérdezi a felhasználótól, hogy szeretné-e lementeni az alábbi sereget. Ha igen, akkor a felhasználónak nevet is kell majd adnia a seregnek.
Ezután az új sereg a sereg-lista menünek a legvégére bekerül, és lementésre kerül.

## Játék elindítása
A *New game* menüben a játékosnak lehetősége lesz mintkét csapat helyére kiválasztania 1-1 sereget, az elkészítettekből.
Ezután el tudja indítani a játékot.

## Játék menete

Miután a felhasználó elindítja a játékot a szimuláció addig fut ameddig egy győztes csapat nem lesz, majd a játék kiírja a végeredményt.


## Bemenet-kezelés
A program a hibás bemeneteket figyelmen kívül hagyja a legtöbb eseteben, csak a felhasználó helyes bemeneteit használja fel.
