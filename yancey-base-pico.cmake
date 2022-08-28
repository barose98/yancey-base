cmake_minimum_required (VERSION 2.8.11)

set( BASE_DIR "/home/roseba/Projects/SOFT/CPP/yancey-base")
set(LIB_NAME "yancey-base" )

set(YANCEY_BASE_INCLUDE "${BASE_DIR}/include")

add_library (${LIB_NAME} SHARED
${BASE_DIR}/src/YanceyBase.cpp
${BASE_DIR}/src/YanceyShape.cpp  
)
target_compile_definitions(${LIB_NAME} PUBLIC DEBUG)

set_target_properties(${LIB_NAME} PROPERTIES PREFIX "")
#target_compile_definitions(${LIB_NAME} PUBLIC DEBUG)


target_include_directories (${LIB_NAME} PUBLIC
  ${YANCEY_BASE_INCLUDE}
  )

#target_link_libraries(${LIB_NAME} ${SDL2_LIBRARIES} ${OPENGL_LIBRARIES}  )


