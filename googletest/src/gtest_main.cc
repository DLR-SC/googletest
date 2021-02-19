// Copyright 2006, Google Inc.
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

#if GTEST_HAS_MPI
// Some MPI vendors require mpi.h to be included before anything else.
#include <mpi.h>
#endif // GTEST_HAS_MPI

#include <stdio.h>

#include "gtest/gtest.h"

GTEST_API_ int main(int argc, char **argv) {
#if GTEST_HAS_MPI
  if( MPI_Init(&argc, &argv) != MPI_SUCCESS )
  {
    GTEST_LOG_(ERROR) << "Error calling MPI_Init!\n";

    return 1;
  }
#endif
  printf("Running main() from gtest_main.cc\n");
  testing::InitGoogleTest(&argc, argv);
  int result = RUN_ALL_TESTS();
#if GTEST_HAS_MPI
  if( MPI_Finalize() != MPI_SUCCESS )
  {
    GTEST_LOG_(ERROR) << "Error calling MPI_Finalize!\n";
    return 1;
  }
#endif
  // Warning: this return value may get lost when executed with MPI
  return result;
}
