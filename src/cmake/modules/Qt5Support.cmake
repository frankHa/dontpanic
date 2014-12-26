MACRO(QT5_ADD_DBUS_INTERFACE_WITH_INCLUDES _sources _interface _basename)    
  get_filename_component(_infile ${_interface} ABSOLUTE)
    set(_header "${CMAKE_CURRENT_BINARY_DIR}/${_basename}.h")
    set(_impl   "${CMAKE_CURRENT_BINARY_DIR}/${_basename}.cpp")
    set(_moc    "${CMAKE_CURRENT_BINARY_DIR}/${_basename}.moc")

    get_source_file_property(_nonamespace ${_interface} NO_NAMESPACE)
    if(_nonamespace)
        set(_params -N -m)
    else()
        set(_params -m)
    endif()

    get_source_file_property(_classname ${_interface} CLASSNAME)
    if(_classname)
        set(_params ${_params} -c ${_classname})
    endif()

    get_source_file_property(_include ${_interface} INCLUDE)
    if(_include)
        set(_params ${_params} -i ${_include})
    endif()

    SET(_includes)
    FOREACH(_include ${ARGN})
      SET(_includes ${_includes} -i ${_include})
    ENDFOREACH(_include)
    
    add_custom_command(OUTPUT "${_impl}" "${_header}"
        COMMAND ${Qt5DBus_QDBUSXML2CPP_EXECUTABLE} ${_params} -p ${_basename} ${_infile} ${_includes}
        DEPENDS ${_infile} VERBATIM)

    set_source_files_properties("${_impl}" PROPERTIES SKIP_AUTOMOC TRUE)

    qt5_generate_moc("${_header}" "${_moc}")

    list(APPEND ${_sources} "${_impl}" "${_header}" "${_moc}")
    macro_add_file_dependencies("${_impl}" "${_moc}")
    set(${_sources} ${${_sources}} PARENT_SCOPE)

    
    
ENDMACRO(QT5_ADD_DBUS_INTERFACE_WITH_INCLUDES)

# macro(create_test test_name)
#   SET(_srcs ${ARGN})
#   qt4_automoc(${_srcs})
#   add_executable(${test_name} ${_srcs})
#   link(${test_name})
#   install(TARGETS ${test_name} RUNTIME DESTINATION bin)
#   add_test(${test_name} ${test_name})
# endmacro(create_test)