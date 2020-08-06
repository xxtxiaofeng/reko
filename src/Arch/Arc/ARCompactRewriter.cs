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

using System;
using System.Collections;
using System.Collections.Generic;
using System.Diagnostics;
using System.Text;
using Reko.Core;
using Reko.Core.Expressions;
using Reko.Core.Machine;
using Reko.Core.Rtl;
using Reko.Core.Services;
using Reko.Core.Types;

namespace Reko.Arch.Arc
{
    public class ARCompactRewriter : IEnumerable<RtlInstructionCluster>
    {
        private const FlagM ZNCV = FlagM.ZF | FlagM.NF | FlagM.CF | FlagM.VF;
        private const FlagM ZNC = FlagM.ZF | FlagM.NF | FlagM.CF;
        private const FlagM ZNV = FlagM.ZF | FlagM.NF | FlagM.VF;
        private const FlagM ZN = FlagM.ZF | FlagM.NF;

        private const AuxFlagM S = AuxFlagM.Sat;

        private readonly ARCompactArchitecture arch;
        private readonly EndianImageReader rdr;
        private readonly ProcessorState state;
        private readonly IStorageBinder binder;
        private readonly IRewriterHost host;
        private readonly IEnumerator<ArcInstruction> dasm;
        private ArcInstruction instr;
        private RtlEmitter m;
        private InstrClass iclass;

        public ARCompactRewriter(ARCompactArchitecture arch, EndianImageReader rdr, ProcessorState state, IStorageBinder binder, IRewriterHost host)
        {
            this.arch = arch;
            this.rdr = rdr;
            this.state = state;
            this.binder = binder;
            this.host = host;
            this.dasm = new ArcDisassembler(arch, rdr).GetEnumerator();
        }

        public IEnumerator<RtlInstructionCluster> GetEnumerator()
        {
            while (dasm.MoveNext())
            {
                this.instr = dasm.Current;
                this.iclass = instr.InstructionClass;
                var instrs = new List<RtlInstruction>();
                m = new RtlEmitter(instrs);
                switch (instr.Mnemonic)
                {
                case Mnemonic.abs:
                case Mnemonic.abss:
                case Mnemonic.abssw:
                case Mnemonic.adds:
                case Mnemonic.asls:
                case Mnemonic.asrs:
                case Mnemonic.ex:
                case Mnemonic.jcc:
                case Mnemonic.jcs:
                case Mnemonic.jge:
                case Mnemonic.jgt:
                case Mnemonic.jhi:
                case Mnemonic.jle:
                case Mnemonic.jls:
                case Mnemonic.jlt:
                case Mnemonic.jmi:
                case Mnemonic.jne:
                case Mnemonic.jpl:
                case Mnemonic.jpnz:
                case Mnemonic.jvc:
                case Mnemonic.jvs:
                case Mnemonic.negs:
                case Mnemonic.negsw:
                case Mnemonic.norm:
                case Mnemonic.normw:
                case Mnemonic.rlc:
                case Mnemonic.rnd16:
                case Mnemonic.rrc:
                case Mnemonic.sat16:
                case Mnemonic.subs:
                case Mnemonic.swap:

                case Mnemonic.abs_s:
                case Mnemonic.not_s:
                case Mnemonic.unimp_s:
                default:
                    EmitUnitTest(this.instr);
                    goto case Mnemonic.Invalid;
                case Mnemonic.Invalid:
                    this.iclass = InstrClass.Invalid;
                    m.Invalid();
                    break;
                case Mnemonic.adc: RewriteAluOp(Adc, ZNCV); break;
                case Mnemonic.add:
                case Mnemonic.add_s:
                    RewriteAluOp(m.IAdd, ZNCV); break;
                case Mnemonic.add1:
                case Mnemonic.add1_s:
                    RewriteAluOp(Add1, ZNCV); break;
                case Mnemonic.add2:
                case Mnemonic.add2_s:
                    RewriteAluOp(Add2, ZNCV); break;
                case Mnemonic.add3:
                case Mnemonic.add3_s:
                    RewriteAluOp(Add3, ZNCV); break;
                case Mnemonic.addsdw: RewriteAddSubsdw("__addsdw"); break;
                case Mnemonic.and:
                case Mnemonic.and_s:
                    RewriteAluOp(m.And, ZN); break;
                case Mnemonic.asl:
                case Mnemonic.asl_s:
                    RewriteShift(m.Shl, ZNCV); break;
                case Mnemonic.asr:
                case Mnemonic.asr_s:
                    RewriteShift(m.Sar, ZNCV); break;
                case Mnemonic.b: case Mnemonic.b_s: RewriteB(ArcCondition.AL); break;
                case Mnemonic.bcc: case Mnemonic.bhs_s: RewriteB(ArcCondition.CC); break;
                case Mnemonic.bcs: case Mnemonic.blo_s: RewriteB(ArcCondition.CS); break;
                case Mnemonic.beq: case Mnemonic.beq_s: RewriteB(ArcCondition.EQ); break;
                case Mnemonic.bge: case Mnemonic.bge_s: RewriteB(ArcCondition.GE); break;
                case Mnemonic.bgt: case Mnemonic.bgt_s: RewriteB(ArcCondition.GT); break;
                case Mnemonic.bhi: case Mnemonic.bhi_s: RewriteB(ArcCondition.HI); break;
                case Mnemonic.ble: case Mnemonic.ble_s: RewriteB(ArcCondition.LE); break;
                case Mnemonic.bls: case Mnemonic.bls_s: RewriteB(ArcCondition.LS); break;
                case Mnemonic.blt: case Mnemonic.blt_s: RewriteB(ArcCondition.LT); break;
                case Mnemonic.bmi: RewriteB(ArcCondition.MI); break;
                case Mnemonic.bne: case Mnemonic.bne_s: RewriteB(ArcCondition.NE); break;
                case Mnemonic.bpl: RewriteB(ArcCondition.PL); break;
                case Mnemonic.bpnz: RewriteB(ArcCondition.PNZ); break;
                case Mnemonic.bvc: RewriteB(ArcCondition.VC); break;
                case Mnemonic.bvs: RewriteB(ArcCondition.VS); break;
                case Mnemonic.bsc: RewriteB(ArcCondition.SC); break;
                case Mnemonic.bss: RewriteB(ArcCondition.SS); break;

                case Mnemonic.bbit0: RewriteBbit(false); break;
                case Mnemonic.bbit1: RewriteBbit(true); break;
                case Mnemonic.bclr:
                case Mnemonic.bclr_s:
                    RewriteAluOp(Bclr, ZN); break;

                case Mnemonic.bl:
                case Mnemonic.bl_s:
                    RewriteBl(ArcCondition.AL); break;
                case Mnemonic.blal: RewriteBl(ArcCondition.AL); break;
                case Mnemonic.blcc: RewriteBl(ArcCondition.CC); break;
                case Mnemonic.blcs: RewriteBl(ArcCondition.CS); break;
                case Mnemonic.bleq: RewriteBl(ArcCondition.EQ); break;
                case Mnemonic.blge: RewriteBl(ArcCondition.GE); break;
                case Mnemonic.blgt: RewriteBl(ArcCondition.GT); break;
                case Mnemonic.blhi: RewriteBl(ArcCondition.HI); break;
                case Mnemonic.blle: RewriteBl(ArcCondition.LE); break;
                case Mnemonic.blls: RewriteBl(ArcCondition.LS); break;
                case Mnemonic.bllt: RewriteBl(ArcCondition.LT); break;
                case Mnemonic.blmi: RewriteBl(ArcCondition.MI); break;
                case Mnemonic.blne: RewriteBl(ArcCondition.NE); break;
                case Mnemonic.blpl: RewriteBl(ArcCondition.PL); break;
                case Mnemonic.blpnz: RewriteBl(ArcCondition.PNZ); break;
                case Mnemonic.blvc: RewriteBl(ArcCondition.VC); break;
                case Mnemonic.blvs: RewriteBl(ArcCondition.VS); break;

                case Mnemonic.breq: case Mnemonic.breq_s: RewriteBr(m.Eq); break;
                case Mnemonic.brge: RewriteBr(m.Ge); break;
                case Mnemonic.brhs: RewriteBr(m.Uge); break;
                case Mnemonic.brlo: RewriteBr(m.Ult); break;
                case Mnemonic.brlt: RewriteBr(m.Lt); break;
                case Mnemonic.brne: case Mnemonic.brne_s: RewriteBr(m.Ne); break;

                case Mnemonic.brk:
                case Mnemonic.brk_s:
                    RewriteBrk(); break;

                case Mnemonic.bic:
                case Mnemonic.bic_s:
                    RewriteAluOp(AndNot, ZN); break;
                case Mnemonic.bmsk:
                case Mnemonic.bmsk_s:
                    RewriteAluOp(Bmsk, ZN); break;
                case Mnemonic.bset:
                case Mnemonic.bset_s:
                    RewriteAluOp(Bset, ZN); break;
                case Mnemonic.btst:
                case Mnemonic.btst_s:
                    RewriteCondInstr(Btst, ZN); break;
                case Mnemonic.bxor:
                    RewriteAluOp(Bxor, ZN); break;


                case Mnemonic.cmp:
                case Mnemonic.cmp_s:
                    RewriteCondInstr(m.ISub, ZNCV); break;
                case Mnemonic.divaw: RewriteDivaw(); break;
                case Mnemonic.extb:
                case Mnemonic.extb_s:
                    RewriteExt(PrimitiveType.Byte, PrimitiveType.Word32); break;
                case Mnemonic.extw:
                case Mnemonic.extw_s:
                    RewriteExt(PrimitiveType.Word16, PrimitiveType.Word32); break;
                case Mnemonic.flag: RewriteFlag(); break;

                case Mnemonic.j: case Mnemonic.j_s: RewriteJ(ArcCondition.AL); break;
                case Mnemonic.jeq: RewriteJ(ArcCondition.EQ); break;

                case Mnemonic.jl: case Mnemonic.jl_s: RewriteJl(); break;

                case Mnemonic.ld:
                case Mnemonic.ld_s:
                    RewriteLoad(PrimitiveType.Word32); break;
                case Mnemonic.ldb:
                case Mnemonic.ldb_s:
                    RewriteLoad(PrimitiveType.Byte); break;
                case Mnemonic.ldw:
                case Mnemonic.ldw_s:
                    RewriteLoad(PrimitiveType.Word16); break;

                case Mnemonic.lp: RewriteLp(ArcCondition.AL); break;
                case Mnemonic.lpcc: RewriteLp(ArcCondition.CC); break;
                case Mnemonic.lpcs: RewriteLp(ArcCondition.CS); break;
                case Mnemonic.lpeq: RewriteLp(ArcCondition.EQ); break;
                case Mnemonic.lpge: RewriteLp(ArcCondition.GE); break;
                case Mnemonic.lpgt: RewriteLp(ArcCondition.GT); break;
                case Mnemonic.lphi: RewriteLp(ArcCondition.HI); break;
                case Mnemonic.lple: RewriteLp(ArcCondition.LE); break;
                case Mnemonic.lpls: RewriteLp(ArcCondition.LS); break;
                case Mnemonic.lplt: RewriteLp(ArcCondition.LT); break;
                case Mnemonic.lpmi: RewriteLp(ArcCondition.MI); break;
                case Mnemonic.lpne: RewriteLp(ArcCondition.NE); break;
                case Mnemonic.lppl: RewriteLp(ArcCondition.PL); break;
                case Mnemonic.lppnz: RewriteLp(ArcCondition.PNZ); break;
                case Mnemonic.lpvc: RewriteLp(ArcCondition.VC); break;
                case Mnemonic.lpvs: RewriteLp(ArcCondition.VS); break;

                case Mnemonic.lr: RewriteLr(); break;
                case Mnemonic.lsr:
                case Mnemonic.lsr_s:
                    RewriteShift(m.Shr, ZNC); break;
                case Mnemonic.max: RewriteAluOp(Max, ZNCV); break;
                case Mnemonic.min: RewriteAluOp(Min, ZNCV); break;
                case Mnemonic.mov:
                case Mnemonic.mov_s:
                    RewriteMov(); break;
                case Mnemonic.mul64:
                case Mnemonic.mul64_s:
                    RewriteMul(m.SMul, PrimitiveType.Int64); break;
                case Mnemonic.mulu64:
                    RewriteMul(m.UMul, PrimitiveType.UInt64); break;
                case Mnemonic.neg_s: RewriteAluOp(m.Neg, ZNCV); break;
                case Mnemonic.nop: m.Nop(); break;
                case Mnemonic.not: RewriteAluOp(m.Comp, ZN); break;
                case Mnemonic.or:
                case Mnemonic.or_s:
                    RewriteAluOp(m.Or, ZN); break;
                case Mnemonic.pop_s: RewritePop(); break;
                case Mnemonic.push_s: RewritePush(); break;
                case Mnemonic.rcmp: RewriteCondInstr(Rsub, ZNCV); break;
                case Mnemonic.ror: RewriteShift(Ror, ZNC); break;
                case Mnemonic.rsub: RewriteAluOp(Rsub, ZNCV); break;
                case Mnemonic.sbc: RewriteAluOp(Sbc, ZNCV); break;
                case Mnemonic.sexb:
                case Mnemonic.sexb_s:
                    RewriteExt(PrimitiveType.SByte, PrimitiveType.Int32); break;
                case Mnemonic.sexw:
                case Mnemonic.sexw_s:
                    RewriteExt(PrimitiveType.Int16, PrimitiveType.Int32); break;
                case Mnemonic.sr: RewriteSr(); break;
                case Mnemonic.st:
                case Mnemonic.st_s:
                    RewriteStore(PrimitiveType.Word32); break;
                case Mnemonic.stb:
                case Mnemonic.stb_s:
                    RewriteStore(PrimitiveType.Byte); break;
                case Mnemonic.stw:
                case Mnemonic.stw_s:
                    RewriteStore(PrimitiveType.Word16); break;
                case Mnemonic.sub:
                case Mnemonic.sub_s:
                    RewriteAluOp(m.ISub, ZNCV); break;
                case Mnemonic.sub1: RewriteAluOp(Sub1, ZNCV); break;
                case Mnemonic.sub2: RewriteAluOp(Sub2, ZNCV); break;
                case Mnemonic.sub3: RewriteAluOp(Sub3, ZNCV); break;
                case Mnemonic.subsdw: RewriteAddSubsdw("__subsdw"); break;
                case Mnemonic.trap_s:
                case Mnemonic.trap0:
                    RewriteTrap();
                    break;
                case Mnemonic.tst:
                case Mnemonic.tst_s:
                    RewriteCondInstr(m.And, ZN); break;
                case Mnemonic.xor:
                case Mnemonic.xor_s:
                    RewriteAluOp(m.Xor, ZN); break;
                }

                TryHandlingZeroOverheadLoop();
                yield return new RtlInstructionCluster(instr.Address, instr.Length, instrs.ToArray())
                {
                    Class = iclass
                };

            }
        }

        private void TryHandlingZeroOverheadLoop()
        {
            // Check if we would hit the LP_END instruction set up by a prior LP instruction.
            var uAddrNext = instr.Address.ToUInt32() + (uint) instr.Length;
            var end = state.GetValue(Registers.LpEnd);
            if (end is Constant cEnd && cEnd.IsValid && cEnd.ToUInt32() == uAddrNext)
            {
                var addrNext = Address.Ptr32(uAddrNext);

                var lpCount = binder.EnsureRegister(Registers.LP_count);
                var start = state.GetValue(Registers.LpStart);
                Expression eBackEdgeTarget;
                if (start is Constant cStart && cStart.IsValid)
                {
                    eBackEdgeTarget= Address.Ptr32(cStart.ToUInt32());
                }
                else
                {
                    eBackEdgeTarget = binder.EnsureRegister(Registers.LpStart);
                }
                m.BranchInMiddleOfInstruction(m.Eq(lpCount, 1), addrNext, InstrClass.ConditionalTransfer);

                m.Assign(lpCount, m.ISubS(lpCount, 1));
                m.Goto(eBackEdgeTarget);
                iclass = InstrClass.ConditionalTransfer;
            }
        }

        IEnumerator IEnumerable.GetEnumerator()
        {
            return GetEnumerator();
        }

        private void EmitUnitTest(MachineInstruction instr, string message = "")
        {
            var testgenSvc = arch.Services.GetService<ITestGenerationService>();
            testgenSvc?.ReportMissingRewriter("ARCompactRw", instr, rdr, message);
        }

        private Expression Adc(Expression a, Expression b)
        {
            var C = binder.EnsureFlagGroup(arch.GetFlagGroup(Registers.Status32, (uint) FlagM.CF));
            return m.IAdd(m.IAdd(a, b), C);
        }

        private Expression Add1(Expression a, Expression b)
        {
            return m.IAdd(a, m.Shl(b, 1));
        }

        private Expression Add2(Expression a, Expression b)
        {
            return m.IAdd(a, m.Shl(b, 2));
        }

        private Expression Add3(Expression a, Expression b)
        {
            return m.IAdd(a, m.Shl(b, 3));
        }

        private Expression Sbc(Expression a, Expression b)
        {
            var C = binder.EnsureFlagGroup(arch.GetFlagGroup(Registers.Status32, (uint) FlagM.CF));
            return m.ISub(m.ISub(a, b), C);
        }

        private Expression Sub1(Expression a, Expression b)
        {
            return m.ISub(a, m.Shl(b, 1));
        }

        private Expression Sub2(Expression a, Expression b)
        {
            return m.ISub(a, m.Shl(b, 2));
        }

        private Expression Sub3(Expression a, Expression b)
        {
            return m.ISub(a, m.Shl(b, 3));
        }

        private Expression Bclr(Expression a, Expression b)
        {
            return host.PseudoProcedure("__bclr", a.DataType, a, b);
        }

        private Expression AndNot(Expression a, Expression b)
        {
            return m.And(a, m.Comp(b));
        }

        private Expression Bset(Expression a, Expression b)
        {
            return host.PseudoProcedure("__bset", a.DataType, a, b);
        }

        private Expression Bmsk(Expression a, Expression b)
        {
            return host.PseudoProcedure("__bitmask", a.DataType, a, b);
        }

        private Expression Btst(Expression a, Expression b)
        {
            return host.PseudoProcedure("__btst", a.DataType, a, b);
        }

        private Expression Bxor(Expression a, Expression b)
        {
            return host.PseudoProcedure("__bxor", a.DataType, a, b);
        }

        private Expression Max(Expression a, Expression b)
        {
            return host.PseudoProcedure("max", PrimitiveType.Int32, a, b);
        }

        private Expression Min(Expression a, Expression b)
        {
            return host.PseudoProcedure("min", PrimitiveType.Int32, a, b);
        }

        private Expression Ror(Expression a, Expression b)
        {
            return host.PseudoProcedure(PseudoProcedure.Ror, a.DataType, a, b);
        }

        private Expression Rsub(Expression a, Expression b)
        {
            return m.ISub(b, a);
        }

        private Expression Operand(int iOp)
        {
            switch (instr.Operands[iOp])
            {
            case RegisterOperand rop:
                return binder.EnsureRegister(rop.Register);
            case ImmediateOperand iop:
                return iop.Value;
            case AddressOperand aop:
                return aop.Address;
            default:
                throw new NotImplementedException($"Unimplemented operand type {instr.Operands[iOp].GetType().Name}.");
            }
        }

        private void MaybeSkip(ArcCondition cond)
        {
            if (cond == ArcCondition.AL)
                return;
            var test = TestFlags(cond).Invert();
            m.BranchInMiddleOfInstruction(test, instr.Address + instr.Length, InstrClass.ConditionalTransfer);
        }


        private Expression TestFlags(ArcCondition cond)
        {
            FlagM grf = 0;
            ConditionCode cc = ConditionCode.None;
            var flagreg = Registers.Status32;
            switch (cond)
            {
            case ArcCondition.EQ: cc = ConditionCode.EQ; grf = FlagM.ZF; break;
            case ArcCondition.NE: cc = ConditionCode.NE; grf = FlagM.ZF; break;
            case ArcCondition.PL: cc = ConditionCode.GE; grf = FlagM.NF; break;
            case ArcCondition.MI: cc = ConditionCode.LT; grf = FlagM.NF; break;
            case ArcCondition.CS: cc = ConditionCode.ULT; grf = FlagM.CF; break;
            case ArcCondition.CC: cc = ConditionCode.UGE; grf = FlagM.CF; break;
            case ArcCondition.VS: cc = ConditionCode.OV; grf = FlagM.VF; break;
            case ArcCondition.VC: cc = ConditionCode.NO; grf = FlagM.VF; break;
            case ArcCondition.GT: cc = ConditionCode.GT; grf = FlagM.ZF | FlagM.NF | FlagM.VF; break;
            case ArcCondition.GE: cc = ConditionCode.GE; grf = FlagM.ZF | FlagM.NF; break;
            case ArcCondition.LT: cc = ConditionCode.LT; grf = FlagM.ZF | FlagM.NF; break;
            case ArcCondition.LE: cc = ConditionCode.LE; grf = FlagM.ZF | FlagM.NF | FlagM.VF; break;
            case ArcCondition.HI: cc = ConditionCode.UGT; grf = FlagM.ZF | FlagM.CF; break;
            case ArcCondition.LS: cc = ConditionCode.ULE; grf = FlagM.ZF | FlagM.CF; break;
            case ArcCondition.PNZ: cc = ConditionCode.GT; grf = FlagM.ZF | FlagM.NF; break;
            case ArcCondition.SC: return TestSaturation(false); 
            case ArcCondition.SS: return TestSaturation(true);
            default:
                EmitUnitTest(instr, $"Unknown ArcCondition {cond}");
                break;
            }
            var flags = binder.EnsureFlagGroup(arch.GetFlagGroup(Registers.Status32, (uint) grf));
            return m.Test(cc, flags);
        }

        private Expression TestSaturation(bool isSaturated)
        {
            var flags = binder.EnsureFlagGroup(arch.GetFlagGroup(Registers.AuxMacmode, (uint) S));
            var test = host.PseudoProcedure("__saturated", PrimitiveType.Bool, flags);
            if (isSaturated)
            {
                return test;
            }
            else
            {
                return m.Not(test);
            }
        }

        private void MaybeCast(Expression dst, Expression src)
        {
            var bitDiff = dst.DataType.BitSize - src.DataType.BitSize;
            if (bitDiff > 0)
            {
                src = m.Convert(src, src.DataType, dst.DataType);
            }
            m.Assign(dst, src);
        }

        private void MaybeSlice(Expression dst, Expression src)
        {
            var bitDiff = src.DataType.BitSize - dst.DataType.BitSize;
            if (bitDiff > 0)
            {
                src = m.Slice(dst.DataType, src, 0);
            }
            m.Assign(dst, src);
        }

        private (RegisterStorage baseReg, Expression ea) RewriteEa(MemoryOperand mem, bool scaleOffset)
        {
            Expression ea = null;
            int offset = mem.Offset;
            if (scaleOffset)
            {
                // Byte size is undefined.
                if (mem.Width.Size == 1)
                {
                    return (null, null);
                }
                offset = offset * mem.Width.Size;
            }
            if (mem.Base != null)
            {
                if (mem.Base == Registers.Pcl)
                {
                    var uAddr = (int) instr.Address.ToUInt32() & ~3;
                    ea = Address.Ptr32((uint) (uAddr + offset));
                }
                else
                {
                    ea = binder.EnsureRegister(mem.Base);
                    ea = m.AddSubSignedInt(ea, offset);
                }
            }
            else
            {
                ea = m.Word32(offset);
            }
            return (mem.Base, ea);
        }

        // Instruction rewriters //////////////////////////

        private void RewriteAddSubsdw(string fnName)
        {
            var dt = new ArrayType(PrimitiveType.Int16, 2);
            var tmp1 = binder.CreateTemporary(dt);
            var tmp2 = binder.CreateTemporary(dt);
            m.Assign(tmp1, Operand(1));
            m.Assign(tmp2, Operand(2));
            var dst = Operand(0);
            m.Assign(dst, host.PseudoProcedure(fnName, dt, tmp1, tmp2));
            var flagReg = binder.EnsureFlagGroup(arch.GetFlagGroup(Registers.Status32, (uint) ZNV));
            var satReg = binder.EnsureFlagGroup(arch.GetFlagGroup(Registers.AuxMacmode, (uint) S));

            m.Assign(flagReg, m.Cond(dst));
            m.Assign(satReg, m.Cond(dst));
        }

        private void RewriteAluOp(Func<Expression, Expression> fn, FlagM grf)
        {
            MaybeSkip(instr.Condition);
            var src = Operand(1);
            var dst = Operand(0);
            m.Assign(dst, fn(src));
            if (instr.SetFlags && grf != 0)
            {
                var flagReg = binder.EnsureFlagGroup(arch.GetFlagGroup(Registers.Status32, (uint) grf));
                m.Assign(flagReg, m.Cond(dst));
            }
        }

        private void RewriteAluOp(Func<Expression, Expression, Expression> fn, FlagM grf)
        {
            MaybeSkip(instr.Condition);
            var src1 = Operand(1);
            var src2 = Operand(2);
            var dst = Operand(0);
            m.Assign(dst, fn(src1, src2));
            if (instr.SetFlags)
            {
                var flagReg = binder.EnsureFlagGroup(arch.GetFlagGroup(Registers.Status32, (uint) grf));
                m.Assign(flagReg, m.Cond(dst));
            }
        }

        private void RewriteB(ArcCondition cond)
        {
            var addr = ((AddressOperand) instr.Operands[0]).Address;
            if (cond == ArcCondition.AL)
            {
                m.Goto(addr, this.iclass);
            }
            else
            {
                m.Branch(this.TestFlags(cond), addr, this.iclass);
            }
        }

        private void RewriteBbit(bool branchIfTrue)
        {
            var op1 = Operand(0);
            var op2 = Operand(1);
            Expression cond = host.PseudoProcedure("__bit", PrimitiveType.Bool, op1, op2);
            if (!branchIfTrue)
            {
                cond = cond.Invert();
            }
            m.Branch(cond, ((AddressOperand) instr.Operands[2]).Address, iclass);
        }

        private void RewriteBl(ArcCondition cond)
        {
            MaybeSkip(cond);
            m.Call(Operand(0), 0, instr.InstructionClass);
        }

        private void RewriteBr(Func<Expression, Expression, Expression> cmp)
        {
            var src1 = Operand(0);
            var src2 = Operand(1);
            m.Branch(cmp(src1, src2), ((AddressOperand) instr.Operands[2]).Address, instr.InstructionClass);
        }

        private void RewriteBrk()
        {
            m.SideEffect(host.PseudoProcedure("__brk", VoidType.Instance), instr.InstructionClass);
        }

        private void RewriteCondInstr(Func<Expression, Expression, Expression> fn, FlagM grf)
        {
            MaybeSkip(instr.Condition);
            var src1 = Operand(0);
            var src2 = Operand(1);
            var dst = binder.EnsureFlagGroup(arch.GetFlagGroup(Registers.Status32, (uint)grf));
            m.Assign(dst, m.Cond(fn(src1, src2)));
        }

        private void RewriteDivaw()
        {
            var src1 = Operand(1);
            var src2 = Operand(2);
            var dst = Operand(0);
            m.Assign(dst, host.PseudoProcedure("__divaw", dst.DataType, src1, src2));
        }

        private void RewriteExt(PrimitiveType dtSlice, PrimitiveType dtExt)
        {
            var src = m.Slice(dtSlice, Operand(1), 0);
            var dst = Operand(0);
            m.Assign(dst, m.Convert(src, src.DataType, dtExt));
        }

        private void RewriteFlag()
        {
            var src = Operand(0);
            m.SideEffect(host.PseudoProcedure("__flag", VoidType.Instance, src));
        }

        private void RewriteJ(ArcCondition cond)
        {
            MaybeSkip(cond);
            if (instr.Operands[0] is MemoryOperand mop)
            {
                if (mop.Base != null && mop.Offset == 0)
                {
                    if (mop.Base == Registers.Blink)
                    {
                        m.Return(0, 0, instr.InstructionClass);
                        return;
                    }
                }
            }
            EmitUnitTest(instr, "Unimplemented J instruction");
        }

        private void RewriteJl()
        {
            if (instr.Operands[0] is MemoryOperand mop)
            {
                var (_, ea) = RewriteEa(mop, false);
                m.Call(ea, 0, instr.InstructionClass);
                return;
            }
            EmitUnitTest(instr, "Unimplemented J instruction");
        }

        private void RewriteLoad(PrimitiveType dt)
        {
            if (instr.SignExtend)
            {
                dt = PrimitiveType.Create(Domain.SignedInt, dt.BitSize);
            }
            var dst = Operand(0);
            var (baseReg, ea) = RewriteEa((MemoryOperand) instr.Operands[1], instr.Writeback == AddressWritebackMode.@as);
            if (ea == null)
            {
                iclass = InstrClass.Invalid;
                m.Invalid();
                return;
            }
            switch (instr.Writeback)
            {
            case AddressWritebackMode.None:
            case AddressWritebackMode.@as:
                MaybeCast(dst, m.Mem(dt, ea));
                break;
            case AddressWritebackMode.ab:
                var reg = binder.EnsureRegister(baseReg);
                MaybeCast(dst, m.Mem(dt, reg));
                m.Assign(reg, ea);
                break;
            case AddressWritebackMode.aw:
                reg = binder.EnsureRegister(baseReg);
                m.Assign(reg, ea);
                MaybeCast(dst, m.Mem(dt, reg));
                break;
            default:
                host.Warn(instr.Address, "Unimplemented writeback mode {0}", instr.Writeback);
                EmitUnitTest(instr);
                return;
            }
        }

        // Rewriting LP instructions is hairy because it's a dynamic property of a loop.
        // We set the LP_START and LP_END regisers in the state and hope they survive.
        // Another static possibility is to assume that the LP target will be reached and 
        // create a "static" edge, but this is not required to happen.
        private void RewriteLp(ArcCondition condition)
        {
            MaybeSkip(condition);
            var uAddrStart = instr.Address.ToUInt32() + (uint) instr.Length;
            var uAddrEnd = ((AddressOperand) instr.Operands[0]).Address.ToUInt32();
            this.state.SetValue(Registers.LpStart, Constant.UInt32(uAddrStart));
            this.state.SetValue(Registers.LpEnd, Constant.UInt32(uAddrEnd));
            m.Assign(binder.EnsureRegister(Registers.LpStart), Address.Ptr32(uAddrStart));
            m.Assign(binder.EnsureRegister(Registers.LpEnd), Address.Ptr32(uAddrEnd));
        }

        private void RewriteLr()
        {
            var dst = Operand(0);
            var src = (uint) ((MemoryOperand) instr.Operands[1]).Offset;
            m.Assign(dst, host.PseudoProcedure("__load_aux_reg", PrimitiveType.Word32, m.Word32(src)));
        }

        private void RewriteMov()
        {
            var src = Operand(1);
            var dst = Operand(0);
            m.Assign(dst, src);
        }

        private void RewriteMul(Func<Expression, Expression, Expression> fn, PrimitiveType dtResult)
        {
            MaybeSkip(instr.Condition);
            var src1 = Operand(0);
            var src2 = Operand(1);
            var result = fn(src1, src2);
            result.DataType = dtResult;
            var mhi_lo = binder.EnsureSequence(dtResult,Registers.Mhi, Registers.Mlo);
            m.Assign(mhi_lo, result);
        }

        private void RewritePop()
        {
            var sp = binder.EnsureRegister(Registers.Sp);
            var dst = Operand(0);
            m.Assign(dst, m.Mem32(sp));
            m.Assign(sp, m.IAddS(sp, 4));
        }

        private void RewritePush()
        {
            var sp = binder.EnsureRegister(Registers.Sp);
            var src = Operand(0);
            m.Assign(sp, m.ISubS(sp, 4));
            m.Assign(m.Mem32(sp), src);
        }

        private void RewriteShift(Func<Expression, Expression, Expression> fn, FlagM grf)
        {
            MaybeSkip(instr.Condition);
            var src1 = Operand(1);
            Expression src2;
            if (instr.Operands.Length == 3)
            {
                src2 = Operand(2);
            }
            else
            {
                src2 = Constant.Int32(1);
            }
            var dst = Operand(0);
            m.Assign(dst, fn(src1, src2));
            if (instr.SetFlags)
            {
                var flagReg = binder.EnsureFlagGroup(arch.GetFlagGroup(Registers.Status32, (uint) grf));
                m.Assign(flagReg, m.Cond(dst));
            }
        }

        private void RewriteSr()
        {
            var src = Operand(0);
            var dst = (uint) ((MemoryOperand) instr.Operands[1]).Offset;
            m.SideEffect(host.PseudoProcedure("__store_aux_reg", VoidType.Instance, m.Word32(dst), src));
        }

        private void RewriteStore(PrimitiveType dt)
        {
            var src = Operand(0);
            var (baseReg, ea) = RewriteEa((MemoryOperand) instr.Operands[1], instr.Writeback == AddressWritebackMode.@as);
            if (ea == null)
            {
                iclass = InstrClass.Invalid;
                m.Invalid();
                return;
            }
            switch (instr.Writeback)
            {
            case AddressWritebackMode.None:
            case AddressWritebackMode.@as:
                MaybeSlice(m.Mem(dt, ea), src);
                break;
            case AddressWritebackMode.aw:
                var reg = binder.EnsureRegister(baseReg);
                m.Assign(reg, ea);
                MaybeSlice(m.Mem(dt, reg), src);
                break;
            case AddressWritebackMode.ab:
                reg = binder.EnsureRegister(baseReg);
                MaybeSlice(m.Mem(dt, reg), src);
                m.Assign(reg, ea);
                break;
            default:
                host.Warn(instr.Address, "Unimplemented writeback mode {0}", instr.Writeback);
                EmitUnitTest(instr);
                m.Invalid();
                iclass = InstrClass.Invalid;
                return;
            }
        }

        private void RewriteTrap()
        {
            m.SideEffect(host.PseudoProcedure(PseudoProcedure.Syscall, VoidType.Instance), instr.InstructionClass);
        }
    }
}