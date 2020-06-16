@md build
@cd build
cmake -DPSE_TEST_MODE:BOOL=false -DCMAKE_TOOLCHAIN_FILE=../cmake_modules/linaro-arm.cmake -G "Unix Makefiles" ..
@cd ..
@pause
