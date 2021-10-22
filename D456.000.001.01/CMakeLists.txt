CMAKE_MINIMUM_REQUIRED (VERSION 2.8)

SET (BUILD_APP "$ENV{APP}")
SET (BUILD_FROM_SRC  "0")
SET (TOPDIR ${CMAKE_CURRENT_LIST_DIR})
SET (ENV{TOPDIR} ${TOPDIR})

EXECUTE_PROCESS(
    COMMAND rm -rf ${TOPDIR}/config/*.c ${TOPDIR}/config/*.h
)



##############################################################
# BUILD LIBRARY
IF ("1" STREQUAL "$ENV{MAKELIB}")
##############################################################
    SET (TARGET_BOARD $ENV{TARGET_BOARD})
    EXECUTE_PROCESS(
        COMMAND rm -rf ${TOPDIR}/config/*.c ${TOPDIR}/config/*.h
        COMMAND node.exe ${TOPDIR}/appoloconfig.js --config ${TOPDIR}/libconfig.js --outdir ${TOPDIR}/libappolo/${TARGET_BOARD}
        RESULT_VARIABLE CONFIG_RESULT
        OUTPUT_VARIABLE CONIFG_RELASE_FILE_NAME
        OUTPUT_STRIP_TRAILING_WHITESPACE
    )

    INCLUDE (${TOPDIR}/boards/${TARGET_BOARD}/board.cmake)

    PROJECT (appolo C ASM)
    ENABLE_LANGUAGE(CXGATE)


    SET (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -D${TARGET_BOARD}")
    SET (CMAKE_CXGATE_FLAGS "${CMAKE_CXGATE_FLAGS} -D${TARGET_BOARD}")

    ADD_SUBDIRECTORY(arch)
    ADD_SUBDIRECTORY(bms_rte)
    ADD_SUBDIRECTORY(dcm)
    ADD_SUBDIRECTORY(boards)
    ADD_SUBDIRECTORY(ucos)
    ADD_SUBDIRECTORY(com)
    ADD_SUBDIRECTORY(libs)
    ADD_SUBDIRECTORY(drivers)
    ADD_SUBDIRECTORY(diagnostic)


    ADD_LIBRARY(appolo.${TARGET_BOARD} ${SOURCE_FILES})
    INCLUDE_DIRECTORIES (include libappolo/${TARGET_BOARD} ${INCUDE_DIRS})
    ADD_CUSTOM_COMMAND(
        TARGET appolo.${TARGET_BOARD}
        COMMAND cp -v appolo.${TARGET_BOARD}.lib ${TOPDIR}/libappolo/${TARGET_BOARD}/appolo.lib
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    )


##############################################################
# BUILD LIBRARY
ELSE ("1" STREQUAL "$ENV{MAKELIB}")
##############################################################


    IF (NOT BUILD_APP)
        MESSAGE(WARN "You do not define APP evnironment, use \"bcu\" for default")
        SET (BUILD_APP "bcu")
    ENDIF (NOT BUILD_APP)

    SET (CALIBRATE_FILE "$ENV{CALIBRATE_FILE}")
    IF (NOT CALIBRATE_FILE)
        MESSAGE(WARN "You do not define CALIBRATE_FILE evnironment, use \"${CMAKE_CURRENT_LIST_DIR}/calibrate.json\" for default")
        SET (CALIBRATE_FILE "${TOPDIR}/applications/${BUILD_APP}/calibrate.json")
    ENDIF (NOT CALIBRATE_FILE)

    EXECUTE_PROCESS(
        COMMAND rm -rf ${TOPDIR}/config/*.c ${TOPDIR}/config/*.h
        COMMAND node.exe ${TOPDIR}/appoloconfig.js --calibrate=${CALIBRATE_FILE} --config ${TOPDIR}/applications/${BUILD_APP}/config.js --outdir ${TOPDIR}/config
        RESULT_VARIABLE CONFIG_RESULT
        OUTPUT_VARIABLE CONFIG_OUTPUT
        OUTPUT_STRIP_TRAILING_WHITESPACE
    )

    IF(NOT "${CONFIG_RESULT}" STREQUAL "0")
    MESSAGE(FATAL_ERROR "Config error")
    ENDIF ()

    list(GET CONFIG_OUTPUT 0 RELASE_FILE_NAME)
    list(GET CONFIG_OUTPUT 1 TARGET_BOARD)
    list(GET CONFIG_OUTPUT 2 BCU_TYPE)

    INCLUDE (${TOPDIR}/boards/${TARGET_BOARD}/board.cmake)
    INCLUDE (${TOPDIR}/toolchain/Toolchain-pclint.cmake)

    PROJECT (appolo C ASM)
    ENABLE_LANGUAGE(CXGATE)

    SET (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -D${TARGET_BOARD} -D${BCU_TYPE}")
    SET (CMAKE_CXGATE_FLAGS "${CMAKE_CXGATE_FLAGS} -D${BCU_TYPE}")
    SET (CMAKE_PC_LINT_FLAGS ${TARGET_LINT_FLAGS} "-D${BCU_TYPE}")
	MESSAGE("" ${CMAKE_PC_LINT_FLAGS})

    INCLUDE (${TOPDIR}/applications/${BUILD_APP}/app.cmake)

##############################################################
# END
ENDIF ("1" STREQUAL "$ENV{MAKELIB}")
##############################################################
