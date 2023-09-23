# Packages all resources into a binary file format for easy loading in c++

import os
from sys import argv
from pathlib import Path

if len(argv) < 3:
    raise Exception("Expected 2 arguments.")

if not isinstance(argv[1], str):
    raise Exception("First argument provided is not of type string. (For directory.)")

if not isinstance(argv[2], str):
    raise Exception("Second argument provided is not of type string. (For destination file.)")

# The following limits are in byte counts
b_maxFileCount = 2
b_maxPathLength = 1
b_maxDataLength = 4

directory = Path(argv[1])
pathlist = list(directory.rglob("**/*.*"))

# Formatted as pathLength, path, length
header = []
data = []

# Number of files
header.append(len(pathlist).to_bytes(b_maxFileCount))

for path in pathlist:
    pathBytes = bytes(str(path.relative_to(directory)), 'utf-8')

    # Path Length
    header.append(len(pathBytes).to_bytes(b_maxPathLength))
    # Path
    header.append(pathBytes)

    byteData = bytes()
    if path.suffix == ".lua":
        os.system('luac54.exe ' + str(path))

        with open("luac.out", 'rb') as luaByteCode:
            byteData = luaByteCode.read()
            print(byteData)

        os.remove("luac.out")
    else:
        byteData = path.read_bytes()
    
    # Data length
    header.append(len(byteData).to_bytes(b_maxDataLength))
    # Data
    data.append(byteData)

newPath = os.path.join(directory.parent.absolute(), argv[2])

combined = header + data
bArray = b''.join(combined)

with open(newPath, 'wb') as binary_file:
    binary_file.truncate(0)
    binary_file.write(bArray)
