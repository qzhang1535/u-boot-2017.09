set(CMAKE_EXE_LINKER_FLAGS "-T${CMAKE_CURRENT_SOURCE_DIR}/s3c2440.lds")

set(DEST_NAME "spl")
set(TARGET_NAME "${DEST_NAME}.elf")
set(BIN_NAME "${DEST_NAME}.bin")

ADD_EXECUTABLE(${TARGET_NAME} 
    start.S
    lowlevel_init.S
    entry.c
)

add_custom_command(TARGET ${TARGET_NAME} POST_BUILD
    COMMAND ${CMAKE_OBJCOPY} -O binary -S --pad-to 4096 ${TARGET_NAME} ${BIN_NAME} 
    COMMAND cp ${BIN_NAME} ../../${BIN_NAME} 
)

TARGET_LINK_LIBRARIES(${TARGET_NAME} user)
TARGET_LINK_LIBRARIES(${TARGET_NAME} drivers)
