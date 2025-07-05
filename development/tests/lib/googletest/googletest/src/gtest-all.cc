// Copyright 2005, Google Inc.
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are
// met:
//
//     * Redistributions of source code must retain the above copyright
// notice, this list of conditions and the following disclaimer.
//     * Redistributions in binary form must reproduce the above
// copyright notice, this list of conditions and the following disclaimer
// in the documentation and/or other materials provided with the
// distribution.
//     * Neither the name of Google Inc. nor the names of its
// contributors may be used to endorse or promote products derived from
// this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
// OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

// This file is a part of the Google C++ Testing and Mocking Framework.
// It is used ONCE PER TEST PROGRAM to compile the GTest library.

// GOOGLETEST_CM0001 DO NOT DELETE

// This is a placeholder for gtest-all.cc.
// In a real Google Test distribution, this file includes many other .cc files
// to build the library. For our minimal, manually created version, this
// will be very simple. It might define some of the static members or globals
// that are declared in our minimal gtest.h.

#include "gtest/gtest.h" // Should be development/tests/lib/googletest/googletest/include/gtest/gtest.h

// Definition for static members from the minimal gtest.h
testing::internal::UnitTest* testing::internal::UnitTest::instance_ = nullptr;

// In a full gtest-all.cc, you'd have:
// #include "src/gtest.cc"
// #include "src/gtest-death-test.cc"
// #include "src/gtest-filepath.cc"
// #include "src/gtest-port.cc"
// #include "src/gtest-printers.cc"
// #include "src/gtest-test-part.cc"
// #include "src/gtest-typed-test.cc"
//
// But we are creating a very stripped-down version.
// The minimal gtest.h provided tries to define most things inline or
// relies on very simple behavior that doesn't need a lot of .cc file definitions.

// The InitGoogleTest and RUN_ALL_TESTS are already defined inline in the minimal gtest.h.
// The AssertHelper and Message classes are also defined inline for simplicity.
// The Test and TestInfo classes are mostly declarations with TestFactoryImpl for TEST macro.

// So, this file might actually be nearly empty for our placeholder version,
// as long as gtest.h is self-contained enough.
// Let's add a simple function to ensure this file is compiled and linked.
void GTestMinimalAllCc() {}
