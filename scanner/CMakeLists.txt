MESSAGE(STATUS "===============================")
MESSAGE(STATUS "Scanner Configuration")
MESSAGE(STATUS "===============================")
project(scanner)

file(GLOB SOURCE CONFIGURE_DEPENDS "src/*")

add_library(${PROJECT_NAME} STATIC ${SOURCE} ${BACKWARD_ENABLE})
add_backward(${PROJECT_NAME})

target_link_libraries(${PROJECT_NAME} PUBLIC 
    
)
target_include_directories(${PROJECT_NAME} PUBLIC 
    src
)

# For testing
if(INSTALL_GTEST)
    MESSAGE(STATUS "GTEST ON")

    file(GLOB TEST_SOURCE CONFIGURE_DEPENDS "gtest/*")

    add_executable(${PROJECT_NAME}_test ${TEST_SOURCE})
    target_link_libraries(${PROJECT_NAME}_test PRIVATE 
        gtest_main
        ${PROJECT_NAME}
    )
endif()