/*
 * network_area_info_3.h
 *
 * Describes a network area information in which the NF service consumer requests the number of UEs. 
 */

#ifndef _OpenAPI_network_area_info_3_H_
#define _OpenAPI_network_area_info_3_H_

#include <string.h>
#include "../external/cJSON.h"
#include "../include/list.h"
#include "../include/keyValuePair.h"
#include "../include/binary.h"
#include "ecgi_1.h"
#include "global_ran_node_id_1.h"
#include "ncgi_1.h"
#include "tai_1.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct OpenAPI_network_area_info_3_s OpenAPI_network_area_info_3_t;
typedef struct OpenAPI_network_area_info_3_s {
    OpenAPI_list_t *ecgis;
    OpenAPI_list_t *ncgis;
    OpenAPI_list_t *g_ran_node_ids;
    OpenAPI_list_t *tais;
} OpenAPI_network_area_info_3_t;

OpenAPI_network_area_info_3_t *OpenAPI_network_area_info_3_create(
    OpenAPI_list_t *ecgis,
    OpenAPI_list_t *ncgis,
    OpenAPI_list_t *g_ran_node_ids,
    OpenAPI_list_t *tais
);
void OpenAPI_network_area_info_3_free(OpenAPI_network_area_info_3_t *network_area_info_3);
OpenAPI_network_area_info_3_t *OpenAPI_network_area_info_3_parseFromJSON(cJSON *network_area_info_3JSON);
cJSON *OpenAPI_network_area_info_3_convertToJSON(OpenAPI_network_area_info_3_t *network_area_info_3);
OpenAPI_network_area_info_3_t *OpenAPI_network_area_info_3_copy(OpenAPI_network_area_info_3_t *dst, OpenAPI_network_area_info_3_t *src);

#ifdef __cplusplus
}
#endif

#endif /* _OpenAPI_network_area_info_3_H_ */

