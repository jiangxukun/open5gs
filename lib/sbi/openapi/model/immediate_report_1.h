/*
 * immediate_report_1.h
 *
 * 
 */

#ifndef _OpenAPI_immediate_report_1_H_
#define _OpenAPI_immediate_report_1_H_

#include <string.h>
#include "../external/cJSON.h"
#include "../include/list.h"
#include "../include/keyValuePair.h"
#include "../include/binary.h"
typedef struct OpenAPI_immediate_report_1_s OpenAPI_immediate_report_1_t;
#include "shared_data_1.h"
#include "subscription_data_sets_1.h"

#ifdef __cplusplus
extern "C" {
#endif

struct OpenAPI_immediate_report_1_s {
    struct OpenAPI_subscription_data_sets_1_s *subscription_data_sets;
    OpenAPI_list_t *shared_data_list;
};

OpenAPI_immediate_report_1_t *OpenAPI_immediate_report_1_create(
    OpenAPI_subscription_data_sets_1_t *subscription_data_sets,
    OpenAPI_list_t *shared_data_list
);
void OpenAPI_immediate_report_1_free(OpenAPI_immediate_report_1_t *immediate_report_1);
OpenAPI_immediate_report_1_t *OpenAPI_immediate_report_1_parseFromJSON(cJSON *immediate_report_1JSON);
cJSON *OpenAPI_immediate_report_1_convertToJSON(OpenAPI_immediate_report_1_t *immediate_report_1);
OpenAPI_immediate_report_1_t *OpenAPI_immediate_report_1_copy(OpenAPI_immediate_report_1_t *dst, OpenAPI_immediate_report_1_t *src);

#ifdef __cplusplus
}
#endif

#endif /* _OpenAPI_immediate_report_1_H_ */

