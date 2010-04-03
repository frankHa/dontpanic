include_directories(${CMAKE_CURRENT_BINARY_DIR})
#include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../libs/remote_proxy/)
#include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../libs/remote_proxy/internal)

macro(link test)
target_link_libraries(${test} libdontpanic_core ${QT_QTTEST_LIBRARY} ${QT_QTCORE_LIBRARY})
endmacro(link)

########################################
# defining our test cases:
########################################
create_test(reportgeneratortest reportgeneratortest.cpp)
