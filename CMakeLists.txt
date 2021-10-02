cmake_minimum_required(VERSION 3.13.0)
project(MhLib VERSION 0.1)
# additional cmake modules

include(GNUInstallDirs)
include(CMakePackageConfigHelpers)
list(APPEND WebP_FIND_COMPONENTS "demux")
LIST(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake_modules")

find_package(GIF REQUIRED)
find_package(PNG REQUIRED)
find_package(TurboJPEG REQUIRED)
find_package(LibSndFile REQUIRED)
find_package(LibSamplerate REQUIRED)
find_package(OpenMPT REQUIRED)
find_package(WebP REQUIRED libwebp demux)
find_package(ZSTD REQUIRED)
find_package(Snappy REQUIRED)
find_package(PhysFS REQUIRED)

set(CMAKE_DEBUG_POSTFIX d)

add_library(${PROJECT_NAME} SHARED)
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 20)
set_target_properties(${PROJECT_NAME} PROPERTIES VERSION ${PROJECT_VERSION})
set(CMAKE_BUILD_TYPE Debug)
#set(CMAKE_BUILD_TYPE Release)

target_compile_options(${PROJECT_NAME} PRIVATE -Wall -fpermissive -DMH_UTIL_EXPORT -DMH_GIMMICK_EXPORT -DMH_IO_EXPORT -DMH_IMAGE_EXPORT -DMH_AUDIO_EXPORT -DMH_ADV_AUDIO_EXPORT -DMH_GFX_EXPORT)

add_subdirectory(src)

target_include_directories(${PROJECT_NAME}
        PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include>
        $<INSTALL_INTERFACE:include/${PROJECT_NAME}>
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src)

if(CMAKE_DL_LIBS)
	target_link_libraries(${PROJECT_NAME} ${CMAKE_DL_LIBS})
endif()
target_link_libraries(${PROJECT_NAME}
        ${GIF_LIBRARIES}
		${PNG_LIBRARIES}
		${TurboJPEG_LIBRARIES}
        ${LIBSNDFILE_LIBRARIES}
        ${LIBSAMPLERATE_LIBRARIES}
        ${OPENMPT_LIBRARIES}
        ${WebP_LIBRARY}
        ${WebP_DEMUX_LIBRARY}
        ${ZSTD_LIBRARY}
        ${SNAPPY_LIBRARIES}
        ${PHYSFS_LIBRARY})

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
add_subdirectory(test)
