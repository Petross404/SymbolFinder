#!/bin/bash

#Make sure it is installed first. Else inform the user.
if ! command -v clang-format &> /dev/null
then
    echo "clang-format could not be found. Install it or make it visible under the PATH."
    exit
fi

find . -regex '.*\.\(cpp\|hpp\|cxx\|ixx\|cu\|c\|h\)' -exec clang-format -style=file -i {} \;
