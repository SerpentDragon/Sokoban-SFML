cmake_minimum_required(VERSION 3.10)

project (SOKOBAN VERSION 1.0.0)

find_package(Boost COMPONENTS locale REQUIRED)
find_package(SFML 2.5 COMPONENTS graphics audio window system REQUIRED)

set(SOURCE_FILE
    GameFiles/source/Interface/Interface.cpp
    GameFiles/source/Interface/Environment.cpp
    GameFiles/source/Interface/VCS/VCSWindow.cpp
    GameFiles/source/Interface/VCS/GraphicsTree.cpp
    GameFiles/source/Interface/pollEvent.cpp
    GameFiles/source/Managers/FileIOManager.cpp
    GameFiles/source/Managers/Localizer.cpp
    GameFiles/source/Managers/TextureManager.cpp
    GameFiles/source/Managers/SoundManager.cpp
    GameFiles/source/Player/Player.cpp
    GameFiles/source/settings/settings.cpp
    GameFiles/source/VersionControl/VersionControlSystem.cpp
    GameFiles/source/VersionControl/CommitTree.cpp
    GameFiles/source/VersionControl/Commit.cpp
    GameFiles/source/Widgets/Button.cpp
    GameFiles/source/Widgets/DropDownList.cpp
    GameFiles/main.cpp
)

file(COPY GameFiles/app_data/fonts DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/app_data)
file(COPY GameFiles/app_data/locale DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/app_data)
file(COPY GameFiles/app_data/music DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/app_data)
file(COPY GameFiles/app_data/textures DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/app_data)

add_executable(sokoban ${SOURCE_FILE})

target_link_libraries(sokoban PRIVATE Boost::locale)
target_link_libraries(sokoban PRIVATE sfml-graphics sfml-audio sfml-window sfml-system)
target_include_directories(sokoban PRIVATE ${CMAKE_BINARY_DIR})

set_target_properties(sokoban PROPERTIES
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED ON
)
