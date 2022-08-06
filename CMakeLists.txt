cmake_minimum_required (VERSION 2.8.11)

project("lib-yancey-base")
set(LIB_NAME ${CMAKE_PROJECT_NAME} )
set(  OpenGL_GL_PREFERENCE "GLVND")

find_package(SDL2 REQUIRED)
find_package(OpenGL REQUIRED)
find_package(Box2D REQUIRED)

#include_directories(
add_library (${LIB_NAME} SHARED
${CMAKE_CURRENT_SOURCE_DIR}/src/YanceyBase.cpp
${CMAKE_CURRENT_SOURCE_DIR}/src/SDLGame.cpp  
)

set_target_properties(${LIB_NAME} PROPERTIES PREFIX "")
#target_compile_definitions(${LIB_NAME} PUBLIC DEBUG)

message("FOUND GL = " ${OPENGL_FOUND})
message("FOUND SDL2 = " ${SDL2_FOUND})
message("FOUND BOX2D = " ${BOX2D_FOUND})
#message( ${CMAKE_MODULE_PATH} )

 #message(${LIB_NAME})
# message(  ${GLEW_LIBRARIES} )
# message(find_library(${GLEW}) )
 
message(  ${OPENGL_LIBRARIES} )
#message(  ${SDL2_INCLUDE_DIRS} )

target_include_directories (${LIB_NAME} PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}/include
  ${OPENGL_INCLUDE_DIRS} 
  ${SDL2_INCLUDE_DIRS}
  )

target_link_libraries(${LIB_NAME} ${SDL2_LIBRARIES} ${OPENGL_LIBRARIES}  )


