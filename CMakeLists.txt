CMAKE_MINIMUM_REQUIRED(VERSION 2.8.2)

PROJECT(piet)

FIND_PACKAGE(Qt4 REQUIRED)

IF(QT4_FOUND)
  MESSAGE(STATUS "Qt found!")
ENDIF()

ADD_SUBDIRECTORY(src)

# generating documentation with Doxygen
find_package(Doxygen)
if(DOXYGEN_FOUND)
  set(DOXYGEN_DIR ${CMAKE_CURRENT_SOURCE_DIR}/doc)
  set(DOXYGEN_CONFIG ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)
  configure_file(${DOXYGEN_DIR}/Doxyfile.in ${DOXYGEN_CONFIG} @ONLY)
  add_custom_target(doc
    ${DOXYGEN_EXECUTABLE} ${DOXYGEN_CONFIG}
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    COMMENT "Generating API documentation with Doxygen" VERBATIM)
  execute_process(COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_CONFIG}
    OUTPUT_FILE "${DOXYGEN_DIR}/doxygen.exec.log"
    ERROR_FILE "${DOXYGEN_DIR}/doxygen.error.log")
else(DOXYGEN_FOUND)
  message(STATUS "Documentation could not be generated")
endif(DOXYGEN_FOUND)

