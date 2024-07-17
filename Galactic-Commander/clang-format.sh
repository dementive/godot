#/usr/bin/env bash

echo "\n\nFormatting galactic-commander-extension with clang-format:\n"
find ./src/ -iname *.hpp -o -iname *.cpp | xargs clang-format --verbose -i

if [ -d ./src ]; then
    cd ./src
    if [ -f ./clang-format.sh ]; then
        ./clang-format.sh
    fi
fi

exit 0
