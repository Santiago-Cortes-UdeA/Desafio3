# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Release")
  file(REMOVE_RECURSE
  "CMakeFiles\\Intento3_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\Intento3_autogen.dir\\ParseCache.txt"
  "Intento3_autogen"
  )
endif()
