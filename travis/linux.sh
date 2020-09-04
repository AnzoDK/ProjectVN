#!/bin/bash
pwd
cd ..
./dependency-builder.sh --use-dev
make dev-deps
./projectvn --test
