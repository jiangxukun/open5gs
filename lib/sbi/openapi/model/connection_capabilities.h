/*
 * connection_capabilities.h
 *
 * 
 */

#ifndef _OpenAPI_connection_capabilities_H_
#define _OpenAPI_connection_capabilities_H_

#include <string.h>
#include "../external/cJSON.h"
#include "../include/list.h"
#include "../include/keyValuePair.h"
#include "../include/binary.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef enum { OpenAPI_connection_capabilities_NULL = 0, OpenAPI_connection_capabilities_IMS, OpenAPI_connection_capabilities_MMS, OpenAPI_connection_capabilities_SUPL, OpenAPI_connection_capabilities_INTERNET } OpenAPI_connection_capabilities_e;

char* OpenAPI_connection_capabilities_ToString(OpenAPI_connection_capabilities_e connection_capabilities);

OpenAPI_connection_capabilities_e OpenAPI_connection_capabilities_FromString(char* connection_capabilities);

#ifdef __cplusplus
}
#endif

#endif /* _OpenAPI_connection_capabilities_H_ */

