// TLCS-90.c
// Generated by decompiling TLCS-90.corpus
// using Reko decompiler version 0.8.1.0.

#include "TLCS-90.h"

// 0000: void fn0000(Register byte a)
void fn0000(byte a)
{
	null = (byte *) a;
}

// 02F4: Register word16 fn02F4(Register byte a, Register cu8 c, Register byte b, Register Eq_n de, Register byte h, Register (ptr16 Eq_n) ix, Stack Eq_n wArg24, Register out Eq_n bcOut, Register out Eq_n deOut, Register out Eq_n hlOut, Register out Eq_n ixOut, Register out Eq_n spOut)
word16 fn02F4(byte a, cu8 c, byte b, Eq_n de, byte h, struct Eq_n * ix, Eq_n wArg24, union Eq_n & bcOut, union Eq_n & deOut, union Eq_n & hlOut, union Eq_n & ixOut, union Eq_n & spOut)
{
	word16 hl_n = DPB(hl, h, 8);
	cu8 a_n = (bool) C + (a + ix->bFFFFFFE4);
	byte a_n = (bool) (a_n < 0x00) + (h + ix->bFFFFFFE5);
	ui8 a_n = a_n ^ ix->bFFFFFFFC;
	ui8 a_n = a_n ^ ix->bFFFFFFFD;
	ui8 a_n = b ^ ix->bFFFFFFFB;
	uint8 a_n = ix->bFFFFFFF6 + (c ^ ix->bFFFFFFFA);
	ix->bFFFFFFF6 = a_n;
	uint8 a_n = (bool) (a_n < 0x00) + (ix->bFFFFFFF7 + a_n);
	ix->bFFFFFFF7 = a_n;
	uint8 a_n = (bool) (a_n < 0x00) + (ix->bFFFFFFF8 + a_n);
	ix->bFFFFFFF8 = a_n;
	ix->bFFFFFFF9 = (uint8) ((bool) (a_n < 0x00) + (ix->bFFFFFFF9 + a_n));
	uint8 c_n = ix->bFFFFFFF6;
	uint8 b_n = ix->bFFFFFFF7;
	ui16 hl_n = DPB(DPB(DPB(DPB(DPB(DPB(hl_n, a_n, 0), a_n, 8), a_n, 0), a_n, 8), ix->bFFFFFFF8, 0), ix->bFFFFFFF9, 8);
	byte a_n;
	for (a_n = 0x04; a_n != 0x00; --a_n)
	{
		c_n <<= 0x01;
		b_n = __rcl(b_n, 0x01, (bool) cond(c_n));
		hl_n = hl_n * 0x02 + (b_n < 0x00);
		uint8 h_n = SLICE(hl_n, byte, 8);
		uint8 l_n = (byte) hl_n;
	}
	uint8 a_n = c_n + ix->bFFFFFFDE;
	Eq_n bc_n;
	Eq_n de_n;
	Eq_n hl_n;
	Eq_n ix_n;
	Eq_n sp_n;
	word16 af_n = fn034E(a_n, b_n, c_n, de, h_n, l_n, ix, wArg24, out bc_n, out de_n, out hl_n, out ix_n, out sp_n);
	bcOut = bc_n;
	deOut = de_n;
	hlOut = hl_n;
	ixOut = ix_n;
	spOut = sp_n;
	return af_n;
}

// 034E: Register word16 fn034E(Register uint8 a, Register uint8 b, Register uint8 c, Register Eq_n de, Register uint8 h, Register uint8 l, Register (ptr16 Eq_n) ix, Stack Eq_n wArg24, Register out Eq_n bcOut, Register out Eq_n deOut, Register out Eq_n hlOut, Register out Eq_n ixOut, Register out Eq_n spOut)
word16 fn034E(uint8 a, uint8 b, uint8 c, Eq_n de, uint8 h, uint8 l, struct Eq_n * ix, Eq_n wArg24, union Eq_n & bcOut, union Eq_n & deOut, union Eq_n & hlOut, union Eq_n & ixOut, union Eq_n & spOut)
{
	ix->bFFFFFFFA = a;
	Eq_n bc_n;
	Eq_n de_n;
	Eq_n hl_n;
	Eq_n ix_n;
	Eq_n sp_n;
	word16 af_n = fn03B2(a, b, c, de, h, l, ix, wArg24, out bc_n, out de_n, out hl_n, out ix_n, out sp_n);
	bcOut = bc_n;
	deOut = de_n;
	hlOut = hl_n;
	ixOut = ix_n;
	spOut = sp_n;
	return af_n;
}

// 039D: void fn039D(Register byte a, Register Eq_n de, Register byte h, Register (ptr16 Eq_n) ix, Stack Eq_n wArg24)
void fn039D(byte a, Eq_n de, byte h, struct Eq_n * ix, Eq_n wArg24)
{
	ix->bFFFFFFFD = a ^ h;
	uint8 v12_n = ix->bFFFFFFF6;
	uint8 v14_n = ix->bFFFFFFF7;
	uint8 v16_n = ix->bFFFFFFF8;
	uint8 v18_n = ix->bFFFFFFF9;
	fn03B2(0x05, v14_n, v12_n, de, v18_n, v16_n, ix, wArg24, out bc_n, out de_n, out hl_n, out ix_n, out sp_n);
}

// 03AA: void fn03AA()
void fn03AA()
{
}

// 03B2: Register word16 fn03B2(Register uint8 a, Register uint8 b, Register uint8 c, Register Eq_n de, Register uint8 h, Register uint8 l, Register (ptr16 Eq_n) ix, Stack Eq_n wArg24, Register out Eq_n bcOut, Register out Eq_n deOut, Register out Eq_n hlOut, Register out Eq_n ixOut, Register out Eq_n spOut)
word16 fn03B2(uint8 a, uint8 b, uint8 c, Eq_n de, uint8 h, uint8 l, struct Eq_n * ix, Eq_n wArg24, union Eq_n & bcOut, union Eq_n & deOut, union Eq_n & hlOut, union Eq_n & ixOut, union Eq_n & spOut)
{
	word16 af_n = DPB(af, a, 8);
}

// 04EE: void fn04EE(Register Eq_n de, Register (ptr16 Eq_n) ix, Stack Eq_n wArg20)
void fn04EE(Eq_n de, struct Eq_n * ix, Eq_n wArg20)
{
	ix->bFFFFFFDB = 55;
	ix->bFFFFFFDC = ~0x10;
	ix->bFFFFFFDD = 0xC6;
	uint8 c_n = ix->bFFFFFFE6;
	uint8 b_n = ix->bFFFFFFE7;
	ui16 hl_n = DPB(DPB(hl, ix->bFFFFFFE8, 0), ix->bFFFFFFE9, 8);
	byte a_n;
	for (a_n = 0x04; a_n != 0x00; --a_n)
	{
		c_n <<= 0x01;
		b_n = __rcl(b_n, 0x01, (bool) cond(c_n));
		hl_n = hl_n * 0x02 + (b_n < 0x00);
		byte h_n = SLICE(hl_n, byte, 8);
		byte l_n = (byte) hl_n;
		ui16 hl_n = DPB(hl_n, h_n, 8);
	}
	uint8 a_n = c_n + ix->bFFFFFFF6;
	ix->bFFFFFFFC = a_n;
	uint8 a_n = (bool) (a_n < 0x00) + (b_n + ix->bFFFFFFF7);
	ix->bFFFFFFFD = a_n;
	uint8 a_n = (bool) (a_n < 0x00) + (l_n + ix->bFFFFFFF8);
	ix->bFFFFFFFE = a_n;
	ix->bFFFFFFFF = (ui8) ((bool) (a_n < 0x00) + (h_n + ix->bFFFFFFF9));
	cu8 a_n = ix->bFFFFFFE6 + ix->bFFFFFFDA;
	cu8 a_n = (bool) (a_n < 0x00) + (ix->bFFFFFFE7 + ix->bFFFFFFDB);
	cu8 a_n = (bool) (a_n < 0x00) + (ix->bFFFFFFE8 + ix->bFFFFFFDC);
	byte a_n = (bool) (a_n < 0x00) + (ix->bFFFFFFE9 + ix->bFFFFFFDD);
	ix->bFFFFFFFC = ix->bFFFFFFFC ^ a_n;
	ix->bFFFFFFFD = ix->bFFFFFFFD ^ a_n;
	ix->bFFFFFFFE = ix->bFFFFFFFE ^ a_n;
	ix->bFFFFFFFF = ix->bFFFFFFFF ^ a_n;
	uint8 v42_n = ix->bFFFFFFE8;
	uint8 c_n = ix->bFFFFFFE6;
	uint8 b_n = ix->bFFFFFFE7;
	uint8 l_n = v42_n;
	ui16 hl_n = DPB(DPB(DPB(hl_n, a_n, 0), a_n, 8), v42_n, 0);
	uint8 h_n = ix->bFFFFFFE9;
	byte a_n;
	for (a_n = 0x05; a_n != 0x00; --a_n)
	{
		h_n >>= 0x01;
		l_n = __rcr(l_n, 0x01, (bool) cond(h_n));
		b_n = __rcr(b_n, 0x01, (bool) cond(l_n));
		ui16 hl_n = DPB(hl_n, h_n, 8);
		c_n = __rcr(c_n, 0x01, (bool) cond(b_n));
	}
	uint8 a_n = c_n + ix->bFFFFFFEA;
	cu8 a_n = (bool) (a_n < 0x00) + (b_n + ix->bFFFFFFEB);
	cu8 a_n = (bool) (a_n < 0x00) + (l_n + ix->bFFFFFFEC);
	uint8 a_n = h_n + ix->bFFFFFFED + (a_n < 0x00);
	ui8 a_n = a_n ^ ix->bFFFFFFFE;
	ui8 a_n = a_n ^ ix->bFFFFFFFF;
	ui8 a_n = a_n ^ ix->bFFFFFFFD;
	uint8 a_n = ix->bFFFFFFDE - (a_n ^ ix->bFFFFFFFC);
	ix->bFFFFFFDE = a_n;
	uint8 a_n = ix->bFFFFFFDF - a_n - (a_n < 0x00);
	ix->bFFFFFFDF = a_n;
	uint8 a_n = ix->bFFFFFFE0 - a_n - (a_n < 0x00);
	ix->bFFFFFFE0 = a_n;
	ix->bFFFFFFE1 = ix->bFFFFFFE1 - a_n - (a_n < 0x00);
	uint8 c_n = ix->bFFFFFFDE;
	uint8 b_n = ix->bFFFFFFDF;
	ui16 hl_n = DPB(DPB(DPB(DPB(DPB(DPB(hl_n, a_n, 0), a_n, 8), a_n, 0), a_n, 8), ix->bFFFFFFE0, 0), ix->bFFFFFFE1, 8);
	byte a_n;
	for (a_n = 0x04; a_n != 0x00; --a_n)
	{
		c_n <<= 0x01;
		b_n = __rcl(b_n, 0x01, (bool) cond(c_n));
		hl_n = hl_n * 0x02 + (b_n < 0x00);
		byte l_n = (byte) hl_n;
		byte h_n = SLICE(hl_n, byte, 8);
	}
	uint8 a_n = c_n + ix->bFFFFFFEE;
	ix->bFFFFFFFC = a_n;
	uint8 a_n = (bool) (a_n < 0x00) + (b_n + ix->bFFFFFFEF);
	ix->bFFFFFFFD = a_n;
	uint8 a_n = (bool) (a_n < 0x00) + (l_n + ix->bFFFFFFF0);
	ix->bFFFFFFFE = a_n;
	ix->bFFFFFFFF = (ui8) ((bool) (a_n < 0x00) + (h_n + ix->bFFFFFFF1));
	cu8 a_n = ix->bFFFFFFDE + ix->bFFFFFFDA;
	uint8 v66_n = ix->bFFFFFFDF;
	fn060E(v66_n, a_n, de, ix, wArg20);
}

// 0607: void fn0607(Register byte a, Register Eq_n de, Register (ptr16 Eq_n) ix, Stack Eq_n wArg20)
void fn0607(byte a, Eq_n de, struct Eq_n * ix, Eq_n wArg20)
{
	cu8 a_n = a + ix->bFFFFFFDA;
	uint8 v9_n = ix->bFFFFFFDF;
	fn060E(v9_n, a_n, de, ix, wArg20);
}

// 060E: void fn060E(Register uint8 a, Register cu8 c, Register Eq_n de, Register (ptr16 Eq_n) ix, Stack Eq_n wArg20)
void fn060E(uint8 a, cu8 c, Eq_n de, struct Eq_n * ix, Eq_n wArg20)
{
	do
	{
		cu8 a_n = a + ix->bFFFFFFDB;
		cu8 a_n = (bool) (a_n < 0x00) + (ix->bFFFFFFE0 + ix->bFFFFFFDC);
		byte a_n = (bool) (a_n < 0x00) + (ix->bFFFFFFE1 + ix->bFFFFFFDD);
		ix->bFFFFFFFC = ix->bFFFFFFFC ^ c;
		ix->bFFFFFFFD = ix->bFFFFFFFD ^ a_n;
		ix->bFFFFFFFE = ix->bFFFFFFFE ^ a_n;
		ix->bFFFFFFFF = ix->bFFFFFFFF ^ a_n;
		uint8 c_n = ix->bFFFFFFDE;
		uint8 b_n = ix->bFFFFFFDF;
		uint8 l_n = ix->bFFFFFFE0;
		uint8 h_n = ix->bFFFFFFE1;
		byte a_n;
		for (a_n = 0x05; a_n != 0x00; --a_n)
		{
			h_n >>= 0x01;
			l_n = __rcr(l_n, 0x01, (bool) cond(h_n));
			b_n = __rcr(b_n, 0x01, (bool) cond(l_n));
			c_n = __rcr(c_n, 0x01, (bool) cond(b_n));
		}
		cu8 a_n = c_n + ix->bFFFFFFF2;
		cu8 a_n = (bool) (a_n < 0x00) + (b_n + ix->bFFFFFFF3);
		cu8 a_n = (bool) (a_n < 0x00) + (l_n + ix->bFFFFFFF4);
		ui8 a_n = a_n ^ ix->bFFFFFFFD;
		ui8 a_n = a_n ^ ix->bFFFFFFFE;
		ui8 a_n = h_n + ix->bFFFFFFF5 + (a_n < 0x00) ^ ix->bFFFFFFFF;
		uint8 a_n = ix->bFFFFFFE6 - (a_n ^ ix->bFFFFFFFC);
		ix->bFFFFFFE6 = a_n;
		uint8 a_n = ix->bFFFFFFE7 - a_n - (a_n < 0x00);
		ix->bFFFFFFE7 = a_n;
		uint8 a_n = ix->bFFFFFFE8 - a_n - (a_n < 0x00);
		ix->bFFFFFFE8 = a_n;
		ix->bFFFFFFE9 = ix->bFFFFFFE9 - a_n - (a_n < 0x00);
		cu8 v44_n = ix->bFFFFFFDA;
		ix->bFFFFFFDA = v44_n + 0x47;
		cu8 a_n = (bool) (v44_n < 0x47) + (ix->bFFFFFFDB + 0x86);
		ix->bFFFFFFDB = a_n;
		cu8 a_n = (bool) (a_n < 0x00) + (ix->bFFFFFFDC + 200);
		ix->bFFFFFFDC = a_n;
		ix->bFFFFFFDD = (bool) (a_n < 0x00) + (ix->bFFFFFFDD + 0x61);
		cu8 v48_n = ix->bFFFFFFE2;
		cu8 a_n = (bool) (v48_n < ~0x00) + (ix->bFFFFFFE3 + ~0x00);
		cu8 a_n = (bool) (a_n < 0x00) + (ix->bFFFFFFE4 + ~0x00);
		byte a_n = (bool) (a_n < 0x00) + (ix->bFFFFFFE5 + ~0x00);
		ix->bFFFFFFE2 = v48_n + ~0x00;
		ix->bFFFFFFE3 = a_n;
		ix->bFFFFFFE4 = a_n;
		ix->bFFFFFFE5 = a_n;
		c = v48_n + ~0x00;
		a = a_n | a_n | a_n | v48_n + ~0x00;
	} while (a != 0x00);
	Eq_n hl_n = fp + 0x0C;
	word16 bc_n;
	for (bc_n = 0x04; bc_n != 0x00; --bc_n)
	{
		*de = *hl_n;
		hl_n = (word32) hl_n + 0x01;
		de = (word32) de + 0x01;
	}
	Eq_n de_n = wArg20;
	Eq_n hl_n = fp + 0x04;
	word16 bc_n;
	for (bc_n = 0x04; bc_n != 0x00; --bc_n)
	{
		*de_n = *hl_n;
		hl_n = (word32) hl_n + 0x01;
		de_n = (word32) de_n + 0x01;
	}
}

// 0805: void fn0805()
void fn0805()
{
	__disable_interrupts();
	fn0823();
	fn0822();
	__halt();
}

// 0822: void fn0822()
void fn0822()
{
	fn0823();
}

// 0823: void fn0823()
void fn0823()
{
}

// 0C1D: void fn0C1D(Register Eq_n de, Register (ptr16 Eq_n) ix, Stack byte bArg00, Stack Eq_n wArg22)
void fn0C1D(Eq_n de, struct Eq_n * ix, byte bArg00, Eq_n wArg22)
{
	uint8 c_n = ix->bFFFFFFE6;
	uint8 b_n = ix->bFFFFFFE7;
	ui16 hl_n = DPB(DPB(hl, ix->bFFFFFFE8, 0), ix->bFFFFFFE9, 8);
	byte a_n = 0x04;
	do
	{
		c_n <<= 0x01;
		b_n = __rcl(b_n, 0x01, (bool) cond(c_n));
		hl_n = hl_n * 0x02 + (b_n < 0x00);
		--a_n;
		byte l_n = (byte) hl_n;
		byte h_n = SLICE(hl_n, byte, 8);
		word16 af_n = DPB(wArg00, a_n, 8);
	} while (a_n != 0x00);
	fn0C35(af_n, c_n, b_n, de, l_n, h_n, ix, wArg22);
}

// 0C35: void fn0C35(Register word16 af, Register uint8 c, Register uint8 b, Register Eq_n de, Register byte l, Register byte h, Register (ptr16 Eq_n) ix, Stack Eq_n wArg20)
void fn0C35(word16 af, uint8 c, uint8 b, Eq_n de, byte l, byte h, struct Eq_n * ix, Eq_n wArg20)
{
	word16 hl_n = DPB(DPB(DPB(DPB(hl, l, 0), h, 8), l, 0), h, 8);
	uint8 a_n = c + ix->bFFFFFFF6;
	ix->bFFFFFFFC = a_n;
	uint8 a_n = (bool) (a_n < 0x00) + (b + ix->bFFFFFFF7);
	ix->bFFFFFFFD = a_n;
	uint8 a_n = (bool) (a_n < 0x00) + (l + ix->bFFFFFFF8);
	ix->bFFFFFFFE = a_n;
	ix->bFFFFFFFF = (ui8) ((bool) (a_n < 0x00) + (h + ix->bFFFFFFF9));
	cu8 a_n = ix->bFFFFFFE6 + ix->bFFFFFFDA;
	cu8 a_n = (bool) (a_n < 0x00) + (ix->bFFFFFFE7 + ix->bFFFFFFDB);
	cu8 a_n = (bool) (a_n < 0x00) + (ix->bFFFFFFE8 + ix->bFFFFFFDC);
	byte a_n = (bool) (a_n < 0x00) + (ix->bFFFFFFE9 + ix->bFFFFFFDD);
	ix->bFFFFFFFC = ix->bFFFFFFFC ^ a_n;
	ix->bFFFFFFFD = ix->bFFFFFFFD ^ a_n;
	ix->bFFFFFFFE = ix->bFFFFFFFE ^ a_n;
	ix->bFFFFFFFF = ix->bFFFFFFFF ^ a_n;
	uint8 v32_n = ix->bFFFFFFE6;
	uint8 v33_n = ix->bFFFFFFE7;
	word16 hl_n = DPB(DPB(DPB(DPB(hl_n, a_n, 0), a_n, 8), ix->bFFFFFFE8, 0), ix->bFFFFFFE9, 8);
	word16 af_n = DPB(af, 0x05, 8);
	fn0C9D(af_n, v33_n, v32_n, de, hl_n, ix, wArg20);
}

// 0C39: void fn0C39(Register word16 af, Register byte b, Register Eq_n de, Register byte l, Register byte h, Register (ptr16 Eq_n) ix, Stack Eq_n wArg20)
void fn0C39(word16 af, byte b, Eq_n de, byte l, byte h, struct Eq_n * ix, Eq_n wArg20)
{
	ix->bFFFFFFFC = a;
	uint8 a_n = (bool) C + (b + ix->bFFFFFFF7);
	ix->bFFFFFFFD = a_n;
	uint8 a_n = (bool) (a_n < 0x00) + (l + ix->bFFFFFFF8);
	ix->bFFFFFFFE = a_n;
	ix->bFFFFFFFF = (ui8) ((bool) (a_n < 0x00) + (h + ix->bFFFFFFF9));
	cu8 a_n = ix->bFFFFFFE6 + ix->bFFFFFFDA;
	cu8 a_n = (bool) (a_n < 0x00) + (ix->bFFFFFFE7 + ix->bFFFFFFDB);
	cu8 a_n = (bool) (a_n < 0x00) + (ix->bFFFFFFE8 + ix->bFFFFFFDC);
	byte a_n = (bool) (a_n < 0x00) + (ix->bFFFFFFE9 + ix->bFFFFFFDD);
	ix->bFFFFFFFC = ix->bFFFFFFFC ^ a_n;
	ix->bFFFFFFFD = ix->bFFFFFFFD ^ a_n;
	word16 af_n = DPB(af, ix->bFFFFFFFE, 8);
	fn0C80(af_n, de, a_n, a_n, ix, wArg20);
}

// 0C80: void fn0C80(Register word16 af, Register Eq_n de, Register cu8 l, Register byte h, Register (ptr16 Eq_n) ix, Stack Eq_n wArg20)
void fn0C80(word16 af, Eq_n de, cu8 l, byte h, struct Eq_n * ix, Eq_n wArg20)
{
	word16 hl_n = DPB(DPB(DPB(DPB(hl, l, 0), h, 8), l, 0), h, 8);
	ix->bFFFFFFFE = a ^ l;
	ix->bFFFFFFFF = ix->bFFFFFFFF ^ h;
	uint8 v14_n = ix->bFFFFFFE6;
	uint8 v16_n = ix->bFFFFFFE7;
	word16 hl_n = DPB(DPB(hl_n, ix->bFFFFFFE8, 0), ix->bFFFFFFE9, 8);
	word16 af_n = DPB(af, 0x05, 8);
	fn0C9D(af_n, v16_n, v14_n, de, hl_n, ix, wArg20);
}

// 0C9D: void fn0C9D(Register word16 af, Register uint8 b, Register uint8 c, Register Eq_n de, Register word16 hl, Register (ptr16 Eq_n) ix, Stack Eq_n wArg20)
void fn0C9D(word16 af, uint8 b, uint8 c, Eq_n de, word16 hl, struct Eq_n * ix, Eq_n wArg20)
{
	byte a_n;
	uint8 h_n = SLICE(hl, byte, 8);
	uint8 l_n = (byte) hl;
	do
	{
		h_n >>= 0x01;
		l_n = __rcr(l_n, 0x01, (bool) cond(h_n));
		b = __rcr(b, 0x01, (bool) cond(l_n));
		word16 hl_n = DPB(hl, h_n, 8);
		c = __rcr(c, 0x01, (bool) cond(b));
		--a_n;
	} while (a_n != 0x00);
	cu8 a_n = c + ix->bFFFFFFEA;
	cu8 a_n = (bool) (a_n < 0x00) + (b + ix->bFFFFFFEB);
	cu8 a_n = (bool) (a_n < 0x00) + (l_n + ix->bFFFFFFEC);
	uint8 a_n = h_n + ix->bFFFFFFED + (a_n < 0x00);
	ui8 a_n = a_n ^ ix->bFFFFFFFE;
	ui8 a_n = a_n ^ ix->bFFFFFFFF;
	ui8 a_n = a_n ^ ix->bFFFFFFFD;
	uint8 a_n = ix->bFFFFFFDE - (a_n ^ ix->bFFFFFFFC);
	ix->bFFFFFFDE = a_n;
	uint8 a_n = ix->bFFFFFFDF - a_n - (a_n < 0x00);
	ix->bFFFFFFDF = a_n;
	uint8 a_n = ix->bFFFFFFE0 - a_n - (a_n < 0x00);
	ix->bFFFFFFE0 = a_n;
	ix->bFFFFFFE1 = ix->bFFFFFFE1 - a_n - (a_n < 0x00);
	uint8 v31_n = ix->bFFFFFFDE;
	uint8 v32_n = ix->bFFFFFFDF;
	ui16 hl_n = DPB(DPB(DPB(DPB(DPB(DPB(hl_n, a_n, 0), a_n, 8), a_n, 0), a_n, 8), ix->bFFFFFFE0, 0), ix->bFFFFFFE1, 8);
	word16 af_n = DPB(af, 0x04, 8);
	fn0D00(af_n, v31_n, v32_n, de, hl_n, ix, wArg20);
}

// 0CB7: void fn0CB7(Register word16 af, Register byte c, Register byte b, Register Eq_n de, Register byte h, Register byte l, Register (ptr16 Eq_n) ix, Stack Eq_n wArg20)
void fn0CB7(word16 af, byte c, byte b, Eq_n de, byte h, byte l, struct Eq_n * ix, Eq_n wArg20)
{
	word16 hl_n = DPB(DPB(hl, h, 8), l, 0);
	byte a_n = (bool) C + (h + ix->bFFFFFFED);
	ui8 a_n = l ^ ix->bFFFFFFFE;
	ui8 a_n = a_n ^ ix->bFFFFFFFF;
	ui8 a_n = b ^ ix->bFFFFFFFD;
	uint8 a_n = ix->bFFFFFFDE - (c ^ ix->bFFFFFFFC);
	ix->bFFFFFFDE = a_n;
	uint8 a_n = ix->bFFFFFFDF - a_n - (a_n < 0x00);
	ix->bFFFFFFDF = a_n;
	uint8 a_n = ix->bFFFFFFE0 - a_n - (a_n < 0x00);
	ix->bFFFFFFE0 = a_n;
	ix->bFFFFFFE1 = ix->bFFFFFFE1 - a_n - (a_n < 0x00);
	uint8 v25_n = ix->bFFFFFFDE;
	uint8 v26_n = ix->bFFFFFFDF;
	ui16 hl_n = DPB(DPB(DPB(DPB(DPB(hl_n, a_n, 8), a_n, 0), a_n, 8), ix->bFFFFFFE0, 0), ix->bFFFFFFE1, 8);
	word16 af_n = DPB(af, 0x04, 8);
	fn0D00(af_n, v25_n, v26_n, de, hl_n, ix, wArg20);
}

// 0D00: void fn0D00(Register word16 af, Register uint8 c, Register uint8 b, Register Eq_n de, Register ui16 hl, Register (ptr16 Eq_n) ix, Stack Eq_n wArg20)
void fn0D00(word16 af, uint8 c, uint8 b, Eq_n de, ui16 hl, struct Eq_n * ix, Eq_n wArg20)
{
	byte a_n;
	do
	{
		c <<= 0x01;
		b = __rcl(b, 0x01, (bool) cond(c));
		hl = hl * 0x02 + (b < 0x00);
		byte l_n = (byte) hl;
		byte h_n = SLICE(hl, byte, 8);
		--a_n;
	} while (a_n != 0x00);
	uint8 a_n = c + ix->bFFFFFFEE;
	ix->bFFFFFFFC = a_n;
	uint8 a_n = (bool) (a_n < 0x00) + (b + ix->bFFFFFFEF);
	ix->bFFFFFFFD = a_n;
	uint8 a_n = (bool) (a_n < 0x00) + (l_n + ix->bFFFFFFF0);
	ix->bFFFFFFFE = a_n;
	ix->bFFFFFFFF = (ui8) ((bool) (a_n < 0x00) + (h_n + ix->bFFFFFFF1));
	cu8 a_n = ix->bFFFFFFDE + ix->bFFFFFFDA;
	cu8 a_n = (bool) (a_n < 0x00) + (ix->bFFFFFFDF + ix->bFFFFFFDB);
	cu8 a_n = (bool) (a_n < 0x00) + (ix->bFFFFFFE0 + ix->bFFFFFFDC);
	byte a_n = (bool) (a_n < 0x00) + (ix->bFFFFFFE1 + ix->bFFFFFFDD);
	ix->bFFFFFFFC = ix->bFFFFFFFC ^ a_n;
	ix->bFFFFFFFD = ix->bFFFFFFFD ^ a_n;
	ix->bFFFFFFFE = ix->bFFFFFFFE ^ a_n;
	ix->bFFFFFFFF = ix->bFFFFFFFF ^ a_n;
	uint8 c_n = ix->bFFFFFFDE;
	uint8 b_n = ix->bFFFFFFDF;
	uint8 l_n = ix->bFFFFFFE0;
	uint8 h_n = ix->bFFFFFFE1;
	byte a_n;
	for (a_n = 0x05; a_n != 0x00; --a_n)
	{
		h_n >>= 0x01;
		l_n = __rcr(l_n, 0x01, (bool) cond(h_n));
		b_n = __rcr(b_n, 0x01, (bool) cond(l_n));
		c_n = __rcr(c_n, 0x01, (bool) cond(b_n));
	}
	cu8 a_n = c_n + ix->bFFFFFFF2;
	cu8 a_n = (bool) (a_n < 0x00) + (b_n + ix->bFFFFFFF3);
	cu8 a_n = (bool) (a_n < 0x00) + (l_n + ix->bFFFFFFF4);
	ui8 a_n = a_n ^ ix->bFFFFFFFD;
	ui8 a_n = a_n ^ ix->bFFFFFFFE;
	ui8 a_n = h_n + ix->bFFFFFFF5 + (a_n < 0x00) ^ ix->bFFFFFFFF;
	uint8 a_n = ix->bFFFFFFE6 - (a_n ^ ix->bFFFFFFFC);
	ix->bFFFFFFE6 = a_n;
	uint8 a_n = ix->bFFFFFFE7 - a_n - (a_n < 0x00);
	ix->bFFFFFFE7 = a_n;
	uint8 a_n = ix->bFFFFFFE8 - a_n - (a_n < 0x00);
	ix->bFFFFFFE8 = a_n;
	ix->bFFFFFFE9 = ix->bFFFFFFE9 - a_n - (a_n < 0x00);
	cu8 v52_n = ix->bFFFFFFDA;
	ix->bFFFFFFDA = v52_n + 0x47;
	cu8 a_n = (bool) (v52_n < 0x47) + (ix->bFFFFFFDB + 0x86);
	ix->bFFFFFFDB = a_n;
	cu8 a_n = (bool) (a_n < 0x00) + (ix->bFFFFFFDC + 200);
	ix->bFFFFFFDC = a_n;
	ix->bFFFFFFDD = (bool) (a_n < 0x00) + (ix->bFFFFFFDD + 0x61);
	cu8 v56_n = ix->bFFFFFFE2;
	cu8 a_n = (bool) (v56_n < ~0x00) + (ix->bFFFFFFE3 + ~0x00);
	cu8 a_n = (bool) (a_n < 0x00) + (ix->bFFFFFFE4 + ~0x00);
	byte a_n = (bool) (a_n < 0x00) + (ix->bFFFFFFE5 + ~0x00);
	ix->bFFFFFFE2 = v56_n + ~0x00;
	ix->bFFFFFFE3 = a_n;
	ix->bFFFFFFE4 = a_n;
	ix->bFFFFFFE5 = a_n;
	uint8 a_n = a_n | a_n | a_n | v56_n + ~0x00;
	if (a_n != 0x00)
		fn060E(a_n, v56_n + ~0x00, de, ix, wArg20);
	else
		fn0E13(de, wArg20);
}

// 0DFC: void fn0DFC(Register cu8 c, Register cu8 b, Register Eq_n de, Register cu8 l, Register byte h, Register (ptr16 Eq_n) ix, Stack Eq_n wArg20)
void fn0DFC(cu8 c, cu8 b, Eq_n de, cu8 l, byte h, struct Eq_n * ix, Eq_n wArg20)
{
	ix->bFFFFFFE2 = c;
	ix->bFFFFFFE3 = b;
	ix->bFFFFFFE4 = l;
	ix->bFFFFFFE5 = h;
	uint8 a_n = h | l | b | c;
	if (a_n != 0x00)
		fn060E(a_n, c, de, ix, wArg20);
	else
		fn0E13(de, wArg20);
}

// 0E13: void fn0E13(Register Eq_n de, Stack Eq_n wArg20)
void fn0E13(Eq_n de, Eq_n wArg20)
{
	Eq_n hl_n = fp + 0x0C;
	word16 bc_n;
	for (bc_n = 0x04; bc_n != 0x00; --bc_n)
	{
		*de = *hl_n;
		hl_n = (word32) hl_n + 0x01;
		++de;
	}
	Eq_n de_n = wArg20;
	Eq_n hl_n = fp + 0x04;
	word16 bc_n;
	for (bc_n = 0x04; bc_n != 0x00; --bc_n)
	{
		*de_n = *hl_n;
		hl_n = (word32) hl_n + 0x01;
		++de_n;
	}
}

// 0F9A: void fn0F9A()
void fn0F9A()
{
}

// 164F: void fn164F(Register cu8 a, Register byte c, Register byte b, Register byte h, Register (ptr16 Eq_n) ix, Stack Eq_n wArg13, Stack byte bArg1A, Stack (ptr16 Eq_n) wArg1B)
void fn164F(cu8 a, byte c, byte b, byte h, struct Eq_n * ix, Eq_n wArg13, byte bArg1A, struct Eq_n * wArg1B)
{
	ix->bFFFFFFEC = a;
	ix->bFFFFFFED = ix->bFFFFFFF9 - h - C;
	cu8 a_n = ix->bFFFFFFF8 - ix->bFFFFFFFC;
	byte v14_n = wArg1B->b0001;
	cu8 a_n = c - wArg1B->b0000;
	byte a_n = ix->bFFFFFFF9 - ix->bFFFFFFFD - (a_n < 0x00);
	byte l_n = (byte) hl_n;
	uint8 c_n = (byte) bc_n;
	uint8 b_n = SLICE(bc_n, byte, 8);
	byte h_n = SLICE(hl_n, byte, 8);
	word16 bc_n;
	Eq_n de_n;
	word16 hl_n;
	struct Eq_n * ix_n;
	struct Eq_n * sp_n;
	word16 af_n = DPB(fn02F4(a_n, a_n, b - v14_n - (a_n < 0x00), wArg13, SLICE(DPB(DPB(DPB(&wArg1B->b0001, v14_n, 8), a_n, 0), a_n, 8), byte, 8), ix, SEQ((byte) wArg1B, bArg1A), out bc_n, out de_n, out hl_n, out ix_n, out sp_n), l_n, 8);
	if (l_n != 0x00)
	{
		struct Eq_n * v30_n = sp_n->ptr001D;
		struct Eq_n * v33_n = sp_n->ptr001B;
		byte v31_n = v30_n->b0000;
		byte v34_n = v33_n->b0000;
		byte v32_n = v30_n->b0001;
		byte v36_n = v33_n->b0001;
		cu8 a_n = v31_n - v34_n;
		ix_n->bFFFFFFEC = a_n;
		ix_n->bFFFFFFED = v32_n - v36_n - (a_n < 0x00);
		struct Eq_n * v38_n = sp_n->ptr0027;
		struct Eq_n * v41_n = sp_n->ptr0014;
		byte v39_n = v38_n->b0000;
		byte v40_n = v38_n->b0001;
		byte v43_n = v41_n->b0001;
		cu8 a_n = v39_n - v41_n->b0000;
		ix_n->bFFFFFFEA = a_n;
		ix_n->bFFFFFFEB = v40_n - v43_n - (a_n < 0x00);
		struct Eq_n * v44_n = sp_n->ptr0021;
		cu8 a_n = v31_n - v44_n->b0000;
		struct Eq_n * v47_n = sp_n->ptr002B;
		cu8 a_n = v39_n - v47_n->b0000;
		byte a_n = v32_n - v44_n->b0001 - (a_n < 0x00);
		byte a_n = v40_n - v47_n->b0001 - (a_n < 0x00);
		sp_n->w0004 = sp_n->w0019;
		word16 v51_n = sp_n->w0017;
		sp_n->w0002 = v51_n;
		sp_n->w0000 = DPB(DPB(DPB(DPB(bc_n, v31_n, 0), v32_n, 8), a_n, 0), a_n, 8);
		Eq_n de_n = DPB(DPB(DPB(DPB(DPB(DPB(de_n, v34_n, 0), v36_n, 8), v39_n, 0), v40_n, 8), a_n, 0), a_n, 8);
		*(sp_n - 0x02) = (union Eq_n *) de_n;
		byte l_n = (byte) hl_n;
		uint8 c_n = (byte) bc_n;
		uint8 b_n = SLICE(bc_n, byte, 8);
		byte h_n = SLICE(hl_n, byte, 8);
		word16 bc_n;
		Eq_n de_n;
		word16 hl_n;
		struct Eq_n * ix_n;
		struct Eq_n * sp_n;
		word16 af_n = DPB(fn02F4(a_n, a_n, a_n, de_n, SLICE(v51_n, byte, 8), ix_n, sp_n->t0020, out bc_n, out de_n, out hl_n, out ix_n, out sp_n), l_n, 8);
		if (l_n != 0x00)
			fn0C35(af_n, c_n, b_n, de_n, 0x00, h_n, ix_n, sp_n->t0026);
		else
			fn0C35(af_n, c_n, b_n, de_n, 0x03, h_n, ix_n, sp_n->t0026);
	}
	else
		fn0C35(af_n, c_n, b_n, de_n, 0x03, h_n, ix_n, sp_n->t0026);
}

// 1873: void fn1873(Register word16 af, Register uint8 c, Register uint8 b, Register Eq_n de, Register (ptr16 Eq_n) ix, Stack (ptr16 Eq_n) wArg13, Stack Eq_n wArg20)
void fn1873(word16 af, uint8 c, uint8 b, Eq_n de, struct Eq_n * ix, struct Eq_n * wArg13, Eq_n wArg20)
{
	wArg13->b0000 = c;
	wArg13->b0001 = b;
	byte h_n = SLICE(&wArg13->b0001, byte, 8);
	fn0C35(af, c, b, de, 0x02, h_n, ix, wArg20);
}

// 1BA4: void fn1BA4(Register word16 bc, Register Eq_n de)
void fn1BA4(word16 bc, Eq_n de)
{
	Eq_n de;
	word16 bc;
	fn0805();
}

// 1BDE: void fn1BDE(Register word16 bc, Register Eq_n de, Register (ptr16 Eq_n) ix)
void fn1BDE(word16 bc, Eq_n de, struct Eq_n * ix)
{
	word16 bc_n = DPB(bc, b, 8);
	++ix->bFFFFFFE9;
	ix->bFFFFFFFF = ix->bFFFFFFE9;
	fn1BF9(bc_n, de, ix);
}

// 1BF9: void fn1BF9(Register word16 bc, Register Eq_n de, Register (ptr16 Eq_n) ix)
void fn1BF9(word16 bc, Eq_n de, struct Eq_n * ix)
{
	cu8 v4_n = ix->bFFFFFFF7;
	ix->bFFFFFFF7 = v4_n + 0x09;
	ix->bFFFFFFF8 = (bool) (v4_n < 0x09) + ix->bFFFFFFF8;
	++ix->bFFFFFFF5;
	word16 bc_n;
	Eq_n hl_n = 0x0823;
	do
	{
		*de = *hl_n;
		++hl_n;
		de = (word32) de + 0x01;
		--bc_n;
	} while (bc_n != 0x00);
}

// 1C89: void fn1C89(Register byte a, Register byte c)
void fn1C89(byte a, byte c)
{
}

// 22A6: void fn22A6(Register word16 bc, Register (ptr16 Eq_n) hl, Register (ptr16 Eq_n) ix, Stack word16 wArg05, Stack word16 wArg10)
void fn22A6(word16 bc, struct Eq_n * hl, struct Eq_n * ix, word16 wArg05, word16 wArg10)
{
	ix->bFFFFFFFC = ix->bFFFFFFF7;
	ix->bFFFFFFFD = 0x00;
	byte * hl_n = wArg10 + (wArg05 + 0x01);
	byte v15_n = *hl_n;
	struct Eq_n * hl_n = DPB(DPB(hl_n, v15_n, 0), 0x00, 8) * 0x08 + DPB(DPB(wArg05 + 0x01, v15_n, 0), 0x00, 8) + bc;
	ix->bFFFFFFF8 = hl_n->b0002;
	ix->bFFFFFFF9 = hl_n->b0003;
	fn03AA();
}

// 3E2D: void fn3E2D(Register word16 bc, Register (ptr16 Eq_n) hl, Register (ptr16 Eq_n) ix, Stack word16 wArg05, Stack word16 wArg10)
void fn3E2D(word16 bc, struct Eq_n * hl, struct Eq_n * ix, word16 wArg05, word16 wArg10)
{
	ix->bFFFFFFFC = ix->bFFFFFFF7;
	ix->bFFFFFFFD = 0x00;
	byte * hl_n = wArg10 + (wArg05 + 0x01);
	byte v15_n = *hl_n;
	struct Eq_n * hl_n = DPB(DPB(hl_n, v15_n, 0), 0x00, 8) * 0x08 + DPB(DPB(wArg05 + 0x01, v15_n, 0), 0x00, 8) + bc;
	ix->bFFFFFFF8 = hl_n->b0002;
	ix->bFFFFFFF9 = hl_n->b0003;
	fn03AA();
}

