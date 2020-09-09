#!/bin/bash
pwd
rm -r -f RPEngine
./dependency-builder.sh --use-dev --Windows
make dev-deps-windows OS=Windows
if [ $? -ne 0 ]
then
    exit 1
fi
wine ./projectvn.exe --test
echo "Windows ExE compile successfuly - Can't run open X display on travis, so manual test is needed to confimrm the build"
