cmake_minimum_required(VERSION 3.19)
project(untitled LANGUAGES CXX)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets)

qt_standard_project_setup()  # sets AUTOMOC/AUTOUIC/AUTORCC ON

qt_add_executable(untitled
    WIN32 MACOSX_BUNDLE
    src/main.cpp
    src/mainwindow.cpp
    src/mainwindow.h
    src/mainwindow.ui
    src/question.h
    src/question.cpp
    src/mcquestion.h src/mcquestion.cpp
    src/saquestion.h src/saquestion.cpp
    src/mainmenu.h src/mainmenu.cpp
    src/game.h src/game.cpp
    src/optionsmenu.h src/optionsmenu.cpp
)

target_link_libraries(untitled PRIVATE Qt6::Core Qt6::Widgets)

include(GNUInstallDirs)

install(TARGETS untitled
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

qt_generate_deploy_app_script(
    TARGET untitled
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})
