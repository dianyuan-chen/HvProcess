#
# Generic Tool chain support.
#
IF(__HC12_CHC12_GENERIC_COMPILER)
  RETURN()
ENDIF(__HC12_CHC12_GENERIC_COMPILER)
SET(__HC12_CHC12_GENERIC_COMPILER 1)


MESSAGE ("Loaded: Generic-chc12-hc12.cmake")

#
# Cross compiler generic support for Freescale (nee Metrowerks) HC12 (S12)
#
# Special variables introduced by this module, these can be overridden:
#
# HC12_CORE                   : Processor core type, one of 'HC12', 'HCS12' or 'HCS12X' (case sensitive!)
# HC12_MEMORY_MODEL           : Memory model, one of 'Small', 'Large' or 'Banked' (case sensitive!)
#
# Internally set variables (based on user specified values above):
#
# HC12_CORE_LETTER            : Automatically set based on HC12_CORE.
# HC12_MEMORY_MODEL_LETTER    : Automatically set based on HC12_MEMORY_MODEL.
# HC12_START12                : Startup object file (start12*.o) based on core and memory model.
# HC12_RTL_LIBS               : Run-time libraries based on core and memory model.
#

#
# Allow user to easily override the variables from a file rather than the CMake command line.
#
INCLUDE ("Freescale-HC12-opt.cmake" OPTIONAL RESULT_VARIABLE _INCLUDED_FREESCALE_HC12_OPT_FILE)
IF (NOT _INCLUDED_FREESCALE_HC12_OPT_FILE)
    INCLUDE ("${CMAKE_BINARY_DIR}/Freescale-HC12-opt.cmake" OPTIONAL RESULT_VARIABLE _INCLUDED_FREESCALE_HC12_OPT_FILE)
ENDIF (NOT _INCLUDED_FREESCALE_HC12_OPT_FILE)

#
# Core type (default is 'HC12'), override this on the CMake command line, e.g. "-DHC12_CORE=HCS12X".
#
IF (NOT DEFINED HC12_CORE)
    SET (HC12_CORE "HC12" CACHE STRING "HC12 core - one of 'HC12', 'HCS12' or 'HCS12X' (case sensitive!)")
ENDIF (NOT DEFINED HC12_CORE)

IF (${HC12_CORE} STREQUAL "HC12")
    SET (HC12_CORE_LETTER "")
ELSEIF (${HC12_CORE} STREQUAL "HCS12")
    SET (HC12_CORE_LETTER "")
ELSEIF (${HC12_CORE} STREQUAL "HCS12X")
    SET (HC12_CORE_LETTER     "x")
    SET (CMAKE_C_FLAGS_INIT    "${CMAKE_C_FLAGS_INIT} -CpuHCS12XE")
    SET (CMAKE_ASM_FLAGS  "${CMAKE_ASM_FLAGS} -CpuHCS12XE")
ELSE (${HC12_CORE} STREQUAL "HCS12X")
       MESSAGE (FATAL_ERROR "HC12_CORE should be set to one of 'HC12', 'HCS12' or 'HCS12X' (case sensitive!)")
ENDIF (${HC12_CORE} STREQUAL "HC12")

#
# Memory model (default is 'Small'), override this on the CMake command line, e.g "-DHC12_MEMORY_MODEL=Banked".
#
IF (NOT DEFINED HC12_MEMORY_MODEL)
    SET (HC12_MEMORY_MODEL "Small" CACHE STRING "HC12 memory model - one of 'Small', 'Large' or 'Banked' (case sensitive!)")
ENDIF (NOT DEFINED HC12_MEMORY_MODEL)

IF (${HC12_MEMORY_MODEL} STREQUAL "Small")
    #
    # Small.
    #
    SET (HC12_MEMORY_MODEL_LETTER "s")
ELSEIF (${HC12_MEMORY_MODEL} STREQUAL "Large")
    #
    # Large.
    #
    SET (HC12_MEMORY_MODEL_LETTER "l")
ELSEIF (${HC12_MEMORY_MODEL} STREQUAL "Banked")
    #
    # Banked
    #
    SET (HC12_MEMORY_MODEL_LETTER "b")
ELSE (${HC12_MEMORY_MODEL} STREQUAL "Banked")
       MESSAGE (FATAL_ERROR "HC12_MEMORY_MODEL should be set to one of 'Small', 'Large' or 'Banked' (case sensitive!)")
ENDIF (${HC12_MEMORY_MODEL} STREQUAL "Small")

SET (CMAKE_C_FLAGS_INIT    "${CMAKE_C_FLAGS_INIT} -M${HC12_MEMORY_MODEL_LETTER}")
SET (CMAKE_ASM_FLAGS       "${CMAKE_ASM_FLAGS} -M${HC12_MEMORY_MODEL_LETTER}")

#
# Starup code and RTL.
#
# TODO: Add C++ support.
#
#SET (HC12_START12   "start12${HC12_CORE_LETTER}${HC12_MEMORY_MODEL_LETTER}.o" CACHE STRING "HC12 startup object")
SET (HC12_RTL_LIBS  "ansi${HC12_CORE_LETTER}${HC12_MEMORY_MODEL_LETTER}.lib ansi_xgi.lib" CACHE STRING "HC12 run-time libraries")

#SET (CMAKE_C_STANDARD_LIBRARIES_INIT  "-Add${HC12_RTL_LIBS} -Add${HC12_START12}")
#SET (CMAKE_C_STANDARD_LIBRARIES_INIT  "${HC12_RTL_LIBS}")
SET (CMAKE_C_FLAGS_INIT               "${CMAKE_C_FLAGS_INIT}          -EnvLIBPATH={Compiler}/lib/hc12c/include")
SET (CMAKE_CXGATE_FLAGS_INIT          "${CMAKE_CXGATE_FLAGS_INIT}     -EnvLIBRARYPATH={Compiler}/lib/hc12c/include;{Compiler}/lib/xgatec/include")
SET (CMAKE_EXE_LINKER_FLAGS_INIT      "${CMAKE_EXE_LINKER_FLAGS_INIT} -EnvOBJPATH={Compiler}/lib/hc12c/lib;{Compiler}/lib/xgatec/lib")

IF (DEFINED HC12_PRM)
    SET (CMAKE_EXE_LINKER_FLAGS_INIT  "${CMAKE_EXE_LINKER_FLAGS_INIT} ${HC12_PRM}")
ENDIF (DEFINED HC12_PRM)

IF (DEFINED HC12_CHIP)
    SET(HC12_CHIP_FILE "${HC12_PATH}/../lib/hc12c/src/${HC12_CHIP}.c")
    SET(HC12_INCLUDE_DIR "${HC12_PATH}/../lib/hc12c/include/")
ENDIF (DEFINED HC12_CHIP)



#
# Give the user some feedback, especially as they may not be aware these exist and have taken on defaults.
#
MESSAGE ("")
MESSAGE ("HC12 core .................: ${HC12_CORE}")
MESSAGE ("HC12 memory model .........: ${HC12_MEMORY_MODEL}")
MESSAGE ("HC12 start12*.o ...........: ${HC12_START12}")
MESSAGE ("HC12 RTL ..................: ${HC12_RTL_LIBS}")
MESSAGE ("HC12 PRM ..................: ${HC12_PRM}")
MESSAGE ("HC12 CHIP FILE.............: ${HC12_CHIP_FILE}")
MESSAGE ("")
