#pragma once

//opaque object handle
class Registered;

using ED_OBJECT_HANDLE  = Registered*;

//void ed_on_object_create(ED_OBJECT_HANDLE handle,uint64_t & cookie)
//called for your module library if object type is declared by you
using PFN_ED_ON_OBJECT_CREATE	= void (*) (ED_OBJECT_HANDLE handle,uint64_t & cookie);

//void ed_on_object_simulate(ED_OBJECT_HANDLE handle,uint64_t & cookie, double t)
//called on each simulation step by object 
using PFN_ED_ON_OBJECT_SIMULATE = void (*) (ED_OBJECT_HANDLE handle,uint64_t & cookie, double t);

//void ed_on_object_destroy(ED_OBJECT_HANDLE handle,uint64_t & cookie)
//called  right before object destruction 
using PFN_ED_ON_OBJECT_DESTROY  = void (*) (ED_OBJECT_HANDLE handle,uint64_t & cookie);

struct  ed_object_api_entry;

//void ed_setup_object_api(const ed_object_api_entry* api)
//called after you module is loaded to setup access object API
using PFN_ED_SETUP_OBJECT_API   = void (*) (const ed_object_api_entry* api);

//view to object args
struct ed_object_args
{	
	const float * data;
	size_t  	  size;
};

struct  ed_object_api_entry
{
	uint64_t	   (*ed_get_object_id)      (ED_OBJECT_HANDLE handle);
	ed_object_args (*ed_get_object_args)    (ED_OBJECT_HANDLE handle);
	//direct memcopy args_src  to internal arguments starting from offset
	void 		   (*ed_copy_to_object_args)(ED_OBJECT_HANDLE handle,float * args_src,int dest_offset,int args_count);
	// set single argument  value 
	void 		   (*ed_set_single_arg)		(ED_OBJECT_HANDLE handle,int index,float value);
};
