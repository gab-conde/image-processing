#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include "tga.hpp"
using namespace std;

int main(int argc, const char** argv) {

    // if no arguments entered or --help argument entered, print help message
    if (argc < 2 || string(argv[1]) == "--help") {
        cout << "Project 2: Image Processing, Summer 2023" << endl;
        cout << endl;
        cout << "Usage:" << endl;
        cout << "\t./project2.out [output] [firstImage] [method] [...]" << endl;
    }
    else {
      
        try {

            /* ========== Identify Output Destination ========== */
            int nextArg = 1;
            ofstream out;
            // store output file path
            string output = string(argv[nextArg]);
            // validate the file name
            if (output.size() < 5) {
                throw runtime_error("Invalid file name.");
            }
            if (output.substr(output.size() - 4, 4) != ".tga") {
                cout << "hello" << endl;
                throw runtime_error("Invalid file name.");
            }
            // validate input file path
            if (output.substr(0, 7) == "output/") {
                out.open(output, ios::binary);
            }
            else {
                out.open("output/" + output, ios::binary);
            }
            nextArg++;
            

            /* ========== Identify Input Source ========== */
            ifstream in;
            // if no more arguments provided, print error message
            if (nextArg == argc) {
                throw runtime_error("Invalid file name.");
            }
            // store input file path
            string input = string(argv[nextArg]);
            // check file extension
            if (input.substr(input.size() - 4, 4) != ".tga" || input.size() < 5) {
                throw runtime_error("Invalid file name.");
            }
            // validate input file path
            if (input.find("input/") != string::npos) {
                in.open(input, ios::binary);
            }
            else {
                in.open("input/" + input, ios::binary);
            }
            // if input did not open, the file does not exist
            if (!in.is_open()) {
                throw runtime_error("File does not exist.");
            }
            nextArg++;
            // once input path is validated, load input
            TGA img;
            img.ReadFile(in);
            in.close();


            /* ========== Execute Methods ========== */
            string method;
            bool isValid = false;
            // loop until end of argv is reached
            while (nextArg < argc) {
                // if searching for first method and no more arguments provided, print error message
                if (argc == 3) {
                    throw runtime_error("Invalid method name.");
                }
                // store next method
                method = string(argv[nextArg]);
                nextArg++;
                // check that method is valid
                // if it is, execute method
                // if not, print error message
                if (method == "multiply") {
                    // store input file path
                    string other = string(argv[nextArg]);
                    // check file extension
                    if (other.substr(other.size() - 4, 4) != ".tga" || other.size() < 5) {
                        throw runtime_error("Invalid argument, invalid file name.");
                    }
                    // validate input file path
                    if (other.find("input/") != string::npos) {
                        in.open(other, ios::binary);
                    }
                    else {
                        in.open("input/" + other, ios::binary);
                    }
                    // if input did not open, the file does not exist
                    if (!in.is_open()) {
                        throw runtime_error("Invalid argument, file does not exist.");
                    }
                    nextArg++;
                    // once input path is validated, load input
                    TGA img2, temp;
                    img2.ReadFile(in);
                    in.close();
                    temp.Multiply(img, img2);
                    img = temp;
                }
                else if (method == "subtract") {
                    // store input file path
                    string other = string(argv[nextArg]);
                    // check file extension
                    if (other.substr(other.size() - 4, 4) != ".tga" || other.size() < 5) {
                        throw runtime_error("Invalid argument, invalid file name.");
                    }
                    // validate input file path
                    if (other.find("input/") != string::npos) {
                        in.open(other, ios::binary);
                    }
                    else {
                        in.open("input/" + other, ios::binary);
                    }
                    // if input did not open, the file does not exist
                    if (!in.is_open()) {
                        throw runtime_error("Invalid argument, file does not exist.");
                    }
                    nextArg++;
                    // once input path is validated, load input
                    TGA img2, temp;
                    img2.ReadFile(in);
                    in.close();
                    temp.Subtract(img, img2);
                    img = temp;
                }
                else if (method == "overlay") {
                    // store input file path
                    string other = string(argv[nextArg]);
                    // check file extension
                    if (other.substr(other.size() - 4, 4) != ".tga" || other.size() < 5) {
                        throw runtime_error("Invalid argument, invalid file name.");
                    }
                    // validate input file path
                    if (other.find("input/") != string::npos) {
                        in.open(other, ios::binary);
                    }
                    else {
                        in.open("input/" + other, ios::binary);
                    }
                    // if input did not open, the file does not exist
                    if (!in.is_open()) {
                        throw runtime_error("Invalid argument, file does not exist.");
                    }
                    nextArg++;
                    // once input path is validated, load input
                    TGA img2, temp;
                    img2.ReadFile(in);
                    in.close();
                    temp.Overlay(img, img2);
                    img = temp;
                }
                else if (method == "screen") {
                    // store input file path
                    string other = string(argv[nextArg]);
                    // check file extension
                    if (other.substr(other.size() - 4, 4) != ".tga" || other.size() < 5) {
                        throw runtime_error("Invalid argument, invalid file name.");
                    }
                    // validate input file path
                    if (other.find("input/") != string::npos) {
                        in.open(other, ios::binary);
                    }
                    else {
                        in.open("input/" + other, ios::binary);
                    }
                    // if input did not open, the file does not exist
                    if (!in.is_open()) {
                        throw runtime_error("Invalid argument, file does not exist.");
                    }
                    nextArg++;
                    // once input path is validated, load input
                    TGA img2, temp;
                    img2.ReadFile(in);
                    in.close();
                    temp.Screen(img2, img);
                    img = temp;
                }
                else if (method == "combine") {
                    // if searching for first method and no more arguments provided, print error message
                    if (nextArg == argc) {
                        throw runtime_error("Missing argument.");
                    }
                    //store input for green channel
                    string green = string(argv[nextArg]);
                    // check file extension
                    if (green.substr(green.size() - 4, 4) != ".tga" || green.size() < 5) {
                        throw runtime_error("Invalid argument, invalid file name.");
                    }
                    // validate input file path
                    if (green.find("input/") != string::npos) {
                        in.open(green, ios::binary);
                    }
                    else {
                        in.open("input/" + green, ios::binary);
                    }
                    // if input did not open, the file does not exist
                    if (!in.is_open()) {
                        throw runtime_error("Invalid argument, file does not exist.");
                    }
                    nextArg++;
                    TGA gc;
                    gc.ReadFile(in);
                    in.close();
                    // if searching for first method and no more arguments provided, print error message
                    if (nextArg == argc) {
                        throw runtime_error("Missing argument.");
                    }
                    //store input for blue channel
                    string blue = string(argv[nextArg]);
                    // check file extension
                    if (blue.substr(blue.size() - 4, 4) != ".tga" || blue.size() < 5) {
                        throw runtime_error("Invalid argument, invalid file name.");
                    }
                    // validate input file path
                    if (blue.find("input/") != string::npos) {
                        in.open(blue, ios::binary);
                    }
                    else {
                        in.open("input/" + blue, ios::binary);
                    }
                    // if input did not open, the file does not exist
                    if (!in.is_open()) {
                        throw runtime_error("Invalid argument, file does not exist.");
                    }
                    nextArg++;
                    TGA bc;
                    bc.ReadFile(in);
                    in.close();
                    unsigned char* pbc = bc.OnlyBlue();
                    unsigned char* pgc = gc.OnlyGreen();
                    unsigned char* prc = img.OnlyRed();
                    TGA temp;
                    temp.CopyHeader(img);
                    temp.Combine(pbc, pgc, prc);
                    img = temp;
                }
                else if (method == "flip") {
                    img.Flip();
                }
                else if (method == "onlyred") {
                    TGA temp;
                    // grab red channel from img
                    unsigned char* red = img.OnlyRed();
                    // copy header from img
                    temp.CopyHeader(img);
                    // produce TGA using only red channel
                    temp.Combine(red, red, red);
                    img = temp;
                }
                else if (method == "onlygreen") {
                    TGA temp;
                    // grab green channel from img
                    unsigned char* green = img.OnlyGreen();
                    // copy header from img
                    temp.CopyHeader(img);
                    // produce TGA using only green channel
                    temp.Combine(green, green, green);
                    img = temp;
                }
                else if (method == "onlyblue") {
                    TGA temp;
                    // grab blue channel from img
                    unsigned char* blue = img.OnlyBlue();
                    // copy header from img
                    temp.CopyHeader(img);
                    // produce TGA using only blue channel
                    temp.Combine(blue, blue, blue);
                    img = temp;
                }
                else if (method == "addred") {
                    // if no more arguments provided, print error message
                    if (nextArg == argc) {
                        throw runtime_error("Missing argument.");
                    }
                    // convert input to numeric type
                    int amount = stoi(string(argv[nextArg]));
                    nextArg++;
                    // add red to img
                    img.AddRed(amount);
                }
                else if (method == "addgreen") {
                    // if no more arguments provided, print error message
                    if (nextArg == argc) {
                        throw runtime_error("Missing argument.");
                    }
                    // convert input to numeric type
                    short amount = stoi(string(argv[nextArg]));
                    nextArg++;
                    // add green to img
                    img.AddGreen(amount);
                }
                else if (method == "addblue") {
                    // if no more arguments provided, print error message
                    if (nextArg == argc) {
                        throw runtime_error("Missing argument.");
                    }
                    // convert input to numeric type
                    short amount = stoi(string(argv[nextArg]));
                    nextArg++;
                    // add blue to img
                    img.AddBlue(amount);
                }
                else if (method == "scalered") {
                    // if no more arguments provided, print error message
                    if (nextArg == argc) {
                        throw runtime_error("Missing argument.");
                    }
                    // convert input to numeric type
                    short amount = stoi(string(argv[nextArg]));
                    nextArg++;
                    // scale red channel
                    img.ScaleRed(amount);
                }
                else if (method == "scalegreen") {
                    // if no more arguments provided, print error message
                    if (nextArg == argc) {
                        throw runtime_error("Missing argument.");
                    }
                    // convert input to numeric type
                    short amount = stoi(string(argv[nextArg]));
                    nextArg++;
                    // scale green channel
                    img.ScaleGreen(amount);
                }
                else if (method == "scaleblue") {
                    // if no more arguments provided, print error message
                    if (nextArg == argc) {
                        throw runtime_error("Missing argument.");
                    }
                    // convert input to numeric type
                    short amount = stoi(string(argv[nextArg]));
                    nextArg++;
                    // scale blue channel
                    img.ScaleBlue(amount);
                }
                else {
                    throw runtime_error("Invalid method name.");
                }
            }


            /* ========== Write Final Image ========== */
            img.WriteFile(out);
            out.close();
        }
        // handle exceptions
        catch (runtime_error& e) {
            cout << e.what() << endl;
        }
        catch (invalid_argument& e) {
            cout << "Invalid argument, expected number." << endl;
        }
        catch (logic_error& e) {
            cout << "Missing argument." << endl;
        }
    }
    
    return 0;
}
