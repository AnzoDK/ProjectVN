#!/bin/bash
pwd
./dependency-builder.sh --use-dev
make dev-deps
./projectvn --test
