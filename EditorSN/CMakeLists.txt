cmake_minimum_required(VERSION 3.19)
project(EditorSN LANGUAGES CXX)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core)

qt_standard_project_setup()

qt_add_executable(EditorSN
    main.cpp
    Node.h
    LinkedList.h
    Stack.h
    Operation.h
)

target_link_libraries(EditorSN
    PRIVATE
        Qt::Core
)

include(GNUInstallDirs)

install(TARGETS EditorSN
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)
