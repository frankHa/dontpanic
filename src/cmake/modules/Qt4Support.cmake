MACRO(QT4_ADD_DBUS_INTERFACE_WITH_INCLUDES _sources _interface _basename)
    GET_FILENAME_COMPONENT(_infile ${_interface} ABSOLUTE)
    SET(_header ${CMAKE_CURRENT_BINARY_DIR}/${_basename}.h)
    SET(_impl   ${CMAKE_CURRENT_BINARY_DIR}/${_basename}.cpp)
    SET(_moc    ${CMAKE_CURRENT_BINARY_DIR}/${_basename}.moc)
    SET(_includes)
    FOREACH(_include ${ARGN})
      SET(_includes ${_includes} -i ${_include})
    ENDFOREACH(_include)
  
    ADD_CUSTOM_COMMAND(OUTPUT ${_impl} ${_header}
        COMMAND ${QT_DBUSXML2CPP_EXECUTABLE} -m -p ${_basename} ${_infile} ${_includes}
        DEPENDS ${_infile})
  
    SET_SOURCE_FILES_PROPERTIES(${_impl} PROPERTIES SKIP_AUTOMOC TRUE)
    
    QT4_GENERATE_MOC(${_header} ${_moc})
  
    SET(${_sources} ${${_sources}} ${_impl} ${_header} ${_moc})
    MACRO_ADD_FILE_DEPENDENCIES(${_impl} ${_moc})
  
ENDMACRO(QT4_ADD_DBUS_INTERFACE_WITH_INCLUDES)

macro(create_test test_name)
  SET(_srcs ${ARGN})
  qt4_automoc(${_srcs})
  add_executable(${test_name} ${_srcs})
  link(${test_name})
  install(TARGETS ${test_name} RUNTIME DESTINATION bin)
  add_test(${test_name} ${test_name})
endmacro(create_test)