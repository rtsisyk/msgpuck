mkdir ./test_build && cd ./test_build && cmake .. -DCMAKE_BUILD_TYPE=RelWithDebugInfo
make
make test
