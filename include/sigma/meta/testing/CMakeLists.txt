CMAKE_MINIMUM_REQUIRED (VERSION 3.0)
PROJECT(sigma_api_meta)

SET(CMAKE_CXX_FLAGS "-std=c++1z -fconcepts")

INCLUDE_DIRECTORIES("${PROJECT_SOURCE_DIR}/../")

FILE(GLOB source_files "src/*.cpp")

SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/bin")

ADD_EXECUTABLE(sigma_api_meta ${source_files})
