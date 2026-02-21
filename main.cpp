#include <stdio.h>
#include <vector>
#include <string>
#include <iostream>
#include<iomanip>
std::vector<unsigned int> encodeInstruction(std::string inst)
{
	unsigned int opcode = 0;
	if (inst.find("ADD") != std::string::npos)
	{
		opcode = 1;

	}
	if (inst.find("SUB") != std::string::npos)
	{
		opcode = 2;

	}
	else if (inst.find("AND") != std::string::npos)
	{
		opcode = 3;

	}
	else if (inst.find("OR_") != std::string::npos) // to simplify decoding, OR will have to become OR_, so it's exactly three characters it makes the logic far less of a headache
	{
		opcode = 4;

	}
	else if (inst.find("XOR") != std::string::npos)
	{
		opcode = 5;

	}
	else if (inst.find("NOT") != std::string::npos)
	{
		opcode = 6;

	}
	else if (inst.find("SHR") != std::string::npos)
	{
		opcode = 7;

	}
	else if (inst.find("SHL") != std::string::npos)
	{
		opcode = 8;

	}
	else if (inst.find("STM") != std::string::npos)
	{
		opcode = 9;

	}
	else if (inst.find("LDM") != std::string::npos)
	{
		opcode = 10;

	}
	else if (inst.find("STJ") != std::string::npos)
	{
		opcode = 11;

	}
	else if (inst.find("JMP") != std::string::npos)
	{
		opcode = 12;

	}
	else if (inst.find("CAL") != std::string::npos)
	{
		opcode = 13;

	}
	else if (inst.find("RET") != std::string::npos)
	{
		opcode = 14;

	}
	else if (inst.find("HLT") != std::string::npos)
	{
		opcode = 15;

	}
	else if (inst.find("LDI") != std::string::npos)
	{
		opcode = 16;

	}
	else if (inst.find("ADF") != std::string::npos)
	{
		opcode = 17;

	}
	else if (inst.find("SUF") != std::string::npos)
	{
		opcode = 18;

	}
	else if (inst.find("MUF") != std::string::npos)
	{
		opcode = 19;

	}
	else if (inst.find("DIF") != std::string::npos)
	{
		opcode = 20;

	}
	else if (inst.find("I2F") != std::string::npos)
	{
		opcode = 21;

	}
	else if (inst.find("F2I") != std::string::npos)
	{
		opcode = 22;

	}
	else if (inst.find("ENV") != std::string::npos)
	{
		opcode = 23;

	}
	else if (inst.find("ERV") != std::string::npos)
	{
		opcode = 24;

	}
	else if (inst.find("ADV") != std::string::npos)
	{
		opcode = 25;

	}
	else if (inst.find("SUV") != std::string::npos)
	{
		opcode = 26;

	}
	else if (inst.find("MUV") != std::string::npos)
	{
		opcode = 27;

	}
	else if (inst.find("DIV") != std::string::npos)
	{
		opcode = 28;

	}
	else if (inst.find("INV") != std::string::npos)
	{
		opcode = 29;

	}
	else if (inst.find("ICM") != std::string::npos)
	{
		opcode = 30;

	}
	else if (inst.find("IFM") != std::string::npos)
	{
		opcode = 31;
	}
	//0123 4 567 89 AB CDE F | GHIJ KLMN OPQR STUV
	//0000 0 000 00 00 000 0 | 0000 0000 0000 0000
	if (opcode == 0 || opcode == 14 || opcode == 15) {
		return { static_cast<unsigned int>((opcode << 27) & 0xFFFFFFFF) };

	}
	unsigned int destFeild = 0;
	bool directMemory = false;
	if (opcode != 12)
	{
		if (inst[4] != 'R')
		{
			char C = inst[4];
			destFeild += 16;
			destFeild += abs(std::stoi(inst.substr(inst[8],inst[9]), nullptr, 16));
			directMemory = true;

		}
		else
		{
			destFeild = abs(std::stoi(inst.substr(inst[5],inst[6]), nullptr, 16));

		}

	}
	else {
		if (inst.find("LT") != std::string::npos)
		{
			destFeild += 1;

		}
		if (inst.find("EQ") != std::string::npos)
		{
			destFeild += 2;

		}
		if (inst.find("GT") != std::string::npos)
		{
			destFeild += 4;

		}

	}
	int A = -1;
	int B = -1;
	bool AConst = false;
	bool BConst = false;
	int tokenA = -1;
	for (int i = 0; i < inst.size(); i++)
	{

		if (A == -1)
		{
			if ((directMemory == false && i > 6) || (directMemory == true && i > 9))
			{
				if (inst[i] == 'R')
				{
					A = abs(std::stoi(inst.substr(i + 1, 1), nullptr, 16));
					tokenA = i;
					continue;

				}
				if (inst[i] == '$')
				{

					A = abs(std::stoi(inst.substr(i + 1, 8), nullptr, 16));
					AConst = true;
					tokenA = i;
					continue;

				}


			}

		}
		if (B == -1)
		{
			if (tokenA != -1 && i > tokenA)
			{
				if (inst[i] == 'R')
				{
					B = abs(std::stoi(inst.substr(i + 1, 1), nullptr, 16));
					continue;

				}
				if (inst[i] == '$')
				{

					B = abs(std::stoi(inst.substr(i + 1, 8), nullptr, 16));
					BConst = true;
					continue;

				}

			}

		}

	}
	unsigned int One = (opcode << 27) & 0xFFFFFFFF;
	unsigned int Two = (destFeild << 22) & 0xFFFFFFFF;
	unsigned int Three = static_cast<unsigned int>(A & 0xF);
	unsigned int Four = static_cast<unsigned int>(B & 0xF);
	if (AConst) {
		Three |= 0x10;

	}
	if (BConst)
	{
		Four |= 0x10;

	}
	Three = (Three << 17) & 0xFFFFFFFF;
	Four = (Four << 12) & 0xFFFFFFFF;
	unsigned int encInst = One | Two | Three | Four;
	std::vector<unsigned int> output;
	output.push_back(encInst);
	if (AConst)
	{
		output.push_back(A);

	}
	if (BConst)
	{
		output.push_back(B);

	}
	return output;
}

int main()
{
	std::cout << "welcome to Revolt, a STBASM32 assembler. Created JAN-2026, Upgraded 8-FEB-2026" << std::endl;
	std::cout << "To start, write some STBASM32 code, and type 'RUN' to run it" << std::endl;
	std::cout << "The valid commands are: NOP, ADD, SUB, AND, OR_, NOT, XOR, SHL, SHR, LDM, STM, STJ, JMP, CAL, RET, HLT." << std::endl;
	std::cout << "LDI, ADF, SUF, MUF, DIF, I2F, F2I, ENV, ERV, ADV, SUV, MUV, DIV, INV, ICM, IFM" << std::endl;
	std::cout << "Most of these shouldn't need much explanation, but do please keep in mind that STBASM32 is 32-bit" << std::endl;
	printf("use # at the start of a line for a comment. make sure you don't include valid instructions (valid instructions are allcaps)");
	printf("invalid instructions will be read by the parser as a NOP. it won't do anything, but it'll take a slot of memory\n");
	std::vector<unsigned int> memory = { 0x0,0x0,0x0 };
	bool thinking = true;
	int length = 0;
	std::string command;
	std::vector<unsigned int> encoded;
	while (thinking)
	{
		//if(length > 65536)
		//	{
		//		thinking = false;
		//	}
		std::cout << length << ": ";
		getline(std::cin, command);
		if (command == "RUN" && length > 0)
		{
			thinking = false;
		}
		if (command == "RUN" && length == 0)
		{
			std::cout << "You need at least one instruction!";
		}
		if (command[0] != '#')
		{
			encoded = encodeInstruction(command);
			for (int i = 0; i < encoded.size(); i++)
			{
				std::cout << std::hex << encoded[i] << " ";
			}


			for (int i = 0; i < encoded.size(); i++)
			{
				memory.push_back(encoded[i]);
			}

			if (command.size() > 2)
			{
				length += encoded.size();
			}
			else
			{
				std::cout << "The shortest acceptable command is 3 characters.";
			}
		}
	}
	std::vector<unsigned int> stack;
	unsigned int PC = 0;
	unsigned int JR = 0;
	//int SP = stack.size() - 1; // Subtract the number of stack frames we want. For now, it's 16. We can adjust this if we so choose;
	unsigned int MI = 0;
	std::vector<unsigned int> R = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
	unsigned short typeFlags = 0;
	std::vector<float> VA;
	std::vector<float> VB;
	std::vector<float> Vout = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };;
	union flint {
		float F;
		unsigned int I;
	};
	while (PC < memory.size())
	{
		int instrCode = memory[PC];
		int A = (instrCode >> 17) & 0xF;
		int B = (instrCode >> 12) & 0xF;
		int AIndex = A;
		int BIndex = B;
		A = R[A];
		B = R[B];
		bool AConst = (instrCode & (1 << 21)) > 0;
		bool BConst = (instrCode & (1 << 16)) > 0;
		int Dest = (instrCode >> 22) & 0xF;
		bool isAddress = (instrCode & 0x04000000) > 0;
		bool incrementPC = true;
		if (AConst && BConst)
		{
			A = memory[PC + 1];
			B = memory[PC + 2];
			PC += 2;

		}
		else if (AConst) {
			A = memory[PC + 1];
			PC++;

		}
		else if (BConst)
		{
			B = memory[PC + 1];
			PC++;

		}
		unsigned int opcode = (instrCode >> 27) & 0x1F;
		int result = 0;
		switch (opcode) {
		case 0x1:
		{
			bool AValid = false;
			bool BValid = false;
			if ((typeFlags & (1 << AIndex)) == 0)
			{
				AValid = true;
			}
			if ((typeFlags & (1 << BIndex)) == 0)
			{
				BValid = true;
			}
			if (!(AValid && BValid))
			{
				std::cout << "ADD does not take float inputs.- The Revolt VM ";
				std::cout << PC;
				return -1;
				break;
			}
			unsigned long long int X = A + B;
			if (X <= 0xFFFFFFFF)
			{
				result = static_cast<int>(X);
			}
			else {
				std::cout << "Integer Overflow!" << std::endl;
				return 0;
			}
			break;
		}
		case 0x2:
		{
			bool AValid = false;
			bool BValid = false;
			if ((typeFlags & (1 << AIndex)) == 0)
			{
				AValid = true;
			}
			if ((typeFlags & (1 << BIndex)) == 0)
			{
				BValid = true;
			}
			if (!(AValid && BValid))
			{
				std::cout << "SUB does not take float inputs. - The Revolt VM";
				std::cout << PC;
				return -1;
				break;
			}

			result = A - B;
			break;
		}
		case 0x3:
			result = A & B;
			break;
		case 0x4:
			result = A | B;
			break;
		case 0x5:
			result = (~A & B) | (A & ~B);
			break;
		case 0x6:
			result = (~A);
			break;
		case 0x7:
			result = A >> B;
			break;
		case 0x8:
			result = A << B;
			break;
		case 0x9:
			if (B >= memory.size())
			{
				//memory.push_back(A);
				for (int i = memory.size(); i < B + 1; i++)
				{
					memory.push_back(0);
				}
				memory[B] = A;

			}
			if (B < memory.size())
			{
				memory[B] = A;

			}
			//	if(memory.size() == 65536 && B > memory.size())
			//	{
			//		MI = B;
			//		memory[MI] = A;
			//
			//	}
			break;
		case 0xA:
			result = memory[B % memory.size()];
			break;
		case 0xB:
			JR = A;
			break;
		case 0xC:
		{
			bool LTEnabled = Dest & 0x1;
			bool EQEnabled = Dest & 0x2;
			bool GTEnabled = Dest & 0x4;
			if ((A < B && LTEnabled) || (A == B && EQEnabled) || (A > B && GTEnabled))
			{
				PC = JR;
				incrementPC = false;

			}
			break;
		}
		case 0xD:
		{
			//SP++;
			unsigned int returnAddress = PC + 1;
			if (AConst)
			{
				returnAddress++;
			}

			stack.push_back(returnAddress); // it might be wise to plump up the memory with enough 0s I'm technically cheating here, but this is the most practical way I know of to implement this
			PC = A;
			incrementPC = false;

			break;
		}
		case 0xE:
			if (stack.size() > 0)
			{
				//SP--;
				PC = stack[stack.size() - 1];
				stack.pop_back();
				incrementPC = false;
			}
			break;
		case 0xF:
			PC = 0;
			R = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
			JR = 0;
			//	SP = 0;
			return 0;
			break;
		case 0x10:
			result = A;
			break;
		case 0x11:
		{
			bool AValid = false;
			bool BValid = false;
			if ((typeFlags & (1 << AIndex)) != 0)
			{
				AValid = true;
			}
			if ((typeFlags & (1 << BIndex)) != 0)
			{
				BValid = true;
			}
			if (!(AValid && BValid))
			{
				std::cout << "Floats require special handling. Please convert to float!";
				std::cout << PC;
				return -1;
				break;
			}
			flint FIA;
			flint FIB;
			FIA.I = A;
			FIB.I = B;
			flint FIout;
			FIout.F = FIA.F + FIB.F;
			result = FIout.I;
			break;
		}
		case 0x12:
		{
			bool AValid = false;
			bool BValid = false;
			if ((typeFlags & (1 << AIndex)) != 0)
			{
				AValid = true;
			}
			if ((typeFlags & (1 << BIndex)) != 0)
			{
				BValid = true;
			}
			if (!(AValid && BValid))
			{
				std::cout << "Floats require special handling. Please convert to float! ";
				std::cout << PC;
				return -1;
				break;
			}
			flint FIA;
			flint FIB;
			FIA.I = A;
			FIB.I = B;
			flint FIout;
			FIout.F = FIA.F - FIB.F;
			result = FIout.I;
			break;
		}
		case 0x13:
		{
			bool AValid = false;
			bool BValid = false;
			if ((typeFlags & (1 << AIndex)) != 0)
			{
				AValid = true;
			}
			if ((typeFlags & (1 << BIndex)) != 0)
			{
				BValid = true;
			}
			if (!(AValid && BValid))
			{
				std::cout << "Floats require special handling. Please convert to float!";
				std::cout << PC;
				break;
			}
			flint FIA;
			flint FIB;
			FIA.I = A;
			FIB.I = B;
			flint FIout;
			FIout.F = FIA.F * FIB.F;
			result = FIout.I;
			break;
		}
		case 0x14:
		{
			bool AValid = false;
			bool BValid = false;
			if ((typeFlags & (1 << AIndex)) != 0)
			{
				AValid = true;
			}
			if ((typeFlags & (1 << BIndex)) != 0)
			{
				BValid = true;
			}
			if (!(AValid && BValid))
			{
				std::cout << "Floats require special handling. Please convert to float!";
				std::cout << PC;
				return -1;
				break;
			}
			if (B == 0.0f)
			{
				std::cout << "Dividing by zero is illegal!";
				return 0;
			}
			flint FIA;
			flint FIB;
			FIA.I = A;
			FIB.I = B;
			flint FIout;
			FIout.F = FIA.F / FIB.F;
			result = FIout.I;
			break;
		}
		case 0x15:
		{
			bool AValid = false;
			bool BValid = false;
			if ((typeFlags & (1 << AIndex)) != 0)
			{
				AValid = true;
			}
			if ((typeFlags & (1 << BIndex)) != 0)
			{
				BValid = true;
			}
			if (!(AValid && BValid))
			{
				std::cout << "Floats require special handling. Please convert to float!";
				std::cout << PC;
				return -1;
				break;
			}

			flint input;
			input.F = static_cast<float>(A);
			result = input.I;
			typeFlags |= 1 << Dest;
			break;

		}
		case 0x16:
		{
			flint input;
			input.I = static_cast<int>(A);
			result = input.I;
			typeFlags &= ~(1 << Dest);
			break;
		}
		case 0x17:
		{
			bool AValid = false;
			bool BValid = false;
			if ((typeFlags & (1 << AIndex)) != 0)
			{
				AValid = true;
			}
			if ((typeFlags & (1 << BIndex)) != 0)
			{
				BValid = true;
			}
			if (!(AValid && BValid))
			{
				std::cout << "Please convert vector arguments to floats!";
				std::cout << PC;
				return -1;
				break;
			}
			flint FIA;
			flint FIB;
			FIA.I = A;
			FIB.I = B;
			if (VA.size() < 16)
			{
				VA.push_back(FIA.F);
			}
			if (VA.size() == 16 || AIndex < VA.size()) {
				VA[AIndex] = FIA.F;

			}
			if (VB.size() < 16)
			{
				VB.push_back(FIB.F);
			}
			if (VB.size() == 16 || BIndex < VB.size())
			{
				VB[BIndex] = FIB.F;
			}
			break;
		}
		case 0x18:
		{
			if (VA.size() == 0 && VB.size() == 0)
			{
				std::cout << "Vectors require at least element!";
				return 0;
			}
			VA.pop_back();
			VB.pop_back();
			break;
		}
		case 0x19:
		{
			if (VA.size() == VB.size())
			{
				for (int i = 0; i < VA.size(); i++)
				{
					Vout[i] = VA[i] + VB[i];
				}
			}
			else {
				std::cout << "Vectors need to be the same size!";
				return 0;
			}
			break;
		}
		case 0x1A:
		{
			if (VA.size() == VB.size())
			{
				for (int i = 0; i < VA.size(); i++)
				{
					Vout[i] = VA[i] - VB[i];
				}
			}
			else {
				std::cout << "Vectors need to be the same size!";
				return 0;
			}
			break;
		}
		case 0x1B:
		{
			if (VA.size() == VB.size())
			{
				for (int i = 0; i < VA.size(); i++)
				{
					Vout[i] = VA[i] * VB[i];
				}
			}
			else {
				std::cout << "Vectors need to be the same size!";
				return 0;
			}
			break;
		}
		case 0x1C:
		{
			if (VA.size() == VB.size())
			{
				for (int i = 0; i < VA.size(); i++)
				{
					if (VB[i] == 0.0f)
					{
						std::cout << "Dividing by zero is illegal!";
						return 0;
					}
					Vout[i] = VA[i] / VB[i];
				}
			}
			else {
				std::cout << "Vectors need to be the same size!";
				return 0;
			}
			break;
		}
		case 0x1D:
		{
			flint vout;
			vout.F = Vout[AIndex];
			result = vout.I;
			break;
		}
		case 0x1E:
		{
			long long X = A * B;
			if (X <= 0xFFFFFFFF)
			{
				result = X;
			}
			else {
				std::cout << "Integer Overflow!";
				return 0;
			}
			break;
		}
		case 0x1F:
		{
			long long int bigboy = A * B;
			flint overflow;
			if (bigboy > 0xFFFFFFFF)
			{
				overflow.F = static_cast<float>(bigboy);
				result = overflow.I;
				typeFlags |= 1 << Dest;
			}
			else {
				result = static_cast<int>(bigboy);
			}
		}
		break;
		}



		if (!isAddress)
		{
			R[Dest] = result;

		}
		else
		{
			memory[R[Dest] % memory.size()] = result;

		}
		if (incrementPC)
		{
			PC++;

		}
		if ((memory[2] & 0x80000000) != 0)
		{
			std::string Tin;
			getline(std::cin, Tin);
			memory[1] = stoi(Tin, nullptr, 16);
			memory[2] &= ~0x80000000;
		}
		if ((memory[2] & 0x40000000) != 0)
		{
			std::cout << memory[0];
			memory[2] &= ~0x40000000;
		}
		if ((memory[2] & 0x20000000) != 0)
		{
			flint F;
			F.I = memory[0];
			std::cout << F.F;
			memory[2] &= ~0x20000000;
		}
		if ((memory[2] & 0x10000000) != 0)
		{
			int temp = memory[0];
			char Char;
			std::string printout;
			for (int i = 0; temp != 0; i++)
			{
				Char = temp & 0xFF;
				printout += Char;
				temp = temp >> 8;
			}
			std::cout << printout;
			memory[2] &= ~0x10000000;
		}
	}

	return 0;
}