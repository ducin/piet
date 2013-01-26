ADD_LIBRARY(PietCore
  pblockmanager.cpp
  pcalcstack.cpp
  pcodepointer.cpp
  pcolormanager.cpp
  pconsole.cpp
  pvirtualmachine.cpp)

TARGET_LINK_LIBRARIES(PietCore ${QT_LIBRARIES})
