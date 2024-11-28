/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "E2SM-KPM-IEs"
 * 	found in "e2sm_kpm_v03.00_standard.asn1"
 * 	`asn1c -S /home/mir/workspace/asn1c_mouse/skeletons/ -no-gen-BER -no-gen-UPER -no-gen-OER -no-gen-JER -fcompound-names -no-gen-example -findirect-choice -fno-include-deps`
 */

#ifndef	_E2SM_KPM_IndicationMessage_H_
#define	_E2SM_KPM_IndicationMessage_H_


#include <asn_application.h>

/* Including external dependencies */
#include <constr_CHOICE.h>
#include <constr_SEQUENCE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Dependencies */
typedef enum E2SM_KPM_IndicationMessage__indicationMessage_formats_PR {
	E2SM_KPM_IndicationMessage__indicationMessage_formats_PR_NOTHING,	/* No components present */
	E2SM_KPM_IndicationMessage__indicationMessage_formats_PR_indicationMessage_Format1,
	E2SM_KPM_IndicationMessage__indicationMessage_formats_PR_indicationMessage_Format2,
	/* Extensions may appear below */
	E2SM_KPM_IndicationMessage__indicationMessage_formats_PR_indicationMessage_Format3
} E2SM_KPM_IndicationMessage__indicationMessage_formats_PR;

/* Forward declarations */
struct E2SM_KPM_IndicationMessage_Format1;
struct E2SM_KPM_IndicationMessage_Format2;
struct E2SM_KPM_IndicationMessage_Format3;

/* E2SM-KPM-IndicationMessage */
typedef struct E2SM_KPM_IndicationMessage {
	struct E2SM_KPM_IndicationMessage__indicationMessage_formats {
		E2SM_KPM_IndicationMessage__indicationMessage_formats_PR present;
		union E2SM_KPM_IndicationMessage__indicationMessage_formats_u {
			struct E2SM_KPM_IndicationMessage_Format1	*indicationMessage_Format1;
			struct E2SM_KPM_IndicationMessage_Format2	*indicationMessage_Format2;
			/*
			 * This type is extensible,
			 * possible extensions are below.
			 */
			struct E2SM_KPM_IndicationMessage_Format3	*indicationMessage_Format3;
		} choice;
		
		/* Context for parsing across buffer boundaries */
		asn_struct_ctx_t _asn_ctx;
	} indicationMessage_formats;
	/*
	 * This type is extensible,
	 * possible extensions are below.
	 */
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} E2SM_KPM_IndicationMessage_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_E2SM_KPM_IndicationMessage;

#ifdef __cplusplus
}
#endif

#endif	/* _E2SM_KPM_IndicationMessage_H_ */
#include <asn_internal.h>
