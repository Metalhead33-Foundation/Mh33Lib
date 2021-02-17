#!/bin/bash

pushd src || exit 1
../generate-cmake.pl '${PROJECT_NAME}'
popd || exit 1
