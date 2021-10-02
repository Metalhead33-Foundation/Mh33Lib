target_sources(${PROJECT_NAME} PRIVATE
PhysFSIO.cpp
MhProxyReadStream.cpp
MhProxyWriteStream.cpp
MhStdout.cpp
MhStdin.cpp
MhStderr.cpp
MhSocket.cpp
MhFile.cpp
MhZstdDecompressor.cpp
MhZstdCompressor.cpp
MhSnappyCompressor.cpp
MhSnappyDecompressor.cpp
MhBufferWrapper.cpp
MhFixedBufferWrapper.cpp
MhTemporaryFile.cpp
)
