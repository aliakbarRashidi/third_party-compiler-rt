//===-- scudo_tls_fuchsia.cpp -----------------------------------*- C++ -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
///
/// Scudo thread local structure implementation for Android.
///
//===----------------------------------------------------------------------===//

#include "sanitizer_common/sanitizer_platform.h"

#if SANITIZER_FUCHSIA

#include "scudo_tls.h"

#include <pthread.h>

namespace __scudo {

static pthread_once_t GlobalInitialized = PTHREAD_ONCE_INIT;
pthread_key_t PThreadKey;

static void initOnce() {
  CHECK_EQ(pthread_key_create(&PThreadKey, NULL), 0);
  initScudo();
}

void initThread() {
  pthread_once(&GlobalInitialized, initOnce);
}

}  // namespace __scudo

#endif  // SANITIZER_FUCHSIA
