#pragma once
#include "skibidi.h"


bool is_bad_write_ptr(LPVOID ptr, UINT_PTR size)
{
    SPOOF_FUNC
    return ptr ? false : true;
}

bool valid_pointer(uintptr_t address)
{
    SPOOF_FUNC
	if (!is_bad_write_ptr((LPVOID)address, (UINT_PTR)8)) return TRUE;
	else return FALSE;
}

template<typename ReadT>
ReadT read(DWORD_PTR address, const ReadT& def = ReadT())
{
    SPOOF_FUNC
    if (valid_pointer(address)) {
        return *(ReadT*)(address);
    }
}