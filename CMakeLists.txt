cmake_minimum_required(VERSION 3.10)

project(hdbextractor VERSION 2.2.0
    DESCRIPTION "C++ api to access historical database"
    LANGUAGES CXX)

# to have CMAKE_INSTALL_INCLUDEDIR CMAKE_INSTALL_LIBDIR
include(GNUInstallDirs)

# Modify CMAKE_INSTALL_INCLUDEDIR to include the library name
set(CMAKE_INSTALL_INCLUDEDIR "include/${PROJECT_NAME}")

file(GLOB_RECURSE SOURCES src/*.cpp)
file(GLOB_RECURSE HEADERS src/*.h)

find_package(elettra.eu.libsqldb 2.2 REQUIRED)

add_library(${PROJECT_NAME} SHARED  ${SOURCES} ${HEADERS})
target_link_libraries(${PROJECT_NAME} PUBLIC elettra.eu.libsqldb)

# in order to have lib and symlinks
set_target_properties(${PROJECT_NAME} PROPERTIES VERSION ${PROJECT_VERSION})
set_target_properties(${PROJECT_NAME} PROPERTIES SOVERSION ${PROJECT_VERSION_MAJOR})
set_target_properties(${PROJECT_NAME} PROPERTIES PUBLIC_HEADER "${HEADERS}" )

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)

target_include_directories(${PROJECT_NAME} PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src/hdbpp>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src/utils>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src/hdb>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}> )

target_compile_definitions(${PROJECT_NAME} PRIVATE
    CU_VERSION=${PROJECT_VERSION}
)

install(TARGETS ${PROJECT_NAME} EXPORT ${PROJECT_NAME}Targets
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
export(TARGETS ${PROJECT_NAME} FILE ${PROJECT_NAME}Targets.cmake)

# install pkgconfig file
configure_file(${PROJECT_NAME}.pc.cmake.in ${PROJECT_NAME}.pc @ONLY)
install(
    FILES ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}.pc
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/pkgconfig
)

## export(PACKAGE ${PROJECT_NAME})
# https://cmake.org/cmake/help/latest/command/export.html#exporting-packages
# "for packaging and for system wide installations, it is not desirable to
# write the user package registry."
#
install(EXPORT ${PROJECT_NAME}Targets
    FILE ${PROJECT_NAME}Targets.cmake
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake)

# Generate Config.cmake file
include(CMakePackageConfigHelpers)
write_basic_package_version_file(
    "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake"
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY SameMajorVersion
)

configure_package_config_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/Config.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
    INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake
)

install(
    FILES
        "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
        "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake"
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake
)
