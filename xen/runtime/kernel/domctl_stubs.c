/*
 * Copyright (c) 2012 Citrix Systems Inc
 *
 * Permission to use, copy, modify, and distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */
#define __XEN_TOOLS__

#include <mini-os/x86/os.h>
#include <mini-os/mm.h>
#include <mini-os/gnttab.h>

#include <caml/mlvalues.h>
#include <caml/memory.h>
#include <caml/alloc.h>
#include <caml/custom.h>
#include <caml/fail.h>
#include <caml/callback.h>
#include <caml/bigarray.h>

#include <log.h>
#include <errno.h>

#include <xen/xen.h>
#include <xen/arch-x86/xen.h>
#include <xen/domctl.h>

CAMLprim value
caml_domctl_getdomaininfo(value v_domid)
{
  CAMLparam1(v_domid);
  CAMLlocal2(ret, tmp);

  ret = Val_int(0); /* None */

  struct xen_domctl domctl;
  domctl.cmd = XEN_DOMCTL_getdomaininfo;
  domctl.u.getdomaininfo.domain = Int_val(v_domid);

  int r = HYPERVISOR_domctl((unsigned long) &domctl);
  if (r == -EACCES){
	printk("ERROR: getdomaininfo returned EACCES. Is a suitable XSM policy configured?\n");
	goto out;
  }
  if (r != 0){
	printk("getdomaininfo(%x, %d) returned %d", &domctl, Int_val(v_domid), r);
	goto out;
  }

  tmp = caml_alloc_tuple(3);
  Store_field(tmp, 0, v_domid);
  Store_field(tmp, 1, Val_bool(domctl.u.getdomaininfo.flags & XEN_DOMINF_dying));
  Store_field(tmp, 2, Val_bool(domctl.u.getdomaininfo.flags & XEN_DOMINF_shutdown));

  ret = caml_alloc_tuple(1); /* Some */
  Store_field(ret, 0, tmp);

 out:
  CAMLreturn(ret);
}
