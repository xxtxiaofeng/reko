// test.h
// Generated by decompiling test
// using Reko decompiler version 0.9.1.0.

/*
// Equivalence classes ////////////
Eq_1: (struct "Globals" (FFFFFFFF code tFFFFFFFF) (10A60 (ptr32 code) ptr10A60) (10AA4 int32 dw10AA4) (10AAC word32 dw10AAC) (10AB0 int32 dw10AB0) (10ABC (ptr32 (ptr32 code)) ptr10ABC) (10AD4 (ptr32 code) ptr10AD4) (10AE4 (ptr32 code) ptr10AE4) (10AF0 byte b10AF0) (10AF4 Eq_63 t10AF4) (20A24 (ptr32 code) ptr20A24) (20A4C ptr32 ptr20A4C) (20A60 word32 dw20A60))
	globals_t (in globals : (ptr32 (struct "Globals")))
Eq_35: (union "Eq_35" (int32 u0) (uint32 u1))
	T_35 (in r5_12 : Eq_35)
	T_41 (in g_dw10AA4 - 0x10A84<32> >> 2<8> : word32)
Eq_43: (union "Eq_43" (int32 u0) (uint32 u1))
	T_43 (in r5_12 >> 0x1F<8> : word32)
Eq_44: (union "Eq_44" (int32 u0) (uint32 u1))
	T_44 (in (r5_12 >>u 0x1F<8>) + r5_12 : word32)
Eq_63: (union "Eq_63" (int32 u0) (uint32 u1))
	T_63 (in r2_40 : Eq_63)
	T_65 (in Mem19[0x10AF4<32>:word32] : word32)
	T_66 (in r16_42 : Eq_63)
	T_74 (in (g_dw10AB0 - 0x10A68<32> >> 2<8>) + -1<i32> : word32)
	T_92 (in r2_47 : Eq_63)
	T_94 (in r2_40 + 1<i32> : word32)
	T_96 (in Mem50[0x10AF4<32>:word32] : word32)
	T_107 (in Mem50[0x10AF4<32>:word32] : word32)
Eq_86: (fn void ())
	T_86 (in deregister_tm_clones : ptr32)
	T_87 (in signature of deregister_tm_clones : void)
Eq_93: (union "Eq_93" (int32 u0) (up32 u1))
	T_93 (in 1<i32> : int32)
Eq_112: (fn void ())
	T_112 (in register_tm_clones : ptr32)
	T_113 (in signature of register_tm_clones : void)
Eq_115: (fn (ptr32 void) ((ptr32 void), int32, Eq_119))
	T_115 (in memset : ptr32)
	T_116 (in signature of memset : void)
Eq_119: (union "Eq_119" (int32 u0) (size_t u1))
	T_119 (in num : size_t)
	T_124 (in 5<i32> : int32)
	T_129 (in num : size_t)
	T_130 (in size : size_t)
	T_131 (in 1<i32> : int32)
	T_132 (in 5<i32> : int32)
Eq_126: (struct "Eq_126" (0 Eq_134 t0000) (1 word32 dw0001) (4 byte b0004))
	T_126 (in r2_38 : (ptr32 Eq_126))
	T_133 (in calloc(1<i32>, 5<i32>) : (ptr32 void))
	T_152 (in r2_43 : word32)
	T_154 (in r2_52 : word32)
Eq_127: (fn (ptr32 Eq_126) (Eq_119, Eq_119))
	T_127 (in calloc : ptr32)
	T_128 (in signature of calloc : void)
Eq_134: (union "Eq_134" (byte u0) (word32 u1))
	T_134 (in dwLoc14 : word32)
	T_137 (in Mem45[r2_38 + 0<32>:word32] : word32)
	T_144 (in 0xC<8> : byte)
	T_147 (in Mem51[r2_38 + 0<32>:byte] : byte)
	T_153 (in r3_44 : word32)
Eq_158: (fn void ())
	T_158 (in _init : ptr32)
	T_159 (in signature of _init : void)
Eq_197: (struct "Eq_197" (FFFF8010 (ptr32 code) ptrFFFF8010))
	T_197 (in r28 : (ptr32 Eq_197))
Eq_202: (struct "Eq_202" (FFFF8010 (ptr32 code) ptrFFFF8010))
	T_202 (in r28 : (ptr32 Eq_202))
Eq_207: (struct "Eq_207" (FFFF8010 (ptr32 code) ptrFFFF8010))
	T_207 (in r28 : (ptr32 Eq_207))
Eq_212: (fn void ())
	T_212 (in _fini : ptr32)
	T_213 (in signature of _fini : void)
// Type Variables ////////////
globals_t: (in globals : (ptr32 (struct "Globals")))
  Class: Eq_1
  DataType: (ptr32 Eq_1)
  OrigDataType: (ptr32 (struct "Globals"))
T_2: (in __gmon_start__ : ptr32)
  Class: Eq_2
  DataType: word32
  OrigDataType: 
T_3: (in signature of __gmon_start__ : void)
  Class: Eq_3
  DataType: Eq_3
  OrigDataType: 
T_4: (in 0<32> : word32)
  Class: Eq_2
  DataType: word32
  OrigDataType: word32
T_5: (in __gmon_start__ == 0<32> : bool)
  Class: Eq_5
  DataType: bool
  OrigDataType: bool
T_6: (in r25_16 : ptr32)
  Class: Eq_6
  DataType: ptr32
  OrigDataType: ptr32
T_7: (in 00020A4C : ptr32)
  Class: Eq_7
  DataType: (ptr32 ptr32)
  OrigDataType: (ptr32 (struct (0 T_8 t0000)))
T_8: (in Mem10[0x00020A4C<p32>:word32] : word32)
  Class: Eq_6
  DataType: ptr32
  OrigDataType: word32
T_9: (in 2004<i32> : int32)
  Class: Eq_9
  DataType: int32
  OrigDataType: int32
T_10: (in r25_16 + 2004<i32> : word32)
  Class: Eq_10
  DataType: (ptr32 code)
  OrigDataType: (ptr32 code)
T_11: (in r25_24 : ptr32)
  Class: Eq_6
  DataType: ptr32
  OrigDataType: ptr32
T_12: (in 00020A4C : ptr32)
  Class: Eq_12
  DataType: (ptr32 ptr32)
  OrigDataType: (ptr32 (struct (0 T_13 t0000)))
T_13: (in Mem10[0x00020A4C<p32>:word32] : word32)
  Class: Eq_6
  DataType: ptr32
  OrigDataType: word32
T_14: (in 2416<i32> : int32)
  Class: Eq_14
  DataType: int32
  OrigDataType: int32
T_15: (in r25_24 + 2416<i32> : word32)
  Class: Eq_15
  DataType: (ptr32 code)
  OrigDataType: (ptr32 code)
T_16: (in r25_31 : word32)
  Class: Eq_16
  DataType: word32
  OrigDataType: word32
T_17: (in __gmon_start__ : ptr32)
  Class: Eq_17
  DataType: (ptr32 code)
  OrigDataType: (ptr32 code)
T_18: (in signature of __gmon_start__ : void)
  Class: Eq_18
  DataType: Eq_18
  OrigDataType: 
T_19: (in r2 : word32)
  Class: Eq_19
  DataType: word32
  OrigDataType: word32
T_20: (in dwArg00 : word32)
  Class: Eq_20
  DataType: word32
  OrigDataType: word32
T_21: (in r8_19 : word32)
  Class: Eq_21
  DataType: word32
  OrigDataType: word32
T_22: (in 00020A60 : ptr32)
  Class: Eq_22
  DataType: (ptr32 word32)
  OrigDataType: (ptr32 (struct (0 T_23 t0000)))
T_23: (in Mem0[0x00020A60<p32>:word32] : word32)
  Class: Eq_21
  DataType: word32
  OrigDataType: word32
T_24: (in 00020A24 : ptr32)
  Class: Eq_24
  DataType: (ptr32 (ptr32 code))
  OrigDataType: (ptr32 (struct (0 T_25 t0000)))
T_25: (in Mem23[0x00020A24<p32>:word32] : word32)
  Class: Eq_25
  DataType: (ptr32 code)
  OrigDataType: (ptr32 code)
T_26: (in 0x10AA4<32> : word32)
  Class: Eq_26
  DataType: (ptr32 int32)
  OrigDataType: (ptr32 (struct (0 T_27 t0000)))
T_27: (in Mem0[0x10AA4<32>:word32] : word32)
  Class: Eq_27
  DataType: int32
  OrigDataType: word32
T_28: (in 0x10A84<32> : word32)
  Class: Eq_27
  DataType: int32
  OrigDataType: word32
T_29: (in g_dw10AA4 == 0x10A84<32> : bool)
  Class: Eq_29
  DataType: bool
  OrigDataType: bool
T_30: (in r25_12 : (ptr32 code))
  Class: Eq_30
  DataType: (ptr32 code)
  OrigDataType: (ptr32 code)
T_31: (in 0<32> : word32)
  Class: Eq_30
  DataType: (ptr32 code)
  OrigDataType: word32
T_32: (in r25_12 == null : bool)
  Class: Eq_32
  DataType: bool
  OrigDataType: bool
T_33: (in 0x10AE4<32> : word32)
  Class: Eq_33
  DataType: (ptr32 (ptr32 code))
  OrigDataType: (ptr32 (struct (0 T_34 t0000)))
T_34: (in Mem0[0x10AE4<32>:word32] : word32)
  Class: Eq_30
  DataType: (ptr32 code)
  OrigDataType: word32
T_35: (in r5_12 : Eq_35)
  Class: Eq_35
  DataType: Eq_35
  OrigDataType: (union (int32 u1) (uint32 u0))
T_36: (in 0x10AA4<32> : word32)
  Class: Eq_36
  DataType: (ptr32 int32)
  OrigDataType: (ptr32 (struct (0 T_37 t0000)))
T_37: (in Mem0[0x10AA4<32>:word32] : word32)
  Class: Eq_27
  DataType: int32
  OrigDataType: int32
T_38: (in 0x10A84<32> : word32)
  Class: Eq_38
  DataType: int32
  OrigDataType: int32
T_39: (in g_dw10AA4 - 0x10A84<32> : word32)
  Class: Eq_39
  DataType: int32
  OrigDataType: int32
T_40: (in 2<8> : byte)
  Class: Eq_40
  DataType: byte
  OrigDataType: byte
T_41: (in g_dw10AA4 - 0x10A84<32> >> 2<8> : word32)
  Class: Eq_35
  DataType: Eq_35
  OrigDataType: int32
T_42: (in 0x1F<8> : byte)
  Class: Eq_42
  DataType: byte
  OrigDataType: byte
T_43: (in r5_12 >> 0x1F<8> : word32)
  Class: Eq_43
  DataType: Eq_43
  OrigDataType: (union (int32 u1) (uint32 u0))
T_44: (in (r5_12 >>u 0x1F<8>) + r5_12 : word32)
  Class: Eq_44
  DataType: Eq_44
  OrigDataType: (union (int32 u1) (uint32 u0))
T_45: (in 1<8> : byte)
  Class: Eq_45
  DataType: byte
  OrigDataType: byte
T_46: (in (r5_12 >>u 0x1F<8>) + r5_12 >> 1<8> : word32)
  Class: Eq_46
  DataType: int32
  OrigDataType: int32
T_47: (in 0<32> : word32)
  Class: Eq_46
  DataType: int32
  OrigDataType: word32
T_48: (in (r5_12 >>u 0x1F<8>) + r5_12 >> 1<8> == 0<32> : bool)
  Class: Eq_48
  DataType: bool
  OrigDataType: bool
T_49: (in r25_17 : (ptr32 code))
  Class: Eq_49
  DataType: (ptr32 code)
  OrigDataType: (ptr32 code)
T_50: (in 0x10AD4<32> : word32)
  Class: Eq_50
  DataType: (ptr32 (ptr32 code))
  OrigDataType: (ptr32 (struct (0 T_51 t0000)))
T_51: (in Mem0[0x10AD4<32>:word32] : word32)
  Class: Eq_49
  DataType: (ptr32 code)
  OrigDataType: word32
T_52: (in 0<32> : word32)
  Class: Eq_49
  DataType: (ptr32 code)
  OrigDataType: word32
T_53: (in r25_17 == null : bool)
  Class: Eq_53
  DataType: bool
  OrigDataType: bool
T_54: (in 0x10AF0<32> : word32)
  Class: Eq_54
  DataType: (ptr32 byte)
  OrigDataType: (ptr32 (struct (0 T_55 t0000)))
T_55: (in Mem19[0x10AF0<32>:byte] : byte)
  Class: Eq_55
  DataType: byte
  OrigDataType: byte
T_56: (in (word32) Mem19[0x10AF0<32>:byte] : word32)
  Class: Eq_56
  DataType: word32
  OrigDataType: word32
T_57: (in 0<32> : word32)
  Class: Eq_56
  DataType: word32
  OrigDataType: word32
T_58: (in (word32) g_b10AF0 != 0<32> : bool)
  Class: Eq_58
  DataType: bool
  OrigDataType: bool
T_59: (in __cxa_finalize : ptr32)
  Class: Eq_59
  DataType: word32
  OrigDataType: 
T_60: (in signature of __cxa_finalize : void)
  Class: Eq_60
  DataType: Eq_60
  OrigDataType: 
T_61: (in 0<32> : word32)
  Class: Eq_59
  DataType: word32
  OrigDataType: word32
T_62: (in __cxa_finalize == 0<32> : bool)
  Class: Eq_62
  DataType: bool
  OrigDataType: bool
T_63: (in r2_40 : Eq_63)
  Class: Eq_63
  DataType: Eq_63
  OrigDataType: up32
T_64: (in 0x10AF4<32> : word32)
  Class: Eq_64
  DataType: (ptr32 Eq_63)
  OrigDataType: (ptr32 (struct (0 T_65 t0000)))
T_65: (in Mem19[0x10AF4<32>:word32] : word32)
  Class: Eq_63
  DataType: Eq_63
  OrigDataType: word32
T_66: (in r16_42 : Eq_63)
  Class: Eq_63
  DataType: Eq_63
  OrigDataType: (union (int32 u0) (uint32 u1))
T_67: (in 0x10AB0<32> : word32)
  Class: Eq_67
  DataType: (ptr32 int32)
  OrigDataType: (ptr32 (struct (0 T_68 t0000)))
T_68: (in Mem19[0x10AB0<32>:word32] : word32)
  Class: Eq_68
  DataType: int32
  OrigDataType: int32
T_69: (in 0x10A68<32> : word32)
  Class: Eq_69
  DataType: int32
  OrigDataType: int32
T_70: (in g_dw10AB0 - 0x10A68<32> : word32)
  Class: Eq_70
  DataType: int32
  OrigDataType: int32
T_71: (in 2<8> : byte)
  Class: Eq_71
  DataType: byte
  OrigDataType: byte
T_72: (in g_dw10AB0 - 0x10A68<32> >> 2<8> : word32)
  Class: Eq_72
  DataType: int32
  OrigDataType: int32
T_73: (in -1<i32> : int32)
  Class: Eq_73
  DataType: int32
  OrigDataType: int32
T_74: (in (g_dw10AB0 - 0x10A68<32> >> 2<8>) + -1<i32> : word32)
  Class: Eq_63
  DataType: Eq_63
  OrigDataType: int32
T_75: (in r2_40 < r16_42 : bool)
  Class: Eq_75
  DataType: bool
  OrigDataType: bool
T_76: (in (word32) (r2_40 <u r16_42) : word32)
  Class: Eq_76
  DataType: word32
  OrigDataType: word32
T_77: (in 0<32> : word32)
  Class: Eq_76
  DataType: word32
  OrigDataType: word32
T_78: (in (word32) (r2_40 < r16_42) == 0<32> : bool)
  Class: Eq_78
  DataType: bool
  OrigDataType: bool
T_79: (in r25_27 : word32)
  Class: Eq_79
  DataType: word32
  OrigDataType: word32
T_80: (in r3_30 : word32)
  Class: Eq_80
  DataType: word32
  OrigDataType: word32
T_81: (in __cxa_finalize : ptr32)
  Class: Eq_81
  DataType: (ptr32 code)
  OrigDataType: (ptr32 code)
T_82: (in signature of __cxa_finalize : void)
  Class: Eq_82
  DataType: Eq_82
  OrigDataType: 
T_83: (in r2_24 : word32)
  Class: Eq_83
  DataType: word32
  OrigDataType: word32
T_84: (in 0x10AAC<32> : word32)
  Class: Eq_84
  DataType: (ptr32 word32)
  OrigDataType: (ptr32 (struct (0 T_85 t0000)))
T_85: (in Mem19[0x10AAC<32>:word32] : word32)
  Class: Eq_83
  DataType: word32
  OrigDataType: word32
T_86: (in deregister_tm_clones : ptr32)
  Class: Eq_86
  DataType: (ptr32 Eq_86)
  OrigDataType: (ptr32 (fn T_88 ()))
T_87: (in signature of deregister_tm_clones : void)
  Class: Eq_86
  DataType: (ptr32 Eq_86)
  OrigDataType: 
T_88: (in deregister_tm_clones() : void)
  Class: Eq_88
  DataType: void
  OrigDataType: void
T_89: (in 1<8> : byte)
  Class: Eq_55
  DataType: byte
  OrigDataType: byte
T_90: (in 0x10AF0<32> : word32)
  Class: Eq_90
  DataType: (ptr32 byte)
  OrigDataType: (ptr32 (struct (0 T_91 t0000)))
T_91: (in Mem76[0x10AF0<32>:byte] : byte)
  Class: Eq_55
  DataType: byte
  OrigDataType: byte
T_92: (in r2_47 : Eq_63)
  Class: Eq_63
  DataType: Eq_63
  OrigDataType: uint32
T_93: (in 1<i32> : int32)
  Class: Eq_93
  DataType: int32
  OrigDataType: (union (int32 u0) (up32 u1))
T_94: (in r2_40 + 1<i32> : word32)
  Class: Eq_63
  DataType: Eq_63
  OrigDataType: up32
T_95: (in 0x10AF4<32> : word32)
  Class: Eq_95
  DataType: (ptr32 Eq_63)
  OrigDataType: (ptr32 (struct (0 T_96 t0000)))
T_96: (in Mem50[0x10AF4<32>:word32] : word32)
  Class: Eq_63
  DataType: Eq_63
  OrigDataType: word32
T_97: (in r2_52 : (ptr32 (ptr32 code)))
  Class: Eq_97
  DataType: (ptr32 (ptr32 code))
  OrigDataType: (ptr32 (struct (0 T_105 t0000)))
T_98: (in 2<8> : byte)
  Class: Eq_98
  DataType: byte
  OrigDataType: byte
T_99: (in r2_47 << 2<8> : word32)
  Class: Eq_99
  DataType: ui32
  OrigDataType: ui32
T_100: (in 0x10A68<32> : word32)
  Class: Eq_100
  DataType: word32
  OrigDataType: word32
T_101: (in (r2_47 << 2<8>) + 0x10A68<32> : word32)
  Class: Eq_97
  DataType: (ptr32 (ptr32 code))
  OrigDataType: ui32
T_102: (in r4_60 : word32)
  Class: Eq_102
  DataType: word32
  OrigDataType: word32
T_103: (in 0<32> : word32)
  Class: Eq_103
  DataType: word32
  OrigDataType: word32
T_104: (in r2_52 + 0<32> : word32)
  Class: Eq_104
  DataType: ui32
  OrigDataType: ui32
T_105: (in Mem50[r2_52 + 0<32>:word32] : word32)
  Class: Eq_105
  DataType: (ptr32 code)
  OrigDataType: (ptr32 code)
T_106: (in 0x10AF4<32> : word32)
  Class: Eq_106
  DataType: (ptr32 Eq_63)
  OrigDataType: (ptr32 (struct (0 T_107 t0000)))
T_107: (in Mem50[0x10AF4<32>:word32] : word32)
  Class: Eq_63
  DataType: Eq_63
  OrigDataType: word32
T_108: (in r2_40 < r16_42 : bool)
  Class: Eq_108
  DataType: bool
  OrigDataType: bool
T_109: (in (word32) (r2_40 <u r16_42) : word32)
  Class: Eq_109
  DataType: word32
  OrigDataType: word32
T_110: (in 0<32> : word32)
  Class: Eq_109
  DataType: word32
  OrigDataType: word32
T_111: (in (word32) (r2_40 < r16_42) != 0<32> : bool)
  Class: Eq_111
  DataType: bool
  OrigDataType: bool
T_112: (in register_tm_clones : ptr32)
  Class: Eq_112
  DataType: (ptr32 Eq_112)
  OrigDataType: (ptr32 (fn T_114 ()))
T_113: (in signature of register_tm_clones : void)
  Class: Eq_112
  DataType: (ptr32 Eq_112)
  OrigDataType: 
T_114: (in register_tm_clones() : void)
  Class: Eq_114
  DataType: void
  OrigDataType: void
T_115: (in memset : ptr32)
  Class: Eq_115
  DataType: (ptr32 Eq_115)
  OrigDataType: (ptr32 (fn T_125 (T_122, T_123, T_124)))
T_116: (in signature of memset : void)
  Class: Eq_115
  DataType: (ptr32 Eq_115)
  OrigDataType: 
T_117: (in r4 : (ptr32 void))
  Class: Eq_117
  DataType: (ptr32 void)
  OrigDataType: 
T_118: (in value : int32)
  Class: Eq_118
  DataType: int32
  OrigDataType: 
T_119: (in num : size_t)
  Class: Eq_119
  DataType: Eq_119
  OrigDataType: 
T_120: (in fp : ptr32)
  Class: Eq_120
  DataType: ptr32
  OrigDataType: ptr32
T_121: (in -20<i32> : int32)
  Class: Eq_121
  DataType: int32
  OrigDataType: int32
T_122: (in fp + -20<i32> : word32)
  Class: Eq_117
  DataType: (ptr32 void)
  OrigDataType: (ptr32 void)
T_123: (in 0<32> : word32)
  Class: Eq_118
  DataType: int32
  OrigDataType: int32
T_124: (in 5<i32> : int32)
  Class: Eq_119
  DataType: int32
  OrigDataType: (union (int32 u0) (size_t u1))
T_125: (in memset(fp + -20<i32>, 0<32>, 5<i32>) : (ptr32 void))
  Class: Eq_125
  DataType: (ptr32 void)
  OrigDataType: (ptr32 void)
T_126: (in r2_38 : (ptr32 Eq_126))
  Class: Eq_126
  DataType: (ptr32 Eq_126)
  OrigDataType: (ptr32 (struct (0 T_134 t0000) (1 T_151 t0001) (4 T_143 t0004)))
T_127: (in calloc : ptr32)
  Class: Eq_127
  DataType: (ptr32 Eq_127)
  OrigDataType: (ptr32 (fn T_133 (T_131, T_132)))
T_128: (in signature of calloc : void)
  Class: Eq_127
  DataType: (ptr32 Eq_127)
  OrigDataType: 
T_129: (in num : size_t)
  Class: Eq_119
  DataType: Eq_119
  OrigDataType: 
T_130: (in size : size_t)
  Class: Eq_119
  DataType: Eq_119
  OrigDataType: 
T_131: (in 1<i32> : int32)
  Class: Eq_119
  DataType: int32
  OrigDataType: (union (int32 u0) (size_t u1))
T_132: (in 5<i32> : int32)
  Class: Eq_119
  DataType: int32
  OrigDataType: (union (int32 u0) (size_t u1))
T_133: (in calloc(1<i32>, 5<i32>) : (ptr32 void))
  Class: Eq_126
  DataType: (ptr32 Eq_126)
  OrigDataType: (ptr32 void)
T_134: (in dwLoc14 : word32)
  Class: Eq_134
  DataType: Eq_134
  OrigDataType: word32
T_135: (in 0<32> : word32)
  Class: Eq_135
  DataType: word32
  OrigDataType: word32
T_136: (in r2_38 + 0<32> : word32)
  Class: Eq_136
  DataType: ptr32
  OrigDataType: ptr32
T_137: (in Mem45[r2_38 + 0<32>:word32] : word32)
  Class: Eq_134
  DataType: Eq_134
  OrigDataType: word32
T_138: (in bLoc10 : byte)
  Class: Eq_138
  DataType: byte
  OrigDataType: byte
T_139: (in (word32) bLoc10 : word32)
  Class: Eq_139
  DataType: word32
  OrigDataType: word32
T_140: (in (byte) (word32) bLoc10 : byte)
  Class: Eq_140
  DataType: byte
  OrigDataType: byte
T_141: (in 4<32> : word32)
  Class: Eq_141
  DataType: word32
  OrigDataType: word32
T_142: (in r2_38 + 4<32> : word32)
  Class: Eq_142
  DataType: ptr32
  OrigDataType: ptr32
T_143: (in Mem48[r2_38 + 4<32>:byte] : byte)
  Class: Eq_140
  DataType: byte
  OrigDataType: byte
T_144: (in 0xC<8> : byte)
  Class: Eq_134
  DataType: byte
  OrigDataType: byte
T_145: (in 0<32> : word32)
  Class: Eq_145
  DataType: word32
  OrigDataType: word32
T_146: (in r2_38 + 0<32> : word32)
  Class: Eq_146
  DataType: (ptr32 word32)
  OrigDataType: (ptr32 word32)
T_147: (in Mem51[r2_38 + 0<32>:byte] : byte)
  Class: Eq_134
  DataType: Eq_134
  OrigDataType: byte
T_148: (in 0<32> : word32)
  Class: Eq_148
  DataType: word32
  OrigDataType: word32
T_149: (in 1<32> : word32)
  Class: Eq_149
  DataType: word32
  OrigDataType: word32
T_150: (in r2_38 + 1<32> : word32)
  Class: Eq_150
  DataType: ptr32
  OrigDataType: ptr32
T_151: (in Mem53[r2_38 + 1<32>:word32] : word32)
  Class: Eq_148
  DataType: word32
  OrigDataType: word32
T_152: (in r2_43 : word32)
  Class: Eq_126
  DataType: (ptr32 Eq_126)
  OrigDataType: (ptr32 (struct (0 T_134 t0000) (1 T_151 t0001) (4 T_143 t0004)))
T_153: (in r3_44 : word32)
  Class: Eq_134
  DataType: Eq_134
  OrigDataType: word32
T_154: (in r2_52 : word32)
  Class: Eq_126
  DataType: (ptr32 Eq_126)
  OrigDataType: (ptr32 (struct (0 T_134 t0000) (1 T_151 t0001) (4 T_143 t0004)))
T_155: (in r4 : word32)
  Class: Eq_155
  DataType: word32
  OrigDataType: word32
T_156: (in r5 : word32)
  Class: Eq_156
  DataType: word32
  OrigDataType: word32
T_157: (in r6 : word32)
  Class: Eq_157
  DataType: word32
  OrigDataType: word32
T_158: (in _init : ptr32)
  Class: Eq_158
  DataType: (ptr32 Eq_158)
  OrigDataType: (ptr32 (fn T_160 ()))
T_159: (in signature of _init : void)
  Class: Eq_158
  DataType: (ptr32 Eq_158)
  OrigDataType: 
T_160: (in _init() : void)
  Class: Eq_160
  DataType: void
  OrigDataType: void
T_161: (in r16_35 : (ptr32 (ptr32 code)))
  Class: Eq_161
  DataType: (ptr32 (ptr32 code))
  OrigDataType: (ptr32 (struct 0004 (0 (ptr32 code) ptr0000)))
T_162: (in 0x10ABC<32> : word32)
  Class: Eq_162
  DataType: (ptr32 (ptr32 (ptr32 code)))
  OrigDataType: (ptr32 (struct (0 T_163 t0000)))
T_163: (in Mem30[0x10ABC<32>:word32] : word32)
  Class: Eq_161
  DataType: (ptr32 (ptr32 code))
  OrigDataType: word32
T_164: (in r18_37 : int32)
  Class: Eq_164
  DataType: int32
  OrigDataType: int32
T_165: (in 0x10ABC<32> : word32)
  Class: Eq_165
  DataType: (ptr32 (ptr32 (ptr32 code)))
  OrigDataType: (ptr32 (struct (0 T_166 t0000)))
T_166: (in Mem30[0x10ABC<32>:word32] : word32)
  Class: Eq_161
  DataType: (ptr32 (ptr32 code))
  OrigDataType: word32
T_167: (in g_ptr10ABC - r16_35 : word32)
  Class: Eq_164
  DataType: int32
  OrigDataType: word32
T_168: (in 2<8> : byte)
  Class: Eq_168
  DataType: byte
  OrigDataType: byte
T_169: (in r18_37 >> 2<8> : word32)
  Class: Eq_169
  DataType: int32
  OrigDataType: int32
T_170: (in 0<32> : word32)
  Class: Eq_169
  DataType: int32
  OrigDataType: word32
T_171: (in r18_37 >> 2<8> == 0<32> : bool)
  Class: Eq_171
  DataType: bool
  OrigDataType: bool
T_172: (in 0<32> : word32)
  Class: Eq_172
  DataType: word32
  OrigDataType: word32
T_173: (in r16_35 + 0<32> : word32)
  Class: Eq_173
  DataType: word32
  OrigDataType: word32
T_174: (in Mem30[r16_35 + 0<32>:word32] : word32)
  Class: Eq_174
  DataType: (ptr32 code)
  OrigDataType: (ptr32 code)
T_175: (in r17_40 : int32)
  Class: Eq_175
  DataType: int32
  OrigDataType: word32
T_176: (in 1<i32> : int32)
  Class: Eq_176
  DataType: int32
  OrigDataType: int32
T_177: (in r17_40 + 1<i32> : word32)
  Class: Eq_175
  DataType: int32
  OrigDataType: word32
T_178: (in r18_37 >> 2<8> : word32)
  Class: Eq_175
  DataType: int32
  OrigDataType: int32
T_179: (in r18_37 >> 2<8> != r17_40 : bool)
  Class: Eq_179
  DataType: bool
  OrigDataType: bool
T_180: (in 0<32> : word32)
  Class: Eq_175
  DataType: int32
  OrigDataType: word32
T_181: (in 4<i32> : int32)
  Class: Eq_181
  DataType: int32
  OrigDataType: int32
T_182: (in r16_35 + 4<i32> : word32)
  Class: Eq_161
  DataType: (ptr32 (ptr32 code))
  OrigDataType: ptr32
T_183: (in r25_18 : (ptr32 code))
  Class: Eq_183
  DataType: (ptr32 code)
  OrigDataType: (ptr32 code)
T_184: (in 0x10A60<32> : word32)
  Class: Eq_184
  DataType: (ptr32 (ptr32 code))
  OrigDataType: (ptr32 (struct (0 T_185 t0000)))
T_185: (in Mem17[0x10A60<32>:word32] : word32)
  Class: Eq_183
  DataType: (ptr32 code)
  OrigDataType: word32
T_186: (in -1<i32> : int32)
  Class: Eq_183
  DataType: (ptr32 code)
  OrigDataType: int32
T_187: (in r25_18 == (<anonymous> *) -1<i32> : bool)
  Class: Eq_187
  DataType: bool
  OrigDataType: bool
T_188: (in r16_21 : (ptr32 word32))
  Class: Eq_188
  DataType: (ptr32 word32)
  OrigDataType: (ptr32 (struct 0004 (0 word32 dw0000)))
T_189: (in 0x10A60<32> : word32)
  Class: Eq_188
  DataType: (ptr32 word32)
  OrigDataType: word32
T_190: (in -4<i32> : int32)
  Class: Eq_190
  DataType: int32
  OrigDataType: int32
T_191: (in r16_21 + -4<i32> : word32)
  Class: Eq_188
  DataType: (ptr32 word32)
  OrigDataType: word32
T_192: (in 0<32> : word32)
  Class: Eq_192
  DataType: word32
  OrigDataType: word32
T_193: (in r16_21 + 0<32> : word32)
  Class: Eq_193
  DataType: word32
  OrigDataType: word32
T_194: (in Mem17[r16_21 + 0<32>:word32] : word32)
  Class: Eq_183
  DataType: (ptr32 code)
  OrigDataType: word32
T_195: (in -1<i32> : int32)
  Class: Eq_183
  DataType: (ptr32 code)
  OrigDataType: int32
T_196: (in r25_18 != (<anonymous> *) -1<i32> : bool)
  Class: Eq_196
  DataType: bool
  OrigDataType: bool
T_197: (in r28 : (ptr32 Eq_197))
  Class: Eq_197
  DataType: (ptr32 Eq_197)
  OrigDataType: (ptr32 (struct (FFFF8010 T_201 tFFFF8010)))
T_198: (in ra : word32)
  Class: Eq_198
  DataType: word32
  OrigDataType: word32
T_199: (in -32752<i32> : int32)
  Class: Eq_199
  DataType: int32
  OrigDataType: int32
T_200: (in r28 + -32752<i32> : word32)
  Class: Eq_200
  DataType: word32
  OrigDataType: word32
T_201: (in Mem0[r28 + -32752<i32>:word32] : word32)
  Class: Eq_201
  DataType: (ptr32 code)
  OrigDataType: (ptr32 code)
T_202: (in r28 : (ptr32 Eq_202))
  Class: Eq_202
  DataType: (ptr32 Eq_202)
  OrigDataType: (ptr32 (struct (FFFF8010 T_206 tFFFF8010)))
T_203: (in ra : word32)
  Class: Eq_203
  DataType: word32
  OrigDataType: word32
T_204: (in -32752<i32> : int32)
  Class: Eq_204
  DataType: int32
  OrigDataType: int32
T_205: (in r28 + -32752<i32> : word32)
  Class: Eq_205
  DataType: word32
  OrigDataType: word32
T_206: (in Mem0[r28 + -32752<i32>:word32] : word32)
  Class: Eq_206
  DataType: (ptr32 code)
  OrigDataType: (ptr32 code)
T_207: (in r28 : (ptr32 Eq_207))
  Class: Eq_207
  DataType: (ptr32 Eq_207)
  OrigDataType: (ptr32 (struct (FFFF8010 T_211 tFFFF8010)))
T_208: (in ra : word32)
  Class: Eq_208
  DataType: word32
  OrigDataType: word32
T_209: (in -32752<i32> : int32)
  Class: Eq_209
  DataType: int32
  OrigDataType: int32
T_210: (in r28 + -32752<i32> : word32)
  Class: Eq_210
  DataType: word32
  OrigDataType: word32
T_211: (in Mem0[r28 + -32752<i32>:word32] : word32)
  Class: Eq_211
  DataType: (ptr32 code)
  OrigDataType: (ptr32 code)
T_212: (in _fini : ptr32)
  Class: Eq_212
  DataType: (ptr32 Eq_212)
  OrigDataType: (ptr32 (fn T_214 ()))
T_213: (in signature of _fini : void)
  Class: Eq_212
  DataType: (ptr32 Eq_212)
  OrigDataType: 
T_214: (in _fini() : void)
  Class: Eq_214
  DataType: void
  OrigDataType: void
T_215: (in r25_15 : ptr32)
  Class: Eq_6
  DataType: ptr32
  OrigDataType: ptr32
T_216: (in 00020A4C : ptr32)
  Class: Eq_216
  DataType: (ptr32 ptr32)
  OrigDataType: (ptr32 (struct (0 T_217 t0000)))
T_217: (in Mem10[0x00020A4C<p32>:word32] : word32)
  Class: Eq_6
  DataType: ptr32
  OrigDataType: word32
T_218: (in 1780<i32> : int32)
  Class: Eq_218
  DataType: int32
  OrigDataType: int32
T_219: (in r25_15 + 1780<i32> : word32)
  Class: Eq_219
  DataType: (ptr32 code)
  OrigDataType: (ptr32 code)
*/
typedef struct Globals {
	<anonymous> tFFFFFFFF;	// FFFFFFFF
	<anonymous> * ptr10A60;	// 10A60
	int32 dw10AA4;	// 10AA4
	word32 dw10AAC;	// 10AAC
	int32 dw10AB0;	// 10AB0
	<anonymous> ** ptr10ABC;	// 10ABC
	<anonymous> * ptr10AD4;	// 10AD4
	<anonymous> * ptr10AE4;	// 10AE4
	byte b10AF0;	// 10AF0
	Eq_63 t10AF4;	// 10AF4
	<anonymous> * ptr20A24;	// 20A24
	ptr32 ptr20A4C;	// 20A4C
	word32 dw20A60;	// 20A60
} Eq_1;

typedef union Eq_35 {
	int32 u0;
	uint32 u1;
} Eq_35;

typedef union Eq_43 {
	int32 u0;
	uint32 u1;
} Eq_43;

typedef union Eq_44 {
	int32 u0;
	uint32 u1;
} Eq_44;

typedef union Eq_63 {
	int32 u0;
	uint32 u1;
} Eq_63;

typedef void (Eq_86)();

typedef union Eq_93 {
	int32 u0;
	up32 u1;
} Eq_93;

typedef void (Eq_112)();

typedef void (Eq_115)(void, int32, Eq_119);

typedef union Eq_119 {
	int32 u0;
	size_t u1;
} Eq_119;

typedef struct Eq_126 {
	Eq_134 t0000;	// 0
	word32 dw0001;	// 1
	byte b0004;	// 4
} Eq_126;

typedef Eq_126 * (Eq_127)(Eq_119, Eq_119);

typedef union Eq_134 {
	byte u0;
	word32 u1;
} Eq_134;

typedef void (Eq_158)();

typedef struct Eq_197 {
	<anonymous> * ptrFFFF8010;	// FFFF8010
} Eq_197;

typedef struct Eq_202 {
	<anonymous> * ptrFFFF8010;	// FFFF8010
} Eq_202;

typedef struct Eq_207 {
	<anonymous> * ptrFFFF8010;	// FFFF8010
} Eq_207;

typedef void (Eq_212)();

