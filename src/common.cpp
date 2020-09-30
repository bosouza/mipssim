#include <common.h>
#include <vector>
#include <iostream>

void rtrim(std::string &s, char c = ' ')
{

    if (s.empty())
        return;

    std::string::iterator p;
    for (p = s.end(); p != s.begin() && *--p == c;)
        ;

    if (*p != c && p != s.begin())
        p++;

    if (s.size() >= 2)
        s.erase(p, s.end());

    if (p == s.begin() && !s.empty() && *p == c)
        s = "";
}

void ltrim(std::string &s, char c = ' ')
{

    if (s.empty())
        return;

    s = std::string(s.rbegin(), s.rend());
    rtrim(s, c);
    s = std::string(s.rbegin(), s.rend());
}

void trim(std::string &s, char c = ' ')
{

    if (s.empty())
        return;

    ltrim(s, c);
    rtrim(s, c);
}

bool checkRegisterNameExistence(const std::string &registerName)
{
    if (registerName == "zero" ||
        registerName == "at" ||
        registerName == "v0" ||
        registerName == "v1" ||
        registerName == "a0" ||
        registerName == "a1" ||
        registerName == "a2" ||
        registerName == "a3" ||
        registerName == "t0" ||
        registerName == "t1" ||
        registerName == "t2" ||
        registerName == "t3" ||
        registerName == "t4" ||
        registerName == "t5" ||
        registerName == "t6" ||
        registerName == "t7" ||
        registerName == "s0" ||
        registerName == "s1" ||
        registerName == "s2" ||
        registerName == "s3" ||
        registerName == "s4" ||
        registerName == "s5" ||
        registerName == "s6" ||
        registerName == "s7" ||
        registerName == "t8" ||
        registerName == "t9" ||
        registerName == "k0" ||
        registerName == "k1" ||
        registerName == "gp" ||
        registerName == "sp" ||
        registerName == "fp" ||
        registerName == "ra")
        return true;
    else
        return false;
}

unsigned int searchRegisterNumberByName(const std::string &registerName)
{
    if (registerName == "zero")
        return 0;
    else if (registerName == "at")
        return 1;
    else if (registerName == "v0")
        return 2;
    else if (registerName == "v1")
        return 3;
    else if (registerName == "a0")
        return 4;
    else if (registerName == "a1")
        return 5;
    else if (registerName == "a2")
        return 6;
    else if (registerName == "a3")
        return 7;
    else if (registerName == "t0")
        return 8;
    else if (registerName == "t1")
        return 9;
    else if (registerName == "t2")
        return 10;
    else if (registerName == "t3")
        return 11;
    else if (registerName == "t4")
        return 12;
    else if (registerName == "t5")
        return 13;
    else if (registerName == "t6")
        return 14;
    else if (registerName == "t7")
        return 15;
    else if (registerName == "s0")
        return 16;
    else if (registerName == "s1")
        return 17;
    else if (registerName == "s2")
        return 18;
    else if (registerName == "s3")
        return 19;
    else if (registerName == "s4")
        return 20;
    else if (registerName == "s5")
        return 21;
    else if (registerName == "s6")
        return 22;
    else if (registerName == "s7")
        return 23;
    else if (registerName == "t8")
        return 24;
    else if (registerName == "t9")
        return 25;
    else if (registerName == "k0")
        return 26;
    else if (registerName == "k1")
        return 27;
    else if (registerName == "gp")
        return 28;
    else if (registerName == "sp")
        return 29;
    else if (registerName == "fp")
        return 30;
    else if (registerName == "ra")
        return 31;
    else
    {
        std::cout << "unknown register $" << registerName << std::endl;
        throw;
    }
}

void validateInstructionLayoutStr(std::string &_layout, std::string::iterator &_pointer)
{
    if (_layout.empty())
    {
        std::cout << "error during instruction processing: instruction layout string is empty" << std::endl;
        throw;
    }
    else
    {
        if (_pointer == _layout.begin() && (*_pointer == ' ' || *_pointer == '\t'))
        {
            trim(_layout);
            trim(_layout, '\t');
            _pointer = _layout.begin();
        }
    }
}

void validateRegisterSintax(std::string &_layout, std::string::iterator &_pointer, const instructionLayoutPart &_part)
{
    if (!(_part == _RS || _part == _RT || _part == _RD))
        return;
    validateInstructionLayoutStr(_layout, _pointer);
    if (*_pointer != '$')
    {
        std::cout << "sixtax error: it was expected the ";
        if (_part == _RS)
            std::cout << "RS ";
        else if (_part == _RT)
            std::cout << "RT ";
        else
            std::cout << "RD ";
        std::cout << "register and it was typed ";

        while (*_pointer != ' ' && *_pointer != '\t' && *_pointer != ',' && _pointer != _layout.end())
        {
            std::cout << *_pointer;
            _pointer++;
        }

        std::cout << std::endl;
        throw;
    }
}

void validateRegisterSpecified(const std::string &_layout, std::string::iterator &_pointer, const instructionLayoutPart &_part)
{
    if (!(_part == _RS || _part == _RT || _part == _RD))
        return;
    if (_pointer != _layout.end())
        _pointer++;
    else
    {
        std::cout << "sintax error: the register ";
        if (_part == _RS)
            std::cout << "RS ";
        else if (_part == _RT)
            std::cout << "RT ";
        else
            std::cout << "RD ";
        std::cout << "wasn't specified" << std::endl;
        throw;
    }
}

void updateRegisterOfTheInstruction(instruction &_instruction, const std::string &_layout, std::string::iterator &_pointer, const instructionLayoutPart &_part)
{
    if (!(_part == _RS || _part == _RT || _part == _RD))
        return;
    if (!(*_pointer >= '0' && *_pointer <= '3'))
    {
        std::string registerName = "";
        while (*_pointer != ' ' && *_pointer != ',' && _pointer != _layout.end() && *_pointer != '\t')
            registerName = registerName + *_pointer++;

        if (!checkRegisterNameExistence(registerName))
        {
            std::cout << "unknown register $" << registerName << std::endl;
            throw;
        }
        else
        {
            if (_part == _RS)
                _instruction.opx.rs = searchRegisterNumberByName(registerName);
            else if (_part == _RT)
                _instruction.opx.rt = searchRegisterNumberByName(registerName);
            else
                _instruction.opx.rd = searchRegisterNumberByName(registerName);
        }
    }
    else
    {
        std::string registerNumberStr = "";
        unsigned int registerNumber = 0;
        while (*_pointer != ' ' && *_pointer != ',' && _pointer != _layout.end() && *_pointer != '\t')
        {
            if (!(*_pointer >= '0' && *_pointer <= '9'))
            {
                std::cout << "it was found a character among the numbers that identifies the register" << std::endl;
                throw;
            }
            else
                registerNumberStr = registerNumberStr + *_pointer++;
        }
        if (registerNumberStr.empty())
        {
            std::cout << "it wasn't specified the register by a number, as expected" << std::endl;
            throw;
        }
        else
        {
            registerNumber = (unsigned int)std::stoi(registerNumberStr);
            if (!(registerNumber >= 0 && registerNumber <= 31))
            {
                std::cout << "unknown register $" << registerNumber << std::endl;
                throw;
            }
            else
            {
                if (_part == _RS)
                    _instruction.opx.rs = registerNumber;
                else if (_part == _RT)
                    _instruction.opx.rt = registerNumber;
                else
                    _instruction.opx.rd = registerNumber;
            }
        }
    }
}

void validateInstructionLayoutRemainder(const std::string &_layout, std::string::iterator &_pointer)
{
    if (*_pointer == ',' && *(_pointer + 1) == ',' && (_pointer + 1) != _layout.end())
    {
        std::cout << "sixtax error: there is comma remaining" << std::endl;
        throw;
    }
    if (_pointer != _layout.end())
        _pointer++;
    while ((*_pointer == ' ' || *_pointer == '\t') && _pointer != _layout.end())
        _pointer++;
    if (*_pointer == ',')
    {
        std::cout << "sixtax error: there is comma remaining" << std::endl;
        throw;
    }
}

void instructionByLayout(instruction &_instruction, std::string &_layout, std::string::iterator &_pointer, const instructionLayoutPart &_part)
{
    validateInstructionLayoutStr(_layout, _pointer);

    if (_part == _RS || _part == _RT || _part == _RD)
    {
        validateRegisterSintax(_layout, _pointer, _part);

        validateRegisterSpecified(_layout, _pointer, _part);

        updateRegisterOfTheInstruction(_instruction, _layout, _pointer, _part);

        validateInstructionLayoutRemainder(_layout, _pointer);
    }
    else if (_part == _SHAMT)
    {
        std::string shamtNumberStr = "";
        unsigned int shamtNumber = 0;
        while (*_pointer != ' ' && *_pointer != ',' && _pointer != _layout.end() && *_pointer != '\t')
        {
            if (!(*_pointer >= '0' && *_pointer <= '9'))
            {
                std::cout << "it was found a character among the numbers that quantifies the shift amount - shamt" << std::endl;
                throw;
            }
            else
                shamtNumberStr = shamtNumberStr + *_pointer++;
        }
        if (shamtNumberStr.empty())
        {
            std::cout << "it wasn't specified the shift amount - shamt, as expected" << std::endl;
            throw;
        }
        else
        {
            shamtNumber = (unsigned int)std::stoi(shamtNumberStr);
            if (!(shamtNumber >= 0 && shamtNumber <= 31))
            {
                std::cout << "shift amount - shamt -  must be between 0 and 31" << std::endl;
                throw;
            }
            else
            {
                _instruction.opx.shamnt = shamtNumber;
            }
        }
        validateInstructionLayoutRemainder(_layout, _pointer);
    }

    else if (_part == _IMMEDIATE)
    {
        std::string immediateNumberStr = "";
        int immediateNumber = 0;
        int mult = 1;
        while (*_pointer != ' ' && *_pointer != ',' && _pointer != _layout.end() && *_pointer != '\t')
        {
            if (!(*_pointer >= '0' && *_pointer <= '9'))
            {
                if (*_pointer == '-' && mult != -1)
                {
                    mult = -1;
                    _pointer++;
                }
                else
                {
                    std::cout << "it was found a character among the numbers that quantifies the immediate value - imm" << std::endl;
                    throw;
                }
            }
            else
                immediateNumberStr = immediateNumberStr + *_pointer++;
        }
        if (immediateNumberStr.empty())
        {
            std::cout << "it wasn't specified the immediate value - imm, as expected" << std::endl;
            throw;
        }
        else
        {
            immediateNumber = mult * std::stoi(immediateNumberStr);
            if (!(immediateNumber >= -(1 << 15) && immediateNumber <= (1 << 15) - 1))
            {
                std::cout << "immediate value - imm -  specified out of range" << std::endl;
                throw;
            }
            else
            {
                _instruction.opx.imm = immediateNumber;
            }
        }
        validateInstructionLayoutRemainder(_layout, _pointer);
    }
    else if (_part == _OFFSET)
    {
        std::string offsetNumberStr = "";
        int offsetNumber = 0;
        int mult = 1;
        while (*_pointer != ' ' && *_pointer != ',' && _pointer != _layout.end() && *_pointer != '(' && *_pointer != '\t')
        {
            if (!(*_pointer >= '0' && *_pointer <= '9'))
            {
                if (*_pointer == '-' && mult != -1)
                {
                    mult = -1;
                }
                else
                {
                    std::cout << "it was found a character among the numbers that quantifies the offset value" << std::endl;
                    throw;
                }
            }
            else
                offsetNumberStr = offsetNumberStr + *_pointer;
            _pointer += 1;
        }
        if (offsetNumberStr.empty())
        {
            std::cout << "it wasn't specified the offset value, as expected" << std::endl;
            throw;
        }
        else
        {
            offsetNumber = mult * std::stoi(offsetNumberStr);
            if (!(offsetNumber >= -(1 << 15) && offsetNumber <= (1 << 15) - 1))
            {
                std::cout << "offset value specified out of range" << std::endl;
                throw;
            }
            else
            {
                while ((*_pointer == ' ' || *_pointer == '\t') && _pointer != _layout.end())
                    _pointer++;
                if (*_pointer == '(')
                {
                    if (_pointer != _layout.end())
                    {
                        _pointer++;
                        while ((*_pointer == ' ' || *_pointer == '\t') && _pointer != _layout.end())
                            _pointer++;
                        validateRegisterSintax(_layout, _pointer, _RS);
                        validateRegisterSpecified(_layout, _pointer, _RS);
                        updateRegisterOfTheInstruction(_instruction, _layout, _pointer, _RS);
                    }
                    else
                    {
                        std::cout << "there is a bracket remaining" << std::endl;
                        throw;
                    }
                    while (*_pointer != ')' && _pointer != _layout.end())
                        _pointer++;
                    if (*_pointer != ')')
                    {
                        std::cout << "it's missing a bracket to close the offset value" << std::endl;
                        throw;
                    }
                }
                validateInstructionLayoutRemainder(_layout, _pointer);
                _instruction.opx.offset = offsetNumber;
            }
        }
    }
    else if (_part == _ADDRESS)
    {
        //it isn't implemented
    }
    else if (_part == _OP)
    {
        //it isn't implemented
    }
    //_FUNCT
    else
    {
        //it isn't implemented
    }
}

template <typename... Many>
void instructionByLayout(instruction &_instruction, std::string &_layout, std::string::iterator &_pointer, const instructionLayoutPart &_part, const Many &... _remaining)
{
    instructionByLayout(_instruction, _layout, _pointer, _part);
    instructionByLayout(_instruction, _layout, _pointer, _remaining...);
}

instruction newInstruction(std::string s)
{
    if (s.empty())
    {
        std::cout << "it's not allowed a line that it isn't a instruction" << std::endl;
        throw;
    }

    std::string::iterator p_aux = s.begin();
    std::string opcode = "";

    while ((*p_aux == ' ' || *p_aux == '\t') && p_aux != s.end())
        p_aux++;
    while ((*p_aux != ' ' && *p_aux != '\t') && p_aux != s.end())
        opcode = opcode + *p_aux++;

    trim(opcode);
    trim(opcode, '\t');

    std::string instructionLayoutStr = "";
    while ((*p_aux == ' ' || *p_aux == '\t') && p_aux != s.end())
        p_aux++;
    while (*p_aux != '#' && p_aux != s.end())
        instructionLayoutStr = instructionLayoutStr + *p_aux++;
    std::string::iterator instructionLayoutPointer = instructionLayoutStr.begin();

    instruction _instruction;

    if (!opcode.compare("add"))
    {
        _instruction.opc = ADD;
        _instruction.format = REGISTER;
        instructionByLayout(_instruction, instructionLayoutStr, instructionLayoutPointer, _RD, _RS, _RT);
    }
    else if (!opcode.compare("addi"))
    {
        _instruction.opc = ADDI;
        _instruction.format = IMMEDIATE;
        instructionByLayout(_instruction, instructionLayoutStr, instructionLayoutPointer, _RT, _RS, _IMMEDIATE);
    }
    else if (!opcode.compare("sub"))
    {
        _instruction.opc = SUB;
        _instruction.format = REGISTER;
        instructionByLayout(_instruction, instructionLayoutStr, instructionLayoutPointer, _RD, _RS, _RT);
    }
    else if (!opcode.compare("subi"))
    {
        _instruction.opc = SUBI;
        _instruction.format = IMMEDIATE;
        instructionByLayout(_instruction, instructionLayoutStr, instructionLayoutPointer, _RT, _RS, _IMMEDIATE);
    }
    else if (!opcode.compare("beq"))
    {
        _instruction.opc = BEQ;
        _instruction.format = IMMEDIATE;
        instructionByLayout(_instruction, instructionLayoutStr, instructionLayoutPointer, _RS, _RT, _OFFSET);
    }
    else if (!opcode.compare("b"))
    {
        _instruction.opc = B;
        _instruction.format = IMMEDIATE;
        instructionByLayout(_instruction, instructionLayoutStr, instructionLayoutPointer, _OFFSET);
    }
    else if (!opcode.compare("nop"))
    {
        _instruction.opc = NOP;
        _instruction.format = REGISTER;
    }
    else
    {
        if (!opcode.empty() && opcode.at(0) == '#')
        {
            std::cout << "comment is only allowed at the end of a instruction" << std::endl;
            throw;
        }
        else
        {
            std::cout << "invalid opcode found when parsing an instruction: " << opcode << std::endl;
            throw;
        }
    }

    return _instruction;
}

bool isValidRegister(unsigned int address)
{
    return address < REGISTER_QTY;
}