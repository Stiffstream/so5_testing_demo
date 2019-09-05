This repository contains examples of unit-tests written by using `so_5::experimental::testing` functionality from SO-5.6.

**NOTE.** *These examples were upgraded to SObjectizer-5.6 in May 2019. For old versions of examples written for SObjectizer-5.5.24 please use tag "v.1.0-so5.5".*

# How To Obtain And Try?

## Prerequisites

A C++ complier with support of C++17. We have tried gcc-7, clang-6 and Visual C++ 15.9.

## How To Obtain?

This repository contains only source codes of the examples. SObjectizer's source code is not included into the repository.
There are two ways to get the examples and all necessary dependencies.

### Download The Full Archive

There is a [Releases section](https://github.com/Stiffstream/so5_testing_demo/releases). It contains archives with all source codes (it means that an archive contains sources of the examples and sources
of all necessary subprojects). The simpliest way is to download a corresponding archive, unpack it, go into
`so5_testing_demo/dev`, then compile and run.

### Use MxxRu::externals

It this case you need to have Ruby + MxxRu + various utilities which every Linux/FreeBSD/macOS-developer usually have (like git, tar, unzip and stuff like that). Then:

1. Install Ruby, RubyGems and Rake (usually RubyGems is installed with Ruby but sometimes you have to install it separatelly).
2. Install MxxRu: `gem install Mxx_ru`
3. Do git clone: `git clone https://github.com/Stiffstream/so5_testing_demo/releases`
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

