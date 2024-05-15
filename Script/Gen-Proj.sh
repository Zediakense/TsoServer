#!/bin/sh

mdir="$(pwd)"
path=$(dirname "$PWD") 
exeFile=$path/"bin/Debug-linux-/TsoServer/TsoServer"
echo $exeFile
if [ ! -e "$exeFile" ]; then
	echo $exeFile "not exist, do nothing"
else
	rm $exeFile
fi

cd ../TsoServer
../Vender/premake5 gmake

cd ./build
make

if [ ! -e "$exeFile" ]; then
	echo $exeFile "failed to generate exe file"
else
	$exeFile
fi