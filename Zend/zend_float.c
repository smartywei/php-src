/*
   +----------------------------------------------------------------------+
   | Zend Engine                                                          |
   +----------------------------------------------------------------------+
   | Copyright (c) 1998-2018 Zend Technologies Ltd. (http://www.zend.com) |
   +----------------------------------------------------------------------+
   | This source file is subject to version 2.00 of the Zend license,     |
   | that is bundled with this package in the file LICENSE, and is        |
   | available through the world-wide-web at the following url:           |
   | http://www.zend.com/license/2_00.txt.                                |
   | If you did not receive a copy of the Zend license and are unable to  |
   | obtain it through the world-wide-web, please send a note to          |
   | license@zend.com so we can mail you a copy immediately.              |
   +----------------------------------------------------------------------+
   | Authors: Christian Seiler <chris_se@gmx.net>                         |
   +----------------------------------------------------------------------+
*/

/* $Id$ */

#include "zend.h"
#include "zend_compile.h"
#include "zend_float.h"

ZEND_API void zend_init_fpu(void) /* {{{ */
{
#if XPFPA_HAVE_CW
	XPFPA_DECLARE

	if (!EG(saved_fpu_cw_ptr)) {
		EG(saved_fpu_cw_ptr) = (void*)&EG(saved_fpu_cw);
	}
	XPFPA_STORE_CW(EG(saved_fpu_cw_ptr));
	XPFPA_SWITCH_DOUBLE();
#else
	EG(saved_fpu_cw_ptr) = NULL;
#endif
}
/* }}} */

ZEND_API void zend_shutdown_fpu(void) /* {{{ */
{
#if XPFPA_HAVE_CW
	if (EG(saved_fpu_cw_ptr)) {
		XPFPA_RESTORE_CW(EG(saved_fpu_cw_ptr));
	}
#endif
	EG(saved_fpu_cw_ptr) = NULL;
}
/* }}} */

ZEND_API void zend_ensure_fpu_mode(void) /* {{{ */
{
	XPFPA_DECLARE

	XPFPA_SWITCH_DOUBLE();
}
/* }}} */

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * indent-tabs-mode: t
 * End:
 * vim600: sw=4 ts=4 fdm=marker
 * vim<600: sw=4 ts=4
 */
