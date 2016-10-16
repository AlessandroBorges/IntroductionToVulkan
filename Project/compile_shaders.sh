#!/bin/bash

# Copyright 2016 Intel Corporation All Rights Reserved
# 
# Intel makes no representations about the suitability of this software for any purpose.
# THIS SOFTWARE IS PROVIDED ""AS IS."" INTEL SPECIFICALLY DISCLAIMS ALL WARRANTIES,
# EXPRESS OR IMPLIED, AND ALL LIABILITY, INCLUDING CONSEQUENTIAL AND OTHER INDIRECT DAMAGES,
# FOR THE USE OF THIS SOFTWARE, INCLUDING LIABILITY FOR INFRINGEMENT OF ANY PROPRIETARY
# RIGHTS, AND INCLUDING THE WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
# Intel does not assume any responsibility for any errors which may appear in this software
# nor any responsibility to update it.

folder=Tutorial$1/Data$1

function convert {
  if [ -f "./$folder/shader.$1" ]; then
    echo "Converting $1 shader..."
    glslangValidator -V -H -o $folder/$1.spv $folder/shader.$1 > $folder/$1.spv.txt
  fi
}

if [ "$1" == "" ]; then
  echo "No arguments provided! Please specify folder number."
  echo "Example usage: source compile_shaders.sh 03"
else
  echo "Converting GLSL shaders into SPIR-V assembly in the '$folder' folder."
  convert vert
  convert frag
fi
