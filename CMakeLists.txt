cmake_minimum_required(VERSION 3.13.0)
project(MhLib VERSION 0.1)
# additional cmake modules

include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

find_package(PkgConfig)
find_package(GIF REQUIRED)

pkg_check_modules(SndFile REQUIRED IMPORTED_TARGET sndfile)
pkg_check_modules(OpenMPT REQUIRED IMPORTED_TARGET libopenmpt)
pkg_check_modules(Samplerate REQUIRED IMPORTED_TARGET samplerate)
pkg_check_modules(TurboJPEG REQUIRED IMPORTED_TARGET libturbojpeg)
pkg_check_modules(WebP REQUIRED IMPORTED_TARGET libwebp)
pkg_check_modules(WebPDecoder REQUIRED IMPORTED_TARGET libwebpdecoder)
pkg_check_modules(WebPDemuxer REQUIRED IMPORTED_TARGET libwebpdemux)
pkg_check_modules(PNG REQUIRED IMPORTED_TARGET libpng)
pkg_check_modules(ZSTD REQUIRED IMPORTED_TARGET libzstd)
pkg_check_modules(PhysFS REQUIRED IMPORTED_TARGET physfs)

set(CMAKE_DEBUG_POSTFIX d)

add_library(${PROJECT_NAME})
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 20)

target_compile_options(${PROJECT_NAME} PRIVATE -Wall -fpermissive)

add_subdirectory(src)

target_include_directories(${PROJECT_NAME}
        PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include>
        $<INSTALL_INTERFACE:include/${PROJECT_NAME}>
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src)

target_link_libraries(${PROJECT_NAME}
        ${GIF_LIBRARIES}
        ${PNG_LIBRARIES}
        PkgConfig::SndFile
        PkgConfig::OpenMPT
        PkgConfig::Samplerate
        PkgConfig::TurboJPEG
        PkgConfig::WebP
        PkgConfig::WebPDecoder
        PkgConfig::WebPDemuxer
        PkgConfig::PNG
        PkgConfig::ZSTD
        PkgConfig::PhysFS)

install(TARGETS ${PROJECT_NAME} EXPORT ${PROJECT_NAME}Targets
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})

install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

install(EXPORT ${PROJECT_NAME}Targets DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}
        NAMESPACE MhLib::)

export(TARGETS ${PROJECT_NAME} NAMESPACE MhLib:: FILE ${PROJECT_NAME}Targets.cmake)
export(PACKAGE ${PROJECT_NAME})

add_library(MhLib::MhLib ALIAS ${PROJECT_NAME})
