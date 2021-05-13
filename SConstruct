#!python
import os
import sys
import subprocess
from SCons import __version__ as scons_raw_version

# Try to detect the host platform automatically.
# This is used if no `platform` argument is passed
if sys.platform.startswith('linux'):
    host_platform = 'linux'
elif sys.platform == 'darwin':
    host_platform = 'osx'
elif sys.platform == 'win32' or sys.platform == 'msys':
    host_platform = 'windows'
else:
    raise ValueError(
        'Could not detect platform automatically, please specify with '
        'platform=<platform>'
    )

opts = Variables([], ARGUMENTS)

# Gets the standard flags CC, CCX, etc.
env = DefaultEnvironment()

# Gets SCons version
scons_ver = env._get_major_minor_revision(scons_raw_version)


if scons_ver >= (4, 0, 0):
    env.Tool("compilation_db")
    env.Alias("compiledb", env.CompilationDatabase())

is64 = sys.maxsize > 2**32
if (
        env['TARGET_ARCH'] == 'amd64' or
        env['TARGET_ARCH'] == 'emt64' or
        env['TARGET_ARCH'] == 'x86_64' or
        env['TARGET_ARCH'] == 'arm64-v8a'
):
    is64 = True

# Define our options
opts.Add(EnumVariable('target', "Compilation target", 'debug', ['d', 'debug', 'r', 'release']))
opts.Add(EnumVariable('platform', "Compilation platform", '', ['', 'windows', 'x11', 'linux', 'osx', 'javascript', 'android']))
opts.Add(EnumVariable('p', "Compilation target, alias for 'platform'", '', ['', 'windows', 'x11', 'linux', 'osx', 'android']))
opts.Add(BoolVariable('use_llvm', "Use the LLVM / Clang compiler", 'no'))
opts.Add(PathVariable('target_path', 'The path where the lib is installed.', 'lib/'))
opts.Add(PathVariable('target_name', 'The library name.', 'libgdnative', PathVariable.PathAccept))
opts.Add(EnumVariable('bits', 'Target platform bits', '64' if is64 else '32', ('32', '64')))
opts.Add(EnumVariable(
    'android_arch',
    'Target Android architecture',
    'armv7',
    ['armv7','arm64v8','x86','x86_64']
))
opts.Add(
    'android_api_level',
    'Target Android API level',
    '18' if ARGUMENTS.get("android_arch", 'armv7') in ['armv7', 'x86'] else '21'
)


# Local dependency paths, adapt them to your setup
if 'GODOT_CPP' in os.environ.keys():
    cpp_bindings_path = os.environ['GODOT_CPP']
else:
    cpp_bindings_path = "godot-cpp/"
    
env["ANDROID_NDK_ROOT"] = os.environ.get("ANDROID_NDK_ROOT", None)

godot_headers_path = os.path.join(cpp_bindings_path, "godot-headers/")
cpp_library = "libgodot-cpp"

# only support 64 at this time..
bits = 64

# Updates the environment with the option variables.
opts.Update(env)

# Process some arguments
if env['use_llvm']:
    env['CC'] = 'clang'
    env['CXX'] = 'clang++'

if env['p'] != '':
    env['platform'] = env['p']

if env['platform'] == '':
    print("No valid target platform selected.")
    quit()

# Check our platform specifics
if env['platform'] == "osx":
    env['target_path'] += 'osx/'
    cpp_library += '.osx'
    if env['target'] in ('debug', 'd'):
        env.Append(CCFLAGS = ['-g','-O2', '-arch', 'x86_64', '-std=c++17'])
        env.Append(LINKFLAGS = ['-arch', 'x86_64'])
    else:
        env.Append(CCFLAGS = ['-g','-O3', '-arch', 'x86_64', '-std=c++17'])
        env.Append(LINKFLAGS = ['-arch', 'x86_64'])

elif env['platform'] in ('x11', 'linux'):
    env['target_path'] += 'x11/'
    if env['target'] in ('debug', 'd'):
        env.Append(CCFLAGS = ['-fPIC', '-g3','-Og', '-std=c++17'])
    else:
        env.Append(CCFLAGS = ['-fPIC', '-g','-O3', '-std=c++17'])

elif env['platform'] == "windows":
    env['target_path'] += 'win64/'
    cpp_library += '.windows'

    if host_platform == 'windows' and not env['use_mingw']:
        # This makes sure to keep the session environment variables on windows,
        # that way you can run scons in a vs 2017 prompt and it will find all the required tools
        env.Append(ENV = os.environ)

        env.Append(CCFLAGS = ['-DWIN32', '-D_WIN32', '-D_WINDOWS', '-W3', '-GR', '-D_CRT_SECURE_NO_WARNINGS'])
        if env['target'] in ('debug', 'd'):
            env.Append(CCFLAGS = ['-EHsc', '-D_DEBUG', '-MDd'])
        else:
            env.Append(CCFLAGS = ['-O2', '-EHsc', '-DNDEBUG', '-MD'])

    elif host_platform == 'linux' or host_platform == 'osx':
        # Cross-compilation using MinGW
        if env['bits'] == '64':
            env['CXX'] = 'x86_64-w64-mingw32-g++'
            env['AR'] = "x86_64-w64-mingw32-ar"
            env['RANLIB'] = "x86_64-w64-mingw32-ranlib"
            env['LINK'] = "x86_64-w64-mingw32-g++"
        elif env['bits'] == '32':
            env['CXX'] = 'i686-w64-mingw32-g++'
            env['AR'] = "i686-w64-mingw32-ar"
            env['RANLIB'] = "i686-w64-mingw32-ranlib"
            env['LINK'] = "i686-w64-mingw32-g++"

    elif host_platform == 'windows' and env['use_mingw']:
        # Don't Clone the environment. Because otherwise, SCons will pick up msvc stuff.
        env = Environment(ENV = os.environ, tools=["mingw"])
        opts.Update(env)
        #env = env.Clone(tools=['mingw'])
        env["SPAWN"] = mySpawn

    # Native or cross-compilation using MinGW
    if host_platform == 'linux' or host_platform == 'osx' or env['use_mingw']:
        # These options are for a release build even using target=debug
        env.Append(CCFLAGS=['-O3', '-std=c++17', '-Wwrite-strings'])
        env.Append(LINKFLAGS=[
            '--static',
            '-Wl,--no-undefined',
            '-static-libgcc',
            '-static-libstdc++',
        ])
        
elif env["platform"] == "android":
    if host_platform == 'windows':
        # Don't Clone the environment. Because otherwise, SCons will pick up msvc stuff.
        env = Environment(ENV = os.environ, tools=["mingw"])
        opts.Update(env)
        #env = env.Clone(tools=['mingw'])

        env["SPAWN"] = mySpawn

    # Verify NDK root
    if not 'ANDROID_NDK_ROOT' in env:
        raise ValueError("To build for Android, ANDROID_NDK_ROOT must be defined. Please set ANDROID_NDK_ROOT to the root folder of your Android NDK installation.")

    # Validate API level
    api_level = int(env['android_api_level'])
    if env['android_arch'] in ['x86_64', 'arm64v8'] and api_level < 21:
        print("WARN: 64-bit Android architectures require an API level of at least 21; setting android_api_level=21")
        env['android_api_level'] = '21'
        api_level = 21

    # Setup toolchain
    toolchain = env['ANDROID_NDK_ROOT'] + "/toolchains/llvm/prebuilt/"
    if host_platform == "windows":
        toolchain += "windows"
        import platform as pltfm
        if pltfm.machine().endswith("64"):
            toolchain += "-x86_64"
    elif host_platform == "linux":
        toolchain += "linux-x86_64"
    elif host_platform == "osx":
        toolchain += "darwin-x86_64"
    env.PrependENVPath('PATH', toolchain + "/bin") # This does nothing half of the time, but we'll put it here anyways

    # Get architecture info
    arch_info_table = {
        "armv7" : {
            "march":"armv7-a", "target":"armv7a-linux-androideabi", "tool_path":"arm-linux-androideabi", "compiler_path":"armv7a-linux-androideabi",
            "ccflags" : ['-mfpu=neon']
            },
        "arm64v8" : {
            "march":"armv8-a", "target":"aarch64-linux-android", "tool_path":"aarch64-linux-android", "compiler_path":"aarch64-linux-android",
            "ccflags" : []
            },
        "x86" : {
            "march":"i686", "target":"i686-linux-android", "tool_path":"i686-linux-android", "compiler_path":"i686-linux-android",
            "ccflags" : ['-mstackrealign']
            },
        "x86_64" : {"march":"x86-64", "target":"x86_64-linux-android", "tool_path":"x86_64-linux-android", "compiler_path":"x86_64-linux-android",
            "ccflags" : []
        }
    }
    arch_info = arch_info_table[env['android_arch']]

    # Setup tools
    env['CC'] = toolchain + "/bin/clang"
    env['CXX'] = toolchain + "/bin/clang++"
    env['AR'] = toolchain + "/bin/" + arch_info['tool_path'] + "-ar"
    env['LD'] = toolchain + "/bin/" + arch_info['tool_path'] + "-ld"
    env['LDFLAGS'] = toolchain + "/bin/" + arch_info['tool_path'] + "-ld"
    
    if env["android_arch"] == "arm64v8":
        env['LINK'] = toolchain + "/bin/aarch64-linux-android21-clang++"
    else:
        env['LINK'] = toolchain + "/bin/armv7a-linux-androideabi21-clang++"
    env.Append(CCFLAGS=['--target=' + arch_info['target'] + env['android_api_level'], '-march=' + arch_info['march'], '-std=c++17', '-fPIC'])#, '-fPIE', '-fno-addrsig', '-Oz'])
    env.Append(CCFLAGS=arch_info['ccflags'])
        
elif env["platform"] == "javascript":
    env['target_path'] += 'wasm32/'
    env["ENV"] = os.environ
    env["CC"] = "emcc"
    env["CXX"] = "em++"
    env["AR"] = "emar"
    env["RANLIB"] = "emranlib"
    env.Append(CPPFLAGS=["-s", "SIDE_MODULE=1", "-std=c++17"])
    env.Append(LINKFLAGS=["-s", "SIDE_MODULE=1"])
    env["SHOBJSUFFIX"] = ".bc"
    env["SHLIBSUFFIX"] = ".wasm"
    # Use TempFileMunge since some AR invocations are too long for cmd.exe.
    # Use POSIX-style paths, required with TempFileMunge.
    env["ARCOM_POSIX"] = env["ARCOM"].replace("$TARGET", "$TARGET.posix").replace("$SOURCES", "$SOURCES.posix")
    env["ARCOM"] = "${TEMPFILE(ARCOM_POSIX)}"
    # All intermediate files are just LLVM bitcode.
    env["OBJPREFIX"] = ""
    env["OBJSUFFIX"] = ".bc"
    env["PROGPREFIX"] = ""
    # Program() output consists of multiple files, so specify suffixes manually at builder.
    env["PROGSUFFIX"] = ""
    env["LIBPREFIX"] = "lib"
    env["LIBSUFFIX"] = ".bc"
    env["LIBPREFIXES"] = ["$LIBPREFIX"]
    env["LIBSUFFIXES"] = ["$LIBSUFFIX"]
    env.Replace(SHLINKFLAGS='$LINKFLAGS')
    
    if env['target'] == "debug":
        env.Append(CCFLAGS = ['-g'])


if env["platform"] == "javascript":
    godot_cpp_suffix = ".wasm.bc"
else:
    godot_cpp_suffix = ".64.a"


cpp_library_filename = "libgodot-cpp.{platform}.{target}{suffix}".format(
    platform=env['platform'],
    target=env['target'],
    suffix=godot_cpp_suffix
    )


if 'android' in cpp_library_filename:
    android_path = {"arm64v8": "arm64-v8a", "armv7": "armeabi-v7a"}
    cpp_library_filename = "libgodot-cpp.android.debug." + env["android_arch"] + ".a"
    env['target_path'] += android_path[env["android_arch"]] + "/"

# make sure our binding library is properly includes
env.Append(CPPPATH=['.', godot_headers_path, os.path.join(cpp_bindings_path, 'include/'), os.path.join(cpp_bindings_path, 'include/core/'), os.path.join(cpp_bindings_path, 'include/gen/')])
env.Append(LIBPATH=[os.path.join(cpp_bindings_path, 'bin/')])
env.Append(LIBS=[env.File(os.path.join(cpp_bindings_path, "bin", cpp_library_filename))])


# tweak this if you want to use different folders, or more folders, to store your source code in.
env.Append(CPPPATH=['src/'])
sources = Glob('src/*.cpp')

library = env.SharedLibrary(target=env['target_path'] + env['target_name'], source=sources)
Default(library)

# Generates help for the -h scons option.
Help(opts.GenerateHelpText(env))
