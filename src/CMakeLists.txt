set(SQLITE_VEC_DIR ${CMAKE_SOURCE_DIR}/extern/sqlite-vec)

# Generate sqlite-vec.h from its template before it's needed
# (exact substitution command TBD once we see the Makefile rule)
file(READ ${SQLITE_VEC_DIR}/VERSION SQLITE_VEC_VERSION)
string(STRIP "${SQLITE_VEC_VERSION}" SQLITE_VEC_VERSION)
configure_file(
    ${SQLITE_VEC_DIR}/sqlite-vec.h.tmpl
    ${CMAKE_BINARY_DIR}/generated/sqlite-vec.h
    @ONLY
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
