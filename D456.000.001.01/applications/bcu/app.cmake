SET(TARGET_ELF ${CMAKE_CURRENT_BINARY_DIR}/app_bcu.elf)

 # EXECUTE_PROCESS(
 #    COMMAND matlab -nosplash -nodesktop -nodisaply -minimize -wait -nouserjavapath -sd "${TOPDIR}/applications/bcu/matlablib" -r \"build_model\"
 #    RESULT_VARIABLE CONFIG_RESULT
 #    OUTPUT_VARIABLE CONIFG_RELASE_FILE_NAME
 #    OUTPUT_STRIP_TRAILING_WHITESPACE
 # )


ADD_SUBDIRECTORY (dcm)
ADD_SUBDIRECTORY (arch)
ADD_SUBDIRECTORY (boards)
ADD_SUBDIRECTORY (drivers)
ADD_SUBDIRECTORY (include)
ADD_SUBDIRECTORY (ucos)
ADD_SUBDIRECTORY (libs)
ADD_SUBDIRECTORY (com)
ADD_SUBDIRECTORY (diagnostic)
ADD_SUBDIRECTORY (bms_rte)
ADD_SUBDIRECTORY (applications/bcu)
ADD_SUBDIRECTORY (config)

IF ("1" STREQUAL "${BUILD_FROM_SRC}")
ELSE ("1" STREQUAL "${BUILD_FROM_SRC}")
SET (INCUDE_DIRS ${INCUDE_DIRS} ${TOPDIR}/libappolo/${TARGET_BOARD})
SET (CMAKE_EXE_LINKER_FLAGS
    " \
	${TARGET_EXE_LINKER_FLAGS} \
	${CMAKE_EXE_LINKER_FLAGS} \
    -Add(${CMAKE_CURRENT_BINARY_DIR}/overlay.lib) \
	-Add{${TOPDIR}/libappolo/${TARGET_BOARD}/appolo.lib} \
	")

ENDIF ("1" STREQUAL "${BUILD_FROM_SRC}")

INCLUDE_DIRECTORIES (${INCUDE_DIRS}, ${TOPDIR}/applications/bcu/overlay)
ADD_LIBRARY(overlay
    ${CMAKE_CURRENT_LIST_DIR}/overlay/CanIf.c
)

ADD_EXECUTABLE(app_bcu ${SOURCE_FILES})
INCLUDE_DIRECTORIES (${INCUDE_DIRS})
INCLUDE_DIRECTORIES (${INCUDE_DIRS}, ${TOPDIR}/bms_rte/matlab/Udan_SOC_ert_rtw)
INCLUDE_DIRECTORIES (${INCUDE_DIRS}, ${TOPDIR}/bms_rte/matlab/slprj/ert/_sharedutils)

ADD_PC_LINT(app_bcu ${SOURCE_FILES})

ADD_CUSTOM_COMMAND (
    TARGET app_bcu
    COMMAND cp -v app_bcu.S19 ${RELASE_FILE_NAME}.S19
    COMMAND cp -v app_bcu.S19 applications/bcu/app_bcu.S19
    COMMAND cp -v app_bcu.S19 applications/bcu/${RELASE_FILE_NAME}.S19
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
)

#ADD_PC_LINT(app_bcu ${THIS_DIR_SRC})
