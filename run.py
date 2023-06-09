#!/usr/bin/env python3

# ./run.py raw 1
# ./run.py temp 1
# ./run.py kop 1
# ./run.py c r500d2 1

import sys, os

scriptDir = os.path.realpath(os.path.dirname(__file__))
id = ""
target = ""
if sys.argv[1] == "c":
	target = "c_" + sys.argv[2] + "_"
	id = sys.argv[3]
elif sys.argv[1] in ("raw", "temp", "kop"):
	target = sys.argv[1]
	id = sys.argv[2]
else:
	raise NameError
target += id

os.system("/opt/jetbrains/apps/CLion/ch-0/231.9011.31/bin/cmake/linux/x64/bin/cmake --build " + scriptDir + "/cmake-build-debug -j 10 --target " + target)
command = scriptDir + "/cmake-build-debug/" + target + " local"
if sys.argv[-1] == "f" or sys.argv[-2] == "f":
	command += " " + scriptDir
	if sys.argv[1] == "c":
		command += "/contests/" + sys.argv[2]
	else:
		command += "/freeplay/" + sys.argv[1]
	command += "/output/output"
	if sys.argv[-1] == "f":
		command += id
	elif sys.argv[-2] == "f":
		command += sys.argv[-1]
	command += ".txt"

os.system(command)
