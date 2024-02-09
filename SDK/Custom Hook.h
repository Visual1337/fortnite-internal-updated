#pragma once

inline auto custom_memcpy(void* dest, const void* src, unsigned long long count) -> void*
{
	SPOOF_FUNC;
	char* char_dest = (char*)dest;
	char* char_src = (char*)src;
	if ((char_dest <= char_src) || (char_dest >= (char_src + count)))
	{
		while (count > 0)
		{
			*char_dest = *char_src;
			char_dest++;
			char_src++;
			count--;
		}
	}
	else
	{
		char_dest = (char*)dest + count - 1;
		char_src = (char*)src + count - 1;
		while (count > 0)
		{
			*char_dest = *char_src;
			char_dest--;
			char_src--;
			count--;
		}
	}
	return dest;
}


template <typename hook_type>
_declspec(noinline) hook_type vmt(void* address, void* hook_function, int index, void** ret = nullptr) {
	SPOOF_FUNC;
	uintptr_t* vtable = *(uintptr_t**)address;

	int methods = 0;
	while (*(uintptr_t*)((uintptr_t)vtable + (methods * 0x8))) {
		++methods;
	}

	uintptr_t* vtable_buf = new uintptr_t[methods];

	custom_memcpy(vtable_buf, vtable, methods * 0x8);

	if (ret) {
		*ret = (void*)vtable[index];
	}

	vtable_buf[index] = (uintptr_t)(hook_function);

	*(uintptr_t**)address = vtable_buf;
	return hook_type(vtable[index]);
}


