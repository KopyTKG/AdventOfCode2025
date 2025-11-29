# !/bin/bash
# constants
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
PROJECT_ROOT=$(realpath "${SCRIPT_DIR}/..")
BUILD_DIR="${PROJECT_ROOT}/build"
SRC_DIR="${PROJECT_ROOT}/src"

# check if cmake is installed
if ! command -v cmake &> /dev/null
then
    echo "cmake could not be found, please install cmake to proceed."
    exit
fi

# check if ninja is installed
if ! command -v ninja &> /dev/null
then
    echo "ninja could not be found, please install ninja to proceed."
    exit
fi

# check if git is installed
if ! command -v git &> /dev/null
then
    echo "git could not be found, please install git to proceed."
    exit
fi

# check if we are in a git repository
if ! git -C "$PROJECT_ROOT" rev-parse &> /dev/null
then
    echo "This script must be run in a git repository."
    exit
fi

# Create / update versio.hpp file
VERSION_FILE="${SRC_DIR}/version.hpp"
VERSION=$(git describe --tags --always --dirty)
echo "#pragma once" > "$VERSION_FILE"
echo "constexpr const char *build = \"$VERSION\";" >> "$VERSION_FILE"
echo "Generated version.hpp with build version: $VERSION"


# Check if BUILD_DIR exists
mkdir -p "$BUILD_DIR"
cd "$BUILD_DIR" || exit
cmake "$PROJECT_ROOT" -G Ninja
ninja
