# Godot + GDNative Template

Even the template aims to ease the initialization process, read the [GDNative Documentation](https://docs.godotengine.org/en/stable/tutorials/plugins/gdnative/gdnative-cpp-example.html).

# Set up and build the Godot native library

1. Clone the project : `git clone --recurse-submodules git@gitlab.com:legionarius/template/godot-native.git`

The `src` directory contains a base file (`GDLibrary.cpp`) necessary to bind your module to Godot.
You can use it directly or create your own, but do not forget to update this file every time you add a new
class to the module (see comments in the file).

2. In the project directory launch : `./build.sh`

This build script will generate: git hooks, the bindings for the current Godot version, the Godot native library and your Godot native module

You can force generation of the binding by passing **-j** to the script and force building Godot native library by passing **-g**. It is possible to
compile for a different platform from your host by passing **-t (windows || osx)**

# Add style pre-commit hook

	Install clang-format :
	- Linux : use your package manager, it should be in it.
	- Windows : it is part of LLVM, install it from https://releases.llvm.org/download.html and make sure it is added to your PATH.

	C++ code style is using Godot rules and is enforced using `clang-format`.
	Get the file from [pre-commit-clang-format](https://raw.githubusercontent.com/godotengine/godot/master/misc/hooks/pre-commit-clang-format)
	Add it to your pre-commit hook.

# Set-up IDE

	With CLion it should automatically use the CmakeLists.txt file to imports the godot library. Note that currently you can't build the project
	with CLion directly, you still need to use Scons. The CmakeLists.txt file is only here to have the completion of the IDE.

# Useful Documentation

	- [C++ Core Guidelines](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines)

