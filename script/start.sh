#! /bin/bash

set -e
ROOT="$(dirname "$0")"

echo "Relocating script to '$ROOT'..."
cd "$ROOT/.."

cat "$1" | ./bin/Compiler "$2" #REVISAR PASAJE DE 2do ARGUMENTO
