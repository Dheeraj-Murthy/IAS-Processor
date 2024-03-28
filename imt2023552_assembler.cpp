#include <bits/stdc++.h>
using namespace std;

string MemGen(string mem) {
  int d = 0;
  for (auto i = 0; i < mem.size(); i++)
    d += (mem[i] - '0') * pow(10, mem.size() - i - 1);

  string b;
  while (d > 0) {
    b = to_string(d % 2) + b;
    d = d / 2;
  }

  if (b.size() < 12) {
    int l = b.size();
    for (int i = 0; i < 12 - l; i++)
      b = '0' + b;
  }

  return b;
}

string OpGen(string op) {

  string command;

  if (op[0] == 'A') // ADD
  {
    command = "00000100";
    string x(op.begin() + 7, op.begin() + 10);
    command += MemGen(x);
  } else if (op[0] == 'C') // CJUMP
  {
    command = "00001001";
    string x(op.begin() + 7, op.begin() + 10);
    command += MemGen(x);
  } else if (op[0] == 'D') {
    if (op[2] == 'V') // DIV
    {
      command = "00000111";
      string x(op.begin() + 7, op.begin() + 10);
      command += MemGen(x);
    } else // DISP
    {
      command = "00001101";
      string x(op.begin() + 7, op.begin() + 10);
      command += MemGen(x);
    }
  } else if (op[0] == 'E') {
    if (op[1] == 'Q') // EQUA
    {
      command = "00001010";
      string x(op.begin() + 7, op.begin() + 10);
      command += MemGen(x);
    } else // END
    {
      command = "00001110";
      for (int i = 0; i < 12; i++)
        command += "0";
    }
  } else if (op[0] == 'J') // JUMP
  {
    command = "00001000";
    string x(op.begin() + 7, op.begin() + 10);
    command += MemGen(x);
  } else if (op[0] == 'L') {
    if (op[1] == 'E') // LESS
    {
      command = "00001011";
      string x(op.begin() + 7, op.begin() + 10);
      command += MemGen(x);
    } else if (op[6] == 'Q') // LOAD MQ
    {
      command = "00000010";
      string x(op.begin() + 7, op.begin() + 10);
      command += MemGen(x);
    } else // LOAD
    {
      command = "00000001";
      string x(op.begin() + 7, op.begin() + 10);
      command += MemGen(x);
    }
  } else if (op[0] == 'M') {
    if (op[1] == 'U') // MUL
    {
      command = "00000110";
      string x(op.begin() + 7, op.begin() + 10);
      command += MemGen(x);
    } else // MORE
    {
      command = "00001100";
      string x(op.begin() + 7, op.begin() + 10);
      command += MemGen(x);
    }
  } else if (op[0] == 'N') // NOP
  {
    for (int i = 0; i < 20; i++)
      command += "0";
  } else if (op[0] == 'S') {
    if (op[1] == 'T') // STOR
    {
      command = "00000011";
      string x(op.begin() + 7, op.begin() + 10);
      command += MemGen(x);
    } else // SUB
    {
      command = "00000101";
      string x(op.begin() + 7, op.begin() + 10);
      command += MemGen(x);
    }
  } else {
    string x(op.begin(), op.begin()+10);
    command = MemGen(x);
    for (int i = 0; i < 8; i++)
      command = '0' + command;
  }
  return command;
}

stringstream main1() {
  string asmbl;
  stringstream byte_code;
  string line;

  while (getline(cin, line))
  {
    if (line.empty())
      break;
    asmbl += line + '\n';
  }

  stringstream str(asmbl);
  string com;

  while (getline(str, com))
  {
    string l(com.begin(), com.begin() + 10);
    string r(com.begin() + 10, com.end());

    byte_code << OpGen(l) + OpGen(r) + '\n';
  }
  cout << byte_code.str() << endl;
  return byte_code;
  
}