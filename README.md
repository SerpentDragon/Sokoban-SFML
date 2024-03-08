# SOKOBAN

This app is a multilevel game Sokoban created using SFML graphic library

# Compilation

You can compile and run the program using CMakeLists.txt from this reposiroty: 
```
git clone git@github.com:SerpentDragon/Sokoban-SFML.git
cd Sokoban-SFML
mkdir build
cd build
cmake ..
cmake --build .
./sokoban
```

# Rules

The rules are quite simple. The player is in a maze inside which boxes are placed. Player should got through the maze and place all the boxes in marked positions. In this case, the level is successfuly completed. For each successfully completed level, player earns coins which can be used to pay on cancelling his wrong move.

## Functional
These keys are used to move the player:
* W (Up) - to move player up;
* A (Left) - to move player left;
* S (Down) - to move player down;
* D (Right) - to move player right;

To exit this application you can press Esc key.

## Launch of the release
You can install downloaded release using
```
sudo dpkg -i SOKOBAN-1.0.0-Linux.deb
```
command.
You should run the app using 
```
sudo sokoban
```
command to ensure correct operation of the app. 
More info in "release_branch" branch.
## Demo
![Alt text](https://github.com/SerpentDragon/Sokoban-SFML/blob/master/Demo/demo1.png)
![Alt text](https://github.com/SerpentDragon/Sokoban-SFML/blob/master/Demo/demo2.png)