
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "_application_data_influence_data_subs_to_notify_post_request_inner.h"

OpenAPI__application_data_influence_data_subs_to_notify_post_request_inner_t *OpenAPI__application_data_influence_data_subs_to_notify_post_request_inner_create(
    char *up_path_chg_notif_corre_id,
    bool is_app_relo_ind,
    int app_relo_ind,
    char *af_app_id,
    char *dnn,
    OpenAPI_list_t *eth_traffic_filters,
    OpenAPI_snssai_t *snssai,
    char *inter_group_id,
    char *supi,
    OpenAPI_list_t *traffic_filters,
    OpenAPI_list_t *traffic_routes,
    bool is_traff_corre_ind,
    int traff_corre_ind,
    char *valid_start_time,
    char *valid_end_time,
    OpenAPI_list_t *temp_validities,
    OpenAPI_network_area_info_1_t *nw_area_info,
    char *up_path_chg_notif_uri,
    OpenAPI_list_t *headers,
    OpenAPI_list_t *subscribed_events,
    OpenAPI_dnai_change_type_e dnai_chg_type,
    bool is_af_ack_ind,
    int af_ack_ind,
    bool is_addr_preser_ind,
    int addr_preser_ind,
    bool is_max_allowed_up_lat,
    int max_allowed_up_lat,
    bool is_sim_conn_ind,
    int sim_conn_ind,
    bool is_sim_conn_term,
    int sim_conn_term,
    char *supported_features,
    char *res_uri,
    OpenAPI_list_t *reset_ids,
    OpenAPI_traffic_influ_data_t *traffic_influ_data
)
{
    OpenAPI__application_data_influence_data_subs_to_notify_post_request_inner_t *_application_data_influence_data_subs_to_notify_post_request_inner_local_var = ogs_malloc(sizeof(OpenAPI__application_data_influence_data_subs_to_notify_post_request_inner_t));
    ogs_assert(_application_data_influence_data_subs_to_notify_post_request_inner_local_var);

    _application_data_influence_data_subs_to_notify_post_request_inner_local_var->up_path_chg_notif_corre_id = up_path_chg_notif_corre_id;
    _application_data_influence_data_subs_to_notify_post_request_inner_local_var->is_app_relo_ind = is_app_relo_ind;
    _application_data_influence_data_subs_to_notify_post_request_inner_local_var->app_relo_ind = app_relo_ind;
    _application_data_influence_data_subs_to_notify_post_request_inner_local_var->af_app_id = af_app_id;
    _application_data_influence_data_subs_to_notify_post_request_inner_local_var->dnn = dnn;
    _application_data_influence_data_subs_to_notify_post_request_inner_local_var->eth_traffic_filters = eth_traffic_filters;
    _application_data_influence_data_subs_to_notify_post_request_inner_local_var->snssai = snssai;
    _application_data_influence_data_subs_to_notify_post_request_inner_local_var->inter_group_id = inter_group_id;
    _application_data_influence_data_subs_to_notify_post_request_inner_local_var->supi = supi;
    _application_data_influence_data_subs_to_notify_post_request_inner_local_var->traffic_filters = traffic_filters;
    _application_data_influence_data_subs_to_notify_post_request_inner_local_var->traffic_routes = traffic_routes;
    _application_data_influence_data_subs_to_notify_post_request_inner_local_var->is_traff_corre_ind = is_traff_corre_ind;
    _application_data_influence_data_subs_to_notify_post_request_inner_local_var->traff_corre_ind = traff_corre_ind;
    _application_data_influence_data_subs_to_notify_post_request_inner_local_var->valid_start_time = valid_start_time;
    _application_data_influence_data_subs_to_notify_post_request_inner_local_var->valid_end_time = valid_end_time;
    _application_data_influence_data_subs_to_notify_post_request_inner_local_var->temp_validities = temp_validities;
    _application_data_influence_data_subs_to_notify_post_request_inner_local_var->nw_area_info = nw_area_info;
    _application_data_influence_data_subs_to_notify_post_request_inner_local_var->up_path_chg_notif_uri = up_path_chg_notif_uri;
    _application_data_influence_data_subs_to_notify_post_request_inner_local_var->headers = headers;
    _application_data_influence_data_subs_to_notify_post_request_inner_local_var->subscribed_events = subscribed_events;
    _application_data_influence_data_subs_to_notify_post_request_inner_local_var->dnai_chg_type = dnai_chg_type;
    _application_data_influence_data_subs_to_notify_post_request_inner_local_var->is_af_ack_ind = is_af_ack_ind;
    _application_data_influence_data_subs_to_notify_post_request_inner_local_var->af_ack_ind = af_ack_ind;
    _application_data_influence_data_subs_to_notify_post_request_inner_local_var->is_addr_preser_ind = is_addr_preser_ind;
    _application_data_influence_data_subs_to_notify_post_request_inner_local_var->addr_preser_ind = addr_preser_ind;
    _application_data_influence_data_subs_to_notify_post_request_inner_local_var->is_max_allowed_up_lat = is_max_allowed_up_lat;
    _application_data_influence_data_subs_to_notify_post_request_inner_local_var->max_allowed_up_lat = max_allowed_up_lat;
    _application_data_influence_data_subs_to_notify_post_request_inner_local_var->is_sim_conn_ind = is_sim_conn_ind;
    _application_data_influence_data_subs_to_notify_post_request_inner_local_var->sim_conn_ind = sim_conn_ind;
    _application_data_influence_data_subs_to_notify_post_request_inner_local_var->is_sim_conn_term = is_sim_conn_term;
    _application_data_influence_data_subs_to_notify_post_request_inner_local_var->sim_conn_term = sim_conn_term;
    _application_data_influence_data_subs_to_notify_post_request_inner_local_var->supported_features = supported_features;
    _application_data_influence_data_subs_to_notify_post_request_inner_local_var->res_uri = res_uri;
    _application_data_influence_data_subs_to_notify_post_request_inner_local_var->reset_ids = reset_ids;
    _application_data_influence_data_subs_to_notify_post_request_inner_local_var->traffic_influ_data = traffic_influ_data;

    return _application_data_influence_data_subs_to_notify_post_request_inner_local_var;
}

void OpenAPI__application_data_influence_data_subs_to_notify_post_request_inner_free(OpenAPI__application_data_influence_data_subs_to_notify_post_request_inner_t *_application_data_influence_data_subs_to_notify_post_request_inner)
{
    OpenAPI_lnode_t *node = NULL;

    if (NULL == _application_data_influence_data_subs_to_notify_post_request_inner) {
        return;
    }
    if (_application_data_influence_data_subs_to_notify_post_request_inner->up_path_chg_notif_corre_id) {
        ogs_free(_application_data_influence_data_subs_to_notify_post_request_inner->up_path_chg_notif_corre_id);
        _application_data_influence_data_subs_to_notify_post_request_inner->up_path_chg_notif_corre_id = NULL;
    }
    if (_application_data_influence_data_subs_to_notify_post_request_inner->af_app_id) {
        ogs_free(_application_data_influence_data_subs_to_notify_post_request_inner->af_app_id);
        _application_data_influence_data_subs_to_notify_post_request_inner->af_app_id = NULL;
    }
    if (_application_data_influence_data_subs_to_notify_post_request_inner->dnn) {
        ogs_free(_application_data_influence_data_subs_to_notify_post_request_inner->dnn);
        _application_data_influence_data_subs_to_notify_post_request_inner->dnn = NULL;
    }
    if (_application_data_influence_data_subs_to_notify_post_request_inner->eth_traffic_filters) {
        OpenAPI_list_for_each(_application_data_influence_data_subs_to_notify_post_request_inner->eth_traffic_filters, node) {
            OpenAPI_eth_flow_description_free(node->data);
        }
        OpenAPI_list_free(_application_data_influence_data_subs_to_notify_post_request_inner->eth_traffic_filters);
        _application_data_influence_data_subs_to_notify_post_request_inner->eth_traffic_filters = NULL;
    }
    if (_application_data_influence_data_subs_to_notify_post_request_inner->snssai) {
        OpenAPI_snssai_free(_application_data_influence_data_subs_to_notify_post_request_inner->snssai);
        _application_data_influence_data_subs_to_notify_post_request_inner->snssai = NULL;
    }
    if (_application_data_influence_data_subs_to_notify_post_request_inner->inter_group_id) {
        ogs_free(_application_data_influence_data_subs_to_notify_post_request_inner->inter_group_id);
        _application_data_influence_data_subs_to_notify_post_request_inner->inter_group_id = NULL;
    }
    if (_application_data_influence_data_subs_to_notify_post_request_inner->supi) {
        ogs_free(_application_data_influence_data_subs_to_notify_post_request_inner->supi);
        _application_data_influence_data_subs_to_notify_post_request_inner->supi = NULL;
    }
    if (_application_data_influence_data_subs_to_notify_post_request_inner->traffic_filters) {
        OpenAPI_list_for_each(_application_data_influence_data_subs_to_notify_post_request_inner->traffic_filters, node) {
            OpenAPI_flow_info_free(node->data);
        }
        OpenAPI_list_free(_application_data_influence_data_subs_to_notify_post_request_inner->traffic_filters);
        _application_data_influence_data_subs_to_notify_post_request_inner->traffic_filters = NULL;
    }
    if (_application_data_influence_data_subs_to_notify_post_request_inner->traffic_routes) {
        OpenAPI_list_for_each(_application_data_influence_data_subs_to_notify_post_request_inner->traffic_routes, node) {
            OpenAPI_route_to_location_free(node->data);
        }
        OpenAPI_list_free(_application_data_influence_data_subs_to_notify_post_request_inner->traffic_routes);
        _application_data_influence_data_subs_to_notify_post_request_inner->traffic_routes = NULL;
    }
    if (_application_data_influence_data_subs_to_notify_post_request_inner->valid_start_time) {
        ogs_free(_application_data_influence_data_subs_to_notify_post_request_inner->valid_start_time);
        _application_data_influence_data_subs_to_notify_post_request_inner->valid_start_time = NULL;
    }
    if (_application_data_influence_data_subs_to_notify_post_request_inner->valid_end_time) {
        ogs_free(_application_data_influence_data_subs_to_notify_post_request_inner->valid_end_time);
        _application_data_influence_data_subs_to_notify_post_request_inner->valid_end_time = NULL;
    }
    if (_application_data_influence_data_subs_to_notify_post_request_inner->temp_validities) {
        OpenAPI_list_for_each(_application_data_influence_data_subs_to_notify_post_request_inner->temp_validities, node) {
            OpenAPI_temporal_validity_free(node->data);
        }
        OpenAPI_list_free(_application_data_influence_data_subs_to_notify_post_request_inner->temp_validities);
        _application_data_influence_data_subs_to_notify_post_request_inner->temp_validities = NULL;
    }
    if (_application_data_influence_data_subs_to_notify_post_request_inner->nw_area_info) {
        OpenAPI_network_area_info_1_free(_application_data_influence_data_subs_to_notify_post_request_inner->nw_area_info);
        _application_data_influence_data_subs_to_notify_post_request_inner->nw_area_info = NULL;
    }
    if (_application_data_influence_data_subs_to_notify_post_request_inner->up_path_chg_notif_uri) {
        ogs_free(_application_data_influence_data_subs_to_notify_post_request_inner->up_path_chg_notif_uri);
        _application_data_influence_data_subs_to_notify_post_request_inner->up_path_chg_notif_uri = NULL;
    }
    if (_application_data_influence_data_subs_to_notify_post_request_inner->headers) {
        OpenAPI_list_for_each(_application_data_influence_data_subs_to_notify_post_request_inner->headers, node) {
            ogs_free(node->data);
        }
        OpenAPI_list_free(_application_data_influence_data_subs_to_notify_post_request_inner->headers);
        _application_data_influence_data_subs_to_notify_post_request_inner->headers = NULL;
    }
    if (_application_data_influence_data_subs_to_notify_post_request_inner->subscribed_events) {
        OpenAPI_list_free(_application_data_influence_data_subs_to_notify_post_request_inner->subscribed_events);
        _application_data_influence_data_subs_to_notify_post_request_inner->subscribed_events = NULL;
    }
    if (_application_data_influence_data_subs_to_notify_post_request_inner->supported_features) {
        ogs_free(_application_data_influence_data_subs_to_notify_post_request_inner->supported_features);
        _application_data_influence_data_subs_to_notify_post_request_inner->supported_features = NULL;
    }
    if (_application_data_influence_data_subs_to_notify_post_request_inner->res_uri) {
        ogs_free(_application_data_influence_data_subs_to_notify_post_request_inner->res_uri);
        _application_data_influence_data_subs_to_notify_post_request_inner->res_uri = NULL;
    }
    if (_application_data_influence_data_subs_to_notify_post_request_inner->reset_ids) {
        OpenAPI_list_for_each(_application_data_influence_data_subs_to_notify_post_request_inner->reset_ids, node) {
            ogs_free(node->data);
        }
        OpenAPI_list_free(_application_data_influence_data_subs_to_notify_post_request_inner->reset_ids);
        _application_data_influence_data_subs_to_notify_post_request_inner->reset_ids = NULL;
    }
    if (_application_data_influence_data_subs_to_notify_post_request_inner->traffic_influ_data) {
        OpenAPI_traffic_influ_data_free(_application_data_influence_data_subs_to_notify_post_request_inner->traffic_influ_data);
        _application_data_influence_data_subs_to_notify_post_request_inner->traffic_influ_data = NULL;
    }
    ogs_free(_application_data_influence_data_subs_to_notify_post_request_inner);
}

cJSON *OpenAPI__application_data_influence_data_subs_to_notify_post_request_inner_convertToJSON(OpenAPI__application_data_influence_data_subs_to_notify_post_request_inner_t *_application_data_influence_data_subs_to_notify_post_request_inner)
{
    cJSON *item = NULL;
    OpenAPI_lnode_t *node = NULL;

    if (_application_data_influence_data_subs_to_notify_post_request_inner == NULL) {
        ogs_error("OpenAPI__application_data_influence_data_subs_to_notify_post_request_inner_convertToJSON() failed [_application_data_influenceData_subs_to_notify_post_request_inner]");
        return NULL;
    }

    item = cJSON_CreateObject();
    if (_application_data_influence_data_subs_to_notify_post_request_inner->up_path_chg_notif_corre_id) {
    if (cJSON_AddStringToObject(item, "upPathChgNotifCorreId", _application_data_influence_data_subs_to_notify_post_request_inner->up_path_chg_notif_corre_id) == NULL) {
        ogs_error("OpenAPI__application_data_influence_data_subs_to_notify_post_request_inner_convertToJSON() failed [up_path_chg_notif_corre_id]");
        goto end;
    }
    }

    if (_application_data_influence_data_subs_to_notify_post_request_inner->is_app_relo_ind) {
    if (cJSON_AddBoolToObject(item, "appReloInd", _application_data_influence_data_subs_to_notify_post_request_inner->app_relo_ind) == NULL) {
        ogs_error("OpenAPI__application_data_influence_data_subs_to_notify_post_request_inner_convertToJSON() failed [app_relo_ind]");
        goto end;
    }
    }

    if (_application_data_influence_data_subs_to_notify_post_request_inner->af_app_id) {
    if (cJSON_AddStringToObject(item, "afAppId", _application_data_influence_data_subs_to_notify_post_request_inner->af_app_id) == NULL) {
        ogs_error("OpenAPI__application_data_influence_data_subs_to_notify_post_request_inner_convertToJSON() failed [af_app_id]");
        goto end;
    }
    }

    if (_application_data_influence_data_subs_to_notify_post_request_inner->dnn) {
    if (cJSON_AddStringToObject(item, "dnn", _application_data_influence_data_subs_to_notify_post_request_inner->dnn) == NULL) {
        ogs_error("OpenAPI__application_data_influence_data_subs_to_notify_post_request_inner_convertToJSON() failed [dnn]");
        goto end;
    }
    }

    if (_application_data_influence_data_subs_to_notify_post_request_inner->eth_traffic_filters) {
    cJSON *eth_traffic_filtersList = cJSON_AddArrayToObject(item, "ethTrafficFilters");
    if (eth_traffic_filtersList == NULL) {
        ogs_error("OpenAPI__application_data_influence_data_subs_to_notify_post_request_inner_convertToJSON() failed [eth_traffic_filters]");
        goto end;
    }
    OpenAPI_list_for_each(_application_data_influence_data_subs_to_notify_post_request_inner->eth_traffic_filters, node) {
        cJSON *itemLocal = OpenAPI_eth_flow_description_convertToJSON(node->data);
        if (itemLocal == NULL) {
            ogs_error("OpenAPI__application_data_influence_data_subs_to_notify_post_request_inner_convertToJSON() failed [eth_traffic_filters]");
            goto end;
        }
        cJSON_AddItemToArray(eth_traffic_filtersList, itemLocal);
    }
    }

    if (_application_data_influence_data_subs_to_notify_post_request_inner->snssai) {
    cJSON *snssai_local_JSON = OpenAPI_snssai_convertToJSON(_application_data_influence_data_subs_to_notify_post_request_inner->snssai);
    if (snssai_local_JSON == NULL) {
        ogs_error("OpenAPI__application_data_influence_data_subs_to_notify_post_request_inner_convertToJSON() failed [snssai]");
        goto end;
    }
    cJSON_AddItemToObject(item, "snssai", snssai_local_JSON);
    if (item->child == NULL) {
        ogs_error("OpenAPI__application_data_influence_data_subs_to_notify_post_request_inner_convertToJSON() failed [snssai]");
        goto end;
    }
    }

    if (_application_data_influence_data_subs_to_notify_post_request_inner->inter_group_id) {
    if (cJSON_AddStringToObject(item, "interGroupId", _application_data_influence_data_subs_to_notify_post_request_inner->inter_group_id) == NULL) {
        ogs_error("OpenAPI__application_data_influence_data_subs_to_notify_post_request_inner_convertToJSON() failed [inter_group_id]");
        goto end;
    }
    }

    if (_application_data_influence_data_subs_to_notify_post_request_inner->supi) {
    if (cJSON_AddStringToObject(item, "supi", _application_data_influence_data_subs_to_notify_post_request_inner->supi) == NULL) {
        ogs_error("OpenAPI__application_data_influence_data_subs_to_notify_post_request_inner_convertToJSON() failed [supi]");
        goto end;
    }
    }

    if (_application_data_influence_data_subs_to_notify_post_request_inner->traffic_filters) {
    cJSON *traffic_filtersList = cJSON_AddArrayToObject(item, "trafficFilters");
    if (traffic_filtersList == NULL) {
        ogs_error("OpenAPI__application_data_influence_data_subs_to_notify_post_request_inner_convertToJSON() failed [traffic_filters]");
        goto end;
    }
    OpenAPI_list_for_each(_application_data_influence_data_subs_to_notify_post_request_inner->traffic_filters, node) {
        cJSON *itemLocal = OpenAPI_flow_info_convertToJSON(node->data);
        if (itemLocal == NULL) {
            ogs_error("OpenAPI__application_data_influence_data_subs_to_notify_post_request_inner_convertToJSON() failed [traffic_filters]");
            goto end;
        }
        cJSON_AddItemToArray(traffic_filtersList, itemLocal);
    }
    }

    if (_application_data_influence_data_subs_to_notify_post_request_inner->traffic_routes) {
    cJSON *traffic_routesList = cJSON_AddArrayToObject(item, "trafficRoutes");
    if (traffic_routesList == NULL) {
        ogs_error("OpenAPI__application_data_influence_data_subs_to_notify_post_request_inner_convertToJSON() failed [traffic_routes]");
        goto end;
    }
    OpenAPI_list_for_each(_application_data_influence_data_subs_to_notify_post_request_inner->traffic_routes, node) {
        cJSON *itemLocal = OpenAPI_route_to_location_convertToJSON(node->data);
        if (itemLocal == NULL) {
            ogs_error("OpenAPI__application_data_influence_data_subs_to_notify_post_request_inner_convertToJSON() failed [traffic_routes]");
            goto end;
        }
        cJSON_AddItemToArray(traffic_routesList, itemLocal);
    }
    }

    if (_application_data_influence_data_subs_to_notify_post_request_inner->is_traff_corre_ind) {
    if (cJSON_AddBoolToObject(item, "traffCorreInd", _application_data_influence_data_subs_to_notify_post_request_inner->traff_corre_ind) == NULL) {
        ogs_error("OpenAPI__application_data_influence_data_subs_to_notify_post_request_inner_convertToJSON() failed [traff_corre_ind]");
        goto end;
    }
    }

    if (_application_data_influence_data_subs_to_notify_post_request_inner->valid_start_time) {
    if (cJSON_AddStringToObject(item, "validStartTime", _application_data_influence_data_subs_to_notify_post_request_inner->valid_start_time) == NULL) {
        ogs_error("OpenAPI__application_data_influence_data_subs_to_notify_post_request_inner_convertToJSON() failed [valid_start_time]");
        goto end;
    }
    }

    if (_application_data_influence_data_subs_to_notify_post_request_inner->valid_end_time) {
    if (cJSON_AddStringToObject(item, "validEndTime", _application_data_influence_data_subs_to_notify_post_request_inner->valid_end_time) == NULL) {
        ogs_error("OpenAPI__application_data_influence_data_subs_to_notify_post_request_inner_convertToJSON() failed [valid_end_time]");
        goto end;
    }
    }

    if (_application_data_influence_data_subs_to_notify_post_request_inner->temp_validities) {
    cJSON *temp_validitiesList = cJSON_AddArrayToObject(item, "tempValidities");
    if (temp_validitiesList == NULL) {
        ogs_error("OpenAPI__application_data_influence_data_subs_to_notify_post_request_inner_convertToJSON() failed [temp_validities]");
        goto end;
    }
    OpenAPI_list_for_each(_application_data_influence_data_subs_to_notify_post_request_inner->temp_validities, node) {
        cJSON *itemLocal = OpenAPI_temporal_validity_convertToJSON(node->data);
        if (itemLocal == NULL) {
            ogs_error("OpenAPI__application_data_influence_data_subs_to_notify_post_request_inner_convertToJSON() failed [temp_validities]");
            goto end;
        }
        cJSON_AddItemToArray(temp_validitiesList, itemLocal);
    }
    }

    if (_application_data_influence_data_subs_to_notify_post_request_inner->nw_area_info) {
    cJSON *nw_area_info_local_JSON = OpenAPI_network_area_info_1_convertToJSON(_application_data_influence_data_subs_to_notify_post_request_inner->nw_area_info);
    if (nw_area_info_local_JSON == NULL) {
        ogs_error("OpenAPI__application_data_influence_data_subs_to_notify_post_request_inner_convertToJSON() failed [nw_area_info]");
        goto end;
    }
    cJSON_AddItemToObject(item, "nwAreaInfo", nw_area_info_local_JSON);
    if (item->child == NULL) {
        ogs_error("OpenAPI__application_data_influence_data_subs_to_notify_post_request_inner_convertToJSON() failed [nw_area_info]");
        goto end;
    }
    }

    if (_application_data_influence_data_subs_to_notify_post_request_inner->up_path_chg_notif_uri) {
    if (cJSON_AddStringToObject(item, "upPathChgNotifUri", _application_data_influence_data_subs_to_notify_post_request_inner->up_path_chg_notif_uri) == NULL) {
        ogs_error("OpenAPI__application_data_influence_data_subs_to_notify_post_request_inner_convertToJSON() failed [up_path_chg_notif_uri]");
        goto end;
    }
    }

    if (_application_data_influence_data_subs_to_notify_post_request_inner->headers) {
    cJSON *headersList = cJSON_AddArrayToObject(item, "headers");
    if (headersList == NULL) {
        ogs_error("OpenAPI__application_data_influence_data_subs_to_notify_post_request_inner_convertToJSON() failed [headers]");
        goto end;
    }
    OpenAPI_list_for_each(_application_data_influence_data_subs_to_notify_post_request_inner->headers, node) {
        if (cJSON_AddStringToObject(headersList, "", (char*)node->data) == NULL) {
            ogs_error("OpenAPI__application_data_influence_data_subs_to_notify_post_request_inner_convertToJSON() failed [headers]");
            goto end;
        }
    }
    }

    if (_application_data_influence_data_subs_to_notify_post_request_inner->subscribed_events != OpenAPI_subscribed_event_NULL) {
    cJSON *subscribed_eventsList = cJSON_AddArrayToObject(item, "subscribedEvents");
    if (subscribed_eventsList == NULL) {
        ogs_error("OpenAPI__application_data_influence_data_subs_to_notify_post_request_inner_convertToJSON() failed [subscribed_events]");
        goto end;
    }
    OpenAPI_list_for_each(_application_data_influence_data_subs_to_notify_post_request_inner->subscribed_events, node) {
        if (cJSON_AddStringToObject(subscribed_eventsList, "", OpenAPI_subscribed_event_ToString((intptr_t)node->data)) == NULL) {
            ogs_error("OpenAPI__application_data_influence_data_subs_to_notify_post_request_inner_convertToJSON() failed [subscribed_events]");
            goto end;
        }
    }
    }

    if (_application_data_influence_data_subs_to_notify_post_request_inner->dnai_chg_type != OpenAPI_dnai_change_type_NULL) {
    if (cJSON_AddStringToObject(item, "dnaiChgType", OpenAPI_dnai_change_type_ToString(_application_data_influence_data_subs_to_notify_post_request_inner->dnai_chg_type)) == NULL) {
        ogs_error("OpenAPI__application_data_influence_data_subs_to_notify_post_request_inner_convertToJSON() failed [dnai_chg_type]");
        goto end;
    }
    }

    if (_application_data_influence_data_subs_to_notify_post_request_inner->is_af_ack_ind) {
    if (cJSON_AddBoolToObject(item, "afAckInd", _application_data_influence_data_subs_to_notify_post_request_inner->af_ack_ind) == NULL) {
        ogs_error("OpenAPI__application_data_influence_data_subs_to_notify_post_request_inner_convertToJSON() failed [af_ack_ind]");
        goto end;
    }
    }

    if (_application_data_influence_data_subs_to_notify_post_request_inner->is_addr_preser_ind) {
    if (cJSON_AddBoolToObject(item, "addrPreserInd", _application_data_influence_data_subs_to_notify_post_request_inner->addr_preser_ind) == NULL) {
        ogs_error("OpenAPI__application_data_influence_data_subs_to_notify_post_request_inner_convertToJSON() failed [addr_preser_ind]");
        goto end;
    }
    }

    if (_application_data_influence_data_subs_to_notify_post_request_inner->is_max_allowed_up_lat) {
    if (cJSON_AddNumberToObject(item, "maxAllowedUpLat", _application_data_influence_data_subs_to_notify_post_request_inner->max_allowed_up_lat) == NULL) {
        ogs_error("OpenAPI__application_data_influence_data_subs_to_notify_post_request_inner_convertToJSON() failed [max_allowed_up_lat]");
        goto end;
    }
    }

    if (_application_data_influence_data_subs_to_notify_post_request_inner->is_sim_conn_ind) {
    if (cJSON_AddBoolToObject(item, "simConnInd", _application_data_influence_data_subs_to_notify_post_request_inner->sim_conn_ind) == NULL) {
        ogs_error("OpenAPI__application_data_influence_data_subs_to_notify_post_request_inner_convertToJSON() failed [sim_conn_ind]");
        goto end;
    }
    }

    if (_application_data_influence_data_subs_to_notify_post_request_inner->is_sim_conn_term) {
    if (cJSON_AddNumberToObject(item, "simConnTerm", _application_data_influence_data_subs_to_notify_post_request_inner->sim_conn_term) == NULL) {
        ogs_error("OpenAPI__application_data_influence_data_subs_to_notify_post_request_inner_convertToJSON() failed [sim_conn_term]");
        goto end;
    }
    }

    if (_application_data_influence_data_subs_to_notify_post_request_inner->supported_features) {
    if (cJSON_AddStringToObject(item, "supportedFeatures", _application_data_influence_data_subs_to_notify_post_request_inner->supported_features) == NULL) {
        ogs_error("OpenAPI__application_data_influence_data_subs_to_notify_post_request_inner_convertToJSON() failed [supported_features]");
        goto end;
    }
    }

    if (_application_data_influence_data_subs_to_notify_post_request_inner->res_uri) {
    if (cJSON_AddStringToObject(item, "resUri", _application_data_influence_data_subs_to_notify_post_request_inner->res_uri) == NULL) {
        ogs_error("OpenAPI__application_data_influence_data_subs_to_notify_post_request_inner_convertToJSON() failed [res_uri]");
        goto end;
    }
    }

    if (_application_data_influence_data_subs_to_notify_post_request_inner->reset_ids) {
    cJSON *reset_idsList = cJSON_AddArrayToObject(item, "resetIds");
    if (reset_idsList == NULL) {
        ogs_error("OpenAPI__application_data_influence_data_subs_to_notify_post_request_inner_convertToJSON() failed [reset_ids]");
        goto end;
    }
    OpenAPI_list_for_each(_application_data_influence_data_subs_to_notify_post_request_inner->reset_ids, node) {
        if (cJSON_AddStringToObject(reset_idsList, "", (char*)node->data) == NULL) {
            ogs_error("OpenAPI__application_data_influence_data_subs_to_notify_post_request_inner_convertToJSON() failed [reset_ids]");
            goto end;
        }
    }
    }

    if (_application_data_influence_data_subs_to_notify_post_request_inner->traffic_influ_data) {
    cJSON *traffic_influ_data_local_JSON = OpenAPI_traffic_influ_data_convertToJSON(_application_data_influence_data_subs_to_notify_post_request_inner->traffic_influ_data);
    if (traffic_influ_data_local_JSON == NULL) {
        ogs_error("OpenAPI__application_data_influence_data_subs_to_notify_post_request_inner_convertToJSON() failed [traffic_influ_data]");
        goto end;
    }
    cJSON_AddItemToObject(item, "trafficInfluData", traffic_influ_data_local_JSON);
    if (item->child == NULL) {
        ogs_error("OpenAPI__application_data_influence_data_subs_to_notify_post_request_inner_convertToJSON() failed [traffic_influ_data]");
        goto end;
    }
    }

end:
    return item;
}

OpenAPI__application_data_influence_data_subs_to_notify_post_request_inner_t *OpenAPI__application_data_influence_data_subs_to_notify_post_request_inner_parseFromJSON(cJSON *_application_data_influence_data_subs_to_notify_post_request_innerJSON)
{
    OpenAPI__application_data_influence_data_subs_to_notify_post_request_inner_t *_application_data_influence_data_subs_to_notify_post_request_inner_local_var = NULL;
    OpenAPI_lnode_t *node = NULL;
    cJSON *up_path_chg_notif_corre_id = NULL;
    cJSON *app_relo_ind = NULL;
    cJSON *af_app_id = NULL;
    cJSON *dnn = NULL;
    cJSON *eth_traffic_filters = NULL;
    OpenAPI_list_t *eth_traffic_filtersList = NULL;
    cJSON *snssai = NULL;
    OpenAPI_snssai_t *snssai_local_nonprim = NULL;
    cJSON *inter_group_id = NULL;
    cJSON *supi = NULL;
    cJSON *traffic_filters = NULL;
    OpenAPI_list_t *traffic_filtersList = NULL;
    cJSON *traffic_routes = NULL;
    OpenAPI_list_t *traffic_routesList = NULL;
    cJSON *traff_corre_ind = NULL;
    cJSON *valid_start_time = NULL;
    cJSON *valid_end_time = NULL;
    cJSON *temp_validities = NULL;
    OpenAPI_list_t *temp_validitiesList = NULL;
    cJSON *nw_area_info = NULL;
    OpenAPI_network_area_info_1_t *nw_area_info_local_nonprim = NULL;
    cJSON *up_path_chg_notif_uri = NULL;
    cJSON *headers = NULL;
    OpenAPI_list_t *headersList = NULL;
    cJSON *subscribed_events = NULL;
    OpenAPI_list_t *subscribed_eventsList = NULL;
    cJSON *dnai_chg_type = NULL;
    OpenAPI_dnai_change_type_e dnai_chg_typeVariable = 0;
    cJSON *af_ack_ind = NULL;
    cJSON *addr_preser_ind = NULL;
    cJSON *max_allowed_up_lat = NULL;
    cJSON *sim_conn_ind = NULL;
    cJSON *sim_conn_term = NULL;
    cJSON *supported_features = NULL;
    cJSON *res_uri = NULL;
    cJSON *reset_ids = NULL;
    OpenAPI_list_t *reset_idsList = NULL;
    cJSON *traffic_influ_data = NULL;
    OpenAPI_traffic_influ_data_t *traffic_influ_data_local_nonprim = NULL;
    up_path_chg_notif_corre_id = cJSON_GetObjectItemCaseSensitive(_application_data_influence_data_subs_to_notify_post_request_innerJSON, "upPathChgNotifCorreId");
    if (up_path_chg_notif_corre_id) {
    if (!cJSON_IsString(up_path_chg_notif_corre_id) && !cJSON_IsNull(up_path_chg_notif_corre_id)) {
        ogs_error("OpenAPI__application_data_influence_data_subs_to_notify_post_request_inner_parseFromJSON() failed [up_path_chg_notif_corre_id]");
        goto end;
    }
    }

    app_relo_ind = cJSON_GetObjectItemCaseSensitive(_application_data_influence_data_subs_to_notify_post_request_innerJSON, "appReloInd");
    if (app_relo_ind) {
    if (!cJSON_IsBool(app_relo_ind)) {
        ogs_error("OpenAPI__application_data_influence_data_subs_to_notify_post_request_inner_parseFromJSON() failed [app_relo_ind]");
        goto end;
    }
    }

    af_app_id = cJSON_GetObjectItemCaseSensitive(_application_data_influence_data_subs_to_notify_post_request_innerJSON, "afAppId");
    if (af_app_id) {
    if (!cJSON_IsString(af_app_id) && !cJSON_IsNull(af_app_id)) {
        ogs_error("OpenAPI__application_data_influence_data_subs_to_notify_post_request_inner_parseFromJSON() failed [af_app_id]");
        goto end;
    }
    }

    dnn = cJSON_GetObjectItemCaseSensitive(_application_data_influence_data_subs_to_notify_post_request_innerJSON, "dnn");
    if (dnn) {
    if (!cJSON_IsString(dnn) && !cJSON_IsNull(dnn)) {
        ogs_error("OpenAPI__application_data_influence_data_subs_to_notify_post_request_inner_parseFromJSON() failed [dnn]");
        goto end;
    }
    }

    eth_traffic_filters = cJSON_GetObjectItemCaseSensitive(_application_data_influence_data_subs_to_notify_post_request_innerJSON, "ethTrafficFilters");
    if (eth_traffic_filters) {
        cJSON *eth_traffic_filters_local = NULL;
        if (!cJSON_IsArray(eth_traffic_filters)) {
            ogs_error("OpenAPI__application_data_influence_data_subs_to_notify_post_request_inner_parseFromJSON() failed [eth_traffic_filters]");
            goto end;
        }

        eth_traffic_filtersList = OpenAPI_list_create();

        cJSON_ArrayForEach(eth_traffic_filters_local, eth_traffic_filters) {
            if (!cJSON_IsObject(eth_traffic_filters_local)) {
                ogs_error("OpenAPI__application_data_influence_data_subs_to_notify_post_request_inner_parseFromJSON() failed [eth_traffic_filters]");
                goto end;
            }
            OpenAPI_eth_flow_description_t *eth_traffic_filtersItem = OpenAPI_eth_flow_description_parseFromJSON(eth_traffic_filters_local);
            if (!eth_traffic_filtersItem) {
                ogs_error("No eth_traffic_filtersItem");
                goto end;
            }
            OpenAPI_list_add(eth_traffic_filtersList, eth_traffic_filtersItem);
        }
    }

    snssai = cJSON_GetObjectItemCaseSensitive(_application_data_influence_data_subs_to_notify_post_request_innerJSON, "snssai");
    if (snssai) {
    snssai_local_nonprim = OpenAPI_snssai_parseFromJSON(snssai);
    if (!snssai_local_nonprim) {
        ogs_error("OpenAPI_snssai_parseFromJSON failed [snssai]");
        goto end;
    }
    }

    inter_group_id = cJSON_GetObjectItemCaseSensitive(_application_data_influence_data_subs_to_notify_post_request_innerJSON, "interGroupId");
    if (inter_group_id) {
    if (!cJSON_IsString(inter_group_id) && !cJSON_IsNull(inter_group_id)) {
        ogs_error("OpenAPI__application_data_influence_data_subs_to_notify_post_request_inner_parseFromJSON() failed [inter_group_id]");
        goto end;
    }
    }

    supi = cJSON_GetObjectItemCaseSensitive(_application_data_influence_data_subs_to_notify_post_request_innerJSON, "supi");
    if (supi) {
    if (!cJSON_IsString(supi) && !cJSON_IsNull(supi)) {
        ogs_error("OpenAPI__application_data_influence_data_subs_to_notify_post_request_inner_parseFromJSON() failed [supi]");
        goto end;
    }
    }

    traffic_filters = cJSON_GetObjectItemCaseSensitive(_application_data_influence_data_subs_to_notify_post_request_innerJSON, "trafficFilters");
    if (traffic_filters) {
        cJSON *traffic_filters_local = NULL;
        if (!cJSON_IsArray(traffic_filters)) {
            ogs_error("OpenAPI__application_data_influence_data_subs_to_notify_post_request_inner_parseFromJSON() failed [traffic_filters]");
            goto end;
        }

        traffic_filtersList = OpenAPI_list_create();

        cJSON_ArrayForEach(traffic_filters_local, traffic_filters) {
            if (!cJSON_IsObject(traffic_filters_local)) {
                ogs_error("OpenAPI__application_data_influence_data_subs_to_notify_post_request_inner_parseFromJSON() failed [traffic_filters]");
                goto end;
            }
            OpenAPI_flow_info_t *traffic_filtersItem = OpenAPI_flow_info_parseFromJSON(traffic_filters_local);
            if (!traffic_filtersItem) {
                ogs_error("No traffic_filtersItem");
                goto end;
            }
            OpenAPI_list_add(traffic_filtersList, traffic_filtersItem);
        }
    }

    traffic_routes = cJSON_GetObjectItemCaseSensitive(_application_data_influence_data_subs_to_notify_post_request_innerJSON, "trafficRoutes");
    if (traffic_routes) {
        cJSON *traffic_routes_local = NULL;
        if (!cJSON_IsArray(traffic_routes)) {
            ogs_error("OpenAPI__application_data_influence_data_subs_to_notify_post_request_inner_parseFromJSON() failed [traffic_routes]");
            goto end;
        }

        traffic_routesList = OpenAPI_list_create();

        cJSON_ArrayForEach(traffic_routes_local, traffic_routes) {
            if (!cJSON_IsObject(traffic_routes_local)) {
                ogs_error("OpenAPI__application_data_influence_data_subs_to_notify_post_request_inner_parseFromJSON() failed [traffic_routes]");
                goto end;
            }
            OpenAPI_route_to_location_t *traffic_routesItem = OpenAPI_route_to_location_parseFromJSON(traffic_routes_local);
            if (!traffic_routesItem) {
                ogs_error("No traffic_routesItem");
                goto end;
            }
            OpenAPI_list_add(traffic_routesList, traffic_routesItem);
        }
    }

    traff_corre_ind = cJSON_GetObjectItemCaseSensitive(_application_data_influence_data_subs_to_notify_post_request_innerJSON, "traffCorreInd");
    if (traff_corre_ind) {
    if (!cJSON_IsBool(traff_corre_ind)) {
        ogs_error("OpenAPI__application_data_influence_data_subs_to_notify_post_request_inner_parseFromJSON() failed [traff_corre_ind]");
        goto end;
    }
    }

    valid_start_time = cJSON_GetObjectItemCaseSensitive(_application_data_influence_data_subs_to_notify_post_request_innerJSON, "validStartTime");
    if (valid_start_time) {
    if (!cJSON_IsString(valid_start_time) && !cJSON_IsNull(valid_start_time)) {
        ogs_error("OpenAPI__application_data_influence_data_subs_to_notify_post_request_inner_parseFromJSON() failed [valid_start_time]");
        goto end;
    }
    }

    valid_end_time = cJSON_GetObjectItemCaseSensitive(_application_data_influence_data_subs_to_notify_post_request_innerJSON, "validEndTime");
    if (valid_end_time) {
    if (!cJSON_IsString(valid_end_time) && !cJSON_IsNull(valid_end_time)) {
        ogs_error("OpenAPI__application_data_influence_data_subs_to_notify_post_request_inner_parseFromJSON() failed [valid_end_time]");
        goto end;
    }
    }

    temp_validities = cJSON_GetObjectItemCaseSensitive(_application_data_influence_data_subs_to_notify_post_request_innerJSON, "tempValidities");
    if (temp_validities) {
        cJSON *temp_validities_local = NULL;
        if (!cJSON_IsArray(temp_validities)) {
            ogs_error("OpenAPI__application_data_influence_data_subs_to_notify_post_request_inner_parseFromJSON() failed [temp_validities]");
            goto end;
        }

        temp_validitiesList = OpenAPI_list_create();

        cJSON_ArrayForEach(temp_validities_local, temp_validities) {
            if (!cJSON_IsObject(temp_validities_local)) {
                ogs_error("OpenAPI__application_data_influence_data_subs_to_notify_post_request_inner_parseFromJSON() failed [temp_validities]");
                goto end;
            }
            OpenAPI_temporal_validity_t *temp_validitiesItem = OpenAPI_temporal_validity_parseFromJSON(temp_validities_local);
            if (!temp_validitiesItem) {
                ogs_error("No temp_validitiesItem");
                goto end;
            }
            OpenAPI_list_add(temp_validitiesList, temp_validitiesItem);
        }
    }

    nw_area_info = cJSON_GetObjectItemCaseSensitive(_application_data_influence_data_subs_to_notify_post_request_innerJSON, "nwAreaInfo");
    if (nw_area_info) {
    nw_area_info_local_nonprim = OpenAPI_network_area_info_1_parseFromJSON(nw_area_info);
    if (!nw_area_info_local_nonprim) {
        ogs_error("OpenAPI_network_area_info_1_parseFromJSON failed [nw_area_info]");
        goto end;
    }
    }

    up_path_chg_notif_uri = cJSON_GetObjectItemCaseSensitive(_application_data_influence_data_subs_to_notify_post_request_innerJSON, "upPathChgNotifUri");
    if (up_path_chg_notif_uri) {
    if (!cJSON_IsString(up_path_chg_notif_uri) && !cJSON_IsNull(up_path_chg_notif_uri)) {
        ogs_error("OpenAPI__application_data_influence_data_subs_to_notify_post_request_inner_parseFromJSON() failed [up_path_chg_notif_uri]");
        goto end;
    }
    }

    headers = cJSON_GetObjectItemCaseSensitive(_application_data_influence_data_subs_to_notify_post_request_innerJSON, "headers");
    if (headers) {
        cJSON *headers_local = NULL;
        if (!cJSON_IsArray(headers)) {
            ogs_error("OpenAPI__application_data_influence_data_subs_to_notify_post_request_inner_parseFromJSON() failed [headers]");
            goto end;
        }

        headersList = OpenAPI_list_create();

        cJSON_ArrayForEach(headers_local, headers) {
            double *localDouble = NULL;
            int *localInt = NULL;
            if (!cJSON_IsString(headers_local)) {
                ogs_error("OpenAPI__application_data_influence_data_subs_to_notify_post_request_inner_parseFromJSON() failed [headers]");
                goto end;
            }
            OpenAPI_list_add(headersList, ogs_strdup(headers_local->valuestring));
        }
    }

    subscribed_events = cJSON_GetObjectItemCaseSensitive(_application_data_influence_data_subs_to_notify_post_request_innerJSON, "subscribedEvents");
    if (subscribed_events) {
        cJSON *subscribed_events_local = NULL;
        if (!cJSON_IsArray(subscribed_events)) {
            ogs_error("OpenAPI__application_data_influence_data_subs_to_notify_post_request_inner_parseFromJSON() failed [subscribed_events]");
            goto end;
        }

        subscribed_eventsList = OpenAPI_list_create();

        cJSON_ArrayForEach(subscribed_events_local, subscribed_events) {
            OpenAPI_subscribed_event_e localEnum = OpenAPI_subscribed_event_NULL;
            if (!cJSON_IsString(subscribed_events_local)) {
                ogs_error("OpenAPI__application_data_influence_data_subs_to_notify_post_request_inner_parseFromJSON() failed [subscribed_events]");
                goto end;
            }
            localEnum = OpenAPI_subscribed_event_FromString(subscribed_events_local->valuestring);
            if (!localEnum) {
                ogs_info("Enum value \"%s\" for field \"subscribed_events\" is not supported. Ignoring it ...",
                         subscribed_events_local->valuestring);
            } else {
                OpenAPI_list_add(subscribed_eventsList, (void *)localEnum);
            }
        }
        if (subscribed_eventsList->count == 0) {
            ogs_error("OpenAPI__application_data_influence_data_subs_to_notify_post_request_inner_parseFromJSON() failed: Expected subscribed_eventsList to not be empty (after ignoring unsupported enum values).");
            goto end;
        }
    }

    dnai_chg_type = cJSON_GetObjectItemCaseSensitive(_application_data_influence_data_subs_to_notify_post_request_innerJSON, "dnaiChgType");
    if (dnai_chg_type) {
    if (!cJSON_IsString(dnai_chg_type)) {
        ogs_error("OpenAPI__application_data_influence_data_subs_to_notify_post_request_inner_parseFromJSON() failed [dnai_chg_type]");
        goto end;
    }
    dnai_chg_typeVariable = OpenAPI_dnai_change_type_FromString(dnai_chg_type->valuestring);
    }

    af_ack_ind = cJSON_GetObjectItemCaseSensitive(_application_data_influence_data_subs_to_notify_post_request_innerJSON, "afAckInd");
    if (af_ack_ind) {
    if (!cJSON_IsBool(af_ack_ind)) {
        ogs_error("OpenAPI__application_data_influence_data_subs_to_notify_post_request_inner_parseFromJSON() failed [af_ack_ind]");
        goto end;
    }
    }

    addr_preser_ind = cJSON_GetObjectItemCaseSensitive(_application_data_influence_data_subs_to_notify_post_request_innerJSON, "addrPreserInd");
    if (addr_preser_ind) {
    if (!cJSON_IsBool(addr_preser_ind)) {
        ogs_error("OpenAPI__application_data_influence_data_subs_to_notify_post_request_inner_parseFromJSON() failed [addr_preser_ind]");
        goto end;
    }
    }

    max_allowed_up_lat = cJSON_GetObjectItemCaseSensitive(_application_data_influence_data_subs_to_notify_post_request_innerJSON, "maxAllowedUpLat");
    if (max_allowed_up_lat) {
    if (!cJSON_IsNumber(max_allowed_up_lat)) {
        ogs_error("OpenAPI__application_data_influence_data_subs_to_notify_post_request_inner_parseFromJSON() failed [max_allowed_up_lat]");
        goto end;
    }
    }

    sim_conn_ind = cJSON_GetObjectItemCaseSensitive(_application_data_influence_data_subs_to_notify_post_request_innerJSON, "simConnInd");
    if (sim_conn_ind) {
    if (!cJSON_IsBool(sim_conn_ind)) {
        ogs_error("OpenAPI__application_data_influence_data_subs_to_notify_post_request_inner_parseFromJSON() failed [sim_conn_ind]");
        goto end;
    }
    }

    sim_conn_term = cJSON_GetObjectItemCaseSensitive(_application_data_influence_data_subs_to_notify_post_request_innerJSON, "simConnTerm");
    if (sim_conn_term) {
    if (!cJSON_IsNumber(sim_conn_term)) {
        ogs_error("OpenAPI__application_data_influence_data_subs_to_notify_post_request_inner_parseFromJSON() failed [sim_conn_term]");
        goto end;
    }
    }

    supported_features = cJSON_GetObjectItemCaseSensitive(_application_data_influence_data_subs_to_notify_post_request_innerJSON, "supportedFeatures");
    if (supported_features) {
    if (!cJSON_IsString(supported_features) && !cJSON_IsNull(supported_features)) {
        ogs_error("OpenAPI__application_data_influence_data_subs_to_notify_post_request_inner_parseFromJSON() failed [supported_features]");
        goto end;
    }
    }

    res_uri = cJSON_GetObjectItemCaseSensitive(_application_data_influence_data_subs_to_notify_post_request_innerJSON, "resUri");
    if (res_uri) {
    if (!cJSON_IsString(res_uri) && !cJSON_IsNull(res_uri)) {
        ogs_error("OpenAPI__application_data_influence_data_subs_to_notify_post_request_inner_parseFromJSON() failed [res_uri]");
        goto end;
    }
    }

    reset_ids = cJSON_GetObjectItemCaseSensitive(_application_data_influence_data_subs_to_notify_post_request_innerJSON, "resetIds");
    if (reset_ids) {
        cJSON *reset_ids_local = NULL;
        if (!cJSON_IsArray(reset_ids)) {
            ogs_error("OpenAPI__application_data_influence_data_subs_to_notify_post_request_inner_parseFromJSON() failed [reset_ids]");
            goto end;
        }

        reset_idsList = OpenAPI_list_create();

        cJSON_ArrayForEach(reset_ids_local, reset_ids) {
            double *localDouble = NULL;
            int *localInt = NULL;
            if (!cJSON_IsString(reset_ids_local)) {
                ogs_error("OpenAPI__application_data_influence_data_subs_to_notify_post_request_inner_parseFromJSON() failed [reset_ids]");
                goto end;
            }
            OpenAPI_list_add(reset_idsList, ogs_strdup(reset_ids_local->valuestring));
        }
    }

    traffic_influ_data = cJSON_GetObjectItemCaseSensitive(_application_data_influence_data_subs_to_notify_post_request_innerJSON, "trafficInfluData");
    if (traffic_influ_data) {
    traffic_influ_data_local_nonprim = OpenAPI_traffic_influ_data_parseFromJSON(traffic_influ_data);
    if (!traffic_influ_data_local_nonprim) {
        ogs_error("OpenAPI_traffic_influ_data_parseFromJSON failed [traffic_influ_data]");
        goto end;
    }
    }

    _application_data_influence_data_subs_to_notify_post_request_inner_local_var = OpenAPI__application_data_influence_data_subs_to_notify_post_request_inner_create (
        up_path_chg_notif_corre_id && !cJSON_IsNull(up_path_chg_notif_corre_id) ? ogs_strdup(up_path_chg_notif_corre_id->valuestring) : NULL,
        app_relo_ind ? true : false,
        app_relo_ind ? app_relo_ind->valueint : 0,
        af_app_id && !cJSON_IsNull(af_app_id) ? ogs_strdup(af_app_id->valuestring) : NULL,
        dnn && !cJSON_IsNull(dnn) ? ogs_strdup(dnn->valuestring) : NULL,
        eth_traffic_filters ? eth_traffic_filtersList : NULL,
        snssai ? snssai_local_nonprim : NULL,
        inter_group_id && !cJSON_IsNull(inter_group_id) ? ogs_strdup(inter_group_id->valuestring) : NULL,
        supi && !cJSON_IsNull(supi) ? ogs_strdup(supi->valuestring) : NULL,
        traffic_filters ? traffic_filtersList : NULL,
        traffic_routes ? traffic_routesList : NULL,
        traff_corre_ind ? true : false,
        traff_corre_ind ? traff_corre_ind->valueint : 0,
        valid_start_time && !cJSON_IsNull(valid_start_time) ? ogs_strdup(valid_start_time->valuestring) : NULL,
        valid_end_time && !cJSON_IsNull(valid_end_time) ? ogs_strdup(valid_end_time->valuestring) : NULL,
        temp_validities ? temp_validitiesList : NULL,
        nw_area_info ? nw_area_info_local_nonprim : NULL,
        up_path_chg_notif_uri && !cJSON_IsNull(up_path_chg_notif_uri) ? ogs_strdup(up_path_chg_notif_uri->valuestring) : NULL,
        headers ? headersList : NULL,
        subscribed_events ? subscribed_eventsList : NULL,
        dnai_chg_type ? dnai_chg_typeVariable : 0,
        af_ack_ind ? true : false,
        af_ack_ind ? af_ack_ind->valueint : 0,
        addr_preser_ind ? true : false,
        addr_preser_ind ? addr_preser_ind->valueint : 0,
        max_allowed_up_lat ? true : false,
        max_allowed_up_lat ? max_allowed_up_lat->valuedouble : 0,
        sim_conn_ind ? true : false,
        sim_conn_ind ? sim_conn_ind->valueint : 0,
        sim_conn_term ? true : false,
        sim_conn_term ? sim_conn_term->valuedouble : 0,
        supported_features && !cJSON_IsNull(supported_features) ? ogs_strdup(supported_features->valuestring) : NULL,
        res_uri && !cJSON_IsNull(res_uri) ? ogs_strdup(res_uri->valuestring) : NULL,
        reset_ids ? reset_idsList : NULL,
        traffic_influ_data ? traffic_influ_data_local_nonprim : NULL
    );

    return _application_data_influence_data_subs_to_notify_post_request_inner_local_var;
end:
    if (eth_traffic_filtersList) {
        OpenAPI_list_for_each(eth_traffic_filtersList, node) {
            OpenAPI_eth_flow_description_free(node->data);
        }
        OpenAPI_list_free(eth_traffic_filtersList);
        eth_traffic_filtersList = NULL;
    }
    if (snssai_local_nonprim) {
        OpenAPI_snssai_free(snssai_local_nonprim);
        snssai_local_nonprim = NULL;
    }
    if (traffic_filtersList) {
        OpenAPI_list_for_each(traffic_filtersList, node) {
            OpenAPI_flow_info_free(node->data);
        }
        OpenAPI_list_free(traffic_filtersList);
        traffic_filtersList = NULL;
    }
    if (traffic_routesList) {
        OpenAPI_list_for_each(traffic_routesList, node) {
            OpenAPI_route_to_location_free(node->data);
        }
        OpenAPI_list_free(traffic_routesList);
        traffic_routesList = NULL;
    }
    if (temp_validitiesList) {
        OpenAPI_list_for_each(temp_validitiesList, node) {
            OpenAPI_temporal_validity_free(node->data);
        }
        OpenAPI_list_free(temp_validitiesList);
        temp_validitiesList = NULL;
    }
    if (nw_area_info_local_nonprim) {
        OpenAPI_network_area_info_1_free(nw_area_info_local_nonprim);
        nw_area_info_local_nonprim = NULL;
    }
    if (headersList) {
        OpenAPI_list_for_each(headersList, node) {
            ogs_free(node->data);
        }
        OpenAPI_list_free(headersList);
        headersList = NULL;
    }
    if (subscribed_eventsList) {
        OpenAPI_list_free(subscribed_eventsList);
        subscribed_eventsList = NULL;
    }
    if (reset_idsList) {
        OpenAPI_list_for_each(reset_idsList, node) {
            ogs_free(node->data);
        }
        OpenAPI_list_free(reset_idsList);
        reset_idsList = NULL;
    }
    if (traffic_influ_data_local_nonprim) {
        OpenAPI_traffic_influ_data_free(traffic_influ_data_local_nonprim);
        traffic_influ_data_local_nonprim = NULL;
    }
    return NULL;
}

OpenAPI__application_data_influence_data_subs_to_notify_post_request_inner_t *OpenAPI__application_data_influence_data_subs_to_notify_post_request_inner_copy(OpenAPI__application_data_influence_data_subs_to_notify_post_request_inner_t *dst, OpenAPI__application_data_influence_data_subs_to_notify_post_request_inner_t *src)
{
    cJSON *item = NULL;
    char *content = NULL;

    ogs_assert(src);
    item = OpenAPI__application_data_influence_data_subs_to_notify_post_request_inner_convertToJSON(src);
    if (!item) {
        ogs_error("OpenAPI__application_data_influence_data_subs_to_notify_post_request_inner_convertToJSON() failed");
        return NULL;
    }

    content = cJSON_Print(item);
    cJSON_Delete(item);

    if (!content) {
        ogs_error("cJSON_Print() failed");
        return NULL;
    }

    item = cJSON_Parse(content);
    ogs_free(content);
    if (!item) {
        ogs_error("cJSON_Parse() failed");
        return NULL;
    }

    OpenAPI__application_data_influence_data_subs_to_notify_post_request_inner_free(dst);
    dst = OpenAPI__application_data_influence_data_subs_to_notify_post_request_inner_parseFromJSON(item);
    cJSON_Delete(item);

    return dst;
}

