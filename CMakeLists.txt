cmake_minimum_required(VERSION 3.17...3.25)

project(udprecv LANGUAGES CXX C)
set(Qt5_DIR "/opt/Qt/5.15.2/gcc_64/lib/cmake/Qt5")
find_package(Qt5 COMPONENTS Core Gui Quick Widgets Quick3D Positioning Multimedia SerialPort Test WebSockets LinguistTools REQUIRED)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

set(SRC_FILES 
    ${PROJECT_SOURCE_DIR}/udp.qrc
    ${PROJECT_SOURCE_DIR}/Udprecv.hpp
    ${PROJECT_SOURCE_DIR}/Udprecv.cpp
    ${PROJECT_SOURCE_DIR}/udpmesg.hpp
    ${PROJECT_SOURCE_DIR}/main.cpp
    
)

add_executable(${PROJECT_NAME} ${SRC_FILES})


target_include_directories(
    ${PROJECT_NAME}
    PRIVATE
        ${Qt5Core_INCLUDE_DIRS}
        ${Qt5Gui_INCLUDE_DIRS}
        ${Qt5Widgets_INCLUDE_DIRS}
        ${Qt5Quick_INCLUDE_DIRS}
        ${PROJECT_BINARY_DIR}
        ${PROJECT_SOURCE_DIR}
)

target_link_libraries(
    ${PROJECT_NAME} 
    PUBLIC
        Qt5::Quick Qt5::Gui Qt5::Multimedia Qt5::Core Qt5::Network Qt5::WebSockets Qt5::Widgets
)

set_target_properties(${PROJECT_NAME} PROPERTIES CXX_STANDARD 17)
target_compile_options(${PROJECT_NAME} PUBLIC "$<$<COMPILE_LANG_AND_ID:CXX,MSVC>:/permissive->")
target_compile_options(${PROJECT_NAME} PUBLIC "$<$<COMPILE_LANG_AND_ID:CXX,GNU,Clang>:-fpermissive>")

