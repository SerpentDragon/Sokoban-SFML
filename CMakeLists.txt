cmake_minimum_required(VERSION 3.10)

project (SOKOBAN VERSION 1.0.0)

set(INSTALL_DIR ${CMAKE_INSTALL_PREFIX}/${PROJECT_NAME})
configure_file(GameFiles/path/absolute_path.h.in absolute_path.h)

find_package(Boost COMPONENTS locale REQUIRED)
find_package(SFML 2.5 COMPONENTS graphics audio window system REQUIRED)

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

file(COPY GameFiles/fonts DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY GameFiles/locale DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY GameFiles/music DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY GameFiles/textures DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

add_executable(sokoban ${SOURCE_FILE})

target_link_libraries(sokoban PRIVATE Boost::locale)
target_link_libraries(sokoban PRIVATE sfml-graphics sfml-audio sfml-window sfml-system)
target_include_directories(sokoban PRIVATE ${CMAKE_BINARY_DIR})

set_target_properties(sokoban PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)

install(TARGETS sokoban RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)

install(DIRECTORY GameFiles/fonts DESTINATION ${INSTALL_DIR})
install(DIRECTORY GameFiles/locale DESTINATION ${INSTALL_DIR})
install(DIRECTORY GameFiles/music DESTINATION ${INSTALL_DIR})
install(DIRECTORY GameFiles/textures DESTINATION ${INSTALL_DIR})
install(CODE "file(MAKE_DIRECTORY ${INSTALL_DIR}/data)")

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT shelyganovdmitry@gmail.com)

include (CPack)
