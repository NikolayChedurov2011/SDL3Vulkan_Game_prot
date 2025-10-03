cmake_minimum_required(VERSION 3.31.5)
project(Game)

file(GLOB_RECURSE GAME_SOURCES CONFIGURE_DEPENDS 
	"${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/src/*.h"
)
add_executable(${PROJECT_NAME})
target_sources(${PROJECT_NAME} PRIVATE ${GAME_SOURCES})

target_link_libraries(${PROJECT_NAME} PRIVATE EngineCore)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)

set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

file(GLOB_RECURSE GAME_ASSETS "${CMAKE_CURRENT_SOURCE_DIR}/assets/*")
foreach(f ${GAME_ASSETS})
file(RELATIVE_PATH rel "${CMAKE_CURRENT_SOURCE_DIR}/assets" "${f}")
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    #COMMAND ${CMAKE_COMMAND} -E copy_directory
            #"${CMAKE_CURRENT_SOURCE_DIR}/assets"
            #"$<TARGET_FILE_DIR:${PROJECT_NAME}>/assets"
			COMMAND ${CMAKE_COMMAND} -E copy_if_different "${f}" "$<TARGET_FILE_DIR:${PROJECT_NAME}>/assets/${rel}"
)
endforeach()