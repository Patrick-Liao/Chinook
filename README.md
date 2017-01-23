![Build Status](https://travis-ci.org/LSRobotics/Chinook.svg?branch=master)
[![Gitter chat](https://badges.gitter.im/gitterHQ/gitter.png)](https://gitter.im/LSRobotics/public?utm_source=share-link&utm_medium=link&utm_campaign=share-link)
<br>

![chinook_copter](https://upload.wikimedia.org/wikipedia/commons/thumb/0/03/CH-47_Chinook_helicopter_flyby.jpg/1280px-CH-47_Chinook_helicopter_flyby.jpg)
<br>Source: Wikipedia article: Chinook.
# Chinook
2017 Robot.

## To contribute
Do not commit directly to this repository. To contribute, create a fork, and submit a pull request. We use reviewable.io to review PRs, and two contributors with push access must be required for one PR to pass: one issueing a LGTM, the other merging the PR into the master branch. Finally, Travis-CI is used to check whether the build passes.

## To Build
 - An installed WPILib is required for this project; the WPILib directory must be that installed by Eclipse plugin: `~/wpilib`.
 - The FRC cross-gcc toolchains is also required.
 - `CMakeLists.txt` is only used to force CLion to correctly perform data-flow analysis, not for build; to build, use the makefile: `make all` or simply `make`.

## C++ Code Guide

**Primary Guideline**: Always favor performance and efficiency over terseness; always favor terseness over readability; always favor readability over other needs.

### DOs
 - Use `BumpyCaps` naming method for **public methods** within a class and class names;
 - Use `BumpyCaps` for `enum` hacks and struct names;
 - For custom types, add the use `BumpyCaps_t`-style naming;
 - Use `camelCase` naming method for any C++-specific implementations, e.g. class-variables, private methods, methods utilizing the STL, etc.
 - For C-compliant or C-style functions and variables, use the `c_style_all_lowercase_underscore_naming_method`.
 - Use enum hacks, `const static` variables and even unions instead of macros.
 - Prefer streams over C-style stdlib functions;
 - Always use object allocation on the heap;
 - Try avoiding use of C-style `char *`s but use `std::string`
 - Prefer procedual functions over singletons
 - The less Object-Oriented, the better;
 - However, when OO makes things easier, use OO.
 
### DONTs
 - Never use Hungarian Notation. Too verbose.
 - Never use a macro, except in rare cases where a macro can significantly boost efficiency and reduce overheads.
 - Never allocate objects ON THE HEAP
 - Use C-style dynamic memory allocations ONLY WHEN other solutions are dreaded out
 - Pointers to malloc'd spaces and arrays ARE NOT THE SAME THING
 - DO NOT try to make everything objects.
 
 ## Primary contributors
  - Alex Fang
  - Tyler Liu
 
 ## License
  GNU GPL v3. TL;DR: If you use this code or modify this code you must open-source it under the same license.
