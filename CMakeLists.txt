# указывайте последнюю доступную вам версию CMake
cmake_minimum_required(VERSION 3.15 FATAL_ERROR)

# название проекта
project(Ans)

# Добавление флагов компиляции для покрытия
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-arcs -ftest-coverage")

if(MSVC)
    add_compile_options(/utf-8)  # Для Visual Studio (MSVC)
else()
    add_compile_options(-finput-charset=UTF-8 -fexec-charset=UTF-8)  # Для GCC/Clang
endif()

# затем следует список инструкций для подключения проектов из подкаталогов

include(cmake/function.cmake)         # подхватываем функции, реализованные в файле function.cmake
                                      # для простоты мы объединили наборы команд для создания статической библиотеки
                                      # и для создания исполняемого проекта в отдельные функции
add_subdirectory(lib_pair)
add_subdirectory(lib_easy_example)    # подключаем дополнительный CMakeLists.txt из подкаталога с именем lib_easy_example
add_subdirectory(main)                # подключаем дополнительный CMakeLists.txt из подкаталога с именем main
add_subdirectory(lib_dmassive)
add_subdirectory(lib_stack)
add_subdirectory(lib_vector)
add_subdirectory(lib_queue)
add_subdirectory(lib_list)
add_subdirectory(lib_check_brackets)
add_subdirectory(lib_stack_list)
add_subdirectory(lib_polinom)
add_subdirectory(lib_matrix)
add_subdirectory(lib_dsu)
add_subdirectory(lib_merge_sorted_lists)
add_subdirectory(lib_itable)
add_subdirectory(lib_tbsttable)
add_subdirectory(lib_bin_search_tree)
add_subdirectory(lib_heap)
add_subdirectory(lib_avl)

option(BTEST "build test?" ON)        # указываем подключаем ли google-тесты (ON или YES) или нет (OFF или NO)

if(BTEST)                             # если тесты подключены
    add_subdirectory(gtest)           # подключаем дополнительный CMakeLists.txt из подкаталога с именем gtest
    add_subdirectory(tests)           # подключаем дополнительный CMakeLists.txt из подкаталога с именем test
endif()

# Добавление цели для генерации отчета о покрытии
add_custom_target(coverage
    COMMAND ${CMAKE_COMMAND} -E remove_directory coverage
    COMMAND mkdir -p coverage
    COMMAND lcov --capture --directory . --output-file coverage.info
    COMMAND genhtml coverage.info --output-directory coverage
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    DEPENDS my_tests
)
