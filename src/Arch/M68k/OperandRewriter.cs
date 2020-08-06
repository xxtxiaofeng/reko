#region License
/* 
 * Copyright (C) 1999-2020 John Källén.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; see the file COPYING.  If not, write to
 * the Free Software Foundation, 675 Mass Ave, Cambridge, MA 02139, USA.
 */
#endregion

using Reko.Core;
using Reko.Core.Expressions;
using Reko.Core.Machine;
using Reko.Core.Rtl;
using Reko.Core.Types;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Reko.Arch.M68k
{
    /// <summary>
    /// Rewrites M68k operands into sequences of RTL expressions and possibly instructions.
    /// </summary>
    /// <remarks>
    /// Some of the operands, like (A6)+ and -(A5), have side effects that need to be expressed
    /// as separate instructions. We must therefore insert RTL instructions into the stream as these
    /// operands are rewritten. Because of these side effects, it is critical that we don't call
    /// Rewrite twice on the same operand, as this will cause two side effect instructions to be
    /// generated.
    /// </remarks>
    public class OperandRewriter
    {
        private readonly M68kArchitecture arch;
        private readonly RtlEmitter m;
        private readonly IStorageBinder binder;

        public OperandRewriter(M68kArchitecture arch, RtlEmitter emitter, IStorageBinder binder, PrimitiveType dataWidth)
        {
            this.arch = arch;
            this.m = emitter;
            this.binder = binder;
            this.DataWidth = dataWidth;
        }

        public PrimitiveType DataWidth { get; set; }     // the data width of the current instruction being rewritten.
        
        /// <summary>
        /// Rewrite operands being used as sources.
        /// </summary>
        /// <param name="operand"></param>
        /// <param name="addrInstr">Address of the current instruction</param>
        public Expression RewriteSrc(MachineOperand operand, Address addrInstr, bool addressAsAddress = false)
        {
            Expression ea;
            Expression r;
            switch (operand)
            {
            case RegisterOperand reg:
                r = binder.EnsureRegister(reg.Register);
                if (DataWidth != null && DataWidth.Size != reg.Width.Size)
                {
                    if (DataWidth.Domain == Domain.Real)
                        r = m.Convert(r, r.DataType, DataWidth);
                    else
                        r = m.Slice(DataWidth, r, 0);
                }
                return r;
            case M68kImmediateOperand imm:
                if (imm.Width.Domain == Domain.Real)
                    return imm.Constant.CloneExpression();
                if (DataWidth != null && DataWidth.BitSize > imm.Width.BitSize)
                    return Constant.Create(DataWidth, imm.Constant.ToInt64());
                else
                    return Constant.Create(imm.Width, imm.Constant.ToUInt32());
            case MemoryOperand mem:
                return RewriteMemoryAccess(mem, DataWidth, addrInstr);
            case M68kAddressOperand addr:
                if (addressAsAddress)
                    return addr.Address;
                else 
                    return m.Mem(DataWidth, addr.Address);
            case PredecrementMemoryOperand pre:
                ea = binder.EnsureRegister(pre.Register);
                m.Assign(ea, m.ISubS(ea, DataWidth.Size));
                return m.Mem(DataWidth, ea);
            case PostIncrementMemoryOperand post:
                r = binder.EnsureRegister(post.Register);
                var tmp = binder.CreateTemporary(DataWidth);
                m.Assign(tmp, m.Mem(DataWidth, r));
                m.Assign(r, m.IAddS(r, DataWidth.Size));
                return tmp;
            case IndirectIndexedOperand indidx:
                ea = RewriteIndirectBaseRegister(indidx, addrInstr);
                Expression ix = binder.EnsureRegister(indidx.XRegister);
                if (indidx.XWidth.Size != 4)
                {
                    ix = m.Slice(PrimitiveType.Int16, ix, 0);
                    ix = m.Convert(ix, PrimitiveType.Int16, PrimitiveType.Int32);
                }
                if (indidx.Scale > 1)
                    ix = m.IMul(ix, Constant.Int32(indidx.Scale));
                return m.Mem(DataWidth, m.IAdd(ea, ix));
            case IndexedOperand indop:  
                ea = Combine(indop.BaseDisplacement, indop.Base, addrInstr);
                if (indop.postindex)
                {
                    ea = m.Mem32(ea);
                }
                if (indop.Index != null)
                {
                    var idx = Combine(null, indop.Index, addrInstr);
                    if (indop.index_reg_width!.BitSize != 32)
                        idx = m.Convert(idx, PrimitiveType.Int16, PrimitiveType.Int32);
                    if (indop.IndexScale > 1)
                        idx = m.IMul(idx, indop.IndexScale);
                    ea = Combine(ea, idx);
                }
                if (indop.preindex)
                {
                    ea = m.Mem32(ea);
                }
                ea = Combine(ea, indop.OuterDisplacement);
                return m.Mem(DataWidth, ea);
            }
            throw new NotImplementedException("Unimplemented RewriteSrc for operand type " + operand.GetType().Name);
        }

        private Expression RewriteIndirectBaseRegister(IndirectIndexedOperand indidx, Address addrInstr)
        {
            if (indidx.ARegister == Registers.pc)
            {
                // pc-relative instruction.
                return addrInstr + indidx.Imm8;
            }
            Expression ea = binder.EnsureRegister(indidx.ARegister);
            if (indidx.Imm8 != 0)
                ea = m.IAddS(ea, indidx.Imm8);
            return ea;
        }

        public Expression Combine(Expression? e, RegisterStorage? reg, Address addrInstr)
        {
            if (reg == null)
                return e!;
            Expression ea;
            if (reg == Registers.pc)
            {
                // The +2 offset is necessary as PC-relative addresses
                // use the address of the instruction extension word
                // as the PC address.
                var addrPc = addrInstr + 2;
                if (e == null)
                    return addrPc;
                if (e is Constant c)
                {
                    return addrPc + c.ToInt32();
                }
                ea = addrPc;
            }
            else
            {
                ea = binder.EnsureRegister(reg);
            }
            if (e == null)
                return ea;
            return m.IAdd(e, ea);
        }

        public Expression Combine(Expression? e, Expression? o)
        {
            if (o is null)
                return e!;
            if (e is null)
                return o;
            if (o is Constant c && c.DataType.BitSize < 32)
                o = Constant.Int32(c.ToInt32());    // Sign extend displacements shorter than a pointer.
            return m.IAdd(e, o);
        }

        public Expression? RewriteDst(MachineOperand operand, Address addrInstr, Expression src, Func<Expression, Expression, Expression> opGen)
        {
            return RewriteDst(operand, addrInstr, this.DataWidth, src, opGen);
        }

        public Expression? RewriteDst(
            MachineOperand operand,
            Address addrInstr,
            PrimitiveType dataWidth,
            Expression src,
            Func<Expression, Expression, Expression> opGen)
        {
            switch (operand)
            {
            case RegisterOperand reg:
                {
                    var r = binder.EnsureRegister(reg.Register);
                    Expression tmpLo = r;
                    if (dataWidth != null &&
                        reg.Width.BitSize > dataWidth.BitSize &&
                        reg.Width.Domain != Domain.Real)
                    {
                        Expression rSub = m.Slice(dataWidth, r, 0);
                        var srcExp = opGen(src, rSub);
                        if (srcExp is Identifier || srcExp is Constant || srcExp is MkSequence)
                        {
                            tmpLo = srcExp;
                        }
                        else
                        {
                            tmpLo = binder.CreateTemporary(dataWidth);
                            m.Assign(tmpLo, srcExp);
                        }
                        var tmpHi = binder.CreateTemporary(PrimitiveType.CreateWord(reg.Width.BitSize - tmpLo.DataType.BitSize));
                        m.Assign(tmpHi, m.Slice(tmpHi.DataType, r, tmpLo.DataType.BitSize));
                        src = m.Seq(tmpHi, tmpLo);
                    }
                    else
                    {
                        src = opGen(src, r);
                    }
                    m.Assign(r, src);
                    return tmpLo;
                }
            case DoubleRegisterOperand dbl:
                {
                    Identifier h = binder.EnsureRegister(dbl.Register1);
                    Identifier l = binder.EnsureRegister(dbl.Register2);
                    var d = binder.EnsureSequence(PrimitiveType.Word64, h.Storage, l.Storage);
                    var result = opGen(src, l);
                    m.Assign(d, result);
                    return d;
                }
            case M68kAddressOperand addr:
                {
                    var load = m.Mem(dataWidth, addr.Address);
                    return EmitStore(load, opGen(src, load));
                }
            case MemoryOperand mem:
                {
                    var load = RewriteMemoryAccess(mem, dataWidth, addrInstr);
                    return EmitStore(load, opGen(src, load));
                }
            case PostIncrementMemoryOperand post:
                {
                    var r = binder.EnsureRegister(post.Register);
                    var access = m.Mem(dataWidth, r);
                    var tmp = EmitStore(access, opGen(src, access));
                    m.Assign(r, m.IAddS(r, dataWidth.Size));
                    return tmp;
                }
            case PredecrementMemoryOperand pre:
                {
                    var r = binder.EnsureRegister(pre.Register);
                    src = Spill(src, r);
                    m.Assign(r, m.ISubS(r, dataWidth.Size));
                    var access = m.Mem(dataWidth, r);
                    return EmitStore(access, opGen(src, access));
                }
            case IndirectIndexedOperand indidx:
                {
                    Expression ea = binder.EnsureRegister(indidx.ARegister);
                    if (indidx.Imm8 != 0)
                        ea = m.IAddS(ea, indidx.Imm8);
                    Expression ix = binder.EnsureRegister(indidx.XRegister);
                    if (indidx.Scale > 1)
                        ix = m.IMul(ix, Constant.Int32(indidx.Scale));
                    var access = m.Mem(dataWidth, m.IAdd(ea, ix));
                    return EmitStore(access, opGen(src, access));
                }
            }
            return null;
        }

        private Expression EmitStore(MemoryAccess store, Expression expression)
        {
            if (expression is Constant || expression is Identifier || expression is Address)
            {
                m.Assign(store, expression);
                return expression;
            }
            else
            {
                var tmp = binder.CreateTemporary(store.DataType);
                m.Assign(tmp, expression);
                m.Assign(store, tmp);
                return tmp;
            }
        }

        private MemoryAccess RewriteMemoryAccess(MemoryOperand mem, PrimitiveType dataWidth, Address addrInstr)
        {
            Expression ea;
            if (mem.Base == Registers.pc)
            {
                var addr = addrInstr;
                if (mem.Offset != null)
                    addr += mem.Offset.ToInt32();
                ea = addr;
            }
            else
            {
                var bReg = binder.EnsureRegister(mem.Base);
                ea = bReg;
                if (mem.Offset != null)
                {
                    ea = m.IAddS(bReg, mem.Offset.ToInt32());
                }
            }
            return m.Mem(dataWidth, ea);
        }

        public Expression RewriteUnary(
            MachineOperand operand, 
            Address addrInstr,
            PrimitiveType dataWidth,
            Func<Expression, Expression> opGen)
        {
            switch (operand)
            {
            case RegisterOperand reg:
                {
                    Expression r = binder.EnsureRegister(reg.Register);
                    if (r.DataType.BitSize > dataWidth.BitSize)
                    {
                        var tmpLo = binder.CreateTemporary(dataWidth);
                        var tmpHi = binder.CreateTemporary(PrimitiveType.CreateWord(r.DataType.BitSize - dataWidth.BitSize));
                        m.Assign(tmpLo, opGen(m.Convert(r, r.DataType, dataWidth)));
                        m.Assign(tmpHi, m.Slice(tmpHi.DataType, r, dataWidth.BitSize));
                        m.Assign(r, m.Seq(tmpHi, tmpLo));
                        return tmpLo;
                    }
                    else
                    {
                        m.Assign(r, opGen(r));
                        return r;
                    }
                }
            case M68kAddressOperand addr:
                {
                    var access = m.Mem(dataWidth, addr.Address);
                    return EmitStore(access, opGen(access));
                }
            case MemoryOperand mem:
                {
                    var access = RewriteMemoryAccess(mem, dataWidth, addrInstr);
                    return EmitStore(access, opGen(access));
                }
            case PostIncrementMemoryOperand post:
                {
                    var r = binder.EnsureRegister(post.Register);
                    var access = m.Mem(dataWidth, r);
                    var tmp = EmitStore(access, opGen(access));
                    m.Assign(r, m.IAddS(r, dataWidth.Size));
                    return tmp;
                }
            case PredecrementMemoryOperand pre:
                {
                    var r = binder.EnsureRegister(pre.Register);
                    m.Assign(r, m.ISubS(r, dataWidth.Size));
                    var access = m.Mem(dataWidth, r);
                    return EmitStore(access, opGen(access));
                }
            case IndirectIndexedOperand indidx:
                {
                    Expression ea = binder.EnsureRegister(indidx.ARegister);
                    if (indidx.Imm8 != 0)
                        ea = m.IAddS(ea, indidx.Imm8);
                    Expression ix = binder.EnsureRegister(indidx.XRegister);
                    if (indidx.Scale > 1)
                        ix = m.IMul(ix, Constant.Int32(indidx.Scale));
                    var access = m.Mem(dataWidth, m.IAdd(ea, ix));
                    return EmitStore(access, opGen(access));
                }
            case IndexedOperand indop:
                {
                    Expression ea = Combine(indop.BaseDisplacement, indop.Base, addrInstr);
                    if (indop.postindex)
                    {
                        ea = m.Mem32(ea);
                    }
                    if (indop.Index != null)
                    {
                        var idx = Combine(null, indop.Index, addrInstr);
                        if (indop.index_reg_width!.BitSize != 32)
                        {
                            idx = m.Slice(PrimitiveType.Int16, idx, 0);
                            idx = m.Convert(idx, PrimitiveType.Int16, PrimitiveType.Int32);
                        }
                        if (indop.IndexScale > 1)
                            idx = m.IMul(idx, m.Int32(indop.IndexScale));
                        ea = Combine(ea, idx);
                    }
                    if (indop.preindex)
                    {
                        ea = m.Mem32(ea);
                    }
                    ea = Combine(ea, indop.OuterDisplacement);
                    var access = m.Mem(DataWidth, ea);
                    return EmitStore(access, opGen(access));
                }
            }
            throw new AddressCorrelatedException(
                addrInstr,
                "Unimplemented RewriteUnary for operand {0} of type {1}.", 
                operand.ToString(),
                operand.GetType().Name);
        }

        public Expression RewriteMoveDst(MachineOperand opDst, Address addrInstr, PrimitiveType dataWidth, Expression src)
        {
            switch (opDst)
            {
            case RegisterOperand reg:
                {
                    var r = binder.EnsureRegister(reg.Register);
                    if (r.DataType.BitSize > src.DataType.BitSize)
                    {
                        var tmpLo = binder.CreateTemporary(src.DataType);
                        var tmpHi = binder.CreateTemporary(PrimitiveType.CreateWord(r.DataType.BitSize - src.DataType.BitSize));
                        m.Assign(tmpHi, m.Slice(tmpHi.DataType, r, dataWidth.BitSize));
                        m.Assign(r, m.Seq(tmpHi, src));
                        return tmpLo;
                    }
                    else
                    {
                        m.Assign(r, src);
                        return r;
                    }
                }
            case MemoryOperand mem:
                {
                    src = Spill(src, binder.EnsureRegister(mem.Base));
                    var access = RewriteMemoryAccess(mem, dataWidth, addrInstr);
                    m.Assign(access, src);
                    return src;
                }
            case PostIncrementMemoryOperand post:
                {
                    var r = binder.EnsureRegister(post.Register);
                    var rExp = Spill(src, r);
                    var access = m.Mem(dataWidth, r);
                    m.Assign(access, rExp);
                    m.Assign(r, m.IAddS(r, dataWidth.Size));
                    return src;
                }
            case PredecrementMemoryOperand pre:
                {
                    var r = binder.EnsureRegister(pre.Register);
                    m.Assign(r, m.ISubS(r, dataWidth.Size));
                    var rExp = Spill(src, r);
                    var access = m.Mem(dataWidth, rExp);
                    m.Assign(access, src);
                    return src;
                }
            case IndexedOperand idxop:
                {
                    Expression? ea = null;
                    if (idxop.Index != null)
                    {
                        var i = binder.EnsureRegister(idxop.Index);
                        var s = m.Const(i.DataType, idxop.IndexScale);
                        if (idxop.IndexScale > 1)
                        {
                            ea = m.IMul(i, s);
                        }
                        else
                        {
                            ea = i;
                        }
                    }
                    if (idxop.Base != null)
                    {
                        var b = binder.EnsureRegister(idxop.Base);
                        if (ea != null)
                        {
                            ea = m.IAdd(b, ea);
                        }
                        else
                        {
                            ea = b;
                        }
                    }
                    if (idxop.BaseDisplacement != null)
                    {
                        if (ea != null)
                        {
                            ea = m.IAdd(ea, idxop.BaseDisplacement);
                        }
                        else
                        {
                            ea = idxop.BaseDisplacement;
                        }
                    }
                    var access = m.Mem(dataWidth, ea!);
                    m.Assign(access, src);
                    return src;
                }
            case IndirectIndexedOperand indidx:
                {
                    var a = binder.EnsureRegister(indidx.ARegister);
                    var x = binder.EnsureRegister(indidx.XRegister);
                    var access = m.Mem(dataWidth, m.IAdd(a, x));
                    m.Assign(access, src);
                    return src;
                }
            case M68kAddressOperand mAddr:
                {
                    m.Assign(
                        m.Mem(
                            dataWidth,
                            m.Ptr32(mAddr.Address.ToUInt32())),
                        src);
                    return src;
                }
            }
            throw new NotImplementedException("Unimplemented RewriteMoveDst for operand type " + opDst.GetType().Name);
        }

        private Expression Spill(Expression src, Identifier r)
        {
            if (src is MemoryAccess || src == r)
            {
                var tmp = binder.CreateTemporary(src.DataType);
                m.Assign(tmp, src);
                src = tmp;
            }
            return src;
        }

        public Identifier FlagGroup(FlagM flags)
        {
            return binder.EnsureFlagGroup(arch.GetFlagGroup(Registers.ccr, (uint)flags));
        }
    }
}
