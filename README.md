# miniguys

## How to build and run
```
git submodule update --init --recursive
cmake -B build
cmake --build build
./build/miniguys
``` 

## Important notes
### Dependencies
- sdl3 
- cmake
- clang-format

## TODO
- [ ] World (Will store everything about the game's world)
    - [ ] Tiles (The "floor")
        - [ ] Type (Each type might change what can be built/naturally generated on top of it, for example, you cannot build on water, trees do not grow on sand, etc)
            - [ ] Grass
            - [ ] Sand
            - [ ] Rock
            - [ ] Water
            - [ ] ...

    - [ ] Structures (probably use a hash map to store it)
        - [ ] Type
        - [ ] King (or neutral, like trees, rocks, some monument, etc)
        - [ ] Health
        - [ ] ...

    - [ ] Player and enemy (would be interesting to implemente both the player and the enemy as a `king` or something, which would be controlled either by the player inputs or an AI) 

    - [ ] Miniguys (all the miniguys are store in a big array and what defines their actual behaviour is which king they're related to and what they're currently doing)
        - [ ] Type 
            - [ ] miner
            - [ ] lumberjack
            - [ ] farmer
            - [ ] archer
            - [ ] knight
            - [ ] spearman
            - [ ] fire mage
            - [ ] ...

        - [ ] Their king (could be the player or an AI king)
        - [ ] What they're doing
        - [ ] Health
        - [ ] ...

