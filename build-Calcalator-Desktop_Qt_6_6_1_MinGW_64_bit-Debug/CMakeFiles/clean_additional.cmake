# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\Calcalator_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\Calcalator_autogen.dir\\ParseCache.txt"
  "Calcalator_autogen"
  )
endif()
