
find_package(ECM 1.0.0 REQUIRED NO_MODULE)
set(CMAKE_MODULE_PATH ${ECM_MODULE_PATH} ${ECM_KDE_MODULE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
find_package(Qt5 REQUIRED COMPONENTS Widgets Core Quick QuickWidgets)
find_package(KF5CoreAddons REQUIRED)
find_package(KF5I18n REQUIRED)
#find_package(KF5KCMUtils REQUIRED)

add_executable(lliurex-desktop-layout-selector main.cpp window.cpp plugin.cpp lnfobject.cpp ../rsrc/resources.qrc)
target_link_libraries(lliurex-desktop-layout-selector Qt5::Widgets Qt5::Core Qt5::Quick Qt5::QuickWidgets KF5::CoreAddons KF5::I18n)

#install(TARGETS panel-design-manager RUNTIME DESTINATION bin)
