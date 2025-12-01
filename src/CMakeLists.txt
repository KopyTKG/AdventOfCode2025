add_library(logger INTERFACE)

target_include_directories(logger INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}")

add_custom_target(hash_all ALL COMMENT "Hashing all binaries...")

file(GLOB day_dirs RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "day*")

foreach(day_dir ${day_dirs})
    if(IS_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/${day_dir}")
        message(STATUS "Configuring Day: ${day_dir}")
        set(DAY_BIN "${day_dir}")           
        set(DAY_TEST "${day_dir}_test")     

        if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/${day_dir}/main.cpp")
            add_executable(${DAY_BIN} "${day_dir}/main.cpp")

	    target_link_libraries(${DAY_BIN} PRIVATE logger)
            
            target_include_directories(${DAY_BIN} PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/${day_dir}")
            set_target_properties(${DAY_BIN} PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
            
            add_custom_command(
                OUTPUT "${CMAKE_BINARY_DIR}/bin/${DAY_BIN}.sha256"
                COMMAND ${CMAKE_COMMAND} -E sha256sum $<TARGET_FILE:${DAY_BIN}> > "${CMAKE_BINARY_DIR}/bin/${DAY_BIN}.sha256"
                DEPENDS ${DAY_BIN}
                VERBATIM
            )
            add_custom_target(hash_${DAY_BIN} DEPENDS "${CMAKE_BINARY_DIR}/bin/${DAY_BIN}.sha256")
            add_dependencies(hash_all hash_${DAY_BIN})
        endif()

	if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/${day_dir}/test.cpp")
    		add_executable(${DAY_TEST} "${day_dir}/test.cpp")
    
    		target_link_libraries(${DAY_TEST} PRIVATE Catch2::Catch2WithMain logger)
    		target_include_directories(${DAY_TEST} PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/${day_dir}")
    
    		set_target_properties(${DAY_TEST} PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

    		target_compile_definitions(${DAY_TEST} PRIVATE TEST_DATA_DIR="${CMAKE_CURRENT_SOURCE_DIR}/${day_dir}/")

    		add_test(NAME ${DAY_TEST} COMMAND ${DAY_TEST})
	endif()

        file(GLOB input_files "${CMAKE_CURRENT_SOURCE_DIR}/${day_dir}/*.txt")
        foreach(input_file ${input_files})
            file(COPY ${input_file} DESTINATION "${CMAKE_BINARY_DIR}/bin")
        endforeach()

    endif()
endforeach()
