/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "E2SM-KPM-IEs"
 * 	found in "e2sm_kpm_v02.01_standard.asn1"
 * 	`asn1c -S /home/mir/workspace/asn1c_mouse/skeletons/ -no-gen-BER -no-gen-UPER -no-gen-OER -no-gen-JER -fcompound-names -no-gen-example -findirect-choice -fno-include-deps`
 */

#ifndef	_MatchingUeCondPerSubList_H_
#define	_MatchingUeCondPerSubList_H_


#include <asn_application.h>

/* Including external dependencies */
#include <asn_SEQUENCE_OF.h>
#include <constr_SEQUENCE_OF.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Forward declarations */
struct MatchingUeCondPerSubItem;

/* MatchingUeCondPerSubList */
typedef struct MatchingUeCondPerSubList {
	A_SEQUENCE_OF(struct MatchingUeCondPerSubItem) list;
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} MatchingUeCondPerSubList_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_MatchingUeCondPerSubList;
extern asn_SET_OF_specifics_t asn_SPC_MatchingUeCondPerSubList_specs_1;
extern asn_TYPE_member_t asn_MBR_MatchingUeCondPerSubList_1[1];
extern asn_per_constraints_t asn_PER_type_MatchingUeCondPerSubList_constr_1;

#ifdef __cplusplus
}
#endif

#endif	/* _MatchingUeCondPerSubList_H_ */
#include <asn_internal.h>
