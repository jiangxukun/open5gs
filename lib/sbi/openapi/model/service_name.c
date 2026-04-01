
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "service_name.h"

char* OpenAPI_service_name_ToString(OpenAPI_service_name_e service_name)
{
    const char *service_nameArray[] =  { "NULL", "nnrf-nfm", "nnrf-disc", "nnrf-oauth2", "nudm-sdm", "nudm-uecm", "nudm-ueau", "nudm-ee", "nudm-pp", "nudm-niddau", "nudm-mt", "nudm-ssau", "nudm-rsds", "namf-comm", "namf-evts", "namf-mt", "namf-loc", "namf-mbs-comm", "namf-mbs-bc", "nsmf-pdusession", "nsmf-event-exposure", "nsmf-nidd", "nausf-auth", "nausf-sorprotection", "nausf-upuprotection", "nnef-pfdmanagement", "nnef-smcontext", "nnef-eventexposure", "nnef-eas-deployment-info", "3gpp-cp-parameter-provisioning", "3gpp-device-triggering", "3gpp-bdt", "3gpp-traffic-influence", "3gpp-chargeable-party", "3gpp-as-session-with-qos", "3gpp-msisdn-less-mo-sms", "3gpp-service-parameter", "3gpp-monitoring-event", "3gpp-nidd-configuration-trigger", "3gpp-nidd", "3gpp-analyticsexposure", "3gpp-racs-parameter-provisioning", "3gpp-ecr-control", "3gpp-applying-bdt-policy", "3gpp-mo-lcs-notify", "3gpp-time-sync", "3gpp-am-influence", "3gpp-am-policyauthorization", "3gpp-akma", "3gpp-eas-deployment", "3gpp-iptvconfiguration", "3gpp-mbs-tmgi", "3gpp-mbs-session", "3gpp-authentication", "3gpp-asti", "npcf-am-policy-control", "npcf-smpolicycontrol", "npcf-policyauthorization", "npcf-bdtpolicycontrol", "npcf-eventexposure", "npcf-ue-policy-control", "npcf-am-policyauthorization", "nsmsf-sms", "nnssf-nsselection", "nnssf-nssaiavailability", "nudr-dr", "nudr-group-id-map", "nlmf-loc", "n5g-eir-eic", "nbsf-management", "nchf-spendinglimitcontrol", "nchf-convergedcharging", "nchf-offlineonlycharging", "nnwdaf-eventssubscription", "nnwdaf-analyticsinfo", "nnwdaf-datamanagement", "nnwdaf-mlmodelprovision", "ngmlc-loc", "nucmf-provisioning", "nucmf-uecapabilitymanagement", "nhss-sdm", "nhss-uecm", "nhss-ueau", "nhss-ee", "nhss-ims-sdm", "nhss-ims-uecm", "nhss-ims-ueau", "nhss-gba-sdm", "nhss-gba-ueau", "nsepp-telescopic", "nsoraf-sor", "nspaf-secured-packet", "nudsf-dr", "nudsf-timer", "nnssaaf-nssaa", "nnssaaf-aiw", "naanf-akma", "n5gddnmf-discovery", "nmfaf-3dadm", "nmfaf-3cadm", "neasdf-dnscontext", "neasdf-baselinednspattern", "ndccf-dm", "ndccf-cm", "nnsacf-nsac", "nnsacf-slice-ee", "nmbsmf-tmgi", "nmbsmf-mbssession", "nadrf-dm", "nbsp-gba", "ntsctsf-time-sync", "ntsctsf-qos-tscai", "ntsctsf-asti", "npkmf-keyreq", "nmnpf-npstatus", "niwmsc-smservice", "nmbsf-mbsuserserv", "nmbsf-mbsuserdataing", "nmbstf-distsession", "npanf-prosekey" };
    size_t sizeofArray = sizeof(service_nameArray) / sizeof(service_nameArray[0]);
    if (service_name < sizeofArray)
        return (char *)service_nameArray[service_name];
    else
        return (char *)"Unknown";
}

OpenAPI_service_name_e OpenAPI_service_name_FromString(char* service_name)
{
    int stringToReturn = 0;
    const char *service_nameArray[] =  { "NULL", "nnrf-nfm", "nnrf-disc", "nnrf-oauth2", "nudm-sdm", "nudm-uecm", "nudm-ueau", "nudm-ee", "nudm-pp", "nudm-niddau", "nudm-mt", "nudm-ssau", "nudm-rsds", "namf-comm", "namf-evts", "namf-mt", "namf-loc", "namf-mbs-comm", "namf-mbs-bc", "nsmf-pdusession", "nsmf-event-exposure", "nsmf-nidd", "nausf-auth", "nausf-sorprotection", "nausf-upuprotection", "nnef-pfdmanagement", "nnef-smcontext", "nnef-eventexposure", "nnef-eas-deployment-info", "3gpp-cp-parameter-provisioning", "3gpp-device-triggering", "3gpp-bdt", "3gpp-traffic-influence", "3gpp-chargeable-party", "3gpp-as-session-with-qos", "3gpp-msisdn-less-mo-sms", "3gpp-service-parameter", "3gpp-monitoring-event", "3gpp-nidd-configuration-trigger", "3gpp-nidd", "3gpp-analyticsexposure", "3gpp-racs-parameter-provisioning", "3gpp-ecr-control", "3gpp-applying-bdt-policy", "3gpp-mo-lcs-notify", "3gpp-time-sync", "3gpp-am-influence", "3gpp-am-policyauthorization", "3gpp-akma", "3gpp-eas-deployment", "3gpp-iptvconfiguration", "3gpp-mbs-tmgi", "3gpp-mbs-session", "3gpp-authentication", "3gpp-asti", "npcf-am-policy-control", "npcf-smpolicycontrol", "npcf-policyauthorization", "npcf-bdtpolicycontrol", "npcf-eventexposure", "npcf-ue-policy-control", "npcf-am-policyauthorization", "nsmsf-sms", "nnssf-nsselection", "nnssf-nssaiavailability", "nudr-dr", "nudr-group-id-map", "nlmf-loc", "n5g-eir-eic", "nbsf-management", "nchf-spendinglimitcontrol", "nchf-convergedcharging", "nchf-offlineonlycharging", "nnwdaf-eventssubscription", "nnwdaf-analyticsinfo", "nnwdaf-datamanagement", "nnwdaf-mlmodelprovision", "ngmlc-loc", "nucmf-provisioning", "nucmf-uecapabilitymanagement", "nhss-sdm", "nhss-uecm", "nhss-ueau", "nhss-ee", "nhss-ims-sdm", "nhss-ims-uecm", "nhss-ims-ueau", "nhss-gba-sdm", "nhss-gba-ueau", "nsepp-telescopic", "nsoraf-sor", "nspaf-secured-packet", "nudsf-dr", "nudsf-timer", "nnssaaf-nssaa", "nnssaaf-aiw", "naanf-akma", "n5gddnmf-discovery", "nmfaf-3dadm", "nmfaf-3cadm", "neasdf-dnscontext", "neasdf-baselinednspattern", "ndccf-dm", "ndccf-cm", "nnsacf-nsac", "nnsacf-slice-ee", "nmbsmf-tmgi", "nmbsmf-mbssession", "nadrf-dm", "nbsp-gba", "ntsctsf-time-sync", "ntsctsf-qos-tscai", "ntsctsf-asti", "npkmf-keyreq", "nmnpf-npstatus", "niwmsc-smservice", "nmbsf-mbsuserserv", "nmbsf-mbsuserdataing", "nmbstf-distsession", "npanf-prosekey" };
    size_t sizeofArray = sizeof(service_nameArray) / sizeof(service_nameArray[0]);
    while (stringToReturn < sizeofArray) {
        if (strcmp(service_name, service_nameArray[stringToReturn]) == 0) {
            return stringToReturn;
        }
        stringToReturn++;
    }
    return 0;
}

