SET (HC12_MEMORY_MODEL   "Large")
SET (HC12_CORE           "HCS12X")
SET (HC12_CHIP           "MC9S12XEP100")
SET (TARGET_ARCH         "hcs12x")
SET (CMAKE_C_FLAGS_INIT  "-AddInclPreInclude.h -D__NO_FLOAT__ -D__MAP_FLASH__ -MapFlash")
SET (TARGET_LINT_FLAGS   "--header(PreInclude.h)" -e91 -mL -w3)
SET (CMAKE_CXGATE_FLAGS_INIT "-AddInclPreInclude.h")

INCLUDE (${TOPDIR}/arch/${TARGET_ARCH}/arch.cmake)
