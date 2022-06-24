#! /bin/sh
wget https://www.libsdl.org/release/SDL2-2.0.22.tar.gz
gunzip SDL2-2.0.22.tar.gz
tar xf SDL2-2.0.22.tar
rm SDL2-2.0.22.*

cd SDL2-2.0.22

if [ $(uname) = Darwin ]; then
    CC=./build-scripts/clang-fat.sh ./configure
else
    ./configure
fi
make $@
