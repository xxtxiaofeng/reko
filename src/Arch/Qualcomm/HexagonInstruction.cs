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
using System;
using System.Text;

namespace Reko.Arch.Qualcomm
{
    public class HexagonInstruction : MachineInstruction
    {
        public HexagonInstruction(Address address, Mnemonic mnemonic, params MachineOperand[] operands)
        {
            Address = address;
            Mnemonic = mnemonic;
            Operands = operands;
        }

        public Mnemonic Mnemonic { get; }
        public override int MnemonicAsInteger => (int) Mnemonic;
        public override string MnemonicAsString => Mnemonic.ToString();
        public ParseType ParseType { get; set; }

        public MachineOperand ConditionPredicate { get; set; }
        public bool ConditionInverted { get; set; }
        public bool ConditionPredicateNew { get; set; }

        public DirectionHint DirectionHint { get; set; }


        public override void Render(MachineInstructionWriter writer, MachineInstructionWriterOptions options)
        {
            if (ConditionPredicate != null)
            {
                writer.WriteMnemonic("if");
                writer.WriteString(" (");
                if (ConditionInverted)
                    writer.WriteChar('!');
                ConditionPredicate.Write(writer, options);
                if (ConditionPredicateNew)
                    writer.WriteString(".new");
                writer.WriteString(") ");
            }
            switch (Mnemonic)
            {
            case Mnemonic.ASSIGN:
                RenderOperand(Operands[0], writer, options);
                writer.WriteString(" = ");
                RenderOperand(Operands[1], writer, options);
                break;
            case Mnemonic.ANDEQ:
                RenderOperand(Operands[0], writer, options);
                writer.WriteString(" &= ");
                RenderOperand(Operands[1], writer, options);
                break;
            case Mnemonic.SUBEQ:
                RenderOperand(Operands[0], writer, options);
                writer.WriteString(" -= ");
                RenderOperand(Operands[1], writer, options);
                break;
            case Mnemonic.OREQ:
                RenderOperand(Operands[0], writer, options);
                writer.WriteString(" |= ");
                RenderOperand(Operands[1], writer, options);
                break;
            case Mnemonic.ADDEQ:
                RenderOperand(Operands[0], writer, options);
                writer.WriteString(" += ");
                RenderOperand(Operands[1], writer, options);
                break;
            case Mnemonic.SIDEEFFECT:
                RenderOperand(Operands[0], writer, options);
                break;
            default:
                RenderMnemonic(writer, options);
                RenderOperands(writer, options);
                break;
            }
        }

        private void RenderMnemonic(MachineInstructionWriter writer, MachineInstructionWriterOptions options)
        {
            var s = Mnemonic.ToString();
            var sb = new StringBuilder();
            for (int i = 0; i < s.Length; ++i)
            {
                char ch = s[i];
                if (ch == '_' && i < s.Length - 1 && s[i + 1] == '_')
                {
                    sb.Append('.');
                    ++i;
                }
                else
                {
                    sb.Append(ch);
                }
            }
            if (DirectionHint != DirectionHint.None)
            {
                sb.Append(':');
                if (DirectionHint == DirectionHint.Taken)
                    sb.Append('t');
                else
                    sb.Append("nt");
            }
            writer.WriteMnemonic(sb.ToString());
        }
    }

    public enum ParseType
    {
        Duplex = 0b00,
        End = 0b11,
    }

    public enum DirectionHint
    {
        None = 0,
        NotTaken = 1,
        Taken = 2,
    }
}