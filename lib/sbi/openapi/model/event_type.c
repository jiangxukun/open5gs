
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "event_type.h"

char* OpenAPI_event_type_ToString(OpenAPI_event_type_e event_type)
{
    const char *event_typeArray[] =  { "NULL", "LOSS_OF_CONNECTIVITY", "UE_REACHABILITY_FOR_DATA", "UE_REACHABILITY_FOR_SMS", "LOCATION_REPORTING", "CHANGE_OF_SUPI_PEI_ASSOCIATION", "ROAMING_STATUS", "COMMUNICATION_FAILURE", "AVAILABILITY_AFTER_DDN_FAILURE", "CN_TYPE_CHANGE", "DL_DATA_DELIVERY_STATUS", "PDN_CONNECTIVITY_STATUS", "UE_CONNECTION_MANAGEMENT_STATE", "ACCESS_TYPE_REPORT", "REGISTRATION_STATE_REPORT", "CONNECTIVITY_STATE_REPORT", "TYPE_ALLOCATION_CODE_REPORT", "FREQUENT_MOBILITY_REGISTRATION_REPORT", "PDU_SES_REL", "PDU_SES_EST", "UE_MEMORY_AVAILABLE_FOR_SMS" };
    size_t sizeofArray = sizeof(event_typeArray) / sizeof(event_typeArray[0]);
    if (event_type < sizeofArray)
        return (char *)event_typeArray[event_type];
    else
        return (char *)"Unknown";
}

OpenAPI_event_type_e OpenAPI_event_type_FromString(char* event_type)
{
    int stringToReturn = 0;
    const char *event_typeArray[] =  { "NULL", "LOSS_OF_CONNECTIVITY", "UE_REACHABILITY_FOR_DATA", "UE_REACHABILITY_FOR_SMS", "LOCATION_REPORTING", "CHANGE_OF_SUPI_PEI_ASSOCIATION", "ROAMING_STATUS", "COMMUNICATION_FAILURE", "AVAILABILITY_AFTER_DDN_FAILURE", "CN_TYPE_CHANGE", "DL_DATA_DELIVERY_STATUS", "PDN_CONNECTIVITY_STATUS", "UE_CONNECTION_MANAGEMENT_STATE", "ACCESS_TYPE_REPORT", "REGISTRATION_STATE_REPORT", "CONNECTIVITY_STATE_REPORT", "TYPE_ALLOCATION_CODE_REPORT", "FREQUENT_MOBILITY_REGISTRATION_REPORT", "PDU_SES_REL", "PDU_SES_EST", "UE_MEMORY_AVAILABLE_FOR_SMS" };
    size_t sizeofArray = sizeof(event_typeArray) / sizeof(event_typeArray[0]);
    while (stringToReturn < sizeofArray) {
        if (strcmp(event_type, event_typeArray[stringToReturn]) == 0) {
            return stringToReturn;
        }
        stringToReturn++;
    }
    return 0;
}

