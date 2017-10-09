#pragma once

typedef unsigned long address_t;

/* 64 Bits architecture */

#ifdef __x86_64__

/* code for 64 bit Intel arch */

#define JB_SP 6
#define JB_PC 7

address_t translate_address(address_t addr)
{
        address_t ret;
        asm volatile("xor    %%fs:0x30,%0\n"
                        "rol    $0x11,%0\n"
        : "=g" (ret)
        : "0" (addr));
        return ret;
}

/* 32 Bits architecture */

#else

/* code for 32 bit Intel arch */

#define JB_SP 4
#define JB_PC 5

address_t translate_address(address_t addr)
{
    address_t ret;
    asm volatile("xor    %%gs:0x18,%0\n"
                "rol    $0x9,%0\n"
                 : "=g" (ret)
                 : "0" (addr));
    return ret;
}

#endif
