# From http://support.amd.com/us/Processor_TechDocs/24594_APM_v3.pdf
# See page 419 for the start of the opcode tables

# Operands
Eb = 'Eb'
Ev = 'Ev'
Gb = 'Gb'
Gv = 'Gv'
AL = 'AL'
Ib = 'Ib'
Iz = 'Iz'
rAX = 'rAX'

CS = 'CS'
DS = 'DS'
ES = 'ES'
SS = 'SS'

# Compatibility
no64 = 'no 64 bit'
no32 = 'no 32 bit'
no16 = 'no 16 bit'
null64 = 'null in 64 bit'

# ModRM.reg extensions
modrm_group_1 = 'ModRM Group 1'
modrm_group_1a = 'ModRM Group 1A'
modrm_group_2 = 'ModRM Group 2'
modrm_group_3 = 'ModRM Group 3'
modrm_group_4 = 'ModRM Group 4'
modrm_group_5 = 'ModRM Group 5'
modrm_group_6 = 'ModRM Group 6'
modrm_group_7 = 'ModRM Group 7'
modrm_group_8 = 'ModRM Group 8'
modrm_group_9 = 'ModRM Group 9'
modrm_group_10 = 'ModRM Group 10'
modrm_group_11 = 'ModRM Group 11'
modrm_group_12 = 'ModRM Group 12'
modrm_group_13 = 'ModRM Group 13'
modrm_group_14 = 'ModRM Group 14'
modrm_group_15 = 'ModRM Group 15'
modrm_group_16 = 'ModRM Group 16'
modrm_group_17 = 'ModRM Group 17'
modrm_group_P = 'ModRM Group P'

# Opcode Maps
primary_map = [None for i in range(0, 256)]
secondary_map = 'Secondary Map'

primary_map[0x00] = ('add', Eb, Gb)
primary_map[0x01] = ('add', Ev, Gv)
primary_map[0x02] = ('add', Gb, Eb)
primary_map[0x03] = ('add', Gv, Ev)
primary_map[0x04] = ('add', AL, Ib)
primary_map[0x05] = ('add', rAX, Iz)
primary_map[0x06] = ('push', ES, no64)
primary_map[0x07] = ('pop', ES, no64)

primary_map[0x08] = ('or', Eb, Gb)
primary_map[0x09] = ('or', Ev, Gv)
primary_map[0x0A] = ('or', Gb, Eb)
primary_map[0x0B] = ('or', Gv, Ev)
primary_map[0x0C] = ('or', AL, Ib)
primary_map[0x0D] = ('or', rAX, Iz, no64)
primary_map[0x0E] = ('push', CS, no64)
primary_map[0x0F] = secondary_map

primary_map[0x10] = ('adc', Eb, Gb)
primary_map[0x11] = ('adc', Ev, Gv)
primary_map[0x12] = ('adc', Gb, Eb)
primary_map[0x13] = ('adc', Gv, Ev)
primary_map[0x14] = ('adc', AL, Ib)
primary_map[0x15] = ('adc', rAX, Iz)
primary_map[0x16] = ('push', SS, no64)
primary_map[0x17] = ('pop', SS, no64)

primary_map[0x18] = ('sbb', Eb, Gb)
primary_map[0x19] = ('sbb', Ev, Gv)
primary_map[0x1A] = ('sbb', Gb, Eb)
primary_map[0x1B] = ('sbb', Gv, Ev)
primary_map[0x1C] = ('sbb', AL, Ib)
primary_map[0x1D] = ('sbb', rAX, Iz)
primary_map[0x1E] = ('push', DS, no64)
primary_map[0x1F] = ('pop', DS, no64)

primary_map[0x20] = 1
primary_map[0x21] = 1
primary_map[0x22] = 1
primary_map[0x23] = 1
primary_map[0x24] = 1
primary_map[0x25] = 1
primary_map[0x26] = 1
primary_map[0x27] = 1

primary_map[0x28] = 1
primary_map[0x29] = 1
primary_map[0x2A] = 1
primary_map[0x2B] = 1
primary_map[0x2C] = 1
primary_map[0x2D] = 1
primary_map[0x2E] = 1
primary_map[0x2F] = 1

primary_map[0x30] = 1
primary_map[0x31] = 1
primary_map[0x32] = 1
primary_map[0x33] = 1
primary_map[0x34] = 1
primary_map[0x35] = 1
primary_map[0x36] = 1
primary_map[0x37] = 1

primary_map[0x38] = 1
primary_map[0x39] = 1
primary_map[0x3A] = 1
primary_map[0x3B] = 1
primary_map[0x3C] = 1
primary_map[0x3D] = 1
primary_map[0x3E] = 1
primary_map[0x3F] = 1

primary_map[0x40] = 1
primary_map[0x41] = 1
primary_map[0x42] = 1
primary_map[0x43] = 1
primary_map[0x44] = 1
primary_map[0x45] = 1
primary_map[0x46] = 1
primary_map[0x47] = 1

primary_map[0x48] = 1
primary_map[0x49] = 1
primary_map[0x4A] = 1
primary_map[0x4B] = 1
primary_map[0x4C] = 1
primary_map[0x4D] = 1
primary_map[0x4E] = 1
primary_map[0x4F] = 1

primary_map[0x50] = 1
primary_map[0x51] = 1
primary_map[0x52] = 1
primary_map[0x53] = 1
primary_map[0x54] = 1
primary_map[0x55] = 1
primary_map[0x56] = 1
primary_map[0x57] = 1

primary_map[0x58] = 1
primary_map[0x59] = 1
primary_map[0x5A] = 1
primary_map[0x5B] = 1
primary_map[0x5C] = 1
primary_map[0x5D] = 1
primary_map[0x5E] = 1
primary_map[0x5F] = 1

primary_map[0x60] = 1
primary_map[0x61] = 1
primary_map[0x62] = 1
primary_map[0x63] = 1
primary_map[0x64] = 1
primary_map[0x65] = 1
primary_map[0x66] = 1
primary_map[0x67] = 1

primary_map[0x68] = 1
primary_map[0x69] = 1
primary_map[0x6A] = 1
primary_map[0x6B] = 1
primary_map[0x6C] = 1
primary_map[0x6D] = 1
primary_map[0x6E] = 1
primary_map[0x6F] = 1

primary_map[0x70] = 1
primary_map[0x71] = 1
primary_map[0x72] = 1
primary_map[0x73] = 1
primary_map[0x74] = 1
primary_map[0x75] = 1
primary_map[0x76] = 1
primary_map[0x77] = 1

primary_map[0x78] = 1
primary_map[0x79] = 1
primary_map[0x7A] = 1
primary_map[0x7B] = 1
primary_map[0x7C] = 1
primary_map[0x7D] = 1
primary_map[0x7E] = 1
primary_map[0x7F] = 1

primary_map[0x80] = 1
primary_map[0x81] = 1
primary_map[0x82] = 1
primary_map[0x83] = 1
primary_map[0x84] = 1
primary_map[0x85] = 1
primary_map[0x86] = 1
primary_map[0x87] = 1

primary_map[0x88] = 1
primary_map[0x89] = 1
primary_map[0x8A] = 1
primary_map[0x8B] = 1
primary_map[0x8C] = 1
primary_map[0x8D] = 1
primary_map[0x8E] = 1
primary_map[0x8F] = 1

primary_map[0x90] = 1
primary_map[0x91] = 1
primary_map[0x92] = 1
primary_map[0x93] = 1
primary_map[0x94] = 1
primary_map[0x95] = 1
primary_map[0x96] = 1
primary_map[0x97] = 1

primary_map[0x98] = 1
primary_map[0x99] = 1
primary_map[0x9A] = 1
primary_map[0x9B] = 1
primary_map[0x9C] = 1
primary_map[0x9D] = 1
primary_map[0x9E] = 1
primary_map[0x9F] = 1

primary_map[0xA0] = 1
primary_map[0xA1] = 1
primary_map[0xA2] = 1
primary_map[0xA3] = 1
primary_map[0xA4] = 1
primary_map[0xA5] = 1
primary_map[0xA6] = 1
primary_map[0xA7] = 1

primary_map[0xA8] = 1
primary_map[0xA9] = 1
primary_map[0xAA] = 1
primary_map[0xAB] = 1
primary_map[0xAC] = 1
primary_map[0xAD] = 1
primary_map[0xAE] = 1
primary_map[0xAF] = 1

primary_map[0xB0] = 1
primary_map[0xB1] = 1
primary_map[0xB2] = 1
primary_map[0xB3] = 1
primary_map[0xB4] = 1
primary_map[0xB5] = 1
primary_map[0xB6] = 1
primary_map[0xB7] = 1

primary_map[0xB8] = 1
primary_map[0xB9] = 1
primary_map[0xBA] = 1
primary_map[0xBB] = 1
primary_map[0xBC] = 1
primary_map[0xBD] = 1
primary_map[0xBE] = 1
primary_map[0xBF] = 1

primary_map[0xC0] = 1
primary_map[0xC1] = 1
primary_map[0xC2] = 1
primary_map[0xC3] = 1
primary_map[0xC4] = 1
primary_map[0xC5] = 1
primary_map[0xC6] = 1
primary_map[0xC7] = 1

primary_map[0xC8] = 1
primary_map[0xC9] = 1
primary_map[0xCA] = 1
primary_map[0xCB] = 1
primary_map[0xCC] = 1
primary_map[0xCD] = 1
primary_map[0xCE] = 1
primary_map[0xCF] = 1

primary_map[0xD0] = 1
primary_map[0xD1] = 1
primary_map[0xD2] = 1
primary_map[0xD3] = 1
primary_map[0xD4] = 1
primary_map[0xD5] = 1
primary_map[0xD6] = 1
primary_map[0xD7] = 1

primary_map[0xD8] = 1
primary_map[0xD9] = 1
primary_map[0xDA] = 1
primary_map[0xDB] = 1
primary_map[0xDC] = 1
primary_map[0xDD] = 1
primary_map[0xDE] = 1
primary_map[0xDF] = 1

primary_map[0xE0] = 1
primary_map[0xE1] = 1
primary_map[0xE2] = 1
primary_map[0xE3] = 1
primary_map[0xE4] = 1
primary_map[0xE5] = 1
primary_map[0xE6] = 1
primary_map[0xE7] = 1

primary_map[0xE8] = 1
primary_map[0xE9] = 1
primary_map[0xEA] = 1
primary_map[0xEB] = 1
primary_map[0xEC] = 1
primary_map[0xED] = 1
primary_map[0xEE] = 1
primary_map[0xEF] = 1

primary_map[0xF0] = 1
primary_map[0xF1] = 1
primary_map[0xF2] = 1
primary_map[0xF3] = 1
primary_map[0xF4] = 1
primary_map[0xF5] = 1
primary_map[0xF6] = 1
primary_map[0xF7] = 1

primary_map[0xF8] = ('clc')
primary_map[0xF9] = ('stc')
primary_map[0xFA] = ('cli')
primary_map[0xFB] = ('sti')
primary_map[0xFC] = ('cld')
primary_map[0xFD] = ('std')
primary_map[0xFE] = modrm_group_4
primary_map[0xFF] = modrm_group_5
