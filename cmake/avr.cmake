set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR avr)

set(CMAKE_C_COMPILER avr-gcc)
set(CMAKE_CXX_COMPILER avr-g++)

set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)

set(MCU atmega32u4 CACHE STRING "AVR MCU")

set(AVR_INCLUDE_DIR "/usr/lib/avr/include")
set(AVR_LIB_DIR     "/usr/lib/avr/lib/avr5")

set(CMAKE_C_FLAGS_INIT
    "-mmcu=${MCU} -isystem ${AVR_INCLUDE_DIR}"
)

set(CMAKE_CXX_FLAGS_INIT
    "-mmcu=${MCU} -isystem ${AVR_INCLUDE_DIR}"
)

set(CMAKE_EXE_LINKER_FLAGS_INIT
    "-mmcu=${MCU} -B${AVR_LIB_DIR}"
)
