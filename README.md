# Laboratorní cvičení BIN3 : Celulární automaty
V tomto cvičení budete hledat přechodová pravidla pro 1D celulární automat, který bude řešit problém __majority__. Genetický algoritmus ve variantě (μ+λ) (neboli μ rodičů a λ potomků) již máte připravený. Vaším úkolem bude doplnit simulátor, který pro daného jedince `Individual` spočítá jeho fitness hodnotu. Evoluční algoritmus se bude snažit tuto fitness maximalizovat.

Pro ladění řešení máte připravený [online simulátor](https://ehw.fit.vutbr.cz/bin-lab-ca/), kam můžete nakopírovat vypsaného jedince ve formátu JSON (`std::cout << population[0] << std::endl`). Poté můžete simulovat chování.


## Příprava
Vaším úkolem bude modifikovat výpočet fitness funkce tak, aby funkce řešila úkol majority. Nejlepší fitness tak budou mít pravidla, která vedou nejblíže k majoritě. Budete zasahovat zejména do souboru [simulator.hpp](simulator.hpp). 

Doplňte určení pravidla pro dvoj- a trojokolí v simulátoru. Například pro buňky `00101`, kdy uprostřed je buňka, pro kterou počítáme výsledek s indexem `cell` a LSB (1) je buňka nejvíc __nalevo__ od hledané buňky (s indexem `cell - 2`), vrátíte `buffer[future][cell] = indiv->getRule(0b00101);`.

Dále doplníte výpočet fitness funkce. Simulace jednoho počátečního stavu `state` probíhá tak, že do 1D pole `buffer[0]` nahrajeme počáteční stav `data[state]`. Dále pro fixní počet kroků `step` pro každou buňku pomocí přechodových pravidel vypočítáme výsledek do `buffer[1]`. Okrajové buňky jsou řešeny tak, že dochází __k replikaci krajních buněk__.

Na závěr každého kroku prohodíme 1D pole (řešeno indexy `current` a `future`).

## Spuštění
```
make
./ca_majority
```

## Úkol 1: základní fitness
Navrhněte fitness tak, že pro všechy stavy simulujete všechny kroky. Vypočítáte, kolik buněk v _nejlepším kroku_ odpovídalo očekávané hodnotě definované v `expected[state]`. Pokud úplně všechny buňky odpovídaly očekávané hodnotě, nepřičítejte do fitness pouze číslo `cells`, ale zaveďte bonus `10 * cells`. Také můžete inkrementovat hodnotu `validStates` pro statistiku.

### Otázky:
- Podařilo se dosáhnout vysoké fitness?
- Co by se stalo, pokud by nebyl zaveden bonus?
- Proč je tato implementace nevhodná (simulujte řešení v simulátoru)


## Úkol 2: stabilní řešení
Upravte výpočet fitness tak, že počítáte pouze stabilní CA (tj. poslední dva stavy jsou stejné, porovnávat můžete pomocí `std::equal`). Pro stabilní stav vypočtěte fitness stavu podle počtu buněk shodných s očekávanou hodnotou. Pokud jsou všechny stejné a odpovídají očekávané, přičtěte bonus. Pokud se neskončilo stabilní konfigurací, k fitness nic nepřičítejte.

### Otázky:
- Podařilo se dosáhnout vysoké fitness?
- Co by se stalo, pokud by nebyl zaveden bonus?