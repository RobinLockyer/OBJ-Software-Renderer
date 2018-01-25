@echo off
pushd ..\build
cl -Zi ..\code\object_viewer.cpp ..\code\Object.cpp ..\code\Renderer.cpp User32.lib Gdi32.lib /EHsc
popd