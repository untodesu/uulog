function(add_example example_name)
    add_executable(${example_name} "${CMAKE_CURRENT_LIST_DIR}/${example_name}.cc")
    target_compile_features(${example_name} PRIVATE cxx_std_20)
    target_link_libraries(${example_name} PRIVATE uulog)
endfunction()

add_example(00_hello)
add_example(01_sinks)
add_example(02_heresy)
