/*
   +----------------------------------------------------------------------+
   | PHP Version 5                                                        |
   +----------------------------------------------------------------------+
   | Copyright (c) 1997-2011 The PHP Group                                |
   +----------------------------------------------------------------------+
   | This source file is subject to version 3.01 of the PHP license,      |
   | that is bundled with this package in the file LICENSE, and is        |
   | available through the world-wide-web at the following url:           |
   | http://www.php.net/license/3_01.txt                                  |
   | If you did not receive a copy of the PHP license and are unable to   |
   | obtain it through the world-wide-web, please send a note to          |
   | license@php.net so we can mail you a copy immediately.               |
   +----------------------------------------------------------------------+
   | Author: Rasmus Lerdorf <rasmus@lerdorf.on.ca>                        |
   +----------------------------------------------------------------------+
 */

/* $Id: safe_mode.c 306939 2011-01-01 02:19:59Z felipe $ */

#include "php.h"

#include <stdio.h>
#include <stdlib.h>

#if HAVE_UNISTD_H
#include <unistd.h>
#endif
#include <sys/stat.h>
#include "ext/standard/pageinfo.h"
#include "safe_mode.h"
#include "SAPI.h"
#include "php_globals.h"


PHPAPI char *php_get_current_user(void)
{
	struct stat *pstat;
	TSRMLS_FETCH();

	if (SG(request_info).current_user) {
		return SG(request_info).current_user;
	}

	/* FIXME: I need to have this somehow handled if
	USE_SAPI is defined, because cgi will also be
	interfaced in USE_SAPI */

	pstat = sapi_get_stat(TSRMLS_C);

	if (!pstat) {
		return "";
	} else {
#ifdef PHP_WIN32
		char name[256];
		DWORD len = sizeof(name)-1;

		if (!GetUserName(name, &len)) {
			return "";
		}
		name[len] = '\0';
		SG(request_info).current_user_length = len;
		SG(request_info).current_user = estrndup(name, len);
		return SG(request_info).current_user;		
#else
		struct passwd *pwd;
#if defined(ZTS) && defined(HAVE_GETPWUID_R) && defined(_SC_GETPW_R_SIZE_MAX)
		struct passwd _pw;
		struct passwd *retpwptr = NULL;
		int pwbuflen = sysconf(_SC_GETPW_R_SIZE_MAX);
		char *pwbuf;

		if (pwbuflen < 1) {
			return "";
		}
		pwbuf = emalloc(pwbuflen);
		if (getpwuid_r(pstat->st_uid, &_pw, pwbuf, pwbuflen, &retpwptr) != 0) {
			efree(pwbuf);
			return "";
		}
		pwd = &_pw;
#else
		if ((pwd=getpwuid(pstat->st_uid))==NULL) {
			return "";
		}
#endif
		SG(request_info).current_user_length = strlen(pwd->pw_name);
		SG(request_info).current_user = estrndup(pwd->pw_name, SG(request_info).current_user_length);
#if defined(ZTS) && defined(HAVE_GETPWUID_R) && defined(_SC_GETPW_R_SIZE_MAX)
		efree(pwbuf);
#endif
		return SG(request_info).current_user;		
#endif
	}	
}	

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: sw=4 ts=4 fdm=marker
 * vim<600: sw=4 ts=4
 */
