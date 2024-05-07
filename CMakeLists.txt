cmake_minimum_required(VERSION 3.26)
project(NHF_REFORMED)

set(CMAKE_CXX_STANDARD 11)

add_executable(NHF_REFORMED main.cpp
        Menu/menu.h
        Menu/button.h
        Menu/menu.cpp
        Menu/button.cpp
        Menu/buttonfunctions.cpp
        Menu/buttonfunctions.h
        Ui/ui.cpp
        Ui/ui.h
        Ui/uiMenu.cpp
        Ui/uiMenu.h
        Game/Game.cpp
        Game/Game.h
        Game/Team.cpp
        Game/Team.h
        Game/Piece.cpp
        Game/Piece.h
        List/List.hpp
        Game/Move.cpp
        Game/Move.h
        Game/Pieces/Horse.cpp
        Game/Pieces/Horse.h
        Game/Pieces/Queen.cpp
        Game/Pieces/Queen.h
        Game/Pieces/King.cpp
        Game/Pieces/King.h
        Game/Pieces/Pawn.cpp
        Game/Pieces/Pawn.h
        Game/Pieces/Bishop.cpp
        Game/Pieces/Bishop.h
        Game/Pieces/Rook.cpp
        Game/Pieces/Rook.h
        Game/Army.cpp
        Game/Army.h
        Ui/uiGame.cpp
        Ui/uiGame.h
        Ui/uiEditor.cpp
        Ui/uiEditor.h
        Editor/Editor.cpp
        Editor/Editor.h
        Game/Pieces/Bishop.h
        Memtrace/memtrace.h
        Memtrace/memtrace.cpp
        "File Management/Filemanagement.h"
        "File Management/Filemanagement.cpp"
        Menu/ButtonFunction.cpp
        Menu/ButtonFunction.h
        Game/Computer.h
        Game/Computer.cpp

)
add_compile_definitions(MEMTRACE)
target_compile_options(NHF_REFORMED PRIVATE -Wall -Werror)