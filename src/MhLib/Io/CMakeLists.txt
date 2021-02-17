add_subdirectory(private)
target_sources(${PROJECT_NAME} PRIVATE
PhysFSIO
MhStdout
MhStdin
MhStderr
MhSocket
MhFile
MhDecompressor
MhCompressor
MhBufferWrapper
)
