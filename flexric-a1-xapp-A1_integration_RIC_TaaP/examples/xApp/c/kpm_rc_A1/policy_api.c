#include "policy_api.h"

// Callback function to handle curl's response
size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp) {
    size_t totalSize = size * nmemb;
    strncat((char *)userp, (char *)contents, totalSize);
    return totalSize;
}

// Function to perform CURL GET request
bool performGetRequest(const char *url, char *response, size_t responseSize) {
    CURL *curl = curl_easy_init();
    if (!curl) {
        fprintf(stderr, "Failed to initialize CURL\n");
        return false;
    }

    struct curl_slist *headers = NULL;
    headers = curl_slist_append(headers, "accept: application/json");

    curl_easy_setopt(curl, CURLOPT_URL, url);
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, response);

    CURLcode res = curl_easy_perform(curl);
    curl_easy_cleanup(curl);
    curl_slist_free_all(headers);

    if (res != CURLE_OK) {
        fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
        return false;
    }
    return true;
}

// Function to perform CURL PUT request
bool performPutRequest(const char *url, const char *data) {
    CURL *curl = curl_easy_init();
    if (!curl) {
        fprintf(stderr, "Failed to initialize CURL\n");
        return false;
    }

    struct curl_slist *headers = NULL;
    headers = curl_slist_append(headers, "accept: application/json");
    headers = curl_slist_append(headers, "Content-Type: application/json");

    curl_easy_setopt(curl, CURLOPT_URL, url);
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
    curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "PUT");
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, data);

    CURLcode res = curl_easy_perform(curl);
    curl_easy_cleanup(curl);
    curl_slist_free_all(headers);

    if (res != CURLE_OK) {
        fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
        return false;
    }
    return true;
}

// Function to print JSON response
void printJsonResponse(const char *jsonResponse) {
    cJSON *json = cJSON_Parse(jsonResponse);
    if (json == NULL) {
        printf("Error parsing JSON\n");
        return;
    }

    char *jsonString = cJSON_Print(json);
    if (jsonString != NULL) {
        printf("%s\n", jsonString);
        free(jsonString);
    }

    cJSON_Delete(json);
}

// Function to fetch the list of policy types
void fetchPolicyTypes() {
    const char *url = "http://0.0.0.0:9000/a1-p/policytypes";
    char response[10000] = "";

    if (performGetRequest(url, response, sizeof(response))) {
        printJsonResponse(response);
    } else {
        printf("Failed to retrieve policy types.\n");
    }
}

// Function to fetch details of a specific policy type
void fetchPolicyTypeDetails(int policyTypeId) {
    char url[256];
    snprintf(url, sizeof(url), "http://0.0.0.0:9000/a1-p/policytypes/%d", policyTypeId);

    char response[10000] = ""; // Buffer for response data
    if (performGetRequest(url, response, sizeof(response))) {
        printf("Details for policy type ID %d:\n", policyTypeId);
        printJsonResponse(response);
    } else {
        printf("Failed to retrieve details for policy type ID %d.\n", policyTypeId);
    }
}

// Function to create or update a policy type with dynamic policy_type_id
void createOrUpdatePolicyType(int policyTypeId) {
    char url[256];
    snprintf(url, sizeof(url), "http://0.0.0.0:9000/a1-p/policytypes/%d", policyTypeId);

    const char *data = "{"
                       "\"name\": \"tsapolicy\","
                       "\"description\": \"tsa parameters\","
                       "\"policy_type_id\": %d,"
                       "\"create_schema\": {"
                       "\"$schema\": \"http://json-schema.org/draft-07/schema#\","
                       "\"type\": \"object\","
                       "\"properties\": {"
                       "\"threshold\": {"
                       "\"type\": \"integer\","
                       "\"default\": 0"
                       "}"
                       "},"
                       "\"additionalProperties\": false"
                       "}"
                       "}";

    char formattedData[512];
    snprintf(formattedData, sizeof(formattedData), data, policyTypeId);

    if (performPutRequest(url, formattedData)) {
        printf("\nSuccessfully created or updated policy type with ID %d.\n", policyTypeId);
    } else {
        printf("Failed to create or update policy type with ID %d.\n", policyTypeId);
    }
}

// Function to update the threshold of a policy instance with dynamic parameters
void updatePolicyThreshold(int policyTypeId, int policyInstanceId, int threshold) {
    char url[256];
    snprintf(url, sizeof(url), "http://0.0.0.0:9000/a1-p/policytypes/%d/policies/%d", policyTypeId, policyInstanceId);

    cJSON *json = cJSON_CreateObject();
    cJSON_AddNumberToObject(json, "threshold", threshold);
    char *data = cJSON_PrintUnformatted(json);

    if (performPutRequest(url, data)) {
        printf("\nSuccessfully updated threshold to %d for policy type %d, instance %d.\n", threshold, policyTypeId, policyInstanceId);
    } else {
        printf("Failed to update threshold for policy type %d, instance %d.\n", policyTypeId, policyInstanceId);
    }

    cJSON_Delete(json);
    free(data);
}

// Function to fetch all policies for a specific policy type
void fetchAllPolicies(int policyTypeId) {
    char url[256];
    snprintf(url, sizeof(url), "http://0.0.0.0:9000/a1-p/policytypes/%d/policies", policyTypeId);
    char response[10000] = "";

    if (performGetRequest(url, response, sizeof(response))) {
        printJsonResponse(response);
    } else {
        printf("Failed to retrieve policies for policy type %d.\n", policyTypeId);
    }
}

// Function to fetch the status of a specific policy instance
void checkPolicyStatus(int policyTypeId, int policyInstanceId) {
    char url[256];
    snprintf(url, sizeof(url), "http://0.0.0.0:9000/a1-p/policytypes/%d/policies/%d/status", policyTypeId, policyInstanceId);

    char response[10000] = "";
    if (performGetRequest(url, response, sizeof(response))) {
        printf("Status for policy instance %d of policy type %d:\n", policyInstanceId, policyTypeId);
        printJsonResponse(response);
    } else {
        printf("Failed to retrieve status for policy instance %d of policy type %d.\n", policyInstanceId, policyTypeId);
    }
}
