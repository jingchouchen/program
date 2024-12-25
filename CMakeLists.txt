cmake_minimum_required(VERSION 3.5)

project(financePlaner VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)
find_package(Qt6 REQUIRED COMPONENTS Sql) #数据库
find_package(Qt6 REQUIRED COMPONENTS Charts) #图表
find_package(Qt6 REQUIRED COMPONENTS Network)


set(PROJECT_SOURCES
        main.cpp
        login.cpp
        login.h
        login.ui
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(finacePlaner
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        mainwindow.h mainwindow.cpp mainwindow.ui
        res.qrc
        cell_income.h cell_income.cpp cell_income.ui
        cell_register.h cell_register.cpp cell_register.ui
        cell_forgetpw.h cell_forgetpw.cpp cell_forgetpw.ui
        cell_login.h cell_login.cpp cell_login.ui
        expenditure.h expenditure.cpp expenditure.ui
        income.h income.cpp income.ui
        cell_expenditure.h cell_expenditure.cpp cell_expenditure.ui
        chart.h chart.cpp chart.ui
        exchangerate.h exchangerate.cpp exchangerate.ui
        calcutor.h calcutor.cpp calcutor.ui
        cell_userinformation.h cell_userinformation.cpp cell_userinformation.ui
        translator.h translator.cpp translator.ui
        translator.cpp
        tchartview.cpp tchartview.h






    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET finacePlaner APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(finacePlaner SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(finacePlaner
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(finacePlaner PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
target_link_libraries(finacePlaner PRIVATE Qt6::Sql)
target_link_libraries(finacePlaner PRIVATE Qt6::Charts)
target_link_libraries(finacePlaner PRIVATE Qt6::Network)
# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.finacePlaner)
endif()
set_target_properties(finacePlaner PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS finacePlaner
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(finacePlaner)
endif()
