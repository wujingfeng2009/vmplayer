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

vm_service* vm_service_aquire(vm_service_t svc_type);
vm_service* vm_service_ref(vm_service*  svc);
vm_service* vm_service_unref(vm_service*  svc);


vm_error_type vm_service_init(vm_service*  svc);
vm_error_type vm_service_deinit(vm_service*  svc);

struct _vm_service {
	vm_handle svc_handle;
};

typedef  struct {

}platform_errs;

typedef  struct {

}platform_notis;


#endif

