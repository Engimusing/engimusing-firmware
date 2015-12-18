#!/bin/bash

cd cores/cortex-m0plus/
make -s
cd ../../devel_c_cpp/test_timers/
make -s
cd ../test_gpios/
make -s
cd ../test_analog/
make -s
cd ../../
