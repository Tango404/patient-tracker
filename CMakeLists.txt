cmake_minimum_required(VERSION 3.22)
project(a1ms3)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(
        main.c
        data/appointmentData.txt
        clinic.c
        clinic.h
        core.c
        core.h
        data/patientData.txt)
