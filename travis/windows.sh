#!/bin/bash
pwd
./dependency-builder.sh --use-dev --Windows
make dev-deps-windows OS=Windows
if [ $? -ne 0 ]
then
    exit 1
fi
wine ./projectvn.exe --test

