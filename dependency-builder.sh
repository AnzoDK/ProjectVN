#!/bin/bash
#ProjectVN dependency resolver

Debug_Level="DEBUG_LEVEL=-g3"

mkdir -p ./includes/RPAudio/
mkdir -p ./includes/RPEngine

for i in "$@"
do
	if [ "$i" == "--optimized" ]
	then
		Debug_Level="DEBUG_LEVEL=-O2"
	fi
done

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
mkdir -p ../includes/RPEngine
mkdir -p ../includes/RPAudio
mkdir -p ../includes/RPAudio/oggvorbis
mkdir -p ../includes/RPAudio/vorbis
mkdir -p ../includes/RPAudio/vorbisfile
mkdir -p ../includes/RPAudio/libopenal
mkdir -p ../includes/RPAudio/libsndio
if [ "$1" == "--use-dev" ]
then
	if [ "$2" == "--Windows" ]
	then
		if [ "$3" == "--optimize" ]
		then
			./dependency-builder.sh --use-dev --Windows --optimize
		else
			./dependency-builder.sh --use-dev --Windows
        fi
        if [ $? -ne 0 ]
        	then
            		rm -r -f RPEngine
            		exit 1
       		fi
        make lib $Debug_Level OS=Windows
		cp includes/RPAudio/librpaudio.dll ../includes/RPAudio/
		cp rpengine.so ../includes/RPEngine/librpengine.dll
		mv -f includes/RPAudio/librpaudio.a ../includes/RPAudio/librpaudio.a
		cp rpengine.dll ../includes/RPEngine/librpengine.dll
		cp includes/RPAudio/librpaudio.a ../includes/RPAudio/
		cp librpengine.a ../includes/RPEngine/librpengine.a
        cp ../includes/RPEngine/librpengine.dll ../rpengine.dll
        cp ../includes/RPAudio/librpaudio.dll ../rpaudio.dll
        cp RPScriptLinker.exe ../RPScriptLinker.exe
	else
		if [ "$2" == "--optimize" ]
		then
			./dependency-builder.sh --use-dev --optimize
		else
			./dependency-builder.sh --use-dev
		fi
        	if [ $? -ne 0 ]
        	then
			cd ..
            		rm -r -f RPEngine
            		exit 1
       		fi
        make lib $Debug_Level OS=Linux
		cp includes/RPAudio/librpaudio.so ../includes/RPAudio/
		cp rpengine.so ../includes/RPEngine/librpengine.so
		cp RPScriptLinker ../RPScriptLinker
	fi
else
	if [ "$1" == "--Windows" ]
	then
		if [ "$2" == "--optimize" ]
		then
			./dependency-builder.sh --Windows
		else
			./dependency-builder.sh --Windows --optimize
		fi
        	if [ $? -ne 0 ]
        	then
			cd ..
            		rm -r -f RPEngine
            		exit 1
        	fi
        	make lib $Debug_Level OS=Windows
        	cp includes/RPAudio/librpaudio.dll ../includes/RPAudio/
            cp rpengine.dll ../includes/RPEngine/librpengine.dll
        	cp includes/RPAudio/librpaudio.a ../includes/RPAudio/
            cp librpengine.a ../includes/RPEngine/librpengine.a
            cp ../includes/RPEngine/librpengine.dll ../rpengine.dll
        	cp ../includes/RPAudio/librpaudio.dll ../rpaudio.dll
        	cp RPScriptLinker.exe ../RPScriptLinker.exe
	else
		if [ "$1" == "--optimize" ]
		then
			./dependency-builder.sh
		else
			./dependency-builder.sh --optimize
		fi
        	if [ $? -ne 0 ]
        	then
			cd ..
            		rm -r -f RPEngine
            		exit 1
        	fi
        	make lib $Debug_Level OS=Linux
		cp includes/RPAudio/librpaudio.so ../includes/RPAudio/
		cp rpengine.so ../includes/RPEngine/librpengine.so
		mv -f includes/RPAudio/librpaudio.a ../includes/RPAudio/librpaudio.a
		cp RPScriptLinker ../RPScriptLinker
	fi
fi
cp -f includes/RPAudio/oggvorbis/* ../includes/RPAudio/oggvorbis/
cp -f includes/RPAudio/vorbis/* ../includes/RPAudio/vorbis/
cp -f includes/RPAudio/libopenal/* ../includes/RPAudio/libopenal/
cp -f includes/RPAudio/vorbisfile/* ../includes/RPAudio/vorbisfile/
cp -f includes/RPAudio/libsndio/* ../includes/RPAudio/libsndio/
cp includes/*.h ../includes/RPEngine/
cp includes/RPAudio/*.h ../includes/RPAudio/
cd ..
rm -r -f RPEngine
echo "Completed"
