cmake_minimum_required(VERSION 4.0)
project(BPP_FOR_DR_ELRAMLY)

set(CMAKE_CXX_STANDARD 14)

include_directories(main/CS213-2025-2026-Assignemnt1-LibraryAndExample/main)

add_executable(BPP_FOR_DR_ELRAMLY
        main/CS213-2025-2026-Assignemnt1-LibraryAndExample/main/Image_Class.h
        main/CS213-2025-2026-Assignemnt1-LibraryAndExample/main/ImageProcessingDemo.cpp
        main/CS213-2025-2026-Assignemnt1-LibraryAndExample/main/main.cpp
        main/CS213-2025-2026-Assignemnt1-LibraryAndExample/main/stb_image.h
        main/CS213-2025-2026-Assignemnt1-LibraryAndExample/main/stb_image_write.h)
