/*
Image processing: ppm image
Read file, write file, struct
Author: 11231720 陳妍芸
Date:      /    /
*/

#include<iostream>
#include<fstream>
using namespace std;

#define HIGHT 2005
#define WIDTH 2005

/**********************************************************************
宣告自定函式原型(PROTOTYPE)
***********************************************************************/
void openfile();       //開檔
void readimage();      //讀出影像檔
void duplicate();      //影像複製
void gray();           //影像灰階
void negative();
void lightred();
void mosaic();
void onecolor_R();
void mean_filter();
void gaussian();
void sharpen();
void glitch();
void writeimage();     //寫入影像檔
void closefile();      //關檔
void choose_filter();
void choose_image();


/**********************************************************************
自訂像素結構
***********************************************************************/
struct PIXEL
{
    int R;
    int G;
    int B;

};


/**********************************************************************
宣告所需變數 (全域變數 - 可用於所有的函式)
***********************************************************************/
PIXEL image1[HIGHT][WIDTH];      //記錄原始影像
PIXEL image2[HIGHT][WIDTH];      //記錄處理後影像

ifstream fin;    //記錄輸入檔案流
ofstream fout;   //記錄輸出檔案流

string infile;
string outfile;
string file_str;

string type;    //記錄影像形態 p3,p5,p6
//char type[5];
int row, col;   //記錄影像大小
int mode;       //記錄色彩模型 255為 0-255，指256色


/**********************************************************************
主程式
***********************************************************************/
int main()
{
    cout << "*** Welcome to wonderful filter world ***" << endl << endl;
    choose_image();
    //開檔
    openfile();
    //讀檔
    readimage();

    //Image processing 這裡妳可以替換影像處理功能
    choose_filter();



    //寫檔
    writeimage();
    //關檔
    closefile();

    return 0;
}


/**********************************************************************
 以下定義各個任務功能模組
***********************************************************************/
void choose_image(){
    int select1;
    cout << "============================" << endl;
    cout << "Please choose a image ~" << endl;
    cout << "----------------------------" << endl;
    cout << "1. cinderella." << endl;
    cout << "2. jasmin." << endl;
    cout << "3. little mermaid." << endl;
    cout << "4. aurora." << endl;
    cout << "5. rapunzel." << endl;
    cout << "============================" << endl;

    cin >> select1;

    switch(select1){
    case 1:
        file_str = "cinderella";
        infile = file_str + ".ppm";
        break;
    case 2:
        file_str = "jasmin";
        infile = file_str + ".ppm";
        break;
    case 3:
        file_str = "little mermaid";
        infile = file_str + ".ppm";
        break;
    case 4:
        file_str = "aurora";
        infile = file_str + ".ppm";
        break;
    case 5:
        file_str = "rapunzel";
        infile = file_str + ".ppm";
        break;
    default:
        cout << "File not found..." << endl;
        choose_image();
    }
    return;
}

void openfile()
{
    //char infile[20];
    //string infile;
    //cout << "Input your filename (ex: original.ppm, lena.ppm... ):";
    //cin >> infile;

    fin.open(infile, ios::in); //open input file   ex: original.ppm, lena.ppm,.....

    if(!fin)
    {
        cout<<"Fail to open file: "<<endl;
    }
}



//讀檔案
void readimage()
{
    fin >> type;
    fin >> col >> row;
    fin >> mode;

    for (int i=0; i<row; i++)
        for (int j=0; j<col; j++)
            fin >> image1[i][j].R >> image1[i][j].G >> image1[i][j].B ;

    cout << "Image size:" << col << " x "  << row << endl;
    cout << "Read Image Successfully!" << endl;
}

void choose_filter(){
    int select2;
    cout << endl;
    cout << "=============================" << endl;
    cout << "Choose a filter ~~" << endl;
    cout << "-----------------------------" << endl;
    cout << "0. End." << endl;
    cout << "1. Duplicate." << endl;
    cout << "2. Gray." << endl;
    cout << "3. Negative." << endl;
    cout << "4. LightRed." << endl;
    cout << "5. Mosaic." << endl;
    cout << "6. OneColor." << endl;
    cout << "7. Mean." << endl;
    cout << "8. Gaussian." << endl;
    cout << "9. Sharpen." << endl;
    cout << "10. Glitch." << endl;
    cout << "=============================" << endl;

    cin >> select2;
    switch(select2){
    case 0:
        cout << "Thank you for using this program!!!" << endl;
        cout << "See you next time ~~ByeBye~~" << endl;
        exit(0);
    case 1:
        duplicate();
        outfile = file_str + "_duplicate.ppm";
        break;
    case 2:
        gray();
        outfile = file_str + "_gray.ppm";
        break;
    case 3:
        negative();
        outfile = file_str + "_negative.ppm";
        break;
    case 4:
        lightred();
        outfile = file_str + "_lightred.ppm";
        break;
    case 5:
        mosaic();
        outfile = file_str + "_mosaic.ppm";
        break;
    case 6:
        onecolor_R();
        outfile = file_str + "_onecolor.ppm";
        break;
    case 7:
        mean_filter();
        outfile = file_str + "_mean.ppm";
        break;
    case 8:
        gaussian();
        outfile = file_str + "_gaussian.ppm";
        break;
    case 9:
        sharpen();
        outfile = file_str + "_sharpen.ppm";
        break;
    case 10:
        glitch();
        outfile = file_str + "_glitch.ppm";
        break;
    default:
        cout << "Please choose a right number for filter" << endl;
        choose_filter();
    }

    return;
}


//複製 Copy
void duplicate()
{
    cout << "Image copying..."  << endl;

    for (int i = 0; i < row; i++){
        for (int j = 0; j < col; j++){
            image2[i][j].R = image1[i][j].R;
            image2[i][j].G = image1[i][j].G;
            image2[i][j].B = image1[i][j].B;
        }
    }
    return;
}


//灰階化
void gray()
{
    cout << "Image graying..."  << endl;

    for(int i = 0; i < row; i++){
        for (int j = 0; j < col; j++){
            int gray = (image1[i][j].R*0.299+image1[i][j].G*0.587+image1[i][j].B*0.114);
            image2[i][j].R = image2[i][j].G = image2[i][j].B = gray;
        }
    }
    return;
}

void negative()
{
    cout << "Image negativing..."  << endl;

    for (int i = 0; i < row; i++){
        for (int j = 0; j < col; j++){
            image2[i][j].R = 225 - image1[i][j].R;
            image2[i][j].G = 225 - image1[i][j].G;
            image2[i][j].B = 225 - image1[i][j].B;
        }
    }
    return;
}

void lightred()
{
    cout << "Image LightReding..."  << endl;

    for (int i = 0; i < row; i++){
        for (int j = 0; j < col; j++){
            image2[i][j].R = image1[i][j].R*1.5;
            image2[i][j].G = image1[i][j].G;
            image2[i][j].B = image1[i][j].B;

            if (image2[i][j].R > 255)
                image2[i][j].R = 255;
        }
    }
    return;
}

void mosaic()
{
    cout << "Image Mosaicing..."  << endl;
    int k = 10;
    for (int i = 0; i < row; i+= k){
        for (int j = 0; j < col; j+= k){
            for (int a = 0; a < k; a++){
                for (int b = 0; b < k; b++){
                    image2[i+a][j+b].R = image1[i][j].R;
                    image2[i+a][j+b].G = image1[i][j].G;
                    image2[i+a][j+b].B = image1[i][j].B;
                }
            }
        }
    }
    return;
}

void onecolor_R()
{
    cout << "Image OneColoring..."  << endl;

    for (int i = 0; i < row; i++){
        for (int j = 0; j < col; j++){
            int gray = (image1[i][j].R*0.299+image1[i][j].G*0.587+image1[i][j].B*0.114);
            image2[i][j].R = gray;
            image2[i][j].G = 0;
            image2[i][j].B = 0;
        }
    }
    return;
}
void glitch()
{
    cout << "Image Glitching..."  << endl;

    for (int i = 1; i < row-1; i++){
        for (int j = 1; j < col-1; j++){
            image2[i][j].R = image1[i][j-1].R;
            image2[i][j].G = image1[i][j].G;
            image2[i][j].B = image1[i][j+1].B;
        }
    }
    return;
}

void mean_filter()
{
    cout << "Image meaning..."  << endl;
    int m_kernel5[5][5]= {{1,1,1,1,1},{1,1,1,1,1},{1,1,1,1,1},{1,1,1,1,1},{1,1,1,1,1}};
    for (int i = 0; i < row; i++){
        for (int j = 0; j < col; j++){
            image2[i][j].R = image1[i][j].R;
            image2[i][j].G = image1[i][j].G;
            image2[i][j].B = image1[i][j].B;
        }
    }

    for(int i = 2; i < row-2; i++){
        for(int j = 2; j < col-2; j++){
            int sum_R = 0;
            for(int p = -2; p < 3; p++)
                for(int q = -2; q < 3; q++)
                    sum_R += image1[i+p][j+q].R* m_kernel5[p+2][q+2];
            image2[i][j].R = sum_R/25;
            int sum_G = 0;
            for(int p = -2; p < 3; p++)
                for(int q = -2; q < 3; q++)
                    sum_G += image1[i+p][j+q].G* m_kernel5[p+2][q+2];
            image2[i][j].G = sum_G/25;
            int sum_B = 0;
            for(int p = -2; p < 3; p++)
                for(int q = -2; q < 3; q++)
                    sum_B += image1[i+p][j+q].B* m_kernel5[p+2][q+2];
            image2[i][j].B = sum_B/25;
        }
    }

    return;
}

void gaussian()
{
    cout << "Image gaussianing..."  << endl;
    int g_kernel5[5][5]= {{1,4,7,4,1},{4,16,26,16,4},{7,26,41,26,7},{4,16,26,16,4},{1,4,7,4,1}};
    for (int i = 0; i < row; i++){
        for (int j = 0; j < col; j++){
            image2[i][j].R = image1[i][j].R;
            image2[i][j].G = image1[i][j].G;
            image2[i][j].B = image1[i][j].B;
        }
    }

    for(int i = 2; i < row-2; i++){
        for(int j = 2; j < col-2; j++){
            int sum_R = 0;
            for(int p = -2; p < 3; p++)
                for(int q = -2; q < 3; q++)
                    sum_R += image1[i+p][j+q].R*g_kernel5[p+2][q+2];
            image2[i][j].R = sum_R/273;
            int sum_G = 0;
            for(int p = -2; p < 3; p++)
                for(int q = -2; q < 3; q++)
                    sum_G += image1[i+p][j+q].G*g_kernel5[p+2][q+2];
            image2[i][j].G = sum_G/273;
            int sum_B = 0;
            for(int p = -2; p < 3; p++)
                for(int q = -2; q < 3; q++)
                    sum_B += image1[i+p][j+q].B*g_kernel5[p+2][q+2];
            image2[i][j].B = sum_B/273;
        }
    }

    return;
}

void sharpen()
{
    cout << "Image sharpening..."  << endl;

    // 銳化用的 3x3 遮罩
    int sharpen_kernel[3][3] = {{0, -1, 0},{-1, 5, -1},{0, -1, 0}};

    // 原圖複製到 image2（保留邊界）
    for (int i = 0; i < row; i++)
        for (int j = 0; j < col; j++)
            image2[i][j] = image1[i][j];

    // 從第1行/列到倒數第2行/列（因為是 3x3 遮罩）
    for (int i = 1; i < row - 1; i++) {
        for (int j = 1; j < col - 1; j++) {

            int sum_R = 0, sum_G = 0, sum_B = 0;

            for (int p = -1; p <= 1; p++) {
                for (int q = -1; q <= 1; q++) {
                    int weight = sharpen_kernel[p + 1][q + 1];
                    sum_R += image1[i + p][j + q].R * weight;
                    sum_G += image1[i + p][j + q].G * weight;
                    sum_B += image1[i + p][j + q].B * weight;
                }
            }

            // 限制結果在 0~255 範圍
            image2[i][j].R = min(255, max(0, sum_R));
            image2[i][j].G = min(255, max(0, sum_G));
            image2[i][j].B = min(255, max(0, sum_B));
        }
    }
}

//寫入檔案
void writeimage()
{
    //char outfile[20];
    //string outfile;
    //cout << "Input your  Output filename (ex: original_gray.ppm, lena_gray.ppm... ):";
    //cin >> outfile;             // ex: original_gray.ppm, lena_gray.ppm

    fout.open(outfile, ios::out); //open output file
    fout << type << endl;
    fout << col << " " << row << endl;
    fout << mode << endl;

    for (int i=0; i<row; i++)
    {
        for (int j=0; j<col; j++)
            fout << image2[i][j].R << " " << image2[i][j].G << " " << image2[i][j].B << " ";
        fout << endl;
    }

    cout << "Write Image Successfully!!"  << endl;

}

//關閉檔案
void closefile()
{
    fin.close();     //close input file
    fout.close();    //close output file

}
