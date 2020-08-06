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
using Reko.Core.Services;
using Reko.Core.Types;
using System;
using System.Collections;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Reko.Arch.M6800.M6809
{
    public class M6809Rewriter : IEnumerable<RtlInstructionCluster>
    {
        private readonly M6809Architecture arch;
        private readonly EndianImageReader rdr;
        private readonly ProcessorState state;
        private readonly IStorageBinder binder;
        private readonly IRewriterHost host;
        private readonly IEnumerator<M6809Instruction> dasm;
        private M6809Instruction instr;
        private InstrClass iclass;
        private RtlEmitter m;

        public M6809Rewriter(M6809Architecture arch, EndianImageReader rdr, ProcessorState state, IStorageBinder binder, IRewriterHost host)
        {
            this.arch = arch;
            this.rdr = rdr;
            this.state = state;
            this.binder = binder;
            this.host = host;
            this.dasm = new M6809Disassembler(arch, rdr).GetEnumerator();
        }

        public IEnumerator<RtlInstructionCluster> GetEnumerator()
        {
            var instrs = new List<RtlInstruction>();
            while (dasm.MoveNext())
            {
                this.instr = dasm.Current;
                this.iclass = instr.InstructionClass;
                instrs.Clear();
                this.m = new RtlEmitter(instrs);
                switch (instr.Mnemonic)
                {
                default:
                    EmitUnitTest();
                    goto case Mnemonic.invalid;
                case Mnemonic.invalid:
                    iclass = InstrClass.Invalid;
                    m.Invalid();
                    break;
                case Mnemonic.abx: RewriteAbx(); break;
                case Mnemonic.adca: RewriteBinary(Registers.A, Adc, NZVC); break;
                case Mnemonic.adcb: RewriteBinary(Registers.B, Adc, NZVC); break;
                case Mnemonic.adda: RewriteBinary(Registers.A, m.IAdd, NZVC); break;
                case Mnemonic.addb: RewriteBinary(Registers.B, m.IAdd, NZVC); break;
                case Mnemonic.addd: RewriteBinary(Registers.D, m.IAdd, NZVC); break;
                case Mnemonic.anda: RewriteBinary(Registers.A, m.And, NZ0_); break;
                case Mnemonic.andb: RewriteBinary(Registers.B, m.And, NZ0_); break;
                case Mnemonic.andcc: RewriteModifyCc(m.And); break;
                case Mnemonic.asr: RewriteUnary(Shl1, NZ_C); break;
                case Mnemonic.beq: RewriteBranch(ConditionCode.EQ, FlagM.Z); break;
                case Mnemonic.bge: RewriteBranch(ConditionCode.GE, FlagM.N | FlagM.V); break;
                case Mnemonic.bgt: RewriteBranch(ConditionCode.GT, FlagM.N | FlagM.Z |FlagM.V); break;
                case Mnemonic.bhi: RewriteBranch(ConditionCode.UGT, FlagM.Z | FlagM.C); break;
                case Mnemonic.bhs: RewriteBranch(ConditionCode.UGE, FlagM.C); break;
                case Mnemonic.bita: RewriteBinaryTest(Registers.A, m.And, NZ0_); break;
                case Mnemonic.bitb: RewriteBinaryTest(Registers.A, m.And, NZ0_); break;
                case Mnemonic.ble: RewriteBranch(ConditionCode.LE, FlagM.N | FlagM.Z |FlagM.V); break;
                case Mnemonic.blo: RewriteBranch(ConditionCode.ULT, FlagM.C); break;
                case Mnemonic.bls: RewriteBranch(ConditionCode.ULE, FlagM.Z | FlagM.C); break;
                case Mnemonic.blt: RewriteBranch(ConditionCode.LT, FlagM.N | FlagM.V); break;
                case Mnemonic.bmi: RewriteBranch(ConditionCode.LT, FlagM.N); break;
                case Mnemonic.bne: RewriteBranch(ConditionCode.NE, FlagM.Z); break;
                case Mnemonic.bpl: RewriteBranch(ConditionCode.GE, FlagM.N); break;
                case Mnemonic.bra: RewriteBra(); break;
                case Mnemonic.brn: m.Nop(); break;
                case Mnemonic.bsr: RewriteBsr(); break;
                case Mnemonic.bvc: RewriteBranch(ConditionCode.NO, FlagM.V); break;
                case Mnemonic.bvs: RewriteBranch(ConditionCode.OV, FlagM.V); break;
                case Mnemonic.clr: RewriteUnary(Clr, ClrCc); break;
                case Mnemonic.cmpa: RewriteBinaryTest(Registers.A, m.ISub, NZVC); break;
                case Mnemonic.cmpb: RewriteBinaryTest(Registers.B, m.ISub, NZVC); break;
                case Mnemonic.cmpd: RewriteBinaryTest(Registers.D, m.ISub, NZVC); break;
                case Mnemonic.cmps: RewriteBinaryTest(Registers.S, m.ISub, NZVC); break;
                case Mnemonic.cmpu: RewriteBinaryTest(Registers.U, m.ISub, NZVC); break;
                case Mnemonic.cmpx: RewriteBinaryTest(Registers.X, m.ISub, NZVC); break;
                case Mnemonic.cmpy: RewriteBinaryTest(Registers.Y, m.ISub, NZVC); break;
                case Mnemonic.com: RewriteUnary(m.Comp, NZ01); break;
                case Mnemonic.cwai: RewriteCwai(); break;
                case Mnemonic.daa: RewriteDaa(); break;
                case Mnemonic.dec: RewriteUnary(Dec, NZV); break;
                case Mnemonic.eora: RewriteBinaryTest(Registers.A, m.Xor, NZ0_); break;
                case Mnemonic.eorb: RewriteBinaryTest(Registers.B, m.Xor, NZ0_); break;
                case Mnemonic.exg: RewriteExg(); break;
                case Mnemonic.inc: RewriteUnary(Inc, NZV); break;
                case Mnemonic.jmp: RewriteJmp(); break;
                case Mnemonic.jsr: RewriteJsr(); break;
                case Mnemonic.lbeq: RewriteBranch(ConditionCode.EQ, FlagM.Z); break;
                case Mnemonic.lbge: RewriteBranch(ConditionCode.GE, FlagM.N | FlagM.V); break;
                case Mnemonic.lbgt: RewriteBranch(ConditionCode.GT, FlagM.N | FlagM.Z | FlagM.V); break;
                case Mnemonic.lbhi: RewriteBranch(ConditionCode.UGT, FlagM.Z | FlagM.C); break;
                case Mnemonic.lbhs: RewriteBranch(ConditionCode.UGE, FlagM.C); break;
                case Mnemonic.lble: RewriteBranch(ConditionCode.LE, FlagM.N | FlagM.Z | FlagM.V); break;
                case Mnemonic.lblo: RewriteBranch(ConditionCode.ULT, FlagM.C); break;
                case Mnemonic.lbls: RewriteBranch(ConditionCode.ULE, FlagM.Z | FlagM.C); break;
                case Mnemonic.lblt: RewriteBranch(ConditionCode.LT, FlagM.N | FlagM.V); break;
                case Mnemonic.lbmi: RewriteBranch(ConditionCode.LT, FlagM.N); break;
                case Mnemonic.lbne: RewriteBranch(ConditionCode.NE, FlagM.Z); break;
                case Mnemonic.lbpl: RewriteBranch(ConditionCode.GE, FlagM.N); break;
                case Mnemonic.lbra: RewriteBra(); break;
                case Mnemonic.lbrn: m.Nop(); break;
                case Mnemonic.lbsr: RewriteBsr(); break;
                case Mnemonic.lbvc: RewriteBranch(ConditionCode.NO, FlagM.V); break;
                case Mnemonic.lbvs: RewriteBranch(ConditionCode.OV, FlagM.V); break;
                case Mnemonic.lda: RewriteBinary(Registers.A, Load, NZ0_); break;
                case Mnemonic.ldb: RewriteBinary(Registers.B, Load, NZ0_); break;
                case Mnemonic.ldd: RewriteBinary(Registers.D, Load, NZ0_); break;
                case Mnemonic.lds: RewriteBinary(Registers.S, Load, NZ0_); break;
                case Mnemonic.ldu: RewriteBinary(Registers.U, Load, NZ0_); break;
                case Mnemonic.ldx: RewriteBinary(Registers.X, Load, NZ0_); break;
                case Mnemonic.ldy: RewriteBinary(Registers.Y, Load, NZ0_); break;
                case Mnemonic.leas: RewriteLea(Registers.S, NoCc); break;
                case Mnemonic.leau: RewriteLea(Registers.U, NoCc); break;
                case Mnemonic.leax: RewriteLea(Registers.X, _Z__); break;
                case Mnemonic.leay: RewriteLea(Registers.Y, _Z__); break;
                case Mnemonic.lsl: RewriteUnary(Shl1, NZVC); break;
                case Mnemonic.lsr: RewriteUnary(Shr1, NZ_C); break;
                case Mnemonic.mul: RewriteMul(); break;
                case Mnemonic.neg: RewriteUnary(m.Neg, NZVC); break;
                case Mnemonic.nop: m.Nop(); break;
                case Mnemonic.ora: RewriteBinary(Registers.A, m.Or, NZ0_); break;
                case Mnemonic.orb: RewriteBinary(Registers.B, m.Or, NZ0_); break;
                case Mnemonic.orcc: RewriteModifyCc(m.Or); break;
                case Mnemonic.pshs: RewritePsh(Registers.S); break;
                case Mnemonic.pshu: RewritePsh(Registers.U); break;
                case Mnemonic.puls: RewritePul(Registers.S); break;
                case Mnemonic.pulu: RewritePul(Registers.U); break;
                case Mnemonic.rol: RewriteUnary(Rol1, NZVC); break;
                case Mnemonic.ror: RewriteUnary(Ror1, NZ_C); break;
                case Mnemonic.rti: RewriteRti(); break;
                case Mnemonic.rts: RewriteRts(); break;
                case Mnemonic.sbca: RewriteBinary(Registers.A, Sbc, NZVC); break;
                case Mnemonic.sbcb: RewriteBinary(Registers.B, Sbc, NZVC); break;
                case Mnemonic.sex: RewriteSex(); break;
                case Mnemonic.sta: RewriteUnary(Store(Registers.A), NZ0_); break;
                case Mnemonic.stb: RewriteUnary(Store(Registers.B), NZ0_); break;
                case Mnemonic.std: RewriteUnary(Store(Registers.D), NZ0_); break;
                case Mnemonic.sts: RewriteUnary(Store(Registers.S), NZ0_); break;
                case Mnemonic.stu: RewriteUnary(Store(Registers.U), NZ0_); break;
                case Mnemonic.stx: RewriteUnary(Store(Registers.X), NZ0_); break;
                case Mnemonic.sty: RewriteUnary(Store(Registers.Y), NZ0_); break;
                case Mnemonic.suba: RewriteBinary(Registers.A, m.ISub, NZVC); break;
                case Mnemonic.subb: RewriteBinary(Registers.B, m.ISub, NZVC); break;
                case Mnemonic.subd: RewriteBinary(Registers.D, m.ISub, NZVC); break;
                case Mnemonic.swi: RewriteSwi(0xFFFA); break;
                case Mnemonic.swi2: RewriteSwi(0xFFF4); break;
                case Mnemonic.swi3: RewriteSwi(0xFFF2); break;
                case Mnemonic.sync: RewriteSync(); break;
                case Mnemonic.tfr: RewriteTfr(); break;
                case Mnemonic.tst: RewriteTst(); break;
                }
                yield return new RtlInstructionCluster(instr.Address, instr.Length, instrs.ToArray())
                {
                    Class = iclass,
                };
            }
        }

        IEnumerator IEnumerable.GetEnumerator()
        {
            return GetEnumerator();
        }

        private void EmitUnitTest()
        {
            var testGenSvc = arch.Services.GetService<ITestGenerationService>();
            testGenSvc?.ReportMissingRewriter("M6809Rw", this.instr, rdr, "");
        }

        private Expression Clr(Expression e)
        {
            return Constant.Zero(e.DataType);
        }

        private void ClrCc(Expression e)
        {
            m.Assign(binder.EnsureFlagGroup(arch.GetFlagGroup(Registers.CC, (uint) FlagM.N)), Constant.False());
            m.Assign(binder.EnsureFlagGroup(arch.GetFlagGroup(Registers.CC, (uint) FlagM.Z)), Constant.True());
            m.Assign(binder.EnsureFlagGroup(arch.GetFlagGroup(Registers.CC, (uint) FlagM.V)), Constant.False());
            m.Assign(binder.EnsureFlagGroup(arch.GetFlagGroup(Registers.CC, (uint) FlagM.C)), Constant.False());
        }

        private void NoCc(Expression e)
        {

        }

        private Expression Adc(Expression a, Expression b)
        {
            var C = binder.EnsureFlagGroup(arch.GetFlagGroup(Registers.CC, (uint) FlagM.C));
            return m.IAdd(m.IAdd(a, b), C);
        }

        private Expression Dec(Expression e)
        {
            return m.ISub(e, 1);
        }

        private Expression Inc(Expression e)
        {
            return m.IAdd(e, 1);
        }

        private Expression Load(Expression d, Expression t)
        {
            return t;
        }

        private void Pull(RegisterStorage stackptr, RegisterStorage reg)
        {
            var sp = binder.EnsureRegister(stackptr);
            var r = binder.EnsureRegister(reg);
            if (reg == Registers.PCR)
            {
                m.Return(2, 0);
            }
            else
            {
                m.Assign(r, m.Mem(r.DataType, sp));
                m.Assign(sp, m.IAddS(sp, r.DataType.Size));
            }
        }

        private void Push(RegisterStorage stackptr, RegisterStorage reg)
        {
            var sp = binder.EnsureRegister(stackptr);
            var r = binder.EnsureRegister(reg);
            m.Assign(sp, m.ISubS(sp, r.DataType.Size));
            m.Assign(m.Mem(r.DataType, sp), r);
        }

        private Expression Rol1(Expression e)
        {
            return host.PseudoProcedure(PseudoProcedure.Rol, e.DataType, e, Constant.Byte(1));
        }

        private Expression Ror1(Expression e)
        {
            return host.PseudoProcedure(PseudoProcedure.Ror, e.DataType, e, Constant.Byte(1));
        }

        private Expression Sbc(Expression a, Expression b)
        {
            var C = binder.EnsureFlagGroup(arch.GetFlagGroup(Registers.CC, (uint) FlagM.C));
            return m.ISub(m.ISub(a, b), C);
        }

        private Expression Shl1(Expression e)
        {
            return m.Shl(e, 1);
        }

        private Expression Shr1(Expression e)
        {
            return m.Shr(e, 1);
        }

        private Func<Expression, Expression> Store(RegisterStorage reg)
        {
            var r = binder.EnsureRegister(reg);
            return t => r;
        }

        private Expression Tst(Expression dummy, Expression e)
        {
            return m.ISub(e, 0);
        }

        private void NZV(Expression e)
        {
            var nzvc = arch.GetFlagGroup(Registers.CC, (uint) (FlagM.N | FlagM.Z | FlagM.V));
            m.Assign(binder.EnsureFlagGroup(nzvc), m.Cond(e));
        }

        private void NZVC(Expression e)
        {
            var nzvc = arch.GetFlagGroup(Registers.CC, (uint) (FlagM.N | FlagM.Z | FlagM.V | FlagM.C));
            m.Assign(binder.EnsureFlagGroup(nzvc), m.Cond(e));
        }
        
        private void NZ_C(Expression e)
        {
            var nz_c = arch.GetFlagGroup(Registers.CC, (uint) (FlagM.N | FlagM.Z |  FlagM.C));
            m.Assign(binder.EnsureFlagGroup(nz_c), m.Cond(e));
        }

        private void NZ0_(Expression e)
        {
            var nz = arch.GetFlagGroup(Registers.CC, (uint) (FlagM.N | FlagM.Z));
            var v = arch.GetFlagGroup(Registers.CC, (uint) FlagM.V);
            m.Assign(binder.EnsureFlagGroup(nz), m.Cond(e));
            m.Assign(binder.EnsureFlagGroup(v), Constant.False());
        }

        private void NZ01(Expression e)
        {
            var nz = arch.GetFlagGroup(Registers.CC, (uint) (FlagM.N | FlagM.Z));
            var v = arch.GetFlagGroup(Registers.CC, (uint) FlagM.V);
            var c = arch.GetFlagGroup(Registers.CC, (uint) FlagM.C);
            m.Assign(binder.EnsureFlagGroup(nz), m.Cond(e));
            m.Assign(binder.EnsureFlagGroup(v), Constant.False());
            m.Assign(binder.EnsureFlagGroup(c), Constant.True());
        }

        private void NZ__(Expression e)
        {
            var nz__ = arch.GetFlagGroup(Registers.CC, (uint) (FlagM.N | FlagM.Z));
            m.Assign(binder.EnsureFlagGroup(nz__), m.Cond(e));
        }

        private void _Z__(Expression e)
        {
            var z = arch.GetFlagGroup(Registers.CC, (uint) FlagM.Z);
            m.Assign(binder.EnsureFlagGroup(z), m.Cond(e));
        }

        private void _ZC_(Expression e)
        {
            var zc = arch.GetFlagGroup(Registers.CC, (uint) (FlagM.Z|FlagM.C));
            m.Assign(binder.EnsureFlagGroup(zc), m.Cond(e));
        }

        Expression EaKernel(Func<Expression, Expression, Expression> f, Expression d, Expression ea, MemoryOperand mem)
        {
            if (mem.Indirect)
            {
                ea = m.Mem(PrimitiveType.Ptr16, ea);
            }
            f(d, ea);
            return d;
        }

        Expression MemKernel(Func<Expression, Expression, Expression> f, Expression d, Expression ea, MemoryOperand mem)
        {
            if (mem.Indirect)
            {
                ea = m.Mem(PrimitiveType.Ptr16, ea);
            }
            m.Assign(d, f(d, m.Mem(mem.Width, ea)));
            return d;
        }

        Expression UnaryMemKernel(Func<Expression, Expression, Expression> f, Expression d, Expression ea, MemoryOperand mem)
        {
            var t = binder.CreateTemporary(mem.Width);
            if (mem.Indirect)
            {
                ea = m.Mem(PrimitiveType.Ptr16, ea);
            }
            m.Assign(t, f(d, m.Mem(t.DataType, ea)));
            m.Assign(m.Mem(t.DataType, ea), t);
            return t;
        }

        Expression TestMemKernel(Func<Expression, Expression, Expression> f, Expression d, Expression ea, MemoryOperand mem)
        {
            var t = binder.CreateTemporary(mem.Width);
            if (mem.Indirect)
            {
                ea = m.Mem(PrimitiveType.Ptr16, ea);
            }
            m.Assign(t, m.Mem(mem.Width, ea));
            m.Assign(t, f(d, t));
            return t;
        }

        private void RewriteBinaryTest(
            Storage reg,
            Func<Expression, Expression, Expression> fn,
            Action<Expression> genFlags)
        {
            RewriteOp(reg, TestMemKernel, fn, genFlags);
        }

        private void RewriteBinary(
            RegisterStorage reg,
            Func<Expression, Expression, Expression> fn,
            Action<Expression> genFlags)
        {
            RewriteOp(reg, MemKernel, fn, genFlags);
        }

        private void RewriteUnary(Func<Expression, Expression> fn, Action<Expression> genFlags)
        {
            RewriteOp(null, UnaryMemKernel, (d, t) => fn(t), genFlags);
        }

        private void RewriteOp(
            Storage rDst, 
            Func<Func<Expression,Expression,Expression>, Expression, Expression, MemoryOperand, Expression> memFn,
            Func<Expression, Expression, Expression> bin, 
            Action<Expression> genFlags)
        {
            Expression dst = rDst != null ? binder.EnsureIdentifier(rDst) : null;
            Expression tmp;
            switch (instr.Operands[0])
            {
            case RegisterOperand reg:
                tmp = binder.EnsureRegister(reg.Register);
                m.Assign(tmp, bin(dst, tmp));
                break;

            case ImmediateOperand imm:
                m.Assign(dst, bin(dst, imm.Value));
                tmp = dst;
                break;
            case MemoryOperand mem:
                Expression ea;
                Expression idx;
                switch (mem.AccessMode)
                {
                case MemoryOperand.Mode.AccumulatorOffset:
                    ea = binder.EnsureRegister(mem.Base);
                    idx = binder.EnsureRegister(mem.Index);
                    if (idx.DataType.BitSize < ea.DataType.BitSize)
                    {
                        idx = m.Convert(idx, idx.DataType, PrimitiveType.Int16);
                    }
                    ea = m.IAdd(ea, idx);
                    tmp = memFn(bin, dst, ea, mem);
                    break;
                case MemoryOperand.Mode.ConstantOffset:
                    if (mem.Base == null)
                    {
                        ea = Address.Ptr16((ushort) mem.Offset);
                    }
                    else if (mem.Base == Registers.PCR)
                    {
                        ea = instr.Address + (instr.Length + mem.Offset);
                    }
                    else
                    {
                        ea = binder.EnsureRegister(mem.Base);
                        ea = m.AddSubSignedInt(ea, mem.Offset);
                    }
                    tmp = memFn(bin, dst, ea, mem);
                    break;
                case MemoryOperand.Mode.Direct:
                    ea = m.IAdd(binder.EnsureRegister(Registers.DP), Constant.Word16((byte) mem.Offset));
                    tmp = memFn(bin, dst, ea, mem);
                    break;
                case MemoryOperand.Mode.PostInc1:
                    ea = binder.EnsureRegister(mem.Base);
                    tmp = memFn(bin, dst, ea, mem);
                    m.Assign(ea, m.IAddS(ea, 1));
                    break;
                case MemoryOperand.Mode.PostInc2:
                    ea = binder.EnsureRegister(mem.Base);
                    tmp = memFn(bin, dst, ea, mem);
                    m.Assign(ea, m.IAddS(ea, 2));
                    break;
                case MemoryOperand.Mode.PreDec1:
                    ea = binder.EnsureRegister(mem.Base);
                    m.Assign(ea, m.ISubS(ea, 1));
                    tmp = memFn(bin, dst, ea, mem);
                    break;
                case MemoryOperand.Mode.PreDec2:
                    ea = binder.EnsureRegister(mem.Base);
                    m.Assign(ea, m.ISubS(ea, 2));
                    tmp = memFn(bin, dst, ea, mem);
                    break;
                default:
                    throw new NotImplementedException($"Unimplemented access mode {mem.AccessMode.ToString()}");
                }
                break;
            default:
                throw new NotImplementedException($"Unimplemented operand type {instr.Operands[0].GetType().Name}");
            }
            genFlags(tmp);
        }

        private void RewriteAbx()
        {
            var b = binder.EnsureRegister(Registers.B);
            var x = binder.EnsureRegister(Registers.X);
            m.Assign(x, m.IAdd(x, m.Convert(b, b.DataType, PrimitiveType.UInt16)));
        }

        private void RewriteModifyCc(Func<Expression, Expression, Expression> fn)
        {
            var imm = ((ImmediateOperand) instr.Operands[0]).Value;
            var cc = binder.EnsureRegister(Registers.CC);
            m.Assign(cc, fn(cc, imm));
        }

        private void RewriteBranch(ConditionCode cc, FlagM flags)
        {
            var flagGrp = binder.EnsureFlagGroup(arch.GetFlagGroup(Registers.CC, (uint)flags));
            m.Branch(m.Test(cc, flagGrp), ((AddressOperand) instr.Operands[0]).Address, instr.InstructionClass); 
        }

        private void RewriteBra()
        {
            m.Goto(((AddressOperand) instr.Operands[0]).Address);
        }

        private void RewriteBsr()
        {
            m.Call(((AddressOperand) instr.Operands[0]).Address, 2);
        }

        private void RewriteCwai()
        {
            var cc = binder.EnsureRegister(Registers.CC);
            m.Assign(cc, m.And(cc, ((ImmediateOperand) instr.Operands[0]).Value));
            Push(Registers.S, Registers.PCR);
            Push(Registers.S, Registers.U);
            Push(Registers.S, Registers.Y);
            Push(Registers.S, Registers.X);
            Push(Registers.S, Registers.DP);
            Push(Registers.S, Registers.B);
            Push(Registers.S, Registers.A);
            Push(Registers.S, Registers.CC);
        }

        private void RewriteDaa()
        {
            var a = binder.EnsureRegister(Registers.A);
            m.Assign(a, host.PseudoProcedure("__daa", PrimitiveType.Byte, a));
            NZ_C(a);
        }

        private void RewriteExg()
        {
            EmitUnitTest();
            iclass = InstrClass.Invalid;
            m.Invalid();
        }

        private void RewriteJmp()
        {
            RewriteOp(null, EaKernel, (a, b) => { m.Goto(b); return null; }, NoCc);
        }

        private void RewriteJsr()
        {
            RewriteOp(null, EaKernel, (a, b) => { m.Call(b, 2); return null; }, NoCc);
        }

        private void RewriteLd(RegisterStorage reg)
        {
            EmitUnitTest();
            iclass = InstrClass.Invalid;
            m.Invalid();
        }

        private void RewriteLea(RegisterStorage reg, Action<Expression> genFlags)
        {
            RewriteOp(reg, EaKernel, (a, b) => { m.Assign(a, b); return null; }, genFlags);
        }

        private void RewriteLsr()
        {
            EmitUnitTest();
            iclass = InstrClass.Invalid;
            m.Invalid();
        }

        private void RewriteMul()
        {
            var a = binder.EnsureRegister(Registers.A);
            var b = binder.EnsureRegister(Registers.B);
            var d = binder.EnsureRegister(Registers.D);
            var product = m.UMul(a, b);
            product.DataType = PrimitiveType.Word16;
            m.Assign(d, product);
            _ZC_(d);
        }

        private void RewritePsh(RegisterStorage stackPtr)
        {
            var mregs = (MultipleRegisterOperand) instr.Operands[0];
            foreach (var reg in mregs.GetRegisters())
            {
                Push(stackPtr, reg);
            }
        }

        private void RewritePul(RegisterStorage stackPtr)
        {
            var mregs = (MultipleRegisterOperand) instr.Operands[0];
            foreach (var reg in mregs.GetRegisters().Reverse())
            {
                Pull(stackPtr, reg);
            }
        }

        private void RewriteRti()
        {
            var cc = binder.EnsureRegister(Registers.CC);
            Pull(Registers.S, Registers.CC);
            Pull(Registers.S, Registers.A);
            Pull(Registers.S, Registers.B);
            Pull(Registers.S, Registers.DP);
            Pull(Registers.S, Registers.X);
            Pull(Registers.S, Registers.Y);
            Pull(Registers.S, Registers.U);
            Pull(Registers.S, Registers.PCR);
        }

        private void RewriteRts()
        {
            m.Return(2, 0);
        }

        private void RewriteSex()
        {
            var b = binder.EnsureRegister(Registers.B);
            var d = binder.EnsureRegister(Registers.D);
            m.Assign(d, m.Convert(b, PrimitiveType.Byte, PrimitiveType.Int16));
            NZ__(d);
        }

        private void RewriteSt(RegisterStorage reg)
        {
            EmitUnitTest();
            iclass = InstrClass.Invalid;
            m.Invalid();
        }

        private void RewriteSub(RegisterStorage reg)
        {
            EmitUnitTest();
            iclass = InstrClass.Invalid;
            m.Invalid();
        }

        private void RewriteSwi(ushort uAddrVector)
        {
            Push(Registers.S, Registers.PCR);
            Push(Registers.S, Registers.U);
            Push(Registers.S, Registers.Y);
            Push(Registers.S, Registers.X);
            Push(Registers.S, Registers.DP);
            Push(Registers.S, Registers.B);
            Push(Registers.S, Registers.A);
            Push(Registers.S, Registers.CC);
            m.Goto(m.Mem16(Address.Ptr16(uAddrVector)));
        }

        private void RewriteSync()
        {
            m.SideEffect(host.PseudoProcedure("__sync", VoidType.Instance));
        }

        private void RewriteTfr()
        {
            var src = binder.EnsureRegister(((RegisterOperand) instr.Operands[0]).Register);
            var dst = binder.EnsureRegister(((RegisterOperand) instr.Operands[1]).Register);
            m.Assign(dst, src);
        }

        private void RewriteTst()
        {
            if (instr.Operands[0] is RegisterOperand reg)
            {
                RewriteBinaryTest(reg.Register, Tst, NZ0_);
            }
            else
            {
                RewriteBinaryTest(null, Tst, NZ0_);
            }
        }
    }
}
