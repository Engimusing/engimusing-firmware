#!/bin/bash

cd cores/cortex-m0plus/
make clean
cd ../../devel_c_cpp/test_timers/
make clean
cd ../test_gpios/
make clean
cd ../test_analog/
make clean
cd ../../
