set(CUR_DIR ${CMAKE_CURRENT_LIST_DIR})

file(GLOB FONTLIB_SRC_FILES ${CUR_DIR}/*.cpp ${CUR_DIR}/*.h)

set(FONTLIB_OUTPUT_NAME fontrendering)

add_library(${FONTLIB_OUTPUT_NAME} STATIC ${FONTLIB_SRC_FILES})

target_include_directories(${FONTLIB_OUTPUT_NAME} PRIVATE ${THIRD_PARTY_DIR}/freetype/include/ ${THIRD_PARTY_DIR}/SDL/include)

set_property(TARGET ${FONTLIB_OUTPUT_NAME} PROPERTY CXX_STANDARD 14)

add_subdirectory(${CUR_DIR}/app)

