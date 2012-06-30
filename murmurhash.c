/*
  +----------------------------------------------------------------------+
  | PHP Version 5                                                        |
  +----------------------------------------------------------------------+
  | Copyright (c) 1997-2008 The PHP Group                                |
  +----------------------------------------------------------------------+
  | This source file is subject to version 3.01 of the PHP license,      |
  | that is bundled with this package in the file LICENSE, and is        |
  | available through the world-wide-web at the following url:           |
  | http://www.php.net/license/3_01.txt                                  |
  | If you did not receive a copy of the PHP license and are unable to   |
  | obtain it through the world-wide-web, please send a note to          |
  | license@php.net so we can mail you a copy immediately.               |
  +----------------------------------------------------------------------+
  | Author:                                                              |
  +----------------------------------------------------------------------+
*/

/* $Id: header 252479 2008-02-07 19:39:50Z iliaa $ */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_ini.h"
#include "ext/standard/info.h"
#include "php_murmurhash.h"

#include "MurmurHash2.cpp"

/* If you declare any globals in php_murmurhash.h uncomment this:
ZEND_DECLARE_MODULE_GLOBALS(murmurhash)
*/

/* True global resources - no need for thread safety here */
static int le_murmurhash;

/* {{{ murmurhash_functions[]
 *
 * Every user visible function must have an entry in murmurhash_functions[].
 */
const zend_function_entry murmurhash_functions[] = {
	PHP_FE(murmurhash,	NULL)
	{NULL, NULL, NULL}	/* Must be the last line in murmurhash_functions[] */
};
/* }}} */

/* {{{ murmurhash_module_entry
 */
zend_module_entry murmurhash_module_entry = {
#if ZEND_MODULE_API_NO >= 20010901
	STANDARD_MODULE_HEADER,
#endif
	"murmurhash",
	murmurhash_functions,
	NULL,//PHP_MINIT(murmurhash),
	NULL,//PHP_MSHUTDOWN(murmurhash),
	NULL,//PHP_RINIT(murmurhash),		/* Replace with NULL if there's nothing to do at request start */
	NULL,//PHP_RSHUTDOWN(murmurhash),	/* Replace with NULL if there's nothing to do at request end */
	NULL,//PHP_MINFO(murmurhash),
#if ZEND_MODULE_API_NO >= 20010901
	"0.1", /* Replace with version number for your extension */
#endif
	STANDARD_MODULE_PROPERTIES
};
/* }}} */

#ifdef COMPILE_DL_MURMURHASH
ZEND_GET_MODULE(murmurhash)
#endif

/* {{{ PHP_INI
 */
/* Remove comments and fill if you need to have entries in php.ini
PHP_INI_BEGIN()
    STD_PHP_INI_ENTRY("murmurhash.global_value",      "42", PHP_INI_ALL, OnUpdateLong, global_value, zend_murmurhash_globals, murmurhash_globals)
    STD_PHP_INI_ENTRY("murmurhash.global_string", "foobar", PHP_INI_ALL, OnUpdateString, global_string, zend_murmurhash_globals, murmurhash_globals)
PHP_INI_END()
*/
/* }}} */

/* {{{ php_murmurhash_init_globals
 */
/* Uncomment this function if you have INI entries
static void php_murmurhash_init_globals(zend_murmurhash_globals *murmurhash_globals)
{
	murmurhash_globals->global_value = 0;
	murmurhash_globals->global_string = NULL;
}
*/
/* }}} */

/* {{{ PHP_MINIT_FUNCTION
 */
PHP_MINIT_FUNCTION(murmurhash)
{
	/* If you have INI entries, uncomment these lines 
	REGISTER_INI_ENTRIES();
	*/
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MSHUTDOWN_FUNCTION
 */
PHP_MSHUTDOWN_FUNCTION(murmurhash)
{
	/* uncomment this line if you have INI entries
	UNREGISTER_INI_ENTRIES();
	*/
	return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request start */
/* {{{ PHP_RINIT_FUNCTION
 */
PHP_RINIT_FUNCTION(murmurhash)
{
	return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request end */
/* {{{ PHP_RSHUTDOWN_FUNCTION
 */
PHP_RSHUTDOWN_FUNCTION(murmurhash)
{
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MINFO_FUNCTION
 */
PHP_MINFO_FUNCTION(murmurhash)
{
	php_info_print_table_start();
	php_info_print_table_header(2, "murmurhash support", "enabled");
	php_info_print_table_end();

	/* Remove comments if you have entries in php.ini
	DISPLAY_INI_ENTRIES();
	*/
}
/* }}} */

PHP_FUNCTION(murmurhash)
{
	char *arg = NULL;
	int arg_len, len;
    long seed = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s|l", &arg, &arg_len, &seed) == FAILURE) {
		return;
	}

	if (arg == NULL || arg_len <= 0) {
		php_error_docref(NULL TSRMLS_CC, E_WARNING, "argument length is too short." );
		RETURN_NULL();
	}

	RETURN_LONG(MurmurHash2(arg, arg_len, seed));
}



/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
