#include <cstdlib>

#include <gtest/gtest.h>
#include <bintrace.h>
#include <udis86.h>

using namespace bintrace;

TEST(DisassemblerTest, Simple) {
    uint8_t data[] = {
        0x55, // push rbp
        0x48, 0x89, 0xe5, // mov rbp, rsp
        0x89, 0x7d, 0xfc, // mov [rbp-0x4], edi
        0x89, 0x75, 0xf8, // mov [rbp-0x8], esi
        0x8b, 0x75, 0xfc, // mov esi, [rbp-0x4]
        0x03, 0x75, 0xf8, // add esi, [rbp-0x8]
        0x89, 0xf0, // mov eax, esi
        0x5d, // pop rbp
        0xc3  // ret
    };
    
    const char* insns[] = {
        "push rbp", 
        "mov rbp, rsp",
        "mov [rbp-0x4], edi",
        "mov [rbp-0x8], esi",
        "mov esi, [rbp-0x4]",
        "add esi, [rbp-0x8]",
        "mov eax, esi",
        "pop rbp",
        "ret "
    };
    
    Disassembler d(data, data + sizeof(data));
    
    const char** txt = insns;
    ud_t* ud = d.next();
    
    while(!d.done()) {
        EXPECT_STREQ(ud_insn_asm(ud), *txt);
        ud = d.next();
        txt++;
    }
}

int main(int argc, char** argv) {
    srand(time(NULL));
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
