# See the build system documentation in IDF programming guide
# for more information about component CMakeLists.txt files.
cmake_minimum_required(VERSION 3.24)
idf_component_register(
    SRCS  "app_main.c"# list the source files of this component
    INCLUDE_DIRS "."       # optional, add here public include directories
    PRIV_INCLUDE_DIRS   # optional, add here private include directories
    REQUIRES MyHAL MyDRIVERS MyFONTS         # optional, list the public requirements (component names)
    PRIV_REQUIRES       # optional, list the private requirements
)