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

namespace Reko.Arch.Qualcomm
{
    public class DecoratorOperand : MachineOperand
    {
        public DecoratorOperand(PrimitiveType width, MachineOperand op) : base(width)
        {
            this.Operand = op;
        }

        public MachineOperand Operand { get; }
        public int BitOffset { get; set;  }

        public bool Inverted { get; set; }

        public bool NewValue { get; set; }

        public bool Complement { get; set; }

        public bool Chop { get;  set; }

        public bool Carry { get; set; }

        public bool Sat { get; set; }
        public bool Rnd { get; set; }
        public bool Lsl16 { get; set; }

        public override void Write(MachineInstructionWriter writer, MachineInstructionWriterOptions options)
        {
            if (Complement)
                writer.WriteChar('~');
            else if (Inverted)
                writer.WriteChar('!');
            this.Operand.Write(writer, options);
            if (this.Width.BitSize < (int) Operand.Width.BitSize)
            {
                writer.WriteChar('.');
                if (BitOffset == 0)
                    writer.WriteChar('l');
                else
                    writer.WriteChar('h');
            }
            if (NewValue)
            {
                writer.WriteString(".new");
            }
            if (Chop)
            {
                writer.WriteString(":chop");
            }
            if (Carry)
            {
                writer.WriteString(":carry");
            }
            if (Rnd)
            {
                writer.WriteString(":rnd");
            }
            if (Sat)
            {
                writer.WriteString(":sat");
            }
            if (Lsl16)
            {
                writer.WriteString(":<<16");
            }
        }
    }
}