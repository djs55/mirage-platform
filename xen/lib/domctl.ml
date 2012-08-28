(*
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
 *)

(* The domctl interface is not part of the xen guest ABI but rather is
   intended to be used by a matching set of tools. The exact definitino
   is kept in the C header, we defer to that rather than parsing the
   data ourselves with cstruct *)

module Xen_domctl_getdomaininfo = struct
	(* A projection of the xen_domctl_getdomaininfo record. *)
	type t = {
		domid: int;
		dying: bool;
		shutdown: bool;
	}
end

external getdomaininfo: int -> Xen_domctl_getdomaininfo.t option = "caml_domctl_getdomaininfo"

