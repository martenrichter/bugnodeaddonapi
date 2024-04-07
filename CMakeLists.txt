cmake_minimum_required(VERSION 3.18)

cmake_policy(SET CMP0091 NEW)


#IF (MSVC)
    set(CMAKE_MSVC_RUNTIME_LIBRARY  "MultiThreaded$<$<CONFIG:Debug>:Debug>")
    add_definitions(-D_ITERATOR_DEBUG_LEVEL=0)
    set(protobuf_MSVC_STATIC_RUNTIME ON)
#ENDIF(MSVC)

project (webtransport)


set(CMAKE_POSITION_INDEPENDENT_CODE TRUE)
set(CMAKE_CXX_STANDARD 20)

set(BUILD_TESTING OFF)





IF (WIN32)
    add_compile_definitions(NOMINMAX)
ENDIF(WIN32)


IF (WIN32)
    add_compile_definitions(WIN32_LEAN_AND_MEAN NOGDI)
ENDIF(WIN32)



if(COMMAND cmake_policy)
cmake_policy(SET CMP0003 NEW)
endif(COMMAND cmake_policy)


add_definitions(-DNAPI_VERSION=${napi_build_version})

if(MSVC AND CMAKE_JS_NODELIB_DEF AND CMAKE_JS_NODELIB_TARGET)
  # Generate node.lib
  execute_process(COMMAND ${CMAKE_LINKER} /def:${CMAKE_JS_NODELIB_DEF} /out:${CMAKE_JS_NODELIB_TARGET} ${CMAKE_STATIC_LINKER_FLAGS})
endif()




# google quiche build parameters end

#include_directories(${CMAKE_JS_INC})
file(GLOB SOURCE_FILES "*.cc" "*.h")
add_library(${PROJECT_NAME} SHARED ${SOURCE_FILES} ${CMAKE_JS_SRC})
set_target_properties(${PROJECT_NAME} PROPERTIES PREFIX "" SUFFIX ".node")
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 20)
target_include_directories(${PROJECT_NAME} 
PUBLIC ${CMAKE_JS_INC})
target_link_libraries(${PROJECT_NAME}  ${CMAKE_JS_LIB} )
set_target_properties(${PROJECT_NAME}  PROPERTIES LINKER_LANGUAGE CXX)
IF (WIN32)
  # place for custom window stuff
ELSE(WIN32)
IF(APPLE)
ELSE(APPLE)
    target_link_libraries(${PROJECT_NAME} -static-libgcc -static-libstdc++)
ENDIF(APPLE)
ENDIF(WIN32)

execute_process(COMMAND node -p "require('node-addon-api').include"
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
        OUTPUT_VARIABLE NODE_ADDON_API_DIR
        )
string(REPLACE "\n" "" NODE_ADDON_API_DIR ${NODE_ADDON_API_DIR})
string(REPLACE "\"" "" NODE_ADDON_API_DIR ${NODE_ADDON_API_DIR})
target_include_directories(${PROJECT_NAME}
 PRIVATE ${NODE_ADDON_API_DIR})






