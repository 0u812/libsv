/* -*- Mode: c; c-basic-offset: 2 -*-
 *
 * option.c - Options
 *
 * Copyright (C) 2009-2015, Dave Beckett http://www.dajobe.org/
 *
 * This package is Free Software
 *
 * It is licensed under the following three licenses as alternatives:
 *   1. GNU Lesser General Public License (LGPL) V2.1 or any newer version
 *   2. GNU General Public License (GPL) V2 or any newer version
 *   3. Apache License, V2.0 or any newer version
 *
 * You may not use this file except in compliance with at least one of
 * the above three licenses.
 *
 * See LICENSE.txt at the top of this package for the
 * complete terms and further detail along with the license texts for
 * the licenses in COPYING.LIB, COPYING and LICENSE-2.0.txt respectively.
 *
 */


#ifdef SV_CONFIG
#include <sv_config.h>
#endif

#include <stdarg.h>

#ifdef HAVE_STDLIB_H
#include <stdlib.h>
#endif

#include <sv.h>
#include "sv_internal.h"


static sv_status_t
sv_set_option_vararg(sv* t, sv_option_t option, va_list arg)
{
  sv_status_t status = SV_STATUS_OK;

  switch(option) {
    case SV_OPTION_SAVE_HEADER:
      t->flags &= ~SV_FLAGS_SAVE_HEADER;
      if(va_arg(arg, long))
        t->flags |= SV_FLAGS_SAVE_HEADER;
      break;

    case SV_OPTION_BAD_DATA_ERROR:
      t->flags &= ~SV_FLAGS_BAD_DATA_ERROR;
      if(va_arg(arg, long))
        t->flags |= SV_FLAGS_BAD_DATA_ERROR;
      break;

    case SV_OPTION_QUOTED_FIELDS:
      t->flags &= ~SV_FLAGS_QUOTED_FIELDS;
      if(va_arg(arg, long))
        t->flags |= SV_FLAGS_QUOTED_FIELDS;
      break;

    case SV_OPTION_STRIP_WHITESPACE:
      t->flags &= ~SV_FLAGS_STRIP_WHITESPACE;
      if(va_arg(arg, long))
        t->flags |= SV_FLAGS_STRIP_WHITESPACE;
      break;

    case SV_OPTION_QUOTE_CHAR:
      if(1) {
        int c = va_arg(arg, int);
        if(c != t->field_sep)
          t->quote_char = c;
      }
      break;

    case SV_OPTION_LINE_CALLBACK:
      if(1) {
        sv_line_callback cb = (sv_line_callback)va_arg(arg, void*);
        t->line_callback = cb;
      }
      break;

    default:
    case SV_OPTION_NONE:
      status = SV_STATUS_FAILED;
      break;

  }

  return status;
}


/**
 * sv_set_option:
 * @t: sv object
 * @option: option name
 *
 * Set an option value.  The value varies in type dependent on the @option
 *
 * Return value: #SV_STATUS_FAILED if failed
 */
sv_status_t
sv_set_option(sv *t, sv_option_t option, ...)
{
  sv_status_t status;
  va_list arg;

  va_start(arg, option);
  status = sv_set_option_vararg(t, option, arg);
  va_end(arg);

  return status;
}
