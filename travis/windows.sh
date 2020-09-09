#!/bin/bash
pwd
rm -r -f RPEngine
./dependency-builder.sh --use-dev --Windows
make dev-deps-windows OS=Windows
if [ $? -ne 0 ]
then
    exit 1
fi
echo "Windows ExE compile successfuly - Can't run exe on travis, so manual test is needed to confimrm the build"
