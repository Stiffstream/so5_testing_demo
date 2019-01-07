This repository contains examples of unit-tests written by using a new `so_5::experimental::testing` functionality from SO-5.5.24.

# How To Obtain And Try?

## Prerequisites

A C++ complier with more or less good support of C++14. We have tried gcc-5.4, clang-3.8 and Visual C++ 15.7.

## How To Obtain?

This repository contains only source codes of the examples. SObjectizer's source code is not included into the repository.
There are two ways to get the examples and all necessary dependencies.

### Download The Full Archive

There is a [Downloads section](https://bitbucket.org/sobjectizerteam/so5_testing_demo/downloads/). It contains archives with all source codes (it means that an archive contains sources of the examples and sources
of all necessary subprojects). The simpliest way is to download a corresponding archive, unpack it, go into
`so5_testing_demo/dev`, then compile and run.

### Use MxxRu::externals

It this case you need to have Ruby + MxxRu + various utilities which every Linux/FreeBSD/macOS-developer usually have (like git, tar, unzip and stuff like that). Then:

1. Install Ruby, RubyGems and Rake (usually RubyGems is installed with Ruby but sometimes you have to install it separatelly).
2. Install MxxRu: `gem install Mxx_ru`
3. Do hg clone: `hg clone https://bitbucket.org/sobjectizerteam/so5_testing_demo`
4. Go into appropriate folder: `cd so5_testing_demo`
5. Run command `mxxruexternals`
6. Wait while add dependencies will be downloaded.

Then go to `dev` subfolder, compile and run.

## How To Try?

### Building With CMake

A well known chain of actions:

~~~~~
cd so5_testing_demo/dev
mkdir cmake_build
cd cmake_build
cmake -DCMAKE_INSTALL_PREFIX=target -DCMAKE_BUILD_TYPE=release ..
cmake --build . --config Release
cmake --build . --config Release --target test
~~~~~

Note that on Windows the last command can looks like:

~~~~~
cmake --build . --config Release --target run_tests
~~~~~


### Building With MxxRu

The following chain of actions is necessary for building with MxxRu:

~~~~~
cd so5_testing_demo/dev
ruby build.rb
~~~~~
