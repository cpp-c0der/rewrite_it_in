cmake_minimum_required(VERSION 3.25)

project(arduboy_game
    LANGUAGES C CXX
)

set (CMAKE_CXX_STANDARD 20)

include(FetchContent)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
if(LINUX)
    add_custom_target(copy_compile_commands ALL
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            ${CMAKE_BINARY_DIR}/compile_commands.json
            ${CMAKE_SOURCE_DIR}/compile_commands.json
        DEPENDS ${CMAKE_BINARY_DIR}/compile_commands.json
        COMMENT "Copying compile_commands.json to project directory"
    )
endif()

FetchContent_Declare(
    arduino_core
    GIT_REPOSITORY https://github.com/arduino/ArduinoCore-avr.git
    GIT_TAG        1.8.6
    GIT_SHALLOW    TRUE)

FetchContent_Declare(
    arduboy2
    GIT_REPOSITORY https://github.com/MLXXXp/Arduboy2.git
    GIT_TAG        master
    GIT_SHALLOW    TRUE
)

FetchContent_MakeAvailable(
    arduino_core
    arduboy2
)

set(ARDUINO_CORE
    ${arduino_core_SOURCE_DIR}/cores/arduino
)

set(ARDUINO_VARIANT
    ${arduino_core_SOURCE_DIR}/variants/leonardo
)

set(ARDUINO_EEPROM
    ${arduino_core_SOURCE_DIR}/libraries/EEPROM/src
)

set(ARDUBOY2_SRC
    ${arduboy2_SOURCE_DIR}/src
)

file(GLOB ARDUINO_CORE_SOURCES CONFIGURE_DEPENDS
    ${ARDUINO_CORE}/*.c
    ${ARDUINO_CORE}/*.cpp
)

add_library(arduino_core STATIC
    ${ARDUINO_CORE_SOURCES}
)

target_include_directories(arduino_core PUBLIC
    ${ARDUINO_CORE}
    ${ARDUINO_VARIANT}
    ${ARDUINO_EEPROM}
)

target_compile_definitions(arduino_core PUBLIC
    F_CPU=16000000L
    ARDUINO=10819
    ARDUINO_AVR_LEONARDO
    ARDUINO_ARCH_AVR

    USB_VID=0x2341
    USB_PID=0x0036
    USB_MANUFACTURER="Arduboy"
    USB_PRODUCT="Arduboy"
)

target_compile_options(arduino_core PRIVATE
    -Os
    -ffunction-sections
    -fdata-sections
    -fno-exceptions
    -fno-threadsafe-statics
)

file(GLOB ARDUBOY2_SOURCES CONFIGURE_DEPENDS
    ${ARDUBOY2_SRC}/*.cpp
)

add_library(arduboy2 STATIC
    ${ARDUBOY2_SOURCES}
)

target_include_directories(arduboy2 PUBLIC
    ${ARDUBOY2_SRC}
    ${ARDUINO_CORE}
    ${ARDUINO_VARIANT}
    ${ARDUINO_EEPROM}
)

target_compile_definitions(arduboy2 PUBLIC
    F_CPU=16000000L
    ARDUINO=10819
    ARDUINO_AVR_LEONARDO
    ARDUINO_ARCH_AVR

    USB_VID=0x2341
    USB_PID=0x0036
    USB_MANUFACTURER="Arduboy"
    USB_PRODUCT="Arduboy"
)

target_compile_options(arduboy2 PRIVATE
    -Os
    -ffunction-sections
    -fdata-sections
    -fno-exceptions
    -fno-threadsafe-statics
)

file(GLOB_RECURSE GAME_SOURCES CONFIGURE_DEPENDS
    ${CMAKE_SOURCE_DIR}/src/*.cpp
)

add_executable(${PROJECT_NAME}
    ${GAME_SOURCES}
    main.cpp
)

target_link_libraries(${PROJECT_NAME}
    PRIVATE
        arduboy2
        arduino_core
)

target_compile_definitions(${PROJECT_NAME} PRIVATE
    F_CPU=16000000L
    ARDUINO=10819
    ARDUINO_AVR_LEONARDO
    ARDUINO_ARCH_AVR
)

target_compile_options(${PROJECT_NAME} PRIVATE
    -Os
    -ffunction-sections
    -fdata-sections
    -fno-exceptions
    -fno-threadsafe-statics
)

target_link_options(${PROJECT_NAME} PRIVATE
    -Os
    -Wl,--gc-sections
    -Wl,--relax
)

target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include)

find_program(AVR_OBJCOPY avr-objcopy REQUIRED)
find_program(AVR_SIZE avr-size REQUIRED)

add_custom_command(
    TARGET ${PROJECT_NAME}
    POST_BUILD

    COMMAND ${AVR_OBJCOPY}
        -O ihex
        -R .eeprom
        $<TARGET_FILE:${PROJECT_NAME}>
        ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}.hex

    COMMAND ${AVR_SIZE}
        --mcu=atmega32u4
        $<TARGET_FILE:${PROJECT_NAME}>

    VERBATIM
)

find_program(AVRDUDE avrdude)

if(AVRDUDE)
    add_custom_target(flash
        COMMAND ${AVRDUDE}
            -p atmega32u4
            -c avr109
            -P /dev/ttyACM0
            -b 115200
            -D
            -U flash:w:${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}.hex:i

        DEPENDS ${PROJECT_NAME}

        USES_TERMINAL
    )
endif()
