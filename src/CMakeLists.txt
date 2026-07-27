set(SQLITE_VEC_DIR ${CMAKE_SOURCE_DIR}/extern/sqlite-vec)

# Read and parse the version string (e.g. "0.1.10-alpha.4")
file(READ ${SQLITE_VEC_DIR}/VERSION VERSION)
string(STRIP "${VERSION}" VERSION)
string(REPLACE "." ";" VERSION_PARTS "${VERSION}")
list(GET VERSION_PARTS 0 VERSION_MAJOR)
list(GET VERSION_PARTS 1 VERSION_MINOR)
list(GET VERSION_PARTS 2 VERSION_PATCH_RAW)
string(REPLACE "-" ";" PATCH_PARTS "${VERSION_PATCH_RAW}")
list(GET PATCH_PARTS 0 VERSION_PATCH)

# DATE/SOURCE are just informational build metadata - safe placeholders
string(TIMESTAMP DATE "%Y-%m-%dT%H:%M:%SZ" UTC)
set(SOURCE "unknown")

configure_file(
    ${SQLITE_VEC_DIR}/sqlite-vec.h.tmpl
    ${CMAKE_BINARY_DIR}/generated/sqlite-vec.h
)

add_executable(lecturehelp
    main.cpp
    ASR.cpp
    ${SQLITE_VEC_DIR}/sqlite-vec.c
)

target_include_directories(lecturehelp PRIVATE
    ${SQLITE_VEC_DIR}
    ${CMAKE_BINARY_DIR}/generated
)

target_link_libraries(lecturehelp PRIVATE
    whisper
    llama
)
