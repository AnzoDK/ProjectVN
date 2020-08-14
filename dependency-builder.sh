#!/bin/bash
git --version &> /dev/null
if [ $? -eq 0 ]
then
    echo "Git installed - YES"
else
    echo "Git Installed - NO"
    echo "Git is needed for this script to work!"
    exit 1
fi

git clone https://github.com/AnzoDK/RPEngine.git
if [ $? -ne 0 ]
then
    echo "Git failed to get RPEngine - Fatal"
    exit 1
fi

cd RPEngine
./dependency-builder.sh
make lib
mkdir -p ../includes/RPEngine
mkdir -p ../includes/RPAudio
cp includes/RPAudio/librpaudio.so ../includes/RPAudio/
cp rpengine.so ../includes/RPEngine/librpengine.so
cp includes/*.h ../includes/RPEngine/
cp includes/RPAudio/*.h ../includes/RPAudio/
cd ..
rm -r -f RPEngine
echo "Completed"
