#!/bin/bash
# Simple build script to compile project

# Build Utils
cd ${PWD##}/utils
make clean
make

# Build GXX
cd ../gxx
make clean
make

# Check we can run sudo command or not
CAN_I_RUN_SUDO=$(sudo -n uptime 2>&1 | grep "load" | wc -l)
if [ ${CAN_I_RUN_SUDO} -gt 0 ]
then
    echo "Installing..."
else
    echo "You must have a root access"
fi

# Install GXX
sudo make install

# Install Libx
cd ../libx
sudo make install

cd ..
echo "Done"