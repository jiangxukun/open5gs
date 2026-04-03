/*
 * prose_service_auth_1.h
 *
 * Indicates whether the UE is authorized to use ProSe Direct Discovery, ProSe Direct Communication, or both. 
 */

#ifndef _OpenAPI_prose_service_auth_1_H_
#define _OpenAPI_prose_service_auth_1_H_

#include <string.h>
#include "../external/cJSON.h"
#include "../include/list.h"
#include "../include/keyValuePair.h"
#include "../include/binary.h"
typedef struct OpenAPI_prose_service_auth_1_s OpenAPI_prose_service_auth_1_t;
#include "ue_auth.h"

#ifdef __cplusplus
extern "C" {
#endif

struct OpenAPI_prose_service_auth_1_s {
    OpenAPI_ue_auth_e prose_direct_discovery_auth;
    OpenAPI_ue_auth_e prose_direct_communication_auth;
};

OpenAPI_prose_service_auth_1_t *OpenAPI_prose_service_auth_1_create(
    OpenAPI_ue_auth_e prose_direct_discovery_auth,
    OpenAPI_ue_auth_e prose_direct_communication_auth
);
void OpenAPI_prose_service_auth_1_free(OpenAPI_prose_service_auth_1_t *prose_service_auth_1);
OpenAPI_prose_service_auth_1_t *OpenAPI_prose_service_auth_1_parseFromJSON(cJSON *prose_service_auth_1JSON);
cJSON *OpenAPI_prose_service_auth_1_convertToJSON(OpenAPI_prose_service_auth_1_t *prose_service_auth_1);
OpenAPI_prose_service_auth_1_t *OpenAPI_prose_service_auth_1_copy(OpenAPI_prose_service_auth_1_t *dst, OpenAPI_prose_service_auth_1_t *src);

#ifdef __cplusplus
}
#endif

#endif /* _OpenAPI_prose_service_auth_1_H_ */

