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

using Reko.Core.Machine;
using Reko.Core.Types;
using System;
using System.Collections.Generic;
using System.Text;

namespace Reko.Arch.Qualcomm
{
    public class ApplicationOperand : MachineOperand
    {
        public ApplicationOperand(PrimitiveType width, Mnemonic mnemonic, params MachineOperand[] ops) : base(width)
        {
            this.Mnemonic = mnemonic;
            this.Operands = ops;
        }

        public Mnemonic Mnemonic { get; }
        public MachineOperand[] Operands { get; }

        public override void Write(MachineInstructionWriter writer, MachineInstructionWriterOptions options)
        {
            switch (Mnemonic)
            {
            case Mnemonic.EQ:
                Operands[0].Write(writer, options);
                writer.WriteString("=");
                Operands[1].Write(writer, options);
                break;
            case Mnemonic.LE:
                Operands[0].Write(writer, options);
                writer.WriteString("<=");
                Operands[1].Write(writer, options);
                break;
            case Mnemonic.GE:
                Operands[0].Write(writer, options);
                writer.WriteString(">=");
                Operands[1].Write(writer, options);
                break;
            case Mnemonic.NE:
                Operands[0].Write(writer, options);
                writer.WriteString("!=");
                Operands[1].Write(writer, options);
                break;

            default:
                writer.WriteMnemonic(Mnemonic.ToString().Replace("__", "."));
                var sep = "(";
                foreach (var op in Operands)
                {
                    writer.WriteString(sep);
                    op.Write(writer, options);
                    sep = ",";
                }
                writer.WriteString(")");
                break;
            }
        }
    }
}
