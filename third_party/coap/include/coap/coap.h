/* -*- Mode: C; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 * -*- */

/* coap.h -- main header file for CoAP stack
 *
 * Copyright (C) 2010-2012,2015 Olaf Bergmann <bergmann@tzi.org>
 *               2015 Carsten Schoenert <c.schoenert@t-online.de>
 *
 * This file is part of the CoAP library libcoap. Please see README for
 * terms of use.
 */

#ifndef _COAP_H_
#define _COAP_H_

/* Define the address where bug reports for libcoap should be sent. */
#define LIBCOAP_PACKAGE_BUGREPORT libcoap-developers@lists.sourceforge.net

/* Define the full name of libcoap. */
#define LIBCOAP_PACKAGE_NAME libcoap

/* Define the full name and version of libcoap. */
#define LIBCOAP_PACKAGE_STRING libcoap 4.1.2

/* Define the home page for libcoap. */
#define LIBCOAP_PACKAGE_URL http://libcoap.sourceforge.net/

/* Define the version of libcoap this file belongs to. */
#define LIBCOAP_PACKAGE_VERSION 4.1.2

#ifdef __cplusplus
extern "C" {
#endif

#include "address.h"
#include "async.h"
#include "bits.h"
#include "block.h"
#include "coap_io.h"
#include "coap_time.h"
#include "debug.h"
#include "encode.h"
#include "mem.h"
#include "net.h"
#include "option.h"
#include "pdu.h"
#include "prng.h"
#include "resource.h"
#include "str.h"
#include "subscribe.h"
#include "t_list.h"
#include "uri.h"
#include "uthash.h"
#include "utlist.h"

#ifdef __cplusplus
}
#endif

#endif /* _COAP_H_ */
