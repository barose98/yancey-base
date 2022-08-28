cmake_minimum_required (VERSION 2.8.11)

set( BASE_DIR "/home/roseba/Projects/SOFT/CPP/yancey-base")
set(LIB_NAME "yancey-base" )
set(  OpenGL_GL_PREFERENCE "GLVND")
set(YANCEY_BASE_INCLUDE "${BASE_DIR}/include")

find_package(SDL2 REQUIRED)
find_package(OpenGL REQUIRED)
find_package(Box2D REQUIRED)

add_library (${LIB_NAME} SHARED
${BASE_DIR}/src/YanceyBase.cpp
${BASE_DIR}/src/SDLGame.cpp  
${BASE_DIR}/src/YanceyShape.cpp  
)
target_compile_definitions(${LIB_NAME} PUBLIC DEBUG)

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
  ${YANCEY_BASE_INCLUDE}
  ${OPENGL_INCLUDE_DIRS} 
  ${SDL2_INCLUDE_DIRS}
  )

target_link_libraries(${LIB_NAME} ${SDL2_LIBRARIES} ${OPENGL_LIBRARIES}  )


