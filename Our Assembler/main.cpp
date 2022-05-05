#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <bits/stdc++.h>

using namespace std;


string BIN_to_HEX(string bin)
{
    string hex;

    if(bin == "0000")
        hex = "0";
    else if(bin == "0001")
        hex = "1";
    else if(bin == "0010")
        hex = "2";
    else if(bin == "0011")
        hex = "3";
    else if(bin == "0100")
        hex = "4";
    else if(bin == "0101")
        hex = "5";
    else if(bin == "0110")
        hex = "6";
    else if(bin == "0111")
        hex = "7";
    else if(bin == "1000")
        hex = "8";
    else if(bin == "1001")
        hex = "9";
    else if(bin == "1010")
        hex = "a";
    else if(bin == "1011")
        hex = "b";
    else if(bin == "1100")
        hex = "c";
    else if(bin == "1101")
        hex = "d";
    else if(bin == "1110")
        hex = "e";
    else if(bin == "1111")
        hex = "f";


    return hex;
}

string instruction_check(string inst)
{
    string conv_inst;
    if(inst == "add")
        conv_inst = "0000";

    else if(inst == "and")
        conv_inst = "0001";

    else if(inst == "or")
        conv_inst = "0010";

    else if(inst == "nor")
        conv_inst = "0011";

    else if(inst == "slt")
        conv_inst = "0100";

    else if(inst == "addi")
        conv_inst = "0101";

    else if(inst == "sll")
        conv_inst = "0110";

    else if(inst == "lw")
        conv_inst = "0111";

    else if(inst == "sw")
        conv_inst = "1000";

    else if(inst == "in")
        conv_inst = "1001";

    else if(inst == "out")
        conv_inst = "1010";

    else if(inst == "bne")
        conv_inst = "1011";

    else if(inst == "j")
        conv_inst = "1100";

    else if(inst == "slti")
        conv_inst = "1101";

    else if(inst == "sub")
        conv_inst = "1110";

    else
    {
        conv_inst = "invalid instruction";
    }


    return conv_inst;
}

string register_check(string reg)
{
    string conv_reg;

    if(reg == "$zero")
        conv_reg = "0000";

    else if(reg == "$spr")
        conv_reg = "0001";

    else if(reg == "$s1")
        conv_reg = "0010";

    else if(reg == "$s2")
        conv_reg = "0011";

    else if(reg == "$s3")
        conv_reg = "0100";

    else if(reg == "$s4")
        conv_reg = "0101";

    else if(reg == "$s5")
        conv_reg = "0110";

    else if(reg == "$s6")
        conv_reg = "0111";

    else if(reg == "$s7")
        conv_reg = "1000";

    else if(reg == "$t0")
        conv_reg = "1001";

    else if(reg == "$t1")
        conv_reg = "1010";

    else if(reg == "$t2")
        conv_reg = "1011";

    else if(reg == "$t3")
        conv_reg = "1100";

    else if(reg == "$t4")
        conv_reg = "1101";

    else if(reg == "$t5")
        conv_reg = "1110";

    else if(reg == "$t6")
        conv_reg = "1111";

    else
        conv_reg = "invalid register";

    return conv_reg;
}

string DEC_to_BIN(int n)
{
    if (n<0)
    {
        n = 16 + n;
    }
    string ext = "";
    string result = "";
    while(n > 0)
    {
        result = (n%2==0 ? "0" : "1")  + result;    //string(1, (char) (n%2 + 48))
        n = n/2;
    }
    for(int i = 0; i< 4-result.size(); i++ )
    {
        ext = "0" + ext;
    }
    result = ext + result;
    return result;
}

int main()
{
    string con_ins, con_rs, con_rd, con_im;
    ifstream inFile;
    inFile.open("inputs");
    ofstream outFile;
    outFile.open("outputs");

    if(inFile.fail())
    {
        cerr << "Error" << endl;
        cerr << "No input file found" << endl;
        exit(1);
    }

    int i = 0;
    string chk,ins, rd, rs, im, out;
    outFile << "v2.0 raw"<< endl;


    while(inFile>>ins)//reads the first word in input file and stores it in ins if the input file is not empty
    {

        transform(ins.begin(), ins.end(), ins.begin(), ::tolower);//converts to lower case
        if(ins == "add" || ins == "and" || ins == "or" || ins == "nor" || ins == "slt" || ins =="sub")
        {

            inFile >> rd >> rs;// reads next two words and stores the first word in rd and the second one in rs


            con_ins = instruction_check(ins);//gives binary code of instruction
            con_rd = register_check(rd);//gives binary code of rd
            con_rs = register_check(rs);////gives binary code of rs

            if(con_rd == "invalid register" || con_rs == "invalid register")
            {
                outFile << "invalid register"<< endl;
                cout << "invalid register" << endl;
                continue;
            }

            else
            {

                out = con_ins + con_rd + con_rs;//merge the binary codes to make a 12 bit instruction code
                cout << ins << endl;
                cout << out << endl;

                out = BIN_to_HEX(con_ins) + BIN_to_HEX(con_rd) + BIN_to_HEX(con_rs);/*convert to
                hexadecimal code*/

                cout << out << endl;
                outFile<< out << endl;
            }




        }
        else if(ins == "sll")
        {
            inFile >> rd >> im;// read the next word from file and store it in rd

            if(std::stoi(im)<0)// stoi function converts a string(numerical) to an integer.
            {
                outFile << "immediate value can't be negative"<< endl;
                cout<< "immediate value can't be negative" << endl;
            }


            else if(stoi(im)>16)
            {
                outFile << "immediate value out of bound"<< endl;
                cout << "immediate value out of bound" << endl;
            }


            else
            {
                con_ins = instruction_check(ins);//gives binary code of instruction
                con_rd = register_check(rd);//gives binary code of im
                con_im = DEC_to_BIN(stoi(im));//gives binary code of im

                if(con_rd == "invalid register")
                {
                    outFile << "invalid register"<< endl;
                    cout << "invalid register" << endl;
                    continue;
                }
                else
                {
                    out = con_ins + con_rd + con_im;// merges the binary codes to give 12 bit instruction code

                    cout << ins << endl;
                    cout << out << endl;

                    out = BIN_to_HEX(con_ins) + BIN_to_HEX(con_rd) + BIN_to_HEX(con_im);
                    /*convert to hexadecimal*/

                    cout << out << endl;
                    outFile<< out << endl;
                }

            }

        }
        else if(ins =="lw" || ins=="sw")
        {

            inFile >> rd >> rs;// read the next word from file and store it in rd

            con_ins = instruction_check(ins);//gives binary code of instruction
            con_rd = register_check(rd);//gives binary code of rd
            con_rs = register_check(rs);////gives binary code of rs

            if(con_rd == "invalid register" || con_rs == "invalid register")
            {
                outFile << "invalid register"<< endl;
                cout << "invalid register" << endl;
                continue;
            }

            else
            {

                out = con_ins + con_rd + con_rs;//merge the binary codes to make a 12 bit instruction code
                cout << ins << endl;
                cout << out << endl;

                out = BIN_to_HEX(con_ins) + BIN_to_HEX(con_rd) + BIN_to_HEX(con_rs);/*convert to
                hexadecimal code*/

                cout << out << endl;
                outFile<< out << endl;
            }


        }
        else if(ins == "addi" || ins == "slti")
        {
            inFile >> rd >> im;// read the next word from file and store it in rd


            if(stoi(im)>8 || stoi(im)< -8)
            {
                outFile << "immediate value out of bound"<< endl;
                cout << "immediate value out of bound" << endl;
            }


            else
            {
                con_ins = instruction_check(ins);//gives binary code of instruction
                con_rd = register_check(rd);//gives binary code of im
                con_im = DEC_to_BIN(stoi(im));//gives binary code of im

                if(con_rd == "invalid register")
                {
                    outFile << "invalid register"<< endl;
                    cout << "invalid register" << endl;
                    continue;
                }
                else
                {
                    out = con_ins + con_rd + con_im;// merges the binary codes to give 12 bit instruction code

                    cout << ins << endl;
                    cout << out << endl;

                    out = BIN_to_HEX(con_ins) + BIN_to_HEX(con_rd) + BIN_to_HEX(con_im);
                    /*convert to hexadecimal*/

                    cout << out << endl;
                    outFile<< out << endl;
                }

            }

        }
        else if(ins == "bne")
        {
            inFile >> rd >> im;// read the next word from file and store it in rd
            if(stoi(im)>8 || stoi(im)<-8)
            {
                outFile << "immediate value is out of bound"<< endl;
                cout<< "immediate value is out of bound" << endl;
            }
            else
            {
                con_ins = instruction_check(ins);//gives binary code of instruction
                con_rd = register_check(rd);//gives binary code of im
                con_im = DEC_to_BIN(stoi(im));//gives binary code of im

                if(con_rd == "invalid register")
                {
                    outFile << "invalid register"<< endl;
                    cout << "invalid register" << endl;
                    continue;
                }
                else
                {
                    out = con_ins + con_rd + con_im;// merges the binary codes to give 12 bit instruction code

                    cout << ins << endl;
                    cout << out << endl;

                    out = BIN_to_HEX(con_ins) + BIN_to_HEX(con_rd) + BIN_to_HEX(con_im);
                    /*convert to hexadecimal*/

                    cout << out << endl;
                    outFile<< out << endl;
                }

            }

        }
        else if(ins == "j")
        {
            inFile >> im;
            con_ins = instruction_check(ins);//gives binary code of instruction
            con_im = DEC_to_BIN(stoi(im));//gives binary code of im


            if(stoi(im)>8 || stoi(im)<-8)
            {
                outFile << "immediate value is out of bound"<< endl;
                cout<< "immediate value is out of bound" << endl;
            }

            else
            {
                out = con_ins + "0000" + con_im;

                cout << ins << endl;
                cout << out << endl;

                out = BIN_to_HEX(con_ins) + "0" + BIN_to_HEX(con_im);

                cout << out << endl;
                outFile<< out << endl;
            }
        }
        else if(ins == "in" || ins == "out")
        {
            inFile >> rd;

            con_ins = instruction_check(ins);
            con_rd = register_check(rd);
            if(con_rd == "invalid register")
            {
                outFile<< "invalid register" << endl;
                cout << "invalid register" << endl;
                continue;
            }
            else
            {

                out = con_ins + con_rd + "0000";

                cout << ins << endl;
                cout << out << endl;

                out = BIN_to_HEX(con_ins) + BIN_to_HEX(con_rd) + "0";

                cout << out << endl;
                outFile<< out << endl;
            }
        }
        else
        {
            outFile<< "Invalid instruction" << endl;
            cout<< "Invalid instruction" << endl;
        }

    }
    inFile.close();
    outFile.close();

}

