#!/bin/bash
../../dependency-builder.sh --use-dev --Windows
cd ../..
make dev-deps-windows OS=Windows
./projectvn.exe --test

