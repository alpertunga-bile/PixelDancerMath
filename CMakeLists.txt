cmake_minimum_required(VERSION 3.5.0)
project(pxd-math VERSION 0.1.0 LANGUAGES C CXX)

include(CTest)
enable_testing()

################################################################################
## GLOBAL DEFINITIONS

# from glm repository's CMakeLists.txt
if((CMAKE_CXX_COMPILER_ID MATCHES "GNU") OR (CMAKE_CXX_COMPILER_ID MATCHES "Clang"))
    add_compile_options(-mavx2)
elseif(CMAKE_CXX_COMPILER_ID MATCHES "Intel")
    add_compile_options(/QxAVX2)
elseif(CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
    add_compile_options(/arch:AVX2)
endif()

set(PXD_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(PXD_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/source)

################################################################################
## Project Definitions

set(PXD_HEADER_FILES
    ${PXD_INCLUDE_DIR}/ConstantValues.h
    ${PXD_INCLUDE_DIR}/LineRay.h
    ${PXD_INCLUDE_DIR}/Matrix3D.h
    ${PXD_INCLUDE_DIR}/Matrix4D.h
    ${PXD_INCLUDE_DIR}/Plane.h
    ${PXD_INCLUDE_DIR}/Point3D.h
    ${PXD_INCLUDE_DIR}/Quaternion.h
    ${PXD_INCLUDE_DIR}/SphericalHarmonics.h
    ${PXD_INCLUDE_DIR}/Transform.h
    ${PXD_INCLUDE_DIR}/Transform4D.h
    ${PXD_INCLUDE_DIR}/Vector2D.h
    ${PXD_INCLUDE_DIR}/Vector3D.h
    ${PXD_INCLUDE_DIR}/Vector4D.h
)

set(PXD_SOURCE_FILES
    ${PXD_SOURCE_DIR}/LineRay.cpp
    ${PXD_SOURCE_DIR}/Matrix3D.cpp
    ${PXD_SOURCE_DIR}/Matrix4D.cpp
    ${PXD_SOURCE_DIR}/Plane.cpp
    ${PXD_SOURCE_DIR}/Quaternion.cpp
    ${PXD_SOURCE_DIR}/SphericalHarmonics.cpp
    ${PXD_SOURCE_DIR}/Transform.cpp
    ${PXD_SOURCE_DIR}/Transform4D.cpp
    ${PXD_SOURCE_DIR}/Vector2D.cpp
    ${PXD_SOURCE_DIR}/Vector3D.cpp
    ${PXD_SOURCE_DIR}/Vector4D.cpp

    ${PXD_HEADER_FILES}
)

include_directories(
    ${PXD_INCLUDE_DIR}
)

add_library(${PROJECT_NAME} ${PXD_SOURCE_FILES})

add_executable(pxd-math-test ${PXD_SOURCE_FILES} main.cpp)

target_precompile_headers(
    ${PROJECT_NAME} PRIVATE
    <random>
    <immintrin.h>
    <cfloat>
    <cmath>
    <stdexcept>
    ${PXD_HEADER_FILES}
)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
