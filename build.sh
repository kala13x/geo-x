#!/bin/bash
# Simple build script to compile project

cd ${PWD##}/utils
make clean
make

cd ../gxx
make clean
make

echo "საჭიროა სუპერ მომხმარებლის პრივილეგიები"
sudo make install

cd ../libx
sudo make install

cd ..