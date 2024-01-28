# SOKOBAN

Данное приложения является многоуровневой игрой Sokoban (Сокобан), созданное с помощью графической библиотеки SFML.

# Комплияция

Компиляция и сборка проекта осуществляются с помощью CMakeLists.txt, предоставленного в данном репозитории

# Правила игры

Правила данной игры достаточно просты: персонаж игрока находится в лабиринте, внутри которого расставлены ящики. Игроку необходимо пройти весь лабиринт, расставив ящики на отмеченные места. В этом случае уровень является успешно пройденным. За каждый пройденный уровень игроку начисляются монетки, которые он может потратить на отмену неверно сделанного хода.


## Функционал
Для перемещения игрока используются клавишы:
* W (Up) - перемещение игрока вверх;
* A (Left) - перемещение игрока влево;
* S (Down) - перемещение игрока вниз;
* D (Right) - перемещение игрока вправо;

Для выхода из приложения можно нажать клавишу Esc.

## Запуск релиза
Скачанный релиз можно установить командой
```
sudo dpkg -i SOKOBAN-1.0.0-Linux.deb
```

Для корректной работы приложения и сохранения настроек запуск приложение осуществляется командой
```
sudo sokoban
```


## Демо
![Alt text](https://github.com/SerpentDragon/Sokoban-SFML/blob/master/Demo/demo1.png)
![Alt text](https://github.com/SerpentDragon/Sokoban-SFML/blob/master/Demo/demo2.png)