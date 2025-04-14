# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "A:/Espressif/frameworks/esp-idf-v5.3.1/components/bootloader/subproject"
  "D:/Workshop/SNS/simple-nav-system/build/bootloader"
  "D:/Workshop/SNS/simple-nav-system/build/bootloader-prefix"
  "D:/Workshop/SNS/simple-nav-system/build/bootloader-prefix/tmp"
  "D:/Workshop/SNS/simple-nav-system/build/bootloader-prefix/src/bootloader-stamp"
  "D:/Workshop/SNS/simple-nav-system/build/bootloader-prefix/src"
  "D:/Workshop/SNS/simple-nav-system/build/bootloader-prefix/src/bootloader-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "D:/Workshop/SNS/simple-nav-system/build/bootloader-prefix/src/bootloader-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "D:/Workshop/SNS/simple-nav-system/build/bootloader-prefix/src/bootloader-stamp${cfgdir}") # cfgdir has leading slash
endif()
