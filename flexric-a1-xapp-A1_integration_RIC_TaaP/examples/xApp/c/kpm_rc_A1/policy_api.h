#ifndef POLICY_API_H
#define POLICY_API_H


#include <stdbool.h>   // Add this line for bool type
#include <stddef.h>    // For size_t
#include <curl/curl.h>
#include <cjson/cJSON.h>

// Callback function to handle curl's response
size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp);

// Function to perform CURL GET request
bool performGetRequest(const char *url, char *response, size_t responseSize);

// Function to perform CURL PUT request
bool performPutRequest(const char *url, const char *data);

// Function to print JSON response
void printJsonResponse(const char *jsonResponse);

// Function to fetch the list of policy types
void fetchPolicyTypes();

// Function to fetch details of a specific policy type
void fetchPolicyTypeDetails(int policyTypeId);

// Function to create or update a policy type with dynamic policy_type_id
void createOrUpdatePolicyType(int policyTypeId);

// Function to update the threshold of a policy instance with dynamic parameters
void updatePolicyThreshold(int policyTypeId, int policyInstanceId, int threshold);

// Function to fetch all policies for a specific policy type
void fetchAllPolicies(int policyTypeId);

// Function to fetch the status of a specific policy instance
void checkPolicyStatus(int policyTypeId, int policyInstanceId);


#endif // POLICY_API_H
