---
name: Bug report
about: Create a report to help us improve
title: ''
labels: ''
assignees: ''

---

**Describe the bug**
> A minimal compilable example of that features the bug.

#### main.cpp
    int main()
    {
        // Action to reproduce bug.
    }

> A description of how to build and run the code

    g++ -std=c++14 -I/usr/local/include -L/usr/local/lib -lThorSerialize17 main.cpp
    cat stuff | ./a.out

**Expected behavior**
> A clear and concise description of what you expected to happen.

**Environment:**
 - OS:
> uname -a
Darwin Host.local 18.5.0 Darwin Kernel Version 18.5.0: Mon Mar 11 20:40:32 PDT 2019; root:xnu-4903.251.3~3/RELEASE_X86_64 x86_64

 - Compiler and Version
> g++ --version
Configured with: --prefix=/Applications/Xcode.app/Contents/Developer/usr --with-gxx-include-dir=/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX10.14.sdk/usr/include/c++/4.2.1
Apple LLVM version 10.0.1 (clang-1001.0.46.3)
Target: x86_64-apple-darwin18.5.0
Thread model: posix
InstalledDir: /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin

**Additional context**
> Add any other context about the problem here.
