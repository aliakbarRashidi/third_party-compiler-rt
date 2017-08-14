//===-- scudo_tls_fuchsia.inc -----------------------------------*- C++ -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
///
/// Scudo thread local structure fastpath functions implementation for Fuchsia.
///
//===----------------------------------------------------------------------===//

#ifndef SCUDO_TLS_FUCHSIA_H_
#define SCUDO_TLS_FUCHSIA_H_

#ifndef SCUDO_TLS_H_
# error "This file must be included inside scudo_tls.h."
#endif  // SCUDO_TLS_H_

#if SANITIZER_FUCHSIA

extern pthread_key_t PThreadKey;

ALWAYS_INLINE void initThreadMaybe() {
  if (pthread_getspecific(PThreadKey) == NULL) {
    (void)pthread_setspecific(PThreadKey, (void *)1);
    initThread();
  }
}

ALWAYS_INLINE ScudoThreadContext *getThreadContextAndLock() {
  return nullptr;
}

#endif  // SANITIZER_FUCHSIA

#endif  // SCUDO_TLS_FUCHSIA_H_
