#include <iostream>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
using namespace std;
using namespace cv;

// 抽出する画像の輝度値の範囲を指定
#define G_MAX 100
#define G_MIN 0
#define B_MAX 100
#define B_MIN 0
#define R_MAX 255
#define R_MIN 100

// RGBの色抽出を行う関数
bool colorExtractorRGB(unsigned char data_g, 
	unsigned char data_b, unsigned char data_r)
{
	if (G_MIN <= data_g && data_g <= G_MAX) {
		if (B_MIN <= data_b && data_b <= B_MAX) {
			if (R_MIN <= data_r && data_r <= R_MAX) {
				return true;
			}
		}
	}
	return false;
}

// メイン関数
int main(void) 
{
	// 入力画像名(ファイルパス)
	string input_filename = "input.jpg";

	// 画像を3チャンネル(GBR)で読み込む
	Mat input_image_rgb = imread(input_filename, CV_LOAD_IMAGE_COLOR);
	
	if (input_image_rgb.empty()) {
		cerr << "入力画像が見つかりません" << endl;
		return -1;
	}

	// 一応表示して確認
	namedWindow("input_RGB");
	imshow("input_RGB", input_image_rgb);

	// 抽出した画像を保存するためのMatを作成
	Mat output_image_rgb = input_image_rgb.clone();

	// 特定色の抽出
	for(int y = 0; y < input_image_rgb.rows; y++){
		for(int x = 0; x < input_image_rgb.cols; x++){
			int index = y * input_image_rgb.step + x * input_image_rgb.elemSize();
			
			// ある画素が設定範囲の色に収まるかを判定
			bool range = colorExtractorRGB(input_image_rgb.data[index], 
				input_image_rgb.data[index+1], input_image_rgb.data[index+2]);
			
			// 設定範囲に収まる場合は画素をそのまま入力
			if(range == true){
				output_image_rgb.data[index] = input_image_rgb.data[index];
				output_image_rgb.data[index+1] = input_image_rgb.data[index+1];
				output_image_rgb.data[index+2] = input_image_rgb.data[index+2];
			}
			// 収まらない画素は黒にする
			else {
				output_image_rgb.data[index] = 0;
				output_image_rgb.data[index+1] = 0;
				output_image_rgb.data[index+2] = 0;
			}
		}
	}

	// 結果の表示と保存
	namedWindow("output_RGB");
	imshow("output_RGB", output_image_rgb);
	imwrite("output.jpg", output_image_rgb);
	waitKey(0);

	return 0;
}