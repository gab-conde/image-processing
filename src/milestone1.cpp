#include <iostream>
#include <fstream>
#include <string>
#include "tga.hpp"
using namespace std;

int main() {

    /* ========== Load Images ========== */
    // load car.tga
    ifstream in("input/car.tga", ios::binary);
    TGA car;
    car.ReadFile(in);
    in.close();

    // load circles.tga
    in.open("input/circles.tga");
    TGA circles;
    circles.ReadFile(in);
    in.close();

    // load layer1.tga
    in.open("input/layer1.tga");
    TGA layer1;
    layer1.ReadFile(in);
    in.close();

    // load layer2.tga
    in.open("input/layer2.tga");
    TGA layer2;
    layer2.ReadFile(in);
    in.close();

    // load layer_blue.tga
    in.open("input/layer_blue.tga");
    TGA layer_blue;
    layer_blue.ReadFile(in);
    in.close();

    // load layer_green.tga
    in.open("input/layer_green.tga");
    TGA layer_green;
    layer_green.ReadFile(in);
    in.close();

    // load layer_red.tga
    in.open("input/layer_red.tga");
    TGA layer_red;
    layer_red.ReadFile(in);
    in.close();

    // load pattern1.tga
    in.open("input/pattern1.tga");
    TGA pattern1;
    pattern1.ReadFile(in);
    in.close();

    // load pattern2.tga
    in.open("./input/pattern2.tga");
    TGA pattern2;
    pattern2.ReadFile(in);
    in.close();

    // load text.tga
    in.open("./input/text.tga");
    TGA text;
    text.ReadFile(in);
    in.close();

    // load text2.tga
    in.open("./input/text2.tga");
    TGA text2;
    text2.ReadFile(in);
    in.close();


    /* ========== Perform Operations ========== */
    // Task1
    TGA task1;
    task1.Multiply(layer1, pattern1);

    // Task 2
    TGA task2;
    task2.Subtract(car, layer2);

    // Task 3
    TGA task3a;
    task3a.Multiply(layer1, pattern2);
    TGA task3b;
    task3b.Screen(task3a, text);

    // Task 4
    TGA task4a;
    task4a.Multiply(layer2, circles);
    TGA task4b;
    task4b.Subtract(task4a, pattern2);

    // Task 5
    TGA task5;
    task5.Overlay(layer1, pattern1);

    // Task 6
    TGA task6 = car;
    task6.AddGreen(200);

    // Task 7
    TGA task7 = car;
    task7.ScaleRed(4);
    task7.ScaleBlue(0);

    // Task 8
    TGA task8b, task8g, task8r;
    task8b.CopyHeader(car);
    task8g.CopyHeader(car);
    task8r.CopyHeader(car);
    unsigned char* blue8 = car.OnlyBlue();
    unsigned char* green8 = car.OnlyGreen();
    unsigned char* red8 = car.OnlyRed();
    task8b.Combine(blue8, blue8, blue8);
    task8g.Combine(green8, green8, green8);
    task8r.Combine(red8, red8, red8);

    // Task 9
    TGA task9;
    task9.CopyHeader(layer_red);
    unsigned char* blue9 = layer_blue.OnlyBlue();
    unsigned char* green9 = layer_green.OnlyGreen();
    unsigned char* red9 = layer_red.OnlyRed();
    task9.Combine(blue9, green9, red9);

    // Task 10
    TGA task10 = text2;
    task10.Flip();
    
    /* ========== Generate Output ========== */
    // Write Task 1 to file
    ofstream out("output/part1.tga", ios::binary);
    task1.WriteFile(out);
    out.close();    

    // Write Task 2 to file
    out.open("output/part2.tga");
    task2.WriteFile(out);
    out.close();

    // Write Task 3 to file
    out.open("output/part3.tga");
    task3b.WriteFile(out);
    out.close();

    // Write Task 4 to file
    out.open("output/part4.tga");
    task4b.WriteFile(out);
    out.close();

    // Write Task 5 to file
    out.open("output/part5.tga");
    task5.WriteFile(out);
    out.close();

    // Write Task 6 to file
    out.open("output/part6.tga");
    task6.WriteFile(out);
    out.close();

    // Write Task 7 to file
    out.open("output/part7.tga");
    task7.WriteFile(out);
    out.close();

    // Write Task 8 to file
    out.open("output/part8_r.tga");
    task8r.WriteFile(out);
    out.close();
    out.open("output/part8_g.tga");
    task8g.WriteFile(out);
    out.close();
    out.open("output/part8_b.tga");
    task8b.WriteFile(out);
    out.close();

    // Write Task 9 to file
    out.open("output/part9.tga");
    task9.WriteFile(out);
    out.close();

    // Write Task 10 to file
    out.open("output/part10.tga");
    task10.WriteFile(out);
    out.close();

    return 0;
}
