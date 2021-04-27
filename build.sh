#!/usr/bin/sh

unset PLATFORM
unset TRANSCONP_PLATFORM
unset FLAG_BINDING
unset FLAG_BUILDGODOT

FILE=./lib

function usage() {
   echo "Usage: $0 [-t <osx|windows>] [-g] [-j] " 1>&2; exit 2;
}

function initPlatform() {
  if [ "$TRANSCONP_PLATFORM" ]; then
    if [ "$TRANSCONP_PLATFORM" != "windows" ] && [ "$TRANSCONP_PLATFORM" != "osx" ]; then
      usage;
      exit 2;
	  elif [[ "$TRANSCONP_PLATFORM" == "osx" ]]; then
	  	PLATFORM="osx"
	  elif [[ "$TRANSCONP_PLATFORM" == "windows" ]]; then
	  	PLATFORM="windows"
	  fi
	else
	  if [[ "$OSTYPE" == "linux-gnu"* ]]; then
		  PLATFORM="linux"
    elif [[ "$OSTYPE" == "darwin"* ]]; then
      PLATFORM="osx"
    else
      PLATFORM="windows"
    fi
  fi
  echo "Build platform: $PLATFORM"
}

function buildBinding() {
  godot --gdnative-generate-json-api api.json
}

function buildModule() {
	scons platform=$PLATFORM
}

function buildGodotCPP() {
	cd godot-cpp; scons platform=$PLATFORM generate_bindings=yes bits=64 use_custom_api_file=yes custom_api_file=../api.json -j4
}

# Create lib folder if doesn't exist
if ! [ -d "$FILE" ]; then
    mkdir $FILE
fi

# Read arguments
while getopts 't:gj' c
do
  case $c in
    t) ((OPTARG == "windows" || OPTARG == "osx")); TRANSCONP_PLATFORM=$OPTARG  || usage ;; # If compilation platform is different from HOST OS
    j) FLAG_BINDING=true ;; # If create binding is needed
    g) FLAG_BUILDGODOT=true ;; # If build godot-cpp is needed
    *) usage ;;
  esac
done

# Execute build functions
initPlatform

# Init git hooks
git config core.hooksPath .githooks

if [ $FLAG_BINDING ] || [ ! -f "api.json" ] ; then
  buildBinding
fi
wait

if [ $FLAG_BUILDGODOT ] || [ ! -d "godot-cpp/bin" ]; then
  buildGodotCPP
fi
wait

buildModule
wait

exit 0;
