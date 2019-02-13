cmake_minimum_required(VERSION 3.6.3)

project(MARSLite)

add_definitions(
	-c
	-Wall
)

file(GLOB_RECURSE HDRS 
	${MARSLite_SOURCE_DIR}/Engine/*.h
	${MARSLite_SOURCE_DIR}/Engine/Classes/*.h
	${MARSLite_SOURCE_DIR}/Engine/*.hpp
	${MARSLite_SOURCE_DIR}/Engine/Classes/*.hpp
)

file(GLOB_RECURSE SRCS 
	${MARSLite_SOURCE_DIR}/Engine/*.cpp
	${MARSLite_SOURCE_DIR}/Engine/Classes/*.cpp
)

find_package(SFML REQUIRED)

include_directories(
	${MARSLite_SOURCE_DIR}/Engine/
	${MARSLite_SOURCE_DIR}/Engine/Classes
	${MARSLite_SOURCE_DIR}/Thirdparty/Include/
)

link_directories(
	${MARSLite_SOURCE_DIR}/Thirdparty/Lib/
)

add_executable(MARSLite ${HDRS} ${SRCS} Engine/Source/Utility/ResourceContainer.cpp)

target_link_libraries( MARSLite
	${SFML_LIBRARIES}
	libsfml-graphics.so
	libsfml-audio.so
	libsfml-network.so
	libsfml-window.so
	libsfml-system.so
)

set_property(TARGET MARSLite PROPERTY CXX_STANDARD 17)