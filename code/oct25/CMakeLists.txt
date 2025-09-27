
add_executable(
        oct25
        test.cpp
)



add_executable(
        init
        init_list.cpp

)

add_executable(
        play
        play_function.cpp
)

add_executable(
        pointer
        leak.cpp
)

add_executable(
        task_scheduler
        task_scheduler.cpp

)

add_executable(
        dynamic
        dynamic_arr.h
        test_arr.cpp
)

add_executable(
        fib
        fib.cpp
)

enable_testing()
add_library(fib_lib STATIC fib.cpp)
add_executable(fib_test fib_test.cpp)
target_link_libraries(fib_test PRIVATE fib_lib)
add_test(NAME fib_test COMMAND fib_test)
