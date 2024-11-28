/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "E2SM-RC-IEs"
 * 	found in "e2sm_rc_v1_03_standard.asn"
 * 	`asn1c -S /home/mir/workspace/asn1c_mouse/skeletons/ -no-gen-BER -no-gen-UPER -no-gen-OER -no-gen-JER -fcompound-names -no-gen-example -findirect-choice -fno-include-deps`
 */

#ifndef	_MessageType_Choice_H_
#define	_MessageType_Choice_H_


#include <asn_application.h>

/* Including external dependencies */
#include <constr_CHOICE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Dependencies */
typedef enum MessageType_Choice_PR {
	MessageType_Choice_PR_NOTHING,	/* No components present */
	MessageType_Choice_PR_messageType_Choice_NI,
	MessageType_Choice_PR_messageType_Choice_RRC
	/* Extensions may appear below */
	
} MessageType_Choice_PR;

/* Forward declarations */
struct MessageType_Choice_NI;
struct MessageType_Choice_RRC;

/* MessageType-Choice */
typedef struct MessageType_Choice {
	MessageType_Choice_PR present;
	union MessageType_Choice_u {
		struct MessageType_Choice_NI	*messageType_Choice_NI;
		struct MessageType_Choice_RRC	*messageType_Choice_RRC;
		/*
		 * This type is extensible,
		 * possible extensions are below.
		 */
	} choice;
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} MessageType_Choice_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_MessageType_Choice;
extern asn_CHOICE_specifics_t asn_SPC_MessageType_Choice_specs_1;
extern asn_TYPE_member_t asn_MBR_MessageType_Choice_1[2];
extern asn_per_constraints_t asn_PER_type_MessageType_Choice_constr_1;

#ifdef __cplusplus
}
#endif

#endif	/* _MessageType_Choice_H_ */
#include <asn_internal.h>
