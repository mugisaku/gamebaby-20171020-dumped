cmake_minimum_required(VERSION 2.8)
project(gmbb)


find_program(CCACHE_FOUND ccache)
if(CCACHE_FOUND)
  set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE "CCACHE_DIR=/tmp/ccachedir ccache")
endif(CCACHE_FOUND)


set(CMAKE_VERBOSE_MAKEFILE ON)


if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug)
endif()


set(CMAKE_C_COMPILER  gcc)
set(CMAKE_C_FLAGS   "-std=c14 -Werror")
set(CMAKE_CXX_COMPILER  g++)
set(CMAKE_CXX_FLAGS "-std=c++14 -Werror")
set(CMAKE_CXX_LINK_FLAGS  "-lstdc++ -lz -lpng -lSDL2 -lSDL2main")


set(CMAKE_C_FLAGS_RELEASE   "${CMAKE_C_FLAGS}   -O2 -march=core2 -fomit-frame-pointer")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS} -O2 -march=core2 -fomit-frame-pointer")
set(CMAKE_C_FLAGS_DEBUG     "${CMAKE_C_FLAGS}   -Og -g")
set(CMAKE_CXX_FLAGS_DEBUG   "${CMAKE_CXX_FLAGS} -Og -g")


if(EMSC)
  set(EXECUTABLE_EXTENSION ".html")
  set(CMAKE_CXX_COMPILER  em++)
  set(CMAKE_CXX_FLAGS "-std=c++14 -Werror -Wno-switch -O2")
  set(CMAKE_CXX_FLAGS_DEBUG "")
  set(CMAKE_CXX_LINK_FLAGS  "${CMAKE_CXX_LINK_FLAGS} -s USE_ZLIB=1 -s USE_LIBPNG=1 -s USE_SDL=2 --embed-file image.png --embed-file large_font.bin --embed-file small_font.bin")
endif()




set(SOURCES
  gmbb_Image.cpp
  gmbb_Image__png.cpp
  gmbb_Image__draw.cpp
  gmbb_Image__transfer.cpp
  gmbb_Image__print.cpp
  gmbb_GlyphSet.cpp
  gmbb_unicode.cpp
  gmbb_environment.cpp
  gmbb_File.cpp
  gmbb_FileReader.cpp
  gmbb_FileWriter.cpp
  gmbb_Storage.cpp
  gmbb_Text.cpp
  gmbb_MessageWindow.cpp
  gmbb_Menu.cpp
  gmbb_ScrollStyleMenuWindow.cpp
  gmbb_ColumnStyleMenuWindow.cpp
  gmbb_RandomNumber.cpp
  gmbb_LineMaker.cpp
  gmbb_Actor.cpp
  gmbb_Director.cpp
  gmbb_EffectObject.cpp
  gmbb_Window.cpp
  gmbb_Window__draw_frame.cpp
  gmbb_Routine.cpp
  gmbb_Game.cpp
  gmbb_Game__Message.cpp
  gmbb_Game__MainMenu.cpp
  gmbb_Game__SackMenu.cpp
  gmbb_Game__Choosing.cpp
  gmbb_Game__StatusMonitor.cpp
  gmbb_Game__StatusReportor.cpp
  gmbb_Game__Debugger.cpp
  gmbb_Game__BoardView.cpp
  gmbb_Game__EffectObject.cpp
  gmbb_Game__controll_hero_piece.cpp
  gmbb_Game__throw_item.cpp
  gmbb_Game__append_enemy.cpp
  gmbb_Game__process_script.cpp
  gmbb_SquareBase.cpp
  gmbb_PieceBase.cpp
  game_GameItem.cpp
  game_SackItem.cpp
  game_Sack.cpp
  game_Hero.cpp
  game_Piece.cpp
  game_Square.cpp
  game_Board.cpp
)


set(SCRIPT_SOURCES
  gmbb_Script.cpp
  gmbb_Script__Token.cpp
  gmbb_Script__TokenString.cpp
  gmbb_Script__StreamReader.cpp
  gmbb_Script__Element.cpp
)




include_directories(./)
include_directories(/usr/include/SDL2)
add_executable("testMain${EXECUTABLE_EXTENSION}" testMain.cpp  ${SCRIPT_SOURCES} ${SOURCES})
add_executable("testScriptElement${EXECUTABLE_EXTENSION}" testScriptElement.cpp ${SCRIPT_SOURCES})


if(EMSC)
add_custom_target(bincopy ALL COMMAND cp ../bin/image.png ./ COMMAND cp /usr/local/share/gmbb/* ./)
set_target_properties("testMain${EXECUTABLE_EXTENSION}"  PROPERTIES LINK_FLAGS "--shell-file ../shell.html")
endif()




