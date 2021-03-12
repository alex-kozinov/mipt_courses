#!/bin/sh
bindir=$(pwd)
cd /Users/alex-kozinov/projects/mipt_courses/computer_graphics/homework_1_sphere/
export 

if test "x$1" = "x--debugger"; then
	shift
	if test "x" = "xYES"; then
		echo "r  " > $bindir/gdbscript
		echo "bt" >> $bindir/gdbscript
		GDB_COMMAND-NOTFOUND -batch -command=$bindir/gdbscript  /Users/alex-kozinov/projects/mipt_courses/computer_graphics/cmake-build-debug/sphere 
	else
		"/Users/alex-kozinov/projects/mipt_courses/computer_graphics/cmake-build-debug/sphere"  
	fi
else
	"/Users/alex-kozinov/projects/mipt_courses/computer_graphics/cmake-build-debug/sphere"  
fi
