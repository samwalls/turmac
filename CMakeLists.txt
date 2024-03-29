# This CMake file was forked from this source (CC): https://github.com/krux02/minimal_cmake_example

cmake_minimum_required(VERSION 3.0) # setting this is required
project(turmac) # this sets the project name

###############################################################################
## file globbing ##############################################################
###############################################################################

include_directories(${PROJECT_SOURCE_DIR}/include/)
file(GLOB_RECURSE includes     include/*.h include/*.hpp)
file(GLOB_RECURSE sources      src/*/*.cpp)
file(GLOB_RECURSE sources_test src/test/*.cpp)
#remove tests from source files
if (DEFINED ${sources_test})
    list(REMOVE_ITEM sources       ${sources_test})
endif()

###############################################################################
## target definitions #########################################################
###############################################################################

# create the turmac library
add_library(turmac ${sources} ${includes})
target_compile_options(turmac PUBLIC -std=c++1y -Wall -Wfloat-conversion)

# create the runtm executable and link the created turmac library
add_executable(runtm src/runtm/main.cpp)
target_compile_options(runtm PUBLIC -std=c++1y -Wall -Wfloat-conversion)
target_link_libraries(runtm turmac)

# This allows to include files relative to the root of the src directory with a <> pair
target_include_directories(runtm PUBLIC src/runtm)

# This copies all resource files in the build directory.
# We need this, because we want to work with paths relative to the executable.
#file(COPY ${data} DESTINATION resources)

###############################################################################
## dependencies ###############################################################
###############################################################################

# This defines the variables Boost_LIBRARIES that containts all library names
# that we need to link into the program.
#find_package(Boost 1.36.0 COMPONENTS filesystem system REQUIRED)

#target_link_libraries(example PUBLIC
#        ${Boost_LIBRARIES}
        # here you can add any library dependencies
#        )

###############################################################################
## testing ####################################################################
###############################################################################

# This is for our testing framework,
# we don't add REQUIRED because it's just for testing.
# People who might want to build the project to use it should not be required
# to install testing dependencies.
find_package(GTest)

if(GTEST_FOUND)
    add_executable(unit_tests ${sources_test} ${sources})

    # This define is added to prevent collision with the main.
    # It might be better solved by not adding the source with the main to the
    # testing target.
    target_compile_definitions(unit_tests PUBLIC UNIT_TESTS)

    # This allows us to use the executable as a link library, and inherit all
    # linker options and library dependencies from it, by simply adding it as dependency.
    set_target_properties(runtm PROPERTIES ENABLE_EXPORTS on)

    target_link_libraries(unit_tests PUBLIC
            ${GTEST_BOTH_LIBRARIES}
            runtm
            )

    target_include_directories(unit_tests PUBLIC
            ${GTEST_INCLUDE_DIRS} # doesn't do anything on linux
            )

endif()

###############################################################################
## packaging ##################################################################
###############################################################################

# All install commands get the same destination. this allows us to use paths
# relative to the executable.
install(TARGETS runtm DESTINATION example_destination)

# This is basically a repeat of the file copy instruction that copies the
# resources in the build directory, but here we tell cmake that we want it
# in the package.
#install(DIRECTORY resources DESTINATION example_destination)

# Now comes everything we need, to create a package
# there are a lot more variables you can set, and some
# you need to set for some package types, but we want to
# be minimal here.
set(CPACK_PACKAGE_NAME "runtm")
set(CPACK_PACKAGE_VERSION "1.0.0")

# We don't want to split our program up into several incomplete pieces.
set(CPACK_MONOLITHIC_INSTALL 1)

# This must be last
include(CPack)