#!/bin/bash
#ProjectVN dependency resolver
git --version &> /dev/null
if [ $? -eq 0 ]
then
    echo "Git installed - YES"
else
    echo "Git Installed - NO"
    echo "Git is needed for this script to work!"
    exit 1
fi

if [ "$1" == "--use-dev" ]
then
    echo "Using dev branch"
    git clone --single-branch --branch dev https://github.com/AnzoDK/RPEngine.git
else
    echo "Using master branch"
    git clone https://github.com/AnzoDK/RPEngine.git
fi
if [ $? -ne 0 ]
then
    echo "Git failed to get RPEngine - Fatal"
    exit 1
fi

cd RPEngine
if [ "$1" == "--use-dev" ]
then
	if [ "$2" == "--Windows" ]
	then
		./dependency-builder.sh --use-dev --Windows
		if [ $? -ne 0 ]
        then
            rm -r -f RPEngine
            exit 1
        fi
		cp includes/RPAudio/librpaudio.dll ../includes/RPAudio/
		cp rpengine.so ../includes/RPEngine/librpengine.dll
		mv -f includes/RPAudio/librpaudio.a ../includes/RPAudio/librpaudio.a
	else
		./dependency-builder.sh --use-dev
        if [ $? -ne 0 ]
        then
            rm -r -f RPEngine
            exit 1
        fi
		cp includes/RPAudio/librpaudio.so ../includes/RPAudio/
		cp rpengine.so ../includes/RPEngine/librpengine.so
	fi
else
	if [ "$1" == "--Windows" ]
	then
		./dependency-builder.sh --Windows
        if [ $? -ne 0 ]
        then
            rm -r -f RPEngine
            exit 1
        fi
	else
		./dependency-builder.sh
        if [ $? -ne 0 ]
        then
            exit 1
        fi
		cp includes/RPAudio/librpaudio.so ../includes/RPAudio/
		cp rpengine.so ../includes/RPEngine/librpengine.so
		mv -f includes/RPAudio/librpaudio.a ../includes/RPAudio/librpaudio.a
	fi
fi

make lib
mkdir -p ../includes/RPEngine
mkdir -p ../includes/RPAudio
cp includes/*.h ../includes/RPEngine/
cp includes/RPAudio/*.h ../includes/RPAudio/
cd ..
rm -r -f RPEngine
echo "Completed"
