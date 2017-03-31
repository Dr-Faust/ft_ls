cmake_minimum_required(VERSION 3.6)
project(ft_ls)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Werror -Wextra")

set(SOURCE_FILES
        src/file.c
        src/length.c
        src/main.c
        src/print.c
        src/print_items.c
        src/row_col.c
        src/sort.c
        src/print_files.c
        ) # sources

include_directories(
        includes
        libft_printf/includes
        libft_printf/libft/includes
) # headers

link_directories(
        libft_printf
) # libraries

add_executable(ft_ls ${SOURCE_FILES}) # compilation

target_link_libraries(ft_ls -lftprintf) # linkage