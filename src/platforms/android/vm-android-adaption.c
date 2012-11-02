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
 
#include	"vm-utils.h"
#include	"vm-platform-adaption.h"


vm_service* vm_service_new(vm_service_t svc_type);


vm_error_type vm_service_init(vm_service*  svc);
vm_error_type vm_service_deinit(vm_service*  svc);

struct _vm_service {
	vm_handle svc_handle;
};

typedef  struct {

}platform_errs;

typedef  struct {

}platform_notis;


