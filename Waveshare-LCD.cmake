set(WAVESHARE "/home/roseba/Projects/SOFT/ARM/PICO/workspace/Waveshare_Pico_LCD/lib")
aux_source_directory(${WAVESHARE}/Config DIR_Config_SRC)
aux_source_directory(${WAVESHARE}/LCD DIR_LCD_SRC)
aux_source_directory(${WAVESHARE}/GUI DIR_GUI_SRC)
aux_source_directory(${WAVESHARE}/infrared DIR_INFRA_SRC)

   # Prefix all shared libraries with 'lib'.
    set(CMAKE_SHARED_LIBRARY_PREFIX "wavesharelib-")
    # Prefix all static libraries with 'lib'.
    set(CMAKE_STATIC_LIBRARY_PREFIX "wavesharelib-")

    include_directories(${WAVESHARE}/Config)
add_library(wslcd_config ${DIR_Config_SRC})
add_library(wslcd ${DIR_LCD_SRC})
add_library(wslcd_gui ${DIR_GUI_SRC})
add_library(wslcd_infrared ${DIR_INFRA_SRC})

target_link_libraries(wslcd_config PUBLIC pico_stdlib hardware_spi hardware_i2c hardware_pwm hardware_adc)
target_link_libraries(wslcd PUBLIC pico_stdlib hardware_spi hardware_i2c hardware_pwm hardware_adc)
target_link_libraries(wslcd_gui PUBLIC pico_stdlib hardware_spi hardware_i2c hardware_pwm hardware_adc)
target_link_libraries(wslcd_infrared PUBLIC pico_stdlib hardware_spi hardware_i2c hardware_pwm hardware_adc)

set( WAVESHARE_CONFIG_SRC ${WAVESHARE}/Config )
