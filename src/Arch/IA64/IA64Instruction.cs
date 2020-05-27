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
using Reko.Core.Machine;
using Reko.Core.Types;
using System.Text;

namespace Reko.Arch.IA64
{
    public class IA64Instruction : MachineInstruction
    {
        public bool Stop { get; set; }
        public Mnemonic Mnemonic { get; set; }

        public RegisterStorage QualifyingPredicate { get; set; }

        /// <summary>
        /// Execution unit.
        /// </summary>
        /*[Obsolete]*/public char Unit { get; set; }


        public override int MnemonicAsInteger => (int) Mnemonic;
        public override string MnemonicAsString => Mnemonic.ToString();


        public override void Render(MachineInstructionWriter writer, MachineInstructionWriterOptions options)
        {
            RenderQualifyingPredicate(writer);
            RenderMnemonic(writer);
            RenderOperands(writer, options);
        }

        private void RenderQualifyingPredicate(MachineInstructionWriter writer)
        {
            if (QualifyingPredicate == Registers.PredicateRegisters[0])
                return;
            if (QualifyingPredicate == null)
                return;
            writer.WriteFormat("({0}) ", QualifyingPredicate.Name);
        }

        private void RenderMnemonic(MachineInstructionWriter writer)
        {
            var sb = new StringBuilder();
            sb.Append(Mnemonic.ToString().Replace('_', '.'));
            writer.WriteMnemonic(sb.ToString());
        }

        protected override void RenderOperand(MachineOperand operand, MachineInstructionWriter writer, MachineInstructionWriterOptions options)
        {
            switch (operand)
            {
            case ImmediateOperand imm:
                if (imm.Width.Domain == Domain.SignedInt)
                {
                    writer.WriteFormat("{0}", imm.Value.ToInt64());
                }
                else
                {
                    writer.WriteFormat("0x{0:X}", imm.Value.ToUInt64());
                }
                return;
            }
            base.RenderOperand(operand, writer, options);
        }
    }
}