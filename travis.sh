#!/bin/bash
if [ $PACK != 'none' ]; then
    echo 'Test skipped(packaging mode)'
    cd build/pack
    bash pack.sh $PACK $OS $DIST $TRAVIS_BRANCH $OUT_REPO $PROD $P_URI
else
    echo 'Preparing tests'
    mkdir ./test_build && cd ./test_build && cmake .. -DCMAKE_BUILD_TYPE=RelWithDebugInfo
    make
    make test
fi
