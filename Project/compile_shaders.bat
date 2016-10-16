@ECHO OFF
SETLOCAL

REM Copyright 2016 Intel Corporation All Rights Reserved
REM 
REM Intel makes no representations about the suitability of this software for any purpose.
REM THIS SOFTWARE IS PROVIDED ""AS IS."" INTEL SPECIFICALLY DISCLAIMS ALL WARRANTIES,
REM EXPRESS OR IMPLIED, AND ALL LIABILITY, INCLUDING CONSEQUENTIAL AND OTHER INDIRECT DAMAGES,
REM FOR THE USE OF THIS SOFTWARE, INCLUDING LIABILITY FOR INFRINGEMENT OF ANY PROPRIETARY
REM RIGHTS, AND INCLUDING THE WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
REM Intel does not assume any responsibility for any errors which may appear in this software
REM nor any responsibility to update it.

if [%1] == [] (
    echo No arguments provided! Please specify folder number.
    echo Example usage: compile_shaders.bat 03
    goto end
)

if exist glslangValidator.exe (
    goto convert
)
for %%X in (glslangValidator.exe) do (set glslangValidator=%%~$PATH:X)
if defined glslangValidator (
    goto convert
)

echo Could not find "glslangValidator.exe" file.
goto end

:convert

set folder=Tutorial%1/Data%1
echo Converting GLSL shaders into SPIR-V assembly in the "%folder%" folder.

if exist %folder%/shader.vert (
    glslangValidator.exe -V -H -o %folder%/vert.spv %folder%/shader.vert > %folder%/vert.spv.txt
)

if exist %folder%/shader.frag (
    glslangValidator.exe -V -H -o %folder%/frag.spv %folder%/shader.frag > %folder%/frag.spv.txt
)

:end

ENDLOCAL