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
        make lib OS=Windows
		cp includes/RPAudio/librpaudio.dll ../includes/RPAudio/
		cp rpengine.dll ../includes/RPEngine/librpengine.dll
		cp includes/RPAudio/librpaudio.a ../includes/RPAudio/
		cp librpengine.a ../includes/RPEngine/librpengine.a
	else
		./dependency-builder.sh --use-dev
        if [ $? -ne 0 ]
        then
            rm -r -f RPEngine
            exit 1
        fi
        make lib OS=Windows
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
        make lib OS=Windows
        cp includes/RPAudio/librpaudio.dll ../includes/RPAudio/
		cp rpengine.dll ../includes/RPEngine/librpengine.dll
        cp includes/RPAudio/librpaudio.a ../includes/RPAudio/
		cp librpengine.a ../includes/RPEngine/librpengine.a
	else
		./dependency-builder.sh
        if [ $? -ne 0 ]
        then
            rm -r -f RPEngine
            exit 1
        fi
        make lib OS=Windows
		cp includes/RPAudio/librpaudio.so ../includes/RPAudio/
		cp rpengine.so ../includes/RPEngine/librpengine.so
		
	fi
fi
mkdir -p ../includes/RPEngine
mkdir -p ../includes/RPAudio
mkdir -p ../includes/RPAudio/oggvorbis
mkdir -p ../includes/RPAudio/vorbis
mkdir -p ../includes/RPAudio/vorbisfile
mkdir -p ../includes/RPAudio/libopenal
cp -f includes/RPAudio/oggvorbis/* ../includes/RPAudio/oggvorbis/
cp -f includes/RPAudio/vorbis/* ../includes/RPAudio/vorbis/
cp -f includes/RPAudio/libopenal/* ../includes/RPAudio/libopenal/
cp -f includes/RPAudio/vorbisfile/* ../includes/RPAudio/vorbisfile/
cp includes/*.h ../includes/RPEngine/
cp includes/RPAudio/*.h ../includes/RPAudio/
cd ..
rm -r -f RPEngine
echo "Completed"
