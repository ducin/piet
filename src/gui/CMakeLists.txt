# Read more about configuring cmake with Qt at:
# http://qt-project.org/quarterly/view/using_cmake_to_build_qt_projects

INCLUDE(${QT_USE_FILE})
ADD_DEFINITIONS(${QT_DEFINITIONS})

INCLUDE_DIRECTORIES(
  ${CMAKE_SOURCE_DIR}/src/core
  ${CMAKE_CURRENT_BINARY_DIR}
)

SET(gui_SOURCES
  machine_widget.cpp
  child_window.cpp
  main_window.cpp
  main.cpp
)

SET(gui_HEADERS
  main_window.h
  child_window.h
  machine_widget.h
)

SET(gui_FORMS
  machine_widget.ui
  main_window.ui
)

SET(gui_RESOURCES
  application.qrc
)

QT4_WRAP_CPP(gui_HEADERS_MOC ${gui_HEADERS})
QT4_WRAP_UI(gui_FORMS_HEADERS ${gui_FORMS})
QT4_ADD_RESOURCES(gui_RESOURCES_RCC ${gui_RESOURCES})

ADD_EXECUTABLE(gui
  pguivirtualmachine.cpp # this is not a UI file (no moc generated)
  ${gui_SOURCES} 
  ${gui_HEADERS_MOC}
  ${gui_FORMS_HEADERS}
  ${gui_RESOURCES_RCC}
)

TARGET_LINK_LIBRARIES(gui
  ${QT_LIBRARIES}
  PietCore
)
