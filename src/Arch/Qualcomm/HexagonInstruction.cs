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
        public ParseType ParseType { get; internal set; }

        public override void Render(MachineInstructionWriter writer, MachineInstructionWriterOptions options)
        {
            if (Mnemonic == Mnemonic.ASSIGN)
            {
                RenderOperand(Operands[0], writer, options);
                writer.WriteString(" = ");
                RenderOperand(Operands[1], writer, options);
            }
            else
            {
                RenderMnemonic(writer, options);
                RenderOperands(writer, options);
            }
        }

        private void RenderMnemonic(MachineInstructionWriter writer, MachineInstructionWriterOptions options)
        {
            writer.WriteMnemonic(Mnemonic.ToString());
        }
    }

    public enum ParseType
    {
        Duplex = 0b00,
    }
}