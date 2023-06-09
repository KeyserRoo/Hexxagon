cmake_minimum_required(VERSION 3.24)
project(Hexxagon)

set(CMAKE_CXX_STANDARD 11)
set(BUILD_SHARED_LIBS FALSE)

include(FetchContent)

FetchContent_Declare(SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 2f11710abc5aa478503a7ff3f9e654bd2078ebab
        )

FetchContent_MakeAvailable(SFML)

add_executable(Hexxagon sourceFiles/main.cpp
        sourceFiles/Background.cpp headerFiles/Background.h
        sourceFiles/Board.cpp headerFiles/Board.h
        sourceFiles/Button.cpp headerFiles/Button.h
        sourceFiles/GameManager.cpp headerFiles/GameManager.h
        sourceFiles/GamePanel.cpp headerFiles/GamePanel.h
        sourceFiles/MenuPanel.cpp headerFiles/MenuPanel.h
        sourceFiles/Node.cpp headerFiles/Node.h
        sourceFiles/Panel.cpp headerFiles/Panel.h
        sourceFiles/PauseMenu.cpp headerFiles/PauseMenu.h
        headerFiles/Owner.h
        )
target_link_libraries(Hexxagon PRIVATE sfml-graphics)