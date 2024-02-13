
cmake_minimum_required(VERSION 3.23)

set(PRJ_NAME "PAH_Inventory")
project(${PRJ_NAME})

get_filename_component(THIS_DIR ./ ABSOLUTE)
set(OUT_DIR "${THIS_DIR}/bin/$<CONFIG>")

add_executable(${PRJ_NAME})
target_compile_features(${PRJ_NAME} PUBLIC cxx_std_20)
set(CMAKE_CXX_STANDARD 20)

set_target_properties(${PRJ_NAME} PROPERTIES
	RUNTIME_OUTPUT_DIRECTORY ${OUT_DIR}
)

target_include_directories(${PRJ_NAME} PUBLIC "${THIS_DIR}/Source")
add_subdirectory("Source")