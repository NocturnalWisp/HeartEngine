# Generates a module from a provided module name and class name
#   in the modules directory.

from sys import argv
import os
from os.path import join
from os.path import isdir
from os import _exit
from string import Formatter

if len(argv) < 2:
    raise Exception("Expected 2 arguments. A module name, and a class name.")

if not isinstance(argv[1], str):
    raise Exception("First argument provided is not of type string. (For module name.)")

if not isinstance(argv[2], str):
    raise Exception("Second argument provided is not of type string. (For namespace name.)")

if not isinstance(argv[3], str):
    raise Exception("Second argument provided is not of type string. (For class name.)")

modulesDir = "../modules"
moduleName = argv[1]
namespaceName = argv[2]
className = argv[3]

if isdir(join(modulesDir, moduleName)):
    print("Module with that name all ready exists.")
    _exit(2)

os.makedirs(join(modulesDir, moduleName, "include", "module"), exist_ok=True)
os.makedirs(join(modulesDir, moduleName, "src"), exist_ok=True)

headerContents = '''#pragma once

#include "heart/module.h"

namespace {1}
{{
class {0} : public HeartEngine::Module
{{
public:
    void registerTypes(HeartEngine::Engine& engine, sol::state& lua) override;
}};
}}'''.format(className, namespaceName)

with (open(join(modulesDir, moduleName, "include", "module", moduleName + ".h"), "w")) as header:
    header.writelines(headerContents)

sourceContents = '''#include "module/{0}.h"

#include "heart/engine.h"
#include "heart/utils.h"

using namespace HeartEngine;

namespace {2}
{{
void {1}::registerTypes(HeartEngine::Engine& engine, sol::state& lua)
{{
    //TODO: Register components/other lua types.
}}
}}'''.format(moduleName, className, namespaceName)

with (open(join(modulesDir, moduleName, "src", moduleName + ".cpp"), "w")) as source:
    source.writelines(sourceContents)

cmakeContents = '''cmake_minimum_required(VERSION 3.5)
project(heart_{0} VERSION 1.0.0)

add_library(heart_{0} src/{0}.cpp)
target_include_directories(heart_{0} PUBLIC include)

# Include libraries here using FetchLibraryGit.

LinkLibrary(heart_{0} HeartEngine core/include)'''.format(moduleName)

with (open(join(modulesDir, moduleName, "CMakeLists.txt"), "w")) as cmake:
    cmake.writelines(cmakeContents)