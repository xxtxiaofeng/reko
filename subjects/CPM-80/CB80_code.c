// CB80_code.c
// Generated by decompiling CB80.COM
// using Reko decompiler version 0.9.1.0.

#include "CB80_code.h"

// 0387: void fn0387()
void fn0387()
{
	<anonymous> * hl_n = globals->ptr1648;
	hl_n();
}

// 0390: void fn0390(Register byte b, Register Eq_n c, Register byte e, Stack Eq_n bArg02)
void fn0390(byte b, Eq_n c, byte e, Eq_n bArg02)
{
	globals->b1656 = e;
	globals->b1655 = b;
	globals->t1654 = c;
	globals->b1653 = (byte) wArg02;
	while (true)
	{
		byte a_n = globals->b1653;
		globals->b1653 = a_n - 0x01;
		if (a_n == 0x00)
			break;
		globals->t1654->u0 = globals->b1656;
		globals->t1654 = (word16) globals->t1654 + 1;
	}
}

// 03BB: FlagGroup bool fn03BB(Register Eq_n c, Register out Eq_n aOut)
bool fn03BB(Eq_n c, union Eq_n & aOut)
{
	globals->t1657 = c;
	byte a_n = 0x00 - (globals->t1657 - 0x61 > 0x1A);
	aOut = ~a_n;
	return (bool) cond(a_n);
}

// 03CB: Register word16 fn03CB(Register Eq_n c)
word16 fn03CB(Eq_n c)
{
	globals->t1658 = c;
	byte a_n = ~(0x00 - (globals->t1658 > 0x5A || globals->t1658 < 0x41));
	byte a_n;
	fn03BB(globals->t1658, out a_n);
	return SEQ(a_n | a_n, f);
}

// 03E6: Register Eq_n fn03E6(Register Eq_n c)
Eq_n fn03E6(Eq_n c)
{
	globals->t1659 = c;
	cu8 a_n;
	if (__rcr(a_n, 0x01, fn03BB(globals->t1659, out a_n)) >= 0x00)
		return globals->t1659;
	return (word16) globals->t1659 + 95;
}

// 0400: void fn0400()
void fn0400()
{
	globals->w1640 = globals->w0006;
	globals->ptr164E = &globals->b0080;
}

// 040D: void fn040D(Register byte b, Register Eq_n c, Register cu8 e, Stack word16 wArg02)
void fn040D(byte b, Eq_n c, cu8 e, word16 wArg02)
{
	globals->b165E = e;
	globals->b165D = b;
	globals->t165C = c;
	globals->b165B = SLICE(wArg02, byte, 8);
	globals->t165A = (byte) wArg02;
	while (globals->b165E > 0x00)
	{
		F_DMAOFF(globals->t165C);
		if (F_READ(globals->t165A) == 0x00)
		{
			--globals->b165E;
			globals->t165C = (word16) globals->t165C + 0x0080;
		}
		else
		{
			globals->t165C->u0 = 0x1A;
			globals->b165E = 0x00;
		}
	}
}

// 045B: Register byte fn045B()
byte fn045B()
{
	if (globals->b0080 == 0x00)
		return 0x00;
	--globals->b0080;
	struct Eq_n * hl_n = globals->ptr164E;
	globals->ptr164E = &hl_n->b0001;
	return hl_n->b0001;
}

// 0473: Register char fn0473(Register char c)
char fn0473(char c)
{
	globals->b165F = c;
	C_WRITE(globals->b165F);
	return 0x02;
}

// 0483: Register word16 fn0483(Register byte b, Register Eq_n c, Register byte d, Register Eq_n e, Stack word16 wArg02)
word16 fn0483(byte b, Eq_n c, byte d, Eq_n e, word16 wArg02)
{
	globals->b1665 = d;
	globals->t1664 = e;
	globals->b1663 = b;
	globals->t1662 = c;
	globals->b1661 = SLICE(wArg02, byte, 8);
	globals->t1660 = (byte) wArg02;
	Eq_n hl_n = <invalid>;
	byte l_n;
	byte c_n = fn1326(0x07, (word16) globals->t1664 + 0x007F, out l_n);
	globals->b1667 = (byte) hl_n;
	word16 bc_n = SEQ(SLICE(wArg02, byte, 8), c_n);
	while (true)
	{
		byte b_n = SLICE(bc_n, byte, 8);
		if (globals->b1667 <= 0x00)
			break;
		F_DMAOFF(globals->t1662);
		bc_n = SEQ(b_n, 0x15);
		if (F_WRITE(globals->t1660) == 0x00)
		{
			--globals->b1667;
			globals->t1662 = (word16) globals->t1662 + 0x0080;
		}
		else
		{
			globals->ptr1668 = &globals->b02A3;
			while (*globals->ptr1668 != 0x24)
			{
				fn0473(*globals->ptr1668);
				++globals->ptr1668;
			}
			if (*globals->t1660 == 0x00)
				*globals->t1660 = DRV_GET() + 0x01;
			fn0473((word16) *globals->t1660 + 96);
			byte c_n = fn0473(0x3A);
			fn0387();
			bc_n = SEQ(b_n, c_n);
		}
	}
	return bc_n;
}

// 0524: Register char fn0524(Register char c)
char fn0524(char c)
{
	globals->b166A = c;
	L_WRITE(globals->b166A);
	return 0x05;
}

// 0534: Register word16 fn0534(Register Eq_n c)
word16 fn0534(Eq_n c)
{
	Eq_n c = (byte) bc;
	globals->t166B = c;
	globals->ptr14BC + globals->w14BE = (union Eq_n *) globals->t166B;
	int16 hl_n = globals->w14BE;
	globals->w14BE = hl_n + 0x01;
	word16 bc_n = bc;
	if (!fn1335(hl_n + 0x01, 0x0200))
	{
		ptr16 hl_n = globals->ptr14BC;
		bc_n = fn0483(SLICE(hl_n, byte, 8), (byte) hl_n, 0x02, 0x00, 0x14C0);
		globals->w14BE = 0x00;
	}
	return bc_n;
}

// 056B: FlagGroup bool fn056B(Register Eq_n bc, Register out Eq_n bcOut)
bool fn056B(Eq_n bc, union Eq_n & bcOut)
{
	char c = (byte) bc;
	byte b = SLICE(bc, byte, 8);
	Eq_n bc_n;
	globals->b166C = c;
	if (globals->b14F3 == 0x01)
		bc_n = SEQ(b, fn0524(globals->b166C));
	else if (globals->b14F3 == 0x02)
		bc_n = SEQ(b, fn0473(globals->b166C));
	else
	{
		bc_n = bc;
		if (globals->b14F3 == 0x04)
			bc_n = fn0534(SEQ(b, globals->b166C));
	}
	char a_n = globals->b166C;
	bool C_n = (bool) cond(a_n - 0x0D);
	if (a_n == 0x0D)
		globals->b14F6 = 0x01;
	else
	{
		char a_n = globals->b166C;
		C_n = (bool) cond(a_n - 0x0A);
		if (a_n == 0x0A)
		{
			cu8 a_n = globals->b14F3;
			C_n = (bool) cond(a_n);
			if (a_n != 0x00)
				++globals->b14FD;
		}
		else
			++globals->b14F6;
	}
	bcOut = bc_n;
	return C_n;
}

// 05CE: Register byte fn05CE(Register Eq_n bc)
byte fn05CE(Eq_n bc)
{
	byte b = SLICE(bc, byte, 8);
	Eq_n c = (byte) bc;
	globals->b166E = b;
	globals->t166D = c;
	Eq_n bc_n = bc;
	while (true)
	{
		byte b_n = SLICE(bc_n, byte, 8);
		if (*globals->t166D == 0x24)
			break;
		fn056B(SEQ(b_n, *globals->t166D), out bc_n);
		globals->t166D = (word16) globals->t166D + 1;
	}
	return SLICE(bc_n, byte, 8);
}

// 05EF: FlagGroup bool fn05EF(Register Eq_n bc, Register out Eq_n bOut)
bool fn05EF(Eq_n bc, union Eq_n & bOut)
{
	byte b = SLICE(bc, byte, 8);
	Eq_n c = (byte) bc;
	globals->b1670 = b;
	globals->t166F = c;
	globals->t1671.u0 = 0x01;
	Eq_n bc_n = bc;
	do
	{
		Eq_n a_n = *globals->t166F;
		byte b_n = SLICE(bc_n, byte, 8);
		bool C_n = (bool) cond(a_n - globals->t1671);
		if (a_n < globals->t1671)
			break;
		C_n = fn056B(SEQ(b_n, Mem12[Mem12[0x166F:word16] + Mem12[0x1671:word16]:byte]), out bc_n);
		globals->t1671 = (word16) globals->t1671 + 1;
	} while (globals->t1671 != 0x00);
	bOut.u0 = <invalid>;
	return C_n;
}

// 061B: FlagGroup bool fn061B(Register byte b, Register Eq_n c, Register byte d, Register Eq_n e)
bool fn061B(byte b, Eq_n c, byte d, Eq_n e)
{
	globals->b1675 = d;
	globals->t1674 = e;
	globals->b1673 = b;
	globals->t1672 = c;
	globals->b14F3 = 0x02;
	fn05CE(globals->t1672);
	byte b_n;
	bool C_n = fn05EF(globals->t1674, out b_n);
	fn0387();
	return C_n;
}

// 063E: void fn063E(Register byte b, Register Eq_n c, Register byte d, Register Eq_n e)
void fn063E(byte b, Eq_n c, byte d, Eq_n e)
{
	globals->b1679 = d;
	globals->t1678 = e;
	globals->b1677 = b;
	globals->t1676 = c;
	globals->b167B = 0x00;
	*globals->t1678 = 0x00;
	globals->t167A.u0 = 0x00;
	while (globals->t167A <= 0x03)
	{
		globals->b167C = 0x30;
		while (true)
		{
			word16 de_n;
			word16 hl_n;
			Eq_n C_n = fn1348(&globals->t1676, globals->t167A * 0x02 + 0x0227, out de_n, out hl_n);
			if (C_n)
				break;
			struct Eq_n * de_n;
			word16 hl_n;
			fn1348(&globals->t1676, globals->t167A * 0x02 + 0x0227, out de_n, out hl_n);
			de_n->bFFFFFFFF = (byte) hl_n;
			de_n->b0000 = SLICE(hl_n, byte, 8);
			globals->b167B = 0x01;
			++globals->b167C;
		}
		if (__rcr(globals->b167B, 0x01, C_n) < 0x00)
		{
			Eq_n hl_n = globals->t1678;
			Eq_n a_n = *hl_n;
			hl_n->u0 = (byte) a_n.t0000 + 1;
			((word16) globals->t1678 + (uint16) ((uint8) ((byte) a_n.t0000 + 1)))->u0 = globals->b167C;
		}
		globals->t167A = (word16) globals->t167A + 1;
		if (globals->t167A == 0x00)
			break;
	}
	Eq_n hl_n = globals->t1678;
	Eq_n hl_n = globals->t1676;
	Eq_n a_n = *hl_n;
	hl_n->u0 = (byte) a_n.t0000 + 1;
	((word16) globals->t1678 + (uint16) ((uint8) ((byte) a_n.t0000 + 1)))->u0 = (byte) ((word16) hl_n.u1 + 48);
}

// 06CE: Register byte fn06CE(Register byte b, Register Eq_n c)
byte fn06CE(byte b, Eq_n c)
{
	globals->b167E = b;
	globals->t167D = c;
	Eq_n hl_n = globals->t167D;
	fn063E(SLICE(hl_n, byte, 8), (byte) hl_n, 22, 44);
	byte b_n;
	fn05EF(5676, out b_n);
	Eq_n bc_n = <invalid>;
	return SLICE(bc_n, byte, 8);
}

// 0722: void fn0722(Register cu8 c, Register byte b)
void fn0722(cu8 c, byte b)
{
	globals->b1681 = c;
	if (globals->b1681 > 0x09)
	{
		word16 bc_n;
		fn056B(SEQ(b, globals->b1681 + 0x57), out bc_n);
	}
	else
	{
		word16 bc_n;
		fn056B(SEQ(b, globals->b1681 + 0x30), out bc_n);
	}
}

// 0745: void fn0745(Register word16 bc)
void fn0745(word16 bc)
{
	cu8 c = (byte) bc;
	globals->b1682 = c;
	word16 bc_n = bc;
	while (true)
	{
		byte b_n = SLICE(bc_n, byte, 8);
		if (globals->b14F6 >= globals->b1682)
			break;
		fn056B(SEQ(b_n, 0x20), out bc_n);
	}
}

// 075C: void fn075C(Register byte b, Register Eq_n c, Register byte d, Register Eq_n e)
void fn075C(byte b, Eq_n c, byte d, Eq_n e)
{
	globals->b1686 = d;
	globals->t1685 = e;
	globals->b1684 = b;
	globals->t1683 = c;
	globals->b14F3 = 0x02;
	if (globals->b14F6 != 0x01)
	{
		word16 bc_n;
		fn056B(SEQ(b, 0x0D), out bc_n);
		word16 bc_n;
		fn056B(SEQ(SLICE(bc_n, byte, 8), 0x0A), out bc_n);
	}
	fn05CE(0x0260);
	Eq_n hl_n = globals->t1683;
	word16 bc_n;
	fn056B(SEQ(SLICE((uint16) (uint8) fn06CE(SLICE(hl_n, byte, 8), (byte) hl_n), byte, 8), 0x0D), out bc_n);
	word16 bc_n;
	fn056B(SEQ(SLICE(bc_n, byte, 8), 0x0A), out bc_n);
	byte l_n;
	if ((fn1353(0x00, &globals->t1685, out l_n) | l_n) != 0x00)
	{
		fn05CE(0x034E);
		Eq_n hl_n = globals->t1685;
		fn06CE(SLICE(hl_n, byte, 8), (byte) hl_n);
	}
	fn0387();
}

// 07B3: void fn07B3(Register Eq_n b)
void fn07B3(Eq_n b)
{
	Eq_n b = SLICE(bc, byte, 8);
	if (__rcr(globals->b14F9, 0x01, C) < 0x00)
	{
		word16 bc_n;
		fn056B(SEQ(b, 0x0D), out bc_n);
		byte b_n = SLICE(bc_n, byte, 8);
		while (globals->b14FD < globals->b14F7)
		{
			word16 bc_n;
			fn056B(SEQ(b_n, 0x0D), out bc_n);
			word16 bc_n;
			fn056B(SEQ(SLICE(bc_n, byte, 8), 0x0A), out bc_n);
			b_n = SLICE(bc_n, byte, 8);
		}
		word16 bc_n;
		fn056B(SEQ(b_n, 0x0D), out bc_n);
		word16 bc_n;
		fn056B(SEQ(SLICE(bc_n, byte, 8), 0x0A), out bc_n);
		fn05CE(0x02B7);
		byte b_n;
		fn05EF(0x14FF, out b_n);
		Eq_n bc_n = <invalid>;
		fn0745(SEQ(SLICE(bc_n, byte, 8), globals->b14F8 - 0x0A));
		fn05CE(0x02FC);
		fn06CE(0x00, globals->t14FE);
		globals->t14FE.u1 = (word16) globals->t14FE + 1;
		byte b_n;
		fn05EF(898, out b_n);
	}
	globals->b14FD = 0x03;
}

// 0814: void fn0814(Register byte b)
void fn0814(byte b)
{
	word16 bc_n;
	fn056B(SEQ(b, 0x0D), out bc_n);
	word16 bc_n;
	fn056B(SEQ(SLICE(bc_n, byte, 8), 0x0A), out bc_n);
	cu8 a_n = globals->b14F7;
	Eq_n bc_n = SEQ(SLICE(bc_n, byte, 8), a_n - 0x03);
	if (globals->b14FD >= a_n - 0x03)
		fn07B3(bc_n);
}

// 082F: Register word16 fn082F(Register byte f, Register byte b, Register Eq_n c, Register cu8 e, Stack word16 wArg02, Stack word16 wArg04)
word16 fn082F(byte f, byte b, Eq_n c, cu8 e, word16 wArg02, word16 wArg04)
{
	globals->b168D = e;
	globals->b168C = b;
	globals->t168B = c;
	globals->b168A = SLICE(wArg02, byte, 8);
	globals->t1689 = (byte) wArg02;
	globals->b1688 = SLICE(wArg04, byte, 8);
	globals->t1687 = (byte) wArg04;
	globals->b168F = 0x00;
	globals->b1690 = 0x00;
	globals->b1691 = 0x00;
	cu8 a_n = __rol(globals->b168D, 0x01);
	if (__rcr(a_n, 0x01, cond(a_n)) < 0x00)
		globals->b1690 = 0x01;
	else
	{
		cu8 a_n = __rol(__rol(globals->b168D, 0x01), 0x01);
		if (__rcr(a_n, 0x01, cond(a_n)) < 0x00)
			globals->b1691 = 0x01;
		else
		{
			cu8 a_n = __rol(__rol(__rol(globals->b168D, 0x01), 0x01), 0x01);
			if (__rcr(a_n, 0x01, cond(a_n)) < 0x00)
				globals->b168F = 0x01;
		}
	}
	cu8 a_n = __rol(__rol(__rol(__rol(globals->b168D, 0x01), 0x01), 0x01), 0x01);
	if (__rcr(a_n, 0x01, cond(a_n)) < 0x00)
		globals->b168E = 0x01;
	globals->b168D += 0x0F;
	Eq_n hl_n = globals->t1687;
	Eq_n hl_n = globals->t1689;
	word16 af_n;
	cu8 a_n = __rcr(~SLICE(af_n, byte, 8), 0x01, fn0990(f, SLICE(hl_n, byte, 8), (byte) hl_n, SLICE(hl_n, byte, 8), (byte) hl_n, out af_n));
	byte f_n = (byte) af_n;
	Eq_n C_n = cond(a_n);
	if (a_n < 0x00)
	{
		Eq_n hl_n = globals->t1687;
		C_n = fn061B(0x02, 0x4C, SLICE(hl_n, byte, 8), (byte) hl_n);
	}
	cu8 a_n = __rcr(globals->b1690, 0x01, C_n);
	Eq_n C_n = cond(a_n);
	if (a_n >= 0x00)
	{
		cu8 a_n = __rcr(globals->b1691, 0x01, C_n);
		Eq_n C_n = cond(a_n);
		if (a_n >= 0x00)
		{
			if (__rcr(globals->b168F, 0x01, C_n) >= 0x00)
				return SEQ(fn0920(), f_n);
			if (globals->b1520 == 0x00)
			{
				*globals->t168B = globals->b151F;
				return SEQ(fn0920(), f_n);
			}
			else
			{
				*globals->t168B = globals->b1520;
				return SEQ(fn0920(), f_n);
			}
		}
		else
		{
			if (globals->b151E != 0x00)
				return SEQ(fn08EC(), f_n);
			*globals->t168B = globals->b151F;
			return SEQ(fn08FD(), f_n);
		}
	}
	else
	{
		if (*globals->t168B == 0x00)
		{
			if (globals->b151D == 0x00)
				*globals->t168B = globals->b151F;
			else
				*globals->t168B = globals->b151D;
		}
		return SEQ(fn0920(), f_n);
	}
}

// 08EC: Register byte fn08EC()
byte fn08EC()
{
	*globals->t168B = globals->b151E;
	return fn08FD();
}

// 08FD: Register byte fn08FD()
byte fn08FD()
{
	return fn0920();
}

// 0920: Register uint8 fn0920()
uint8 fn0920()
{
	uint8 a_n;
	F_DMAOFF(0x80);
	if (globals->b168D == 0x00)
	{
		byte b_n;
		byte h_n;
		cu8 a_n;
		byte l_n;
		S_BDOSVER(out b_n, out h_n, out a_n, out l_n);
		if ((~(0x00 - (a_n < 0x30)) & globals->b168E) >> 0x01 < 0x00)
			((word16) globals->t168B + 7)->u0 = *((word16) globals->t168B + 7) | 0x80;
		a_n = F_OPEN(globals->t168B);
		if (a_n == ~0x00)
		{
			Eq_n hl_n = globals->t1687;
			fn061B(0x02, 0x36, SLICE(hl_n, byte, 8), (byte) hl_n);
		}
	}
	else
	{
		F_DELETE(globals->t168B);
		a_n = F_MAKE(globals->t168B);
		if (a_n == ~0x00)
		{
			Eq_n hl_n = globals->t1687;
			fn061B(0x02, 0x87, SLICE(hl_n, byte, 8), (byte) hl_n);
		}
	}
	return a_n;
}

// 0990: FlagGroup Eq_n fn0990(Register byte f, Register byte b, Register Eq_n c, Register byte d, Register Eq_n e, Register out Eq_n afOut)
Eq_n fn0990(byte f, byte b, Eq_n c, byte d, Eq_n e, union Eq_n & afOut)
{
	globals->b1695 = d;
	globals->t1694 = e;
	globals->b1693 = b;
	globals->t1692 = c;
	Eq_n hl_n = globals->t168B;
	fn0390(SLICE((word16) hl_n + 1, byte, 8), (byte) ((word16) hl_n + 1), 0x20, SEQ(b, 11));
	globals->t1696 = *globals->t1692;
	Eq_n hl_n = globals->t1692;
	globals->t1692 = (word16) hl_n + 1;
	Eq_n sp_n = <invalid>;
	if (*((word16) hl_n + 2) == 0x3A)
	{
		Eq_n af_n = fn03CB(*globals->t1692);
		*((word16) sp_n - 2) = af_n;
		*((word16) sp_n - 2) = af_n;
		bcu8 a_n = 0x00 - (globals->t1696 > 0x02) & *((word16) sp_n + 3);
		f = (byte) af_n;
		Eq_n C_n = cond(a_n >> 0x01);
		if (a_n >> 0x01 >= 0x00)
		{
			afOut.u0 = (uint16) (uint8) f;
			return C_n;
		}
		*globals->t168B = *globals->t1692 & 0x1F;
		Eq_n hl_n = globals->t168B;
		Eq_n C_n = (bool) cond(0x10 - *hl_n);
		if (*hl_n > 0x10)
		{
			afOut.u0 = (uint16) (uint8) f;
			return C_n;
		}
		globals->t1692 = (word16) globals->t1692 + 2;
		--globals->t1696;
		--globals->t1696;
	}
	else
		*globals->t168B = 0x00;
	globals->t1697.u0 = 0x00;
	while (true)
	{
		*((word16) sp_n - 2) = SEQ(~(0x00 - (globals->t1697 > 0x07)), f);
		word16 af_n = fn0B74();
		f = (byte) af_n;
		if ((SLICE(af_n, byte, 8) & *((word16) sp_n + 3)) >> 0x01 >= 0x00)
			break;
		Mem399[sp_n + -2:word16] = Mem123[5778:word16] + Mem123[0x1697:word16];
		byte a_n = **((word16) sp_n - 2);
		((word16) globals->t168B + ((word16) globals->t1697 + 1))->u0 = a_n;
		Eq_n C_n = (bool) cond(a_n - 0x2A);
		if (a_n == 0x2A)
		{
			afOut.u0 = (uint16) (uint8) f;
			return C_n;
		}
		fn0B91();
	}
	byte b_n;
	cu8 * hl_n = (word16) globals->t1692 + (uint16) ((uint8) globals->t1697);
	*((word16) sp_n - 2) = SEQ(0x00 - (globals->t1696 > 0x01), f);
	if ((0x00 - (*hl_n < 0x2F) & *((word16) sp_n + 3)) >> 0x01 < 0x00)
	{
		fn0B91();
		Eq_n C_n = (bool) cond(0x03 - globals->t1696);
		if (globals->t1696 > 0x03)
		{
			afOut.u0 = (uint16) (uint8) f;
			return C_n;
		}
		*((word16) sp_n - 2) = globals->t1696;
		Mem256[sp_n + -4:word16] = Mem247[5778:word16] + Mem247[0x1697:word16];
		byte * de_n = (word16) globals->t168B + 9;
		byte * bc_n = *((word16) sp_n - 4);
		byte l_n;
		do
		{
			*de_n = *bc_n;
			++bc_n;
			b_n = SLICE(bc_n, byte, 8);
			++de_n;
			--l_n;
		} while (l_n != 0x00);
	}
	else
	{
		word16 hl_n = Mem157[5778:word16] + Mem157[0x1697:word16];
		*((word16) sp_n - 2) = SEQ(0x00 - (globals->t1696 < 0x01), f);
		bcu8 a_n = 0x00 - (*hl_n < 0x2F) | *((word16) sp_n + 3);
		Eq_n C_n = cond(a_n >> 0x01);
		if (a_n >> 0x01 >= 0x00)
		{
			afOut.u0 = (uint16) (uint8) f;
			return C_n;
		}
		Eq_n hl_n = globals->t1694;
		*((word16) sp_n - 2) = SEQ(SLICE(hl_n, byte, 8), *hl_n);
		*((word16) sp_n - 4) = (word16) globals->t1694 + 1;
		byte * de_n = (word16) globals->t168B + 9;
		byte * bc_n = *((word16) sp_n - 4);
		byte l_n;
		do
		{
			*de_n = *bc_n;
			++bc_n;
			b_n = SLICE(bc_n, byte, 8);
			++de_n;
			--l_n;
		} while (l_n != 0x00);
	}
	*((word16) sp_n - 2) = SEQ(b_n, 0x03);
	Eq_n hl_n = globals->t168B;
	fn0390(SLICE((word16) hl_n + 0x0C, byte, 8), (byte) ((word16) hl_n + 0x0C), 0x00, *((word16) sp_n - 2));
	((word16) globals->t168B + 32)->u0 = 0x00;
	globals->t1697.u0 = 0x00;
	while (globals->t1697 <= 0x07)
	{
		((word16) globals->t168B + ((word16) globals->t1697 + 1))->u0 = fn03E6(*((word16) globals->t168B + ((word16) globals->t1697 + 1)));
		Eq_n a_n = globals->t1697;
		globals->t1697 = (word16) a_n + 1;
		if (a_n == 0x01)
			break;
	}
	globals->t1697.u0 = 0x00;
	do
	{
		Eq_n C_n = (bool) cond(0x02 - globals->t1697);
		if (globals->t1697 > 0x02)
			break;
		byte a_n = fn03E6(*((word16) globals->t168B + ((word16) globals->t1697 + 9)));
		byte * hl_n = (word16) globals->t168B + ((word16) globals->t1697 + 9);
		*hl_n = a_n;
		Eq_n a_n = globals->t1697;
		globals->t1697 = (word16) a_n + 1;
		C_n = (bool) cond(hl_n);
	} while (a_n != 0x01);
	afOut = SEQ(0x01, f);
	return C_n;
}

// 0B74: Register word16 fn0B74()
word16 fn0B74()
{
	return SEQ(0x00 - (Mem20[0x1696:byte] <u ~0x00) & 0x00 - (Mem0[Mem0[5778:word16] + Mem0[0x1697:word16]:byte] <u 0x2F), f);
}

// 0B91: void fn0B91()
void fn0B91()
{
	globals->t1697 = (word16) globals->t1697 + 1;
	--globals->t1696;
}

// 0BE4: void fn0BE4(Register byte f)
void fn0BE4(byte f)
{
	byte a_n = 0x00 - (globals->b138A < ~0x01);
	if ((0x00 - (globals->b14F3 < 0x03) & a_n) >> 0x01 < 0x00)
	{
		if (globals->b14F6 != 0x01)
			fn0814(a_n);
		fn05CE(662);
		fn0814(SLICE((uint16) (uint8) fn06CE(0x00, globals->b138A - 0x01), byte, 8));
	}
	struct Eq_n * hl_n = globals->ptr1388;
	globals->b1645 = globals->b138A + 0x30;
	hl_n->wFFFFFFFE = 0x0231;
	hl_n->wFFFFFFFC = 0x1642;
	Eq_n af_n = fn082F(f, 0x00, 0x5C, 0x10, hl_n->wFFFFFFFC, hl_n->wFFFFFFFE);
	hl_n->wFFFFFFFA = 0x5C;
	byte l_n;
	fn1326(0x07, fn1346(&globals->w0108, &globals->t0103), out l_n);
	Eq_n hl_n = <invalid>;
	word16 hl_n = globals->w0108;
	fn040D(SLICE(hl_n, byte, 8), (byte) hl_n, (byte) hl_n, hl_n->wFFFFFFF8);
	Eq_n sp_n = <invalid>;
	*((word16) sp_n - 2) = af_n;
	byte f_n = (byte) af_n;
	if ((0x00 - (globals->b138A > 0x03) | *((word16) sp_n + 3)) >> 0x01 < 0x00)
		fn075C(0x00, 0x01, 0x00, 0x00);
	if (globals->b138A != 0x01)
	{
		if (globals->b138A != 0x02)
		{
			if (globals->b138A != 0x03)
				return;
			fn1729();
		}
		else
			fn177D();
	}
	else
		fn172D();
}

// 0C93: Register byte fn0C93()
byte fn0C93()
{
	return (word16) globals->t138C + globals->b138D + ((uint16) ((uint8) globals->t138C) + 5004) + 0x7F;
}

// 0D64: FlagGroup Eq_n fn0D64(Register out Eq_n aOut)
Eq_n fn0D64(union Eq_n & aOut)
{
	bcu8 a_n = globals->ptr1521->b0009;
	aOut = a_n >> 0x01;
	return cond(a_n >> 0x01);
}

// 0D6F: void fn0D6F()
void fn0D6F()
{
	struct Eq_n * hl_n = globals->ptr1521;
	hl_n->b0009 |= 0x02;
}

// 0D84: void fn0D84()
void fn0D84()
{
	cu8 a_n;
	if (__rcr(a_n, 0x01, fn0D64(out a_n)) < 0x00)
		fn075C(0x00, 0x02, 0x00, 0x00);
	struct Eq_n * hl_n = globals->ptr1521;
	hl_n->b0009 |= 0x01;
}

// 0DB9: void fn0DB9()
void fn0DB9()
{
	bcu8 a_n = globals->ptr1521->b0009;
	cu8 a_n = __rcr(a_n + 252, 0x01, (bool) cond(a_n + 252));
	cu8 a_n = __rcr(a_n, 0x01, cond(a_n));
	__rcr(a_n, 0x01, cond(a_n));
}

// 0DCB: void fn0DCB()
void fn0DCB()
{
	struct Eq_n * hl_n = globals->ptr1521;
	hl_n->b0009 |= 0x08;
}

// 0E63: void fn0E63(Register byte c)
void fn0E63(byte c)
{
	globals->b16A6 = c;
	uint16 bc_n = (uint16) (uint8) fn0C93();
	struct Eq_n * hl_n = bc_n + 0x152C + bc_n;
	globals->ptr1521 = SEQ(hl_n->b0001, hl_n->b0000);
	while (true)
	{
		Eq_n hl_n = <invalid>;
		byte l_n;
		if ((fn1353(0x00, &globals->ptr1521, out l_n) | (byte) hl_n) == 0x00)
			break;
		if (globals->b16A6 == (globals->ptr1521)->b0002)
		{
			cu8 a_n;
			if (__rcr(a_n, 0x01, fn0EAB(out a_n)) < 0x00)
				return;
		}
		struct Eq_n * hl_n = globals->ptr1521;
		globals->ptr1521 = SEQ(hl_n->b0001, hl_n->b0000);
	}
}

// 0EAB: FlagGroup bool fn0EAB(Register out Eq_n aOut)
bool fn0EAB(union Eq_n & aOut)
{
	globals->t16A7.u0 = 0x00;
	while (true)
	{
		Eq_n a_n = globals->t138C;
		bool C_n = (bool) cond(a_n - globals->t16A7);
		if (a_n < globals->t16A7)
			break;
		Eq_n hl_n = globals->t16A7;
		byte a_n = globals->ptr1521[((word16) globals->t16A7 + 0x0A) / 0x0A];
		bool C_n = (bool) cond(a_n - *((word16) hl_n + 5004));
		if (a_n != *((word16) hl_n + 5004))
		{
			aOut.u0 = 0x00;
			return C_n;
		}
		globals->t16A7 = (word16) globals->t16A7 + 1;
	}
	aOut.u0 = 0x01;
	return C_n;
}

// 0FB8: void fn0FB8()
void fn0FB8()
{
}

// 100A: void fn100A(Register word16 af)
void fn100A(word16 af)
{
	while (true)
	{
		byte f_n = (byte) af;
		if ((0x00 - (globals->b14FF < 0x0E) & SLICE(af, byte, 8)) >> 0x01 >= 0x00)
			break;
		cu8 a_n = globals->b14FF;
		globals->b14FF = a_n + 0x01;
		(uint16) (uint8) (a_n + 0x01) + 0x14FF = (uint16) globals->b16A8;
		globals->b16A8 = fn045B();
		af = SEQ(0x00 - (globals->b16A8 < 33), f_n);
	}
	if (globals->b14FF == 0x00)
	{
		fn05CE(0x0369);
		fn0387();
	}
	while ((0x00 - (globals->b16A8 < ~0x00) & 0x00 - (globals->b16A8 < 0x03)) >> 0x01 < 0x00)
		globals->b16A8 = fn045B();
	globals->b16A8 = fn045B();
	while (true)
	{
		byte a_n = 0x00 - (globals->b16A8 < 0x01);
		if ((0x00 - (globals->b16A8 < ~0x00) & a_n) >> 0x01 >= 0x00)
			break;
		if (globals->b16A8 == 0x20)
			fn1262();
		if (globals->b16A8 == 66)
			globals->b14F3 = 0x00;
		else if (globals->b16A8 == 0x43)
		{
			word16 af_n = fn12D8();
			globals->b151D = SLICE(af_n, byte, 8);
			f_n = (byte) af_n;
		}
		else if (globals->b16A8 == 0x44)
		{
			word16 af_n = fn1279();
			globals->b138B = SLICE(af_n, byte, 8);
			f_n = (byte) af_n;
		}
		else if (globals->b16A8 == 0x46)
			globals->b14F3 = 0x04;
		else if (globals->b16A8 == 0x49)
			globals->b14FA = 0x01;
		else if (globals->b16A8 == 0x4C)
		{
			word16 af_n = fn1279();
			globals->b14F7 = SLICE(af_n, byte, 8);
			f_n = (byte) af_n;
		}
		else if (globals->b16A8 == 0x4E)
			globals->b14FB = 0x01;
		else if (globals->b16A8 == 0x4F)
			globals->b14EF = 0x00;
		else if (globals->b16A8 == 0x50)
			globals->b14F3 = 0x01;
		else if (globals->b16A8 == 0x52)
		{
			word16 af_n = fn12D8();
			globals->b1520 = SLICE(af_n, byte, 8);
			f_n = (byte) af_n;
		}
		else if (globals->b16A8 == 0x53)
			globals->b14F0 = 0x01;
		else if (globals->b16A8 == 0x54)
			globals->b14F5 = 0x01;
		else if (globals->b16A8 == 0x55)
			globals->b1529 = 0x01;
		else if (globals->b16A8 == 0x56)
			globals->b14FC = 0x01;
		else if (globals->b16A8 == 0x57)
		{
			word16 af_n = fn1279();
			globals->b14F8 = SLICE(af_n, byte, 8);
			f_n = (byte) af_n;
		}
		else if (globals->b16A8 == 88)
		{
			word16 af_n = fn12D8();
			globals->b151E = SLICE(af_n, byte, 8);
			f_n = (byte) af_n;
		}
		else
			fn1229();
		globals->b16A8 = fn045B();
		fn1262();
		if (globals->b16A8 == 44)
			globals->b16A8 = fn045B();
		else if (globals->b16A8 == 0x02)
		{
			globals->b16A8 = fn045B();
			fn1262();
			if (globals->b16A8 != 0x04)
				globals->b16A8 = 0x5D;
			else
				globals->b16A8 = fn045B();
		}
	}
	Eq_n bc_n = SEQ(a_n, a_n);
	if (globals->b14F3 == 0x01)
	{
		fn056B(SEQ(a_n, 0x0C), out bc_n);
		globals->b14F9 = 0x01;
	}
	globals->b14F4 = globals->b14F3;
	globals->b14FD = globals->b14F7 + 0x01;
	globals->b138A = 0x01;
	fn07B3(bc_n);
	fn0BE4(f_n);
	__ei();
	__hlt();
}

// 1229: void fn1229()
void fn1229()
{
	globals->b14F3 = 0x02;
	byte b_n = SLICE((uint16) (uint8) fn05CE(0x02D1), byte, 8);
	if (globals->b16A8 != 0x00)
	{
		word16 bc_n;
		fn056B(SEQ(b_n, 0x3E), out bc_n);
		word16 bc_n;
		fn056B(SEQ(SLICE(bc_n, byte, 8), 0x20), out bc_n);
		while (true)
		{
			byte b_n = SLICE(bc_n, byte, 8);
			if (globals->b16A8 == 0x00)
				break;
			fn056B(SEQ(b_n, globals->b16A8), out bc_n);
			globals->b16A8 = fn045B();
		}
	}
	fn0387();
}

// 1262: void fn1262()
void fn1262()
{
	if (globals->b16A8 == 0x20)
	{
		do
		{
			cu8 a_n = fn045B();
			globals->b16A8 = a_n;
		} while (a_n == 0x20);
	}
}

// 1279: Register word16 fn1279()
word16 fn1279()
{
	globals->b16A8 = fn045B();
	fn1262();
	if (globals->b16A8 != 0x28)
		fn1229();
	globals->b16AA = 0x00;
	while (true)
	{
		cu8 a_n = fn045B();
		globals->b16A9 = a_n;
		if (a_n > 0x39 || a_n < 0x30)
			break;
		globals->b16AA = globals->b16A9 + 0x0F + (globals->b16AA * 0x02 + globals->b16AA * 0x08);
	}
	if (globals->b16A9 == 0x20)
		fn1262();
	if (globals->b16A9 != 0x29)
		fn1229();
	return SEQ(globals->b16AA, f);
}

// 12D8: Register word16 fn12D8()
word16 fn12D8()
{
	globals->b16A8 = fn045B();
	fn1262();
	if (globals->b16A8 == 0x28)
		globals->b16AB = fn045B() + 0x1F;
	else
		fn1229();
	if ((0x00 - (globals->b16AB > 0x10) | 0x00 - (fn045B() < 0x2A)) >> 0x01 < 0x00)
		fn1229();
	return SEQ(globals->b16AB, f);
}

// 1315: void fn1315()
void fn1315()
{
}

// 1326: Register byte fn1326(Register byte c, Register uint16 hl, Register out Eq_n lOut)
byte fn1326(byte c, uint16 hl, union Eq_n & lOut)
{
	uint16 hl_n = hl;
	do
	{
		uint16 v13_n = hl_n >> 0x01;
		Eq_n l_n = (byte) v13_n;
		--c;
		hl_n = v13_n;
	} while (c != 0x00);
	lOut = l_n;
	return c;
}

// 1335: FlagGroup bool fn1335(Register word16 de, Register word16 hl)
bool fn1335(word16 de, word16 hl)
{
	return (bool) cond(SLICE(de - hl, byte, 8));
}

// 133C: void fn133C()
void fn133C()
{
}

// 1346: Register word16 fn1346(Register (ptr16 Eq_n) bc, Register (ptr16 Eq_n) de)
word16 fn1346(struct Eq_n * bc, struct Eq_n * de)
{
	word16 hl_n;
	word16 de_n;
	fn1348(de, bc, out de_n, out hl_n);
	return hl_n;
}

// 1348: FlagGroup bool fn1348(Register (ptr16 Eq_n) de, Register (ptr16 Eq_n) hl, Register out (ptr16 ui8) deOut, Register out Eq_n hlOut)
bool fn1348(struct Eq_n * de, struct Eq_n * hl, ui8 & deOut, union Eq_n & hlOut)
{
	Eq_n a_a_n = SEQ(de->b0001, de->b0000) - SEQ(hl->b0001, hl->b0000);
	deOut = (ui8 *) &de->b0001;
	hlOut = a_a_n;
	return (bool) cond(SLICE(a_a_n, byte, 8));
}

// 1353: Register byte fn1353(Register byte a, Register (ptr16 Eq_n) de, Register out Eq_n lOut)
byte fn1353(byte a, struct Eq_n * de, union Eq_n & lOut)
{
	Eq_n a_n = de->b0000 - a;
	byte a_n = de->b0001 - (a_n < 0x00);
	lOut = a_n;
	return a_n;
}

// 1356: void fn1356()
void fn1356()
{
}

// 140B: void fn140B(Register byte a)
void fn140B(byte a)
{
	null = (byte *) a;
	fn156F();
}

// 156F: void fn156F()
void fn156F()
{
	fn15B0();
}

// 15B0: void fn15B0()
void fn15B0()
{
	__hlt();
}

