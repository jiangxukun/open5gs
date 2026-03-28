/*
 * event_type.h
 *
 * 
 */

#ifndef _OpenAPI_event_type_H_
#define _OpenAPI_event_type_H_

#include <string.h>
#include "../external/cJSON.h"
#include "../include/list.h"
#include "../include/keyValuePair.h"
#include "../include/binary.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef enum { OpenAPI_event_type_NULL = 0, OpenAPI_event_type_LOSS_OF_CONNECTIVITY, OpenAPI_event_type_UE_REACHABILITY_FOR_DATA, OpenAPI_event_type_UE_REACHABILITY_FOR_SMS, OpenAPI_event_type_LOCATION_REPORTING, OpenAPI_event_type_CHANGE_OF_SUPI_PEI_ASSOCIATION, OpenAPI_event_type_ROAMING_STATUS, OpenAPI_event_type_COMMUNICATION_FAILURE, OpenAPI_event_type_AVAILABILITY_AFTER_DDN_FAILURE, OpenAPI_event_type_CN_TYPE_CHANGE, OpenAPI_event_type_DL_DATA_DELIVERY_STATUS, OpenAPI_event_type_PDN_CONNECTIVITY_STATUS, OpenAPI_event_type_UE_CONNECTION_MANAGEMENT_STATE, OpenAPI_event_type_ACCESS_TYPE_REPORT, OpenAPI_event_type_REGISTRATION_STATE_REPORT, OpenAPI_event_type_CONNECTIVITY_STATE_REPORT, OpenAPI_event_type_TYPE_ALLOCATION_CODE_REPORT, OpenAPI_event_type_FREQUENT_MOBILITY_REGISTRATION_REPORT, OpenAPI_event_type_PDU_SES_REL, OpenAPI_event_type_PDU_SES_EST, OpenAPI_event_type_UE_MEMORY_AVAILABLE_FOR_SMS } OpenAPI_event_type_e;

char* OpenAPI_event_type_ToString(OpenAPI_event_type_e event_type);

OpenAPI_event_type_e OpenAPI_event_type_FromString(char* event_type);

#ifdef __cplusplus
}
#endif

#endif /* _OpenAPI_event_type_H_ */

