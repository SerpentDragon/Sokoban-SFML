cmake_minimum_required(VERSION 3.10)

project (SOKOBAN)

set(SOURCE_FILE
    GameFiles/Interface/Interface.cpp
    GameFiles/Interface/Drawing.cpp
    GameFiles/Managers/FileIOManager.cpp
    GameFiles/Managers/Localizer.cpp
    GameFiles/Managers/TextureManager.cpp
    GameFiles/Managers/SoundManager.cpp
    GameFiles/Player/Player.cpp
    GameFiles/Player/settings.cpp
    GameFiles/Widgets/Button.cpp
    GameFiles/Widgets/DropDownList.cpp
    GameFiles/main.cpp
)

find_package(Boost COMPONENTS locale REQUIRED)
find_package(SFML 2.5 COMPONENTS graphics audio window system REQUIRED)

file(COPY GameFiles/fonts DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY GameFiles/locale DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY GameFiles/music DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY GameFiles/textures DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

add_executable(sfml-app ${SOURCE_FILE})

target_link_libraries(sfml-app PRIVATE Boost::locale)
target_link_libraries(sfml-app PRIVATE sfml-graphics sfml-audio sfml-window sfml-system)

set_target_properties(sfml-app PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)
