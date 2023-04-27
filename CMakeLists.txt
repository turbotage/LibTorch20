cmake_minimum_required(VERSION 3.24)

project("TestTorch20" VERSION 0.1)



set(BUILD_SHARED_LIBS ON)

set(TEST_SOURCES
	"lib/tests/tests1.cpp"
)

add_library(TestTorch20 SHARED
	"src/main.ixx"
)


# Linking CUDA
if (${BUILD_CUDA})
	find_package(CUDAToolkit REQUIRED)
	message("CUDA Build chosen - Found CUDAToolkit = ${CUDAToolkit_FOUND}")
	if (${CUDAToolkit_FOUND})
		message("CUDA Toolkit Version = ${CUDAToolkit_VERSION}")
	endif()

	target_link_libraries(TestTorch20 PUBLIC CUDA::toolkit)
	target_link_libraries(TestTorch20 PUBLIC CUDA::nvrtc)
	target_link_libraries(TestTorch20 PUBLIC CUDA::cudart)
	target_link_libraries(TestTorch20 PUBLIC CUDA::nvToolsExt)

	message("Linked CUDA Libs")
endif()




if (${BUILD_CUDA})
	set(USE_CUDA ON)
	set(USE_CUDNN ON)
	set(CAFFE2_USE_CUDNN TRUE)
endif()
find_package(Torch REQUIRED)
target_link_libraries(TestTorch20 PUBLIC ${TORCH_LIBRARIES})



target_compile_features(TestTorch20 PUBLIC cxx_std_23)
set_property(TARGET TestTorch20 PROPERTY CXX_STANDARD 23)


if (MSVC)
  file(GLOB TORCH_DLLS "${TORCH_INSTALL_PREFIX}/lib/*.dll")
  add_custom_command(TARGET TestTorch20
                     POST_BUILD
                     COMMAND ${CMAKE_COMMAND} -E copy_if_different
                     ${TORCH_DLLS}
                     $<TARGET_FILE_DIR:TestTorch20>)
endif()

