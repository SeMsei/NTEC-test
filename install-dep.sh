#!/bin/sh

BUILD_TYPE="Debug"
NPROC=1

rm -rf tmp

mkdir tmp
cd tmp

git clone --depth=1 https://github.com/oatpp/oatpp

cd oatpp
mkdir build
cd build

cmake -DCMAKE_BUILD_TYPE="Debug" -DOATPP_BUILD_TESTS=OFF ..
make install -j $NPROC

cd ../../

git clone --depth=1 https://github.com/oatpp/oatpp-swagger

cd oatpp-swagger
mkdir build
cd build

cmake -DCMAKE_BUILD_TYPE="Debug" -DOATPP_BUILD_TESTS=OFF ..
make install -j $NPROC

cd ../../

git clone --depth=1 https://github.com/oatpp/oatpp-sqlite

cd oatpp-sqlite
mkdir build
cd build

cmake -DCMAKE_BUILD_TYPE="Debug" -DOATPP_BUILD_TESTS=OFF -DOATPP_SQLITE_AMALGAMATION=ON ..
make install -j $NPROC

cd ../../

cd ../
rm -rf tmp
