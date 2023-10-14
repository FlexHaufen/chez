cmake_minimum_required(VERSION 3.24.1)

#----------------------------------------------------
#			   	 PROJECT PROPERTIES
#----------------------------------------------------
project(chez VERSION 0.0.3)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})

## Requierments ## 
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 20)

# Set release and debug folder
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/bin/debug)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/bin/release)


#----------------------------------------------------
#				       RESOURCE
#----------------------------------------------------
#set(ACAER_APP_ICO "${CMAKE_SOURCE_DIR}/resource/images/logo.rc")

#----------------------------------------------------
#				  SOURCE & INCLUDE
#----------------------------------------------------
# Global Header fildes
file(GLOB_RECURSE HEADER_FILES ${CMAKE_SOURCE_DIR}/src/*.h
	                           ${CMAKE_SOURCE_DIR}/src/*.hpp)

# Global Source files
file(GLOB_RECURSE SRC_FILES ${CMAKE_SOURCE_DIR}/src/*c
                            ${CMAKE_SOURCE_DIR}/src/*.cpp)

### APP ###
add_executable(${PROJECT_NAME} 	${SRC_FILES} 
							   	${HEADER_FILES}
							   	${ACAER_APP_ICO})

# Compiler Flags
#target_compile_options(${PROJECT_NAME} PRIVATE /W4)


#----------------------------------------------------
#				    	LIBS
#----------------------------------------------------

#---------SFML---------
set(SFML_STATIC_LIBRARIES TRUE)
set(SFML_DIR ${CMAKE_SOURCE_DIR}/lib/SFML-2.5.1/lib/cmake/SFML)
find_package(SFML 2.5.1 REQUIRED COMPONENTS window system graphics audio network)

#--------SPDLOG-------
add_subdirectory(${CMAKE_SOURCE_DIR}/lib/vendor/spdlog/)

#----IMGUI-SFML-------
set(IMGUI_DIR ${CMAKE_SOURCE_DIR}/lib/vendor/imgui/)
add_subdirectory(${CMAKE_SOURCE_DIR}/lib/vendor/imgui-sfml/)

#----------------------------------------------------
#				      INCLUDE DIRS
#----------------------------------------------------
include_directories(
	${CMAKE_SOURCE_DIR}/src
	#SFML
	${CMAKE_SOURCE_DIR}/lib/SFML-2.5.1/include
)



#----------------------------------------------------
#				      LINK & PCH
#----------------------------------------------------

#Put all libraries into a variable
set(LIBS 	sfml-window
			sfml-system
			sfml-graphics
			sfml-audio
			sfml-network
			spdlog
			ImGui-SFML)

target_link_libraries(${PROJECT_NAME} ${LIBS})



### PCH ###
target_precompile_headers(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/src/chez/ch_pch.h)

	