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
 
#ifndef	__H_VM_PLATFORM_ADAPTION_API_H__
#define	__H_VM_PLATFORM_ADAPTION_API_H__

#include	"vm-utils.h"

typedef  struct	_vm_service	vm_service;

typedef enum{
	VM_SVC_PLAYER,
	VM_SVC_VOICE_RECOGNITION,
	VM_SVC_SOUND_RECORDER,
	VM_SVC_NUM
}vm_service_t;


VM_API void vm_platform_load(void);
VM_API void vm_platform_unload(void);
VM_API vm_service* vm_service_aquire(vm_service_t svc_type);
VM_API void vm_service_ref(vm_service*  svc);
VM_API void vm_service_unref(vm_service*  svc);

#endif

