
@echo off
md build
cd build

cmake -G "Visual Studio 16 2019" CMakeLists.txt ..
cmake --build . --config Debug
cmake --build . --config Release

set tmp_file=slimMesh.zip

echo "Retriving SlimMesh lib."
curl https://appfile1.hicloud.com:443/FileServer/getFile/app/011/111/111/0000000000011111111.20210628162242.66620339971961991630702673917497:20471231000000:0001:DFFCEE02FF9320E718DF135C9AC82B0745A6EBAAB1F4E068EA1BF22BBB349D40.zip?needInitFileName=true -o %tmp_file% -s

mkdir lib
powershell -Command "Expand-Archive -Path %tmp_file% -DestinationPath lib/"

echo "Copy SlimMesh dll to test lib dir"
copy %cd%\lib\SlimMesh.dll %cd%\Release\SlimMesh.dll /Y /B /V
copy %cd%\lib\SlimMesh.dll %cd%\Debug\SlimMesh.dll /Y /B /V
del /Q /F %tmp_file%
@pause