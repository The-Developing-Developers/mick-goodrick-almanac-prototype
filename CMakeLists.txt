cmake_minimum_required(VERSION 3.15)

project(Almanac VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(MY_SOURCE_FILES_DIR src)
set(MY_SOURCE_FILES_ENUMS_DIR enums)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

set(PROJECT_SOURCES
  ${MY_SOURCE_FILES_DIR}/main.cpp

  ${MY_SOURCE_FILES_DIR}/mainwindow.cpp
  ${MY_SOURCE_FILES_DIR}/mainwindow.h
  ${MY_SOURCE_FILES_DIR}/mainwindow.ui
  ${MY_SOURCE_FILES_DIR}/chord.cpp
  ${MY_SOURCE_FILES_DIR}/chord.hpp
  ${MY_SOURCE_FILES_DIR}/chordbuilder.cpp
  ${MY_SOURCE_FILES_DIR}/chordbuilder.hpp
  ${MY_SOURCE_FILES_DIR}/constants.hpp
  ${MY_SOURCE_FILES_DIR}/scale.cpp
  ${MY_SOURCE_FILES_DIR}/scale.hpp

  ${MY_SOURCE_FILES_DIR}/${MY_SOURCE_FILES_ENUMS_DIR}/alteration.cpp
  ${MY_SOURCE_FILES_DIR}/${MY_SOURCE_FILES_ENUMS_DIR}/alteration.hpp
  ${MY_SOURCE_FILES_DIR}/${MY_SOURCE_FILES_ENUMS_DIR}/chromaticpitch.cpp
  ${MY_SOURCE_FILES_DIR}/${MY_SOURCE_FILES_ENUMS_DIR}/chromaticpitch.hpp
  ${MY_SOURCE_FILES_DIR}/${MY_SOURCE_FILES_ENUMS_DIR}/degree.cpp
  ${MY_SOURCE_FILES_DIR}/${MY_SOURCE_FILES_ENUMS_DIR}/degree.hpp
  ${MY_SOURCE_FILES_DIR}/${MY_SOURCE_FILES_ENUMS_DIR}/distanceinsemitones.cpp
  ${MY_SOURCE_FILES_DIR}/${MY_SOURCE_FILES_ENUMS_DIR}/distanceinsemitones.hpp
  ${MY_SOURCE_FILES_DIR}/${MY_SOURCE_FILES_ENUMS_DIR}/enumerations.hpp
  ${MY_SOURCE_FILES_DIR}/${MY_SOURCE_FILES_ENUMS_DIR}/functionalsequence.cpp
  ${MY_SOURCE_FILES_DIR}/${MY_SOURCE_FILES_ENUMS_DIR}/functionalsequence.hpp
  ${MY_SOURCE_FILES_DIR}/${MY_SOURCE_FILES_ENUMS_DIR}/interval.cpp
  ${MY_SOURCE_FILES_DIR}/${MY_SOURCE_FILES_ENUMS_DIR}/interval.hpp
  ${MY_SOURCE_FILES_DIR}/${MY_SOURCE_FILES_ENUMS_DIR}/naturalnote.cpp
  ${MY_SOURCE_FILES_DIR}/${MY_SOURCE_FILES_ENUMS_DIR}/naturalnote.hpp
  ${MY_SOURCE_FILES_DIR}/${MY_SOURCE_FILES_ENUMS_DIR}/note.cpp
  ${MY_SOURCE_FILES_DIR}/${MY_SOURCE_FILES_ENUMS_DIR}/note.hpp
  ${MY_SOURCE_FILES_DIR}/${MY_SOURCE_FILES_ENUMS_DIR}/octave.cpp
  ${MY_SOURCE_FILES_DIR}/${MY_SOURCE_FILES_ENUMS_DIR}/octave.hpp

  resources.qrc
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
  qt_add_executable(Almanac
    MANUAL_FINALIZATION
    ${PROJECT_SOURCES}
  )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET Almanac APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
  if(ANDROID)
    add_library(Almanac SHARED
      ${PROJECT_SOURCES}
    )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
  else()
    add_executable(Almanac
      ${PROJECT_SOURCES}
    )
  endif()
endif()

target_include_directories(Almanac PRIVATE ${MY_SOURCE_FILES_DIR})
target_include_directories(Almanac PRIVATE ${MY_SOURCE_FILES_DIR}/${MY_SOURCE_FILES_ENUMS_DIR}/)
target_link_libraries(Almanac PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.Almanac)
endif()
set_target_properties(Almanac PROPERTIES
  ${BUNDLE_ID_OPTION}
  MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
  MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
  MACOSX_BUNDLE TRUE
  WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS Almanac
  BUNDLE DESTINATION .
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
  qt_finalize_executable(Almanac)
endif()
