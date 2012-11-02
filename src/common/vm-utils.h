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
 #ifndef    __H_VM_UTILS_H__
#define	__H_VM_UTILS_H__

#define	ASSERT()

#define	VM_RETURN_VAL_IF_FAILED(expr, ret_val)
#define	VM_RETURN_IF_FAILED(expr)

#define	BEGIN_C_PLUS_PLUS	
#define	END_C_PLUS_PLUS

#define	VM_API	
#define	VM_INTERNAL	static


typedef  enum {
	false = 0,
	true = !false
}vm_bool;

typedef  enum {
	VM_ERROR_NONE = 0X0,
	VM_ERROR_OPEN = 0X01,
}vm_error_type;


#ifdef  __LUNUX__

typedef	int		vm_int;
typedef	char		vm_char;
typedef	void*	vm_ptr;
typedef	void*	vm_handle;

#define 	VM_HANDLE_NULL 0

#include <dlfcn.h>
#include <pthread.h>

#define	DEFAULT_DL_OPEN_FLAG	RTLD_NOW
vm_handle vm_dlopen(const vm_char *filename, vm_int flag)
{
	return dlopen(filename, flag);
}
vm_char* vm_dlerror(void)
{
	return dlerror();
}
vm_handle vm_dlsym(vm_handle handle, const vm_char *symbol)
{
	return dlsym(handle, symbol);
}
vm_int vm_dlclose(vm_handle handle)
{
	return dlclose(handle);
}
 

#else //  _WIN32__

#endif

#endif
