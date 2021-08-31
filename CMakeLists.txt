cmake_minimum_required(VERSION 3.12)

include(pico_sdk_import.cmake)
project(play)

pico_sdk_init()

add_executable(play src/play.cpp src/PWM.cpp src/Notes.cpp src/PWMPlayer.cpp)
# Pull in our pico_stdlib which pulls in commonly used features
target_link_libraries(play pico_stdlib hardware_pwm hardware_gpio hardware_clocks)

# create map/bin/hex file etc.
pico_add_extra_outputs(play)



