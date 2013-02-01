ADD_LIBRARY(PietCore
  p_block_manager.cpp
  p_calc_stack.cpp
  p_code_pointer.cpp
  p_color_manager.cpp
  p_console.cpp
  p_virtual_machine.cpp
  p_console_virtual_machine.cpp)

TARGET_LINK_LIBRARIES(PietCore ${QT_LIBRARIES})
