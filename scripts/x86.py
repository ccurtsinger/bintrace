# From http://support.amd.com/us/Processor_TechDocs/24594_APM_v3.pdf
# See page 419 for the start of the opcode tables

# Decoding process from page 2
# Suffix = ModRM => SIB? => Disp? => (Imm? | 3DNow)

#def mode(legacy, long):
#	return '32: '+str(legacy)+', 64: '+str(long)

#def inst(mnemonic, *ops):
#	return (mnemonic, ops)

def prefix(name):
	def decoder(i, b, bytes):
		i.prefixes.append(name)
		return (False, primary)
	return decoder

def inst(mnemonic, *ops):
	def decoder(i, b, bytes):
		i.mnemonic = mnemonic
		i.operands = ops
		return (True, primary)
	return decoder

def mode(legacy, long):
	return long

# Operands
Ap = 'Ap'
Eb = 'Eb'
Ev = 'Ev'
Ew = 'Ew'
Ed = 'Ed'
Fv = 'Fv'
Gb = 'Gb'
Gv = 'Gv'
Gw = 'Gw'
Gz = 'Gz'
Ib = 'Ib'
Iv = 'Iv'
Iw = 'Iw'
Iz = 'Iz'
Jb = 'Jb'
Jz = 'Jz'
M = 'M'
Ma = 'Ma'
Mp = 'Mp'
MwRv = 'Mw/Rv'
Ob = 'Ob'
Ov = 'Ov'
Sw = 'Sw'
Xb = 'Xb'
Xv = 'Xv'
Xz = 'Xz'
Yb = 'Yb'
Yv = 'Yv'
Yz = 'Yz'

AL = 'AL'
eAX = 'eAX'
rAX = 'rAX'
eCX = 'eCX'
DX = 'DX'
eDX = 'eDX'
eBX = 'eBX'
eSP = 'eSP'
eBP = 'eBP'
eSI = 'eSI'
eDI = 'eDI'
r8 = 'r8'

# Long mode REX.B selected registers
rAXr8 = 'rAX or r8'
rCXr9 = 'rCX or r9'
rDXr10 = 'rDX or r10'
rBXr11 = 'rBX or r11'
rSPr12 = 'rSP or r12'
rBPr13 = 'rBP or r13'
rSIr14 = 'rSI or r14'
rDIr15 = 'rDI or r15'

ALr8b = 'AL or r8b'
CLr9b = 'CL or r9b'
DLr10b = 'DL or r10b'
BLr11b = 'BL or r11b'
AHr12b = 'AH or r12b'
CHr13b = 'CH or r13b'
DHr14b = 'DH or r14b'
BHr15b = 'BH or r15b'

# Segment registers
CS = 'CS'
DS = 'DS'
ES = 'ES'
FS = 'FS'
GS = 'GS'
SS = 'SS'

# Segment prefixes
CSprefix = prefix('CS')
DSprefix = prefix('DS')
ESprefix = prefix('ES')
FSprefix = prefix('FS')
GSprefix = prefix('GS')
SSprefix = prefix('SS')

# Common instructions
nop = 'no op'
invalid = 'invalid'

# Prefixes
opSizePrefix = prefix('opSize')
addrSizePrefix = prefix('addrSize')
repnePrefix = prefix('repne')
repPrefix = prefix('repe')
nullPrefix = prefix('null')
lockPrefix = prefix('lock')
rexPrefix = prefix('REX')
vexPrefix = prefix('VEX')

# ModRM.reg extensions
group1 = 'ModRM Group 1'
group1a = 'ModRM Group 1a'
group2 = 'ModRM Group 2'
group3 = 'ModRM Group 3'
group4 = 'ModRM Group 4'
group5 = 'ModRM Group 5'
group6 = 'ModRM Group 6'
group7 = 'ModRM Group 7'
group8 = 'ModRM Group 8'
group9 = 'ModRM Group 9'
group10 = 'ModRM Group 10'
group11 = 'ModRM Group 11'
group12 = 'ModRM Group 12'
group13 = 'ModRM Group 13'
group14 = 'ModRM Group 14'
group15 = 'ModRM Group 15'
group16 = 'ModRM Group 16'
group17 = 'ModRM Group 17'
groupP = 'ModRM Group P'

# Opcode Maps
primary = [None for i in range(0, 256)]
secondary = 'Secondary Map'
x87 = 'x87 map'

# Opcodes
primary[0x00] = inst('add', Eb, Gb)
primary[0x01] = inst('add', Ev, Gv)
primary[0x02] = inst('add', Gb, Eb)
primary[0x03] = inst('add', Gv, Ev)
primary[0x04] = inst('add', AL, Ib)
primary[0x05] = inst('add', rAX, Iz)
primary[0x06] = mode(legacy=inst('push', ES), long=invalid)
primary[0x07] = mode(legacy=inst('pop', ES), long=invalid)

primary[0x08] = inst('or', Eb, Gb)
primary[0x09] = inst('or', Ev, Gv)
primary[0x0A] = inst('or', Gb, Eb)
primary[0x0B] = inst('or', Gv, Ev)
primary[0x0C] = inst('or', AL, Ib)
primary[0x0D] = inst('or', rAX, Iz)
primary[0x0E] = mode(legacy=inst('push', CS), long=invalid)
primary[0x0F] = secondary

primary[0x10] = inst('adc', Eb, Gb)
primary[0x11] = inst('adc', Ev, Gv)
primary[0x12] = inst('adc', Gb, Eb)
primary[0x13] = inst('adc', Gv, Ev)
primary[0x14] = inst('adc', AL, Ib)
primary[0x15] = inst('adc', rAX, Iz)
primary[0x16] = mode(legacy=inst('push', SS), long=invalid)
primary[0x17] = mode(legacy=inst('pop', SS), long=invalid)

primary[0x18] = inst('sbb', Eb, Gb)
primary[0x19] = inst('sbb', Ev, Gv)
primary[0x1A] = inst('sbb', Gb, Eb)
primary[0x1B] = inst('sbb', Gv, Ev)
primary[0x1C] = inst('sbb', AL, Ib)
primary[0x1D] = inst('sbb', rAX, Iz)
primary[0x1E] = mode(legacy=inst('push', DS), long=invalid)
primary[0x1F] = mode(legacy=inst('pop', DS), long=invalid)

primary[0x20] = inst('and', Eb, Gb)
primary[0x21] = inst('and', Ev, Gv)
primary[0x22] = inst('and', Gb, Eb)
primary[0x23] = inst('and', Gv, Ev)
primary[0x24] = inst('and', AL, Ib)
primary[0x25] = inst('and', rAX, Iz)
primary[0x26] = mode(legacy=ESprefix, long=nullPrefix)
primary[0x27] = mode(legacy=inst('aaa'), long=invalid)

primary[0x28] = inst('sub', Eb, Gb)
primary[0x29] = inst('sub', Ev, Gv)
primary[0x2A] = inst('sub', Gb, Eb)
primary[0x2B] = inst('sub', Gv, Ev)
primary[0x2C] = inst('sub', AL, Ib)
primary[0x2D] = inst('sub', rAX, Iz)
primary[0x2E] = mode(legacy=CSprefix, long=nullPrefix)
primary[0x2F] = mode(legacy=inst('aas'), long=invalid)

primary[0x30] = inst('xor', Eb, Gb)
primary[0x31] = inst('xor', Ev, Gv)
primary[0x32] = inst('xor', Gb, Eb)
primary[0x33] = inst('xor', Gv, Ev)
primary[0x34] = inst('xor', AL, Ib)
primary[0x35] = inst('xor', rAX, Iz)
primary[0x36] = mode(legacy=SSprefix, long=nullPrefix)
primary[0x37] = mode(legacy=inst('aaa'), long=invalid)

primary[0x38] = inst('cmp', Eb, Gb)
primary[0x39] = inst('cmp', Ev, Gv)
primary[0x3A] = inst('cmp', Gb, Eb)
primary[0x3B] = inst('cmp', Gv, Ev)
primary[0x3C] = inst('cmp', AL, Ib)
primary[0x3D] = inst('cmp', rAX, Iz)
primary[0x3E] = mode(legacy=DSprefix, long=nullPrefix)
primary[0x3F] = mode(legacy=inst('aas'), long=invalid)

primary[0x40] = mode(legacy=inst('inc', eAX), long=rexPrefix)
primary[0x41] = mode(legacy=inst('inc', eCX), long=rexPrefix)
primary[0x42] = mode(legacy=inst('inc', eDX), long=rexPrefix)
primary[0x43] = mode(legacy=inst('inc', eBX), long=rexPrefix)
primary[0x44] = mode(legacy=inst('inc', eSP), long=rexPrefix)
primary[0x45] = mode(legacy=inst('inc', eBP), long=rexPrefix)
primary[0x46] = mode(legacy=inst('inc', eSI), long=rexPrefix)
primary[0x47] = mode(legacy=inst('inc', eDI), long=rexPrefix)

primary[0x48] = mode(legacy=inst('dec', eAX), long=rexPrefix)
primary[0x49] = mode(legacy=inst('dec', eCX), long=rexPrefix)
primary[0x4A] = mode(legacy=inst('dec', eDX), long=rexPrefix)
primary[0x4B] = mode(legacy=inst('dec', eBX), long=rexPrefix)
primary[0x4C] = mode(legacy=inst('dec', eSP), long=rexPrefix)
primary[0x4D] = mode(legacy=inst('dec', eBP), long=rexPrefix)
primary[0x4E] = mode(legacy=inst('dec', eSI), long=rexPrefix)
primary[0x4F] = mode(legacy=inst('dec', eDI), long=rexPrefix)

primary[0x50] = inst('push', rAXr8)
primary[0x51] = inst('push', rCXr9)
primary[0x52] = inst('push', rDXr10)
primary[0x53] = inst('push', rBXr11)
primary[0x54] = inst('push', rSPr12)
primary[0x55] = inst('push', rBPr13)
primary[0x56] = inst('push', rSIr14)
primary[0x57] = inst('push', rDIr15)

primary[0x58] = inst('pop', rAXr8)
primary[0x59] = inst('pop', rCXr9)
primary[0x5A] = inst('pop', rDXr10)
primary[0x5B] = inst('pop', rBXr11)
primary[0x5C] = inst('pop', rSPr12)
primary[0x5D] = inst('pop', rBPr13)
primary[0x5E] = inst('pop', rSIr14)
primary[0x5F] = inst('pop', rDIr15)

primary[0x60] = mode(legacy=inst('pusha'), long=invalid)
primary[0x61] = mode(legacy=inst('popa'), long=invalid)
primary[0x62] = mode(legacy=inst('bound', Gv, Ma), long=invalid)
primary[0x63] = mode(legacy=inst('arpl', Ew, Gw), long=inst('movsxd', Gv, Ed))
primary[0x64] = FSprefix
primary[0x65] = GSprefix
primary[0x66] = opSizePrefix
primary[0x67] = addrSizePrefix

primary[0x68] = inst('push', Iz)
primary[0x69] = inst('imul', Gv, Ev, Iz)
primary[0x6A] = inst('push', Ib)
primary[0x6B] = inst('imul', Gv, Ev, Ib)
primary[0x6C] = inst('ins', Yb, DX)
primary[0x6D] = inst('ins', Yz, DX)
primary[0x6E] = inst('outs', DX, Xb)
primary[0x6F] = inst('outs', DX, Xz)

primary[0x70] = inst('jo', Jb)
primary[0x71] = inst('jno', Jb)
primary[0x72] = inst('jb', Jb)
primary[0x73] = inst('jnb', Jb)
primary[0x74] = inst('jz', Jb)
primary[0x75] = inst('jnz', Jb)
primary[0x76] = inst('jbe', Jb)
primary[0x77] = inst('jnbe', Jb)

primary[0x78] = inst('js', Jb)
primary[0x79] = inst('jns', Jb)
primary[0x7A] = inst('jp', Jb)
primary[0x7B] = inst('jnp', Jb)
primary[0x7C] = inst('jl', Jb)
primary[0x7D] = inst('jnl', Jb)
primary[0x7E] = inst('jle', Jb)
primary[0x7F] = inst('jnle', Jb)

primary[0x80] = group1 # Eb, Ib
primary[0x81] = group1 # Ev, Iz
primary[0x82] = mode(legacy=group1, long=invalid) # Eb, Ib
primary[0x83] = group1 # Ev, Ib
primary[0x84] = inst('test', Eb, Gb)
primary[0x85] = inst('test', Ev, Gv)
primary[0x86] = inst('xchg', Eb, Gb)
primary[0x87] = inst('xchg', Ev, Gv)

primary[0x88] = inst('mov', Eb, Gb)
primary[0x89] = inst('mov', Ev, Gv)
primary[0x8A] = inst('mov', Gb, Eb)
primary[0x8B] = inst('mov', Gv, Ev)
primary[0x8C] = inst('mov', MwRv, Sw)
primary[0x8D] = inst('lea', Gv, M)
primary[0x8E] = inst('mov', Sw, Ew)
primary[0x8F] = group1a

primary[0x90] = inst('xchg', r8, rAX) # pause w/ repnePrefix
primary[0x91] = inst('xchg', rCXr9, rAX)
primary[0x92] = inst('xchg', rDXr10, rAX)
primary[0x93] = inst('xchg', rBXr11, rAX)
primary[0x94] = inst('xchg', rSPr12, rAX)
primary[0x95] = inst('xchg', rBPr13, rAX)
primary[0x96] = inst('xchg', rSIr14, rAX)
primary[0x97] = inst('xchg', rDIr15, rAX)

primary[0x98] = inst('cbw') # inst('cwde') or inst('cdqe')
primary[0x99] = inst('cwd') # inst('cdq') or inst('cqo')
primary[0x9A] = mode(legacy=inst('call', Ap), long=invalid)
primary[0x9B] = inst('wait') # inst('fwait')
primary[0x9C] = inst('push', Fv)
primary[0x9D] = inst('pop', Fv)
primary[0x9E] = inst('sahf')
primary[0x9F] = inst('lahf')

primary[0xA0] = inst('mov', AL, Ob)
primary[0xA1] = inst('mov', rAX, Ov)
primary[0xA2] = inst('mov', Ob, AL)
primary[0xA3] = inst('mov', Ov, rAX)
primary[0xA4] = inst('movsb', Yb, Xb)
primary[0xA5] = inst('movsw', Yv, Xv) # movsd, movsq
primary[0xA6] = inst('cmpsb', Xb, Yb)
primary[0xA7] = inst('cmpsw', Xv, Yv) # cmpsd, cmpsq

primary[0xA8] = inst('test', AL, Ib)
primary[0xA9] = inst('test', rAX, Iz)
primary[0xAA] = inst('stosb', Yb, AL)
primary[0xAB] = inst('stosw', Yv, rAX) # stosd, stosq
primary[0xAC] = inst('lodsb', AL, Xb)
primary[0xAD] = inst('lodsw', rAX, Xv) # lodsd, lodsq
primary[0xAE] = inst('scasb', AL, Yb)
primary[0xAF] = inst('scasw', rAX, Yv) # scasd, scasq

primary[0xB0] = inst('mov', ALr8b, Ib)
primary[0xB1] = inst('mov', CLr9b, Ib)
primary[0xB2] = inst('mov', DLr10b, Ib)
primary[0xB3] = inst('mov', BLr11b, Ib)
primary[0xB4] = inst('mov', AHr12b, Ib)
primary[0xB5] = inst('mov', CHr13b, Ib)
primary[0xB6] = inst('mov', DHr14b, Ib)
primary[0xB7] = inst('mov', BHr15b, Ib)

primary[0xB8] = inst('mov', rAXr8, Iv)
primary[0xB9] = inst('mov', rCXr9, Iv)
primary[0xBA] = inst('mov', rDXr10, Iv)
primary[0xBB] = inst('mov', rBXr11, Iv)
primary[0xBC] = inst('mov', rSPr12, Iv)
primary[0xBD] = inst('mov', rBPr13, Iv)
primary[0xBE] = inst('mov', rSIr14, Iv)
primary[0xBF] = inst('mov', rDIr15, Iv)

primary[0xC0] = group2 # Eb, Ib
primary[0xC1] = group2 # Ev, Ib
primary[0xC2] = inst('ret', Iw)
primary[0xC3] = inst('ret')
primary[0xC4] = mode(legacy=inst('les', Gz, Mp), long=vexPrefix)
primary[0xC5] = mode(legacy=inst('lds', Gz, Mp), long=vexPrefix)
primary[0xC6] = group11 # Eb, Ib
primary[0xC7] = group11 # Ev, Iz

primary[0xC8] = inst('enter', Iw, Ib)
primary[0xC9] = inst('leave')
primary[0xCA] = inst('ret', Iw)
primary[0xCB] = inst('ret')
primary[0xCC] = inst('int', 3)
primary[0xCD] = inst('int', Ib)
primary[0xCE] = mode(legacy=inst('into'), long=invalid)
primary[0xCF] = inst('iret') # iretd, iretq

primary[0xD0] = group2 # Eb, 1
primary[0xD1] = group2 # Ev, 1
primary[0xD2] = group2 # Eb, CL
primary[0xD3] = group2 # Ev, CL
primary[0xD4] = mode(legacy=inst('aam', Ib), long=invalid)
primary[0xD5] = mode(legacy=inst('aad', Ib), long=invalid)
primary[0xD6] = invalid
primary[0xD7] = inst('xlat') # xlatb

primary[0xD8] = x87
primary[0xD9] = x87
primary[0xDA] = x87
primary[0xDB] = x87
primary[0xDC] = x87
primary[0xDD] = x87
primary[0xDE] = x87
primary[0xDF] = x87

primary[0xE0] = inst('loopne', Jb) # loopnz
primary[0xE1] = inst('loope', Jb) # loopz
primary[0xE2] = inst('loop', Jb)
primary[0xE3] = inst('jrcxz', Jb)
primary[0xE4] = inst('in', AL, Ib)
primary[0xE5] = inst('in', eAX, Ib)
primary[0xE6] = inst('out', Ib, AL)
primary[0xE7] = inst('out', Ib, eAX)

primary[0xE8] = inst('call', Jz)
primary[0xE9] = inst('jmp', Jz)
primary[0xEA] = mode(legacy=inst('jmp', Ap), long=invalid)
primary[0xEB] = inst('jmp', Jb)
primary[0xEC] = inst('in', AL, DX)
primary[0xED] = inst('in', eAX, DX)
primary[0xEE] = inst('out', DX, AL)
primary[0xEF] = inst('out', DX, eAX)

primary[0xF0] = lockPrefix
primary[0xF1] = inst('int', 1)
primary[0xF2] = repnePrefix
primary[0xF3] = repPrefix
primary[0xF4] = inst('hlt')
primary[0xF5] = inst('cmc')
primary[0xF6] = group3 # Eb
primary[0xF7] = group3 # Ev

primary[0xF8] = inst('clc')
primary[0xF9] = inst('stc')
primary[0xFA] = inst('cli')
primary[0xFB] = inst('sti')
primary[0xFC] = inst('cld')
primary[0xFD] = inst('std')
primary[0xFE] = group4
primary[0xFF] = group5
