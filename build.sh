#!/bin/bash
# Simple build script to compile project

cd ${PWD##}/utils
make clean
make

cd ../compiler
make clean
make

echo "დასაინსტალირებლად საჭიროა სუპერ მომხმარებლის პრივილეგიები"
sudo make install