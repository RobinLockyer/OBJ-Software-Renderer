call .\build
set file=cow.obj
IF NOT [%1]==[] set file = "%1"
..\build\object_viewer.exe ..\data\%file%