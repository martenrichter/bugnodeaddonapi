cmake_minimum_required(VERSION 3.18)


project (webtransport)



if(MSVC AND CMAKE_JS_NODELIB_DEF AND CMAKE_JS_NODELIB_TARGET)
  # Generate node.lib
  execute_process(COMMAND ${CMAKE_LINKER} /def:${CMAKE_JS_NODELIB_DEF} /out:${CMAKE_JS_NODELIB_TARGET} ${CMAKE_STATIC_LINKER_FLAGS})
endif()




# google quiche build parameters end

#include_directories(${CMAKE_JS_INC})
file(GLOB SOURCE_FILES "*.cc" "*.h")
add_library(${PROJECT_NAME} SHARED ${SOURCE_FILES} ${CMAKE_JS_SRC})
set_target_properties(${PROJECT_NAME} PROPERTIES PREFIX "" SUFFIX ".node")
target_include_directories(${PROJECT_NAME} 
PUBLIC ${CMAKE_JS_INC})
target_link_libraries(${PROJECT_NAME}  ${CMAKE_JS_LIB} )
set_target_properties(${PROJECT_NAME}  PROPERTIES LINKER_LANGUAGE CXX)

execute_process(COMMAND node -p "require('node-addon-api').include"
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
        OUTPUT_VARIABLE NODE_ADDON_API_DIR
        )
string(REPLACE "\n" "" NODE_ADDON_API_DIR ${NODE_ADDON_API_DIR})
string(REPLACE "\"" "" NODE_ADDON_API_DIR ${NODE_ADDON_API_DIR})
target_include_directories(${PROJECT_NAME}
 PRIVATE ${NODE_ADDON_API_DIR})






