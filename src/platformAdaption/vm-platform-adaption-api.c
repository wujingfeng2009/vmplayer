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
 
#include	"vm-log.h"
#include	"vm-platform-adaption.h"
#include	"vm-platform-external.h"

#define	DL_FILE_NAME		"vm-platform-adaption.so"
#define	DL_SVC_NEW_FUNC	"vm_ext_service_new"

VM_INTERNAL	vm_handle	global_dl_handle = VM_HANDLE_NULL;
VM_INTERNAL	vm_handle	global_dl_svc_nwe_func = VM_HANDLE_NULL;

struct _vm_service {
	vm_handle svc_handle;
	vm_int refcount;
	vm_char* svc_name;
	vm_ptr	svc_ops;
};

VM_INTERNAL vm_service* vm_service_new(vm_service_t svc_type)
{
	vm_service* svc = NULL;
	vm_handle svc_handle = VM_HANDLE_NULL;
	VM_LOG_ENTER_FUNC;
	
	VM_RETURN_VAL_IF_FAILED(global_dl_svc_nwe_func != VM_HANDLE_NULL, NULL);
	vm_ext_service_new svc_new_func = (vm_ext_service_new)global_dl_svc_nwe_func;
	svc_handle = svc_new_func(svc_type);
	VM_RETURN_VAL_IF_FAILED(svc_handle != VM_HANDLE_NULL, NULL);
	
	svc = (vm_service*)malloc(sizeof(vm_service));
	VM_RETURN_VAL_IF_FAILED(svc != NULL, NULL);	
	svc->svc_handle = svc_handle;
	svc->svc_ops = ((vm_svc_handle*)svc_handle)->ops;
	svc->svc_name = ((vm_svc_handle*)svc_handle)->name;
	return svc;

}

VM_INTERNAL void vm_service_free(vm_service*  svc)
{
	VM_LOG_ENTER_FUNC;
	VM_RETURN_IF_FAILED(svc !=  NULL);
	free(svc);

}

VM_INTERNAL vm_error_type vm_service_init(vm_service*  svc)
{
	VM_LOG_ENTER_FUNC;
	
	return VM_ERROR_NONE;

}

VM_INTERNAL void vm_service_deinit(vm_service*  svc)
{
	VM_LOG_ENTER_FUNC;
	

}

VM_API vm_error_type vm_platform_load(void)
{
	VM_LOG_ENTER_FUNC;
	if(global_dl_handle != VM_HANDLE_NULL && global_dl_svc_nwe_func != VM_HANDLE_NULL)
		return VM_ERROR_NONE;
	
	if(global_dl_handle != VM_HANDLE_NULL && global_dl_svc_nwe_func == VM_HANDLE_NULL)
		return VM_ERROR_OPEN;
	
	global_dl_handle = vm_dlopen(DL_FILE_NAME, DEFAULT_DL_OPEN_FLAG);
	if(global_dl_handle == VM_HANDLE_NULL)
	{
		VM_LOG_ERROR("Open dl (%s) failed!\n", DL_FILE_NAME);
		return VM_ERROR_OPEN;
	}
	global_dl_svc_nwe_func = vm_dlsym(global_dl_handle, vm_service_new);
	
	if(global_dl_svc_nwe_func == VM_HANDLE_NULL)
	{
		VM_LOG_ERROR("Get dl funtion (%s) failed!\n", vm_service_new);
		return VM_ERROR_OPEN;
	}
	
	return VM_ERROR_NONE;
}

VM_API void vm_platform_unload(void)
{
	VM_LOG_ENTER_FUNC;
	if(global_dl_handle != VM_HANDLE_NULL )
		vm_dlclose(global_dl_handle);
	global_dl_handle = VM_HANDLE_NULL;
	global_dl_svc_nwe_func = VM_HANDLE_NULL;
}

VM_API vm_service* vm_service_aquire(vm_service_t svc_type)
{
	vm_error_type ret;
	VM_LOG_ENTER_FUNC;
		
	vm_service* svc = vm_service_new(svc_type);
	VM_RETURN_VAL_IF_FAILED(svc, NULL);
	
	VM_LOG_DEBUG("Create  service (%s) success!\n", svc->svc_name);
	ret = vm_service_init(svc);
	if(ret != VM_ERROR_NONE)
	{
		VM_LOG_ERROR("Init service  failed! now free the service (%s).\n", svc->svc_name);
		vm_service_free(svc);
		return NULL;
	}
	svc->refcount = 1;
	VM_LOG_DEBUG("Aquire  service (%s) success! now the refcount is: %d.\n", svc->svc_name, svc->refcount);
	return svc;

}

VM_API void vm_service_ref(vm_service*  svc)
{
	VM_LOG_ENTER_FUNC;
	VM_RETURN_IF_FAILED(svc);
	
	VM_LOG_DEBUG("Before ref, the refcount is: %d.\n", svc->refcount);
	svc->refcount ++;
	VM_LOG_DEBUG("After ref, the refcount is: %d.\n", svc->refcount);

}

VM_API void vm_service_unref(vm_service*  svc)
{
	VM_LOG_ENTER_FUNC;
	VM_RETURN_IF_FAILED(svc);
	
	VM_LOG_DEBUG("Before unref, the refcount of service (%s) is: %d.\n", svc->svc_name, svc->refcount);
	if(svc->refcount > 1)
	{
		svc->refcount--;
		VM_LOG_DEBUG("After unref, the refcount of service (%s) is: %d.\n", svc->svc_name, svc->refcount);
	}
	else
	{
		VM_LOG_DEBUG("The refcount is: %d, so we deinit and free the service (%s).\n", svc->refcount, svc->svc_name);
		vm_service_deinit(svc);
		vm_service_free(svc);
		svc = NULL;
	}
}



