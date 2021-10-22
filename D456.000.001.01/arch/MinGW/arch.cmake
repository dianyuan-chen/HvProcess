SET (CMAKE_C_COMPILER "gcc")
SET (TARGET_C_FLAGS "-m32 -std=gnu99 -m32 -D__near= -Dnear= -Dprintf=myprintf -Dsprintf=mysprintf  -includePreInclude.h")
SET (TARGET_EXE_LINKER_FLAGS "-m32 -lwinmm -lgdi32 -lrtm -lusbcan_dummy -L${CMAKE_CURRENT_LIST_DIR}")
SET (CMAKE_SHARED_LINKER_FLAGS  "-m32 -lwinmm -lgdi32 -lrtm -lusbcan_dummy -L${CMAKE_CURRENT_LIST_DIR}")
