#
# Mbed CE Hello World Project
#
cmake_minimum_required(VERSION 3.19)
cmake_policy(VERSION 3.19)

# Initialize Mbed OS build system. 
# Note: This block must be before the project() call.
set(MBED_APP_JSON_PATH mbed_app.json)
# set(CUSTOM_TARGETS_JSON_PATH custom_targets.json) # If you need a custom target, use this line to specify the custom_targets.json

include(mbed-os/tools/cmake/app.cmake) # Load Mbed CE toolchain file and basic build system

# If you need any custom upload method configuration for your target, do that here

add_subdirectory(mbed-os) # Load Mbed OS build targets.  Must be added before any other subdirectories

project(RT_ML) # TODO: change this to your project name

add_executable(RT_ML)

target_include_directories(RT_ML
    PRIVATE
        .
        tflm
        tflm/third_party/flatbuffers/include
        tflm/third_party/gemmlowp
        tflm/third_party/kissfft
        tflm/third_party/ruy
 #       tflm/third_party/cmsis_nn
 #       tflm/third_party/cmsis_nn/Include
)

target_compile_definitions(RT_ML
    PRIVATE
        CMSIS_NN
        TF_LITE_STATIC_MEMORY
        TF_LITE_MCU_DEBUG_LOG
)

target_sources(RT_ML
    PRIVATE
        main_TFLM.cpp
        variant.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/tflm/examples/hello_world/hello_world_test.cc
        ${CMAKE_CURRENT_SOURCE_DIR}/tflm/examples/hello_world/models/hello_world_float_model_data.cc
        ${CMAKE_CURRENT_SOURCE_DIR}/tflm/examples/hello_world/models/hello_world_int8_model_data.cc
)

target_link_libraries(RT_ML
    mbed-os
    mbed-storage-sd
    ${CMAKE_CURRENT_SOURCE_DIR}/libtensorflow-microlite-sfp.a
) # Can also link to mbed-baremetal here

mbed_set_post_build(RT_ML) # Must call this for each target to set up bin file creation, code upload, etc

mbed_finalize_build() # Make sure this is the last line of the top-level buildscript