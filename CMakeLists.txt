cmake_minimum_required(VERSION 3.19)
project(FinanceApp LANGUAGES CXX)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets)
find_package(Qt6 REQUIRED COMPONENTS LinguistTools)

qt_standard_project_setup()

qt_add_executable(FinanceApp
    WIN32 MACOSX_BUNDLE
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    password.txt
    Auth.h Auth.cpp
    User.h User.cpp
    financetopics.txt
    quiz.txt
    en.txt
    Quiz_fr.txt
    financetopics_fr.txt

)

qt_add_translations(FinanceApp TS_FILES FinanceApplication_fr_MU_copy.ts)

target_link_libraries(FinanceApp
    PRIVATE
        Qt::Core
        Qt::Widgets
)

install(TARGETS FinanceApp
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

qt_generate_deploy_app_script(
    TARGET FinanceApp
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})
