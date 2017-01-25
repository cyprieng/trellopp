cmake_minimum_required(VERSION 3.0)
project(trello)

###############################################################################
## Qt #########################################################################
###############################################################################
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)

find_package(Qt5Widgets)
find_package(Qt5Network)
find_package(Qt5WebEngineWidgets)

###############################################################################
## Add sources   ##############################################################
###############################################################################
file(GLOB_RECURSE sources      src/*.cpp src/*.h)
add_executable(trello ${sources})

###############################################################################
## target definitions #########################################################
###############################################################################
target_compile_options(trello PUBLIC -std=c++1y -Wall -Wfloat-conversion)

# This allows to include files relative to the root of the src directory with a <> pair
target_include_directories(trello PUBLIC src/main)


###############################################################################
## dependencies ###############################################################
###############################################################################
target_link_libraries(trello Qt5::Widgets Qt5::Network Qt5::WebEngineWidgets)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/external/liboauthcpp/build/)
target_link_libraries(trello oauthcpp)
include_directories(trello
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/external/liboauthcpp/include/
)

###############################################################################
## packaging ##################################################################
###############################################################################
# All install commands get the same destination
install(TARGETS trello DESTINATION trello_destination)

set(CPACK_PACKAGE_NAME "trello")
set(CPACK_PACKAGE_VERSION "0.0.1")
set(CPACK_MONOLITHIC_INSTALL 1)

include(CPack)
