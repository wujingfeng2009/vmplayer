/*	vmplayer is designed to be a cross-platform multimedia player with fantastic voice features.
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 */
 
#ifndef	__H_VM_PLATFORM_EXTERNAL_H__
#define	__H_VM_PLATFORM_EXTERNAL_H__

#include	"vm-platform-adaption.h"

typedef struct {
	vm_char* name;
	vm_handle ops;
}vm_svc_handle;

typedef	vm_handle (*vm_ext_service_new)(vm_service_t svc_type);

#endif

