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
    raise Exception("Second argument provided is not of type string. (For class name.)")

modulesDir = "../modules"
moduleName = argv[1]
className = argv[2]

if isdir(join(modulesDir, moduleName)):
    print("Module with that name all ready exists.")
    _exit(2)

os.makedirs(join(modulesDir, moduleName, "include", "module"), exist_ok=True)
os.makedirs(join(modulesDir, moduleName, "src"), exist_ok=True)

headerContents = '''#pragma once

#include <sol/sol.hpp>

#include "heart/module.h"

namespace HeartEngine {{ class Engine; }}

namespace HeartRayLib
{{
class {0} : public HeartEngine::Module
{{
public:
    {0}(bool includeSetting = true)
        : includeSetting(includeSetting) {{}}

    void registerTypes(HeartEngine::Engine& engine, sol::state& lua) override
    {{
        if (includeSetting)
            Setup(engine, lua);
    }}

    void Setup(HeartEngine::Engine& engine, sol::state& lua);
private:
    bool includeSetting;
}};
}}'''.format(className)

with (open(join(modulesDir, moduleName, "include", "module", moduleName + ".h"), "w")) as header:
    header.writelines(headerContents)

sourceContents = '''#include "module/{0}.h"

#include "heart/engine.h"

using namespace HeartEngine;

namespace HeartRayLib
{{
void {1}::Setup(HeartEngine::Engine& engine, sol::state& lua)
{{
    //TODO:
}}
}}'''.format(moduleName, className)

with (open(join(modulesDir, moduleName, "src", moduleName + ".cpp"), "w")) as source:
    source.writelines(sourceContents)

cmakeContents = '''cmake_minimum_required(VERSION 3.5)
project(heart_{0} VERSION 1.0.0)

add_library(heart_{0} src/{0}.cpp)
target_include_directories(heart_{0} PUBLIC include)'''.format(moduleName)

with (open(join(modulesDir, moduleName, "CMakeLists.txt"), "w")) as cmake:
    cmake.writelines(cmakeContents)