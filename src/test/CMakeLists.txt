include_directories(${CMAKE_CURRENT_BINARY_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../dontpanic/core)

macro(link test)
target_link_libraries(${test} libdontpanic_core dontpanic_lib ${QT_QTTEST_LIBRARY} ${QT_QTCORE_LIBRARY})
endmacro(link)

########################################
# defining our test cases:
########################################
create_test(reportgeneratortest reportgeneratortest.cpp dummypersistence.cpp)
