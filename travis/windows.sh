#!/bin/bash
pwd
#cd ..
./dependency-builder.sh --use-dev --Windows
make dev-deps-windows OS=Windows
wine ./projectvn.exe --test

