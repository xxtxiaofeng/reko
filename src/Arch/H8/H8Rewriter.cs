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
using Reko.Core.Pascal;
using Reko.Core.Rtl;
using Reko.Core.Services;
using Reko.Core.Types;
using System;
using System.Collections;
using System.Collections.Generic;
using System.Runtime.InteropServices;

namespace Reko.Arch.H8
{
    public class H8Rewriter : IEnumerable<RtlInstructionCluster>
    {
        private static readonly FlagGroupStorage C = new FlagGroupStorage(Registers.CcRegister, (uint) FlagM.CF, "C", PrimitiveType.Bool);
        private static readonly FlagGroupStorage N = new FlagGroupStorage(Registers.CcRegister, (uint) FlagM.NF, "N", PrimitiveType.Bool);
        private static readonly FlagGroupStorage NV = new FlagGroupStorage(Registers.CcRegister, (uint) (FlagM.NF | FlagM.VF), "NV", PrimitiveType.Byte);
        private static readonly FlagGroupStorage NZ = new FlagGroupStorage(Registers.CcRegister, (uint) (FlagM.NF | FlagM.ZF), "NZ", PrimitiveType.Byte);
        private static readonly FlagGroupStorage NZC = new FlagGroupStorage(Registers.CcRegister, (uint) (FlagM.NF|FlagM.ZF|FlagM.VF), "NZC", PrimitiveType.Byte);
        private static readonly FlagGroupStorage NZV = new FlagGroupStorage(Registers.CcRegister, (uint) (FlagM.NF|FlagM.ZF|FlagM.VF), "NZV", PrimitiveType.Byte);
        private static readonly FlagGroupStorage NZVC = new FlagGroupStorage(Registers.CcRegister, (uint) (FlagM.NF|FlagM.ZF|FlagM.VF|FlagM.CF), "NZVC", PrimitiveType.Byte);
        private static readonly FlagGroupStorage V = new FlagGroupStorage(Registers.CcRegister, (uint) FlagM.VF, "V", PrimitiveType.Bool);
        private static readonly FlagGroupStorage ZC = new FlagGroupStorage(Registers.CcRegister, (uint) (FlagM.ZF | FlagM.CF), "ZC", PrimitiveType.Byte);
        private static readonly FlagGroupStorage Z = new FlagGroupStorage(Registers.CcRegister, (uint) FlagM.ZF, "Z", PrimitiveType.Bool);


        private readonly H8Architecture arch;
        private readonly EndianImageReader rdr;
        private readonly ProcessorState state;
        private readonly IStorageBinder binder;
        private readonly IRewriterHost host;
        private readonly IEnumerator<H8Instruction> dasm;
        private RtlEmitter m;
        private InstrClass iclass;

        public H8Rewriter(H8Architecture arch, EndianImageReader rdr, ProcessorState state, IStorageBinder binder, IRewriterHost host)
        {
            this.arch = arch;
            this.rdr = rdr;
            this.state = state;
            this.binder = binder;
            this.host = host;
            this.dasm = new H8Disassembler(arch, rdr).GetEnumerator();
            this.m = new RtlEmitter(new List<RtlInstruction>());
        }

        public IEnumerator<RtlInstructionCluster> GetEnumerator()
        {
            while (dasm.MoveNext())
            {
                var instr = dasm.Current;
                this.iclass = instr.InstructionClass;
                switch (instr.Mnemonic)
                {
                default:
                    EmitUnitTest(instr);
                    goto case Mnemonic.Invalid;
                case Mnemonic.Invalid:
                    m.Invalid();
                    iclass = InstrClass.Invalid;
                    break;
                case Mnemonic.add: RewriteAdd(instr); break;
                case Mnemonic.adds: RewriteAdds(instr); break;
                case Mnemonic.addx: RewriteAddxSubx(instr, m.IAdd); break;
                case Mnemonic.and: RewriteLogical(instr, m.And); break;
                case Mnemonic.bld: RewriteBtst(instr, C); break;
                case Mnemonic.bset: RewriteBset(instr, Constant.True()); break;
                case Mnemonic.bst: RewriteBset(instr, binder.EnsureFlagGroup(C)); break;
                case Mnemonic.btst: RewriteBtst(instr, Z); break;
                case Mnemonic.bra: RewriteBranch(instr); break;
                case Mnemonic.brn: RewriteNop(); break;
                case Mnemonic.bhi: RewriteBranch(instr, ConditionCode.UGT, ZC); break;
                case Mnemonic.bls: RewriteBranch(instr, ConditionCode.ULE, ZC); break;
                case Mnemonic.bcc: RewriteBranch(instr, ConditionCode.UGE, C); break;
                case Mnemonic.bcs: RewriteBranch(instr, ConditionCode.ULT, C); break;
                case Mnemonic.bne: RewriteBranch(instr, ConditionCode.NE, Z); break;
                case Mnemonic.beq: RewriteBranch(instr, ConditionCode.EQ, Z); break;
                case Mnemonic.bvc: RewriteBranch(instr, ConditionCode.NO, V); break;
                case Mnemonic.bvs: RewriteBranch(instr, ConditionCode.OV, V); break;
                case Mnemonic.bpl: RewriteBranch(instr, ConditionCode.GE, N); break;
                case Mnemonic.bmi: RewriteBranch(instr, ConditionCode.LT, N); break;
                case Mnemonic.bge: RewriteBranch(instr, ConditionCode.GE, NV); break;
                case Mnemonic.blt: RewriteBranch(instr, ConditionCode.LT, NV); break;
                case Mnemonic.bgt: RewriteBranch(instr, ConditionCode.GT, NZV); break;
                case Mnemonic.ble: RewriteBranch(instr, ConditionCode.LE, NZV); break;
                case Mnemonic.cmp: RewriteCmp(instr); break;
                case Mnemonic.extu: RewriteExt(instr, Domain.UnsignedInt); break;
                case Mnemonic.jmp: RewriteJmp(instr); break;
                case Mnemonic.jsr: RewriteJsr(instr); break;
                case Mnemonic.ldc: RewriteLdc(instr); break;
                case Mnemonic.mov: RewriteMov(instr); break;
                case Mnemonic.mulxu: RewriteMulxu(instr); break;
                case Mnemonic.nop: RewriteNop(); break;
                case Mnemonic.not: RewriteUnaryLogical(instr, m.Comp); break;
                case Mnemonic.or: RewriteLogical(instr, m.Or); break;
                case Mnemonic.rotxl: RewriteRotationX(instr, PseudoProcedure.RolC); break;
                case Mnemonic.rotxr: RewriteRotationX(instr, PseudoProcedure.RorC); break;
                case Mnemonic.rts: RewriteRts(); break;
                case Mnemonic.shal: RewriteShift(instr, m.Shl); break;
                case Mnemonic.shar: RewriteShift(instr, m.Sar); break;
                case Mnemonic.shll: RewriteShift(instr, m.Shl); break;
                case Mnemonic.shlr: RewriteShift(instr, m.Shr); break;
                case Mnemonic.sub: RewriteSub(instr); break;
                case Mnemonic.subs: RewriteSubs(instr); break;
                case Mnemonic.subx: RewriteAddxSubx(instr, m.ISub); break;
                case Mnemonic.xor: RewriteLogical(instr, m.Xor); break;
                }
                yield return m.MakeCluster(instr.Address, instr.Length, iclass);
                this.m = new RtlEmitter(new List<RtlInstruction>());
            }
        }



        IEnumerator IEnumerable.GetEnumerator()
        {
            return GetEnumerator();
        }

        private Expression OpSrc(MachineOperand op)
        {
            switch (op)
            {
            case RegisterOperand reg:
                return binder.EnsureRegister(reg.Register);
            case ImmediateOperand imm:
                return imm.Value;
            case MemoryOperand mem:
                Expression ea;
                if (mem.Base != null)
                {
                    var regBase = binder.EnsureRegister(mem.Base);
                    if (mem.PostIncrement)
                    {
                        ea = binder.CreateTemporary(regBase.DataType);
                        m.Assign(ea, regBase);
                    }
                    else if (mem.PreDecrement)
                    {
                        m.Assign(regBase, m.ISubS(regBase, mem.Width.Size));
                        ea = regBase;
                    }
                    else
                    {
                        ea = m.AddSubSignedInt(regBase, mem.Offset);
                    }
                }
                else
                {
                    ea = Address.Ptr16((ushort) mem.Offset);
                }
                return m.Mem(mem.Width ?? (DataType) VoidType.Instance, ea);
            }
            throw new NotImplementedException();
        }

        private Expression OpDst(MachineOperand op, Expression src, Func<Expression,Expression,Expression> fn)
        {
            Expression dst;
            switch (op)
            {
            case RegisterOperand reg:
                dst = binder.EnsureRegister(reg.Register);
                m.Assign(dst, fn(dst, src));
                return dst;
            case MemoryOperand mem:
                Expression ea;
                if (mem.Base != null)
                {
                    var regBase = binder.EnsureRegister(mem.Base);
                    if (mem.PreDecrement)
                    {
                        ea = binder.EnsureRegister(mem.Base!);
                        m.Assign(ea, m.ISubS(ea, mem.Width.Size));
                    }
                    else if (mem.PostIncrement)
                    {
                        throw new NotImplementedException();
                    }
                    else
                    {
                        ea = m.AddSubSignedInt(regBase, mem.Offset);
                    }
                }
                else
                {
                    ea = Address.Ptr16((ushort) mem.Offset);
                }
                dst = fn(m.Mem(mem.Width, ea), src);
                if (dst is Identifier || dst is Constant)
                {
                    m.Assign(m.Mem(mem.Width, ea), dst);
                }
                else
                {
                    var tmp = binder.CreateTemporary(mem.Width);
                    m.Assign(tmp, dst);
                    dst = tmp;
                }
                if (mem.PostIncrement)
                {
                    m.Assign(ea, m.IAddS(ea, mem.Width.Size));
                }
                return dst;
            }
            throw new NotImplementedException();
        }

        private void EmitCond(FlagGroupStorage grf, Expression e)
        {
            m.Assign(binder.EnsureFlagGroup(grf), m.Cond(e));
        }

        private void EmitUnitTest(MachineInstruction instr, string message = "")
        {
            var testgenSvc = arch.Services.GetService<ITestGenerationService>();
            testgenSvc?.ReportMissingRewriter("H8Rw", instr, rdr, message);
        }


        private void RewriteAdd(H8Instruction instr)
        {
            var src = OpSrc(instr.Operands[0]);
            var dst = OpDst(instr.Operands[1], src, m.IAdd);
            EmitCond(NZVC, dst);
        }

        private void RewriteAdds(H8Instruction instr)
        {
            var src = OpSrc(instr.Operands[0]);
            var dst = OpDst(instr.Operands[1], src, m.IAdd);
        }

        private void RewriteAddxSubx(H8Instruction instr, Func<Expression, Expression, Expression> fn)
        {
            var src = OpSrc(instr.Operands[0]);
            var dst = OpDst(instr.Operands[1], src, (d, s) => fn(fn(d, s), binder.EnsureFlagGroup(C)));
            EmitCond(NZVC, dst);
        }

        private void RewriteBranch(H8Instruction instr)
        {
            m.Goto(((AddressOperand) instr.Operands[0]).Address);
        }

        private void RewriteBranch(H8Instruction instr, ConditionCode cc, FlagGroupStorage grf)
        {
            var test = m.Test(cc, binder.EnsureFlagGroup(grf));
            m.Branch(test, ((AddressOperand) instr.Operands[0]).Address);
        }

        private void RewriteCmp(H8Instruction instr)
        {
            var right = OpSrc(instr.Operands[0]);
            var left = OpSrc(instr.Operands[1]);
            EmitCond(NZVC, m.ISub(left, right));
        }

        private void RewriteExt(H8Instruction instr, Domain domain)
        {
            var dstRange = new BitRange(0, instr.Size!.BitSize);
            var srcRange = new BitRange(0, instr.Size!.BitSize / 2);
            var dt = PrimitiveType.Create(domain, dstRange.Extent);
            var dst = (Identifier) OpSrc(instr.Operands[0]);
            var src = binder.EnsureRegister(arch.GetRegister(
                dst.Storage.Domain, 
                srcRange)!);
            m.Assign(dst, m.Convert(src, src.DataType, dt));
            EmitCond(Z, dst);
            m.Assign(binder.EnsureFlagGroup(N), Constant.False());
            m.Assign(binder.EnsureFlagGroup(V), Constant.False());
        }

        private void RewriteJmp(H8Instruction instr)
        {
            var target = ((MemoryAccess) OpSrc(instr.Operands[0])).EffectiveAddress;
            m.Goto(target);
        }

        private void RewriteJsr(H8Instruction instr)
        {
            var target = ((MemoryAccess) OpSrc(instr.Operands[0])).EffectiveAddress;
            m.Call(target, 2);      //$REVIEW: what about 'advanced mode'?
        }

        private void RewriteLdc(H8Instruction instr)
        {
            m.Assign(binder.EnsureFlagGroup(NZVC), OpSrc(instr.Operands[0]));
        }

        private void RewriteBset(H8Instruction instr, Expression value)
        {
            var pos = OpSrc(instr.Operands[0]);
            var dst = OpSrc(instr.Operands[1]);
            m.Assign(dst, host.PseudoProcedure("__bst", dst.DataType, dst, value, pos));
        }

        private void RewriteBtst(H8Instruction instr, FlagGroupStorage flag)
        {
            var right = OpSrc(instr.Operands[0]);
            var left = OpSrc(instr.Operands[1]);
            var dst = binder.EnsureFlagGroup(flag);
            m.Assign(dst, host.PseudoProcedure("__btst", dst.DataType, left, right));
        }

        private void RewriteLogical(H8Instruction instr, Func<Expression,Expression, Expression> fn)
        {
            var src = OpSrc(instr.Operands[0]);
            var dst = OpDst(instr.Operands[1], src, fn);
            EmitCond(NZ, dst);
            m.Assign(binder.EnsureFlagGroup(V), Constant.False());
        }

        private void RewriteMov(H8Instruction instr)
        {
            var src = OpSrc(instr.Operands[0]);
            var dst = OpDst(instr.Operands[1], src, (d, s) => s);
            EmitCond(NZ, dst);
            m.Assign(binder.EnsureFlagGroup(V), Constant.False());
        }

        private void RewriteMulxu(H8Instruction instr)
        {
            var right = OpSrc(instr.Operands[0]);
            var left = (Identifier) OpSrc(instr.Operands[1]);
            var dst = binder.EnsureRegister(arch.GetRegister(
                left.Storage.Domain,
                new BitRange(0, left.DataType.BitSize * 2))!);
            var umul = m.UMul(left, right);
            umul.DataType = dst.DataType;
            m.Assign(dst, umul);
        }

        private void RewriteNop()
        {
            m.Nop();
        }

        private void RewriteRotationX(H8Instruction instr, string intrinsicName)
        {
            var src = OpSrc(instr.Operands[0]);
            var c = binder.EnsureFlagGroup(C);
            m.Assign(src, host.PseudoProcedure(intrinsicName, src.DataType,
                src, Constant.Int32(1), c));
            EmitCond(NZC, src);
            m.Assign(binder.EnsureFlagGroup(V), Constant.False());
        }

        private void RewriteRts()
        {
            m.Return(2, 0);
        }

        private void RewriteShift(H8Instruction instr, Func<Expression, Expression, Expression> fn)
        {
            var src = OpSrc(instr.Operands[0]);
            m.Assign(src, fn(src, Constant.Int32(1)));
            EmitCond(NZVC, src);
        }

        private void RewriteSub(H8Instruction instr)
        {
            var src = OpSrc(instr.Operands[0]);
            var dst = OpDst(instr.Operands[1], src, m.ISub);
            EmitCond(NZVC, dst);
        }

        private void RewriteSubs(H8Instruction instr)
        {
            var src = OpSrc(instr.Operands[0]);
            var dst = OpDst(instr.Operands[1], src, m.ISub);
        }

        private void RewriteUnaryLogical(H8Instruction instr, Func<Expression, Expression> fn)
        {
            var src = OpSrc(instr.Operands[0]);
            m.Assign(src, fn(src));
            EmitCond(NZ, src);
            m.Assign(binder.EnsureFlagGroup(V), Constant.False());
        }
    }
}