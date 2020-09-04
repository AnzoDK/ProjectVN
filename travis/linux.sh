#!/bin/bash
../../dependency-builder.sh --use-dev
cd ../..
make dev-deps
./projectvn --test
