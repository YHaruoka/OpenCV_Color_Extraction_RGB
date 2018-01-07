#include <iostream>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
using namespace std;
using namespace cv;

// ���o����摜�̋P�x�l�͈̔͂��w��
#define G_MAX 100
#define G_MIN 0
#define B_MAX 100
#define B_MIN 0
#define R_MAX 255
#define R_MIN 100

// RGB�̐F���o���s���֐�
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

// ���C���֐�
int main(void) 
{
	// ���͉摜��(�t�@�C���p�X)
	string input_filename = "input.jpg";

	// �摜��3�`�����l��(GBR)�œǂݍ���
	Mat input_image_rgb = imread(input_filename, CV_LOAD_IMAGE_COLOR);
	
	if (input_image_rgb.empty()) {
		cerr << "���͉摜��������܂���" << endl;
		return -1;
	}

	// �ꉞ�\�����Ċm�F
	namedWindow("input_RGB");
	imshow("input_RGB", input_image_rgb);

	// ���o�����摜��ۑ����邽�߂�Mat���쐬
	Mat output_image_rgb = input_image_rgb.clone();

	// ����F�̒��o
	for(int y = 0; y < input_image_rgb.rows; y++){
		for(int x = 0; x < input_image_rgb.cols; x++){
			int index = y * input_image_rgb.step + x * input_image_rgb.elemSize();
			
			// �����f���ݒ�͈͂̐F�Ɏ��܂邩�𔻒�
			bool range = colorExtractorRGB(input_image_rgb.data[index], 
				input_image_rgb.data[index+1], input_image_rgb.data[index+2]);
			
			// �ݒ�͈͂Ɏ��܂�ꍇ�͉�f�����̂܂ܓ���
			if(range == true){
				output_image_rgb.data[index] = input_image_rgb.data[index];
				output_image_rgb.data[index+1] = input_image_rgb.data[index+1];
				output_image_rgb.data[index+2] = input_image_rgb.data[index+2];
			}
			// ���܂�Ȃ���f�͍��ɂ���
			else {
				output_image_rgb.data[index] = 0;
				output_image_rgb.data[index+1] = 0;
				output_image_rgb.data[index+2] = 0;
			}
		}
	}

	// ���ʂ̕\���ƕۑ�
	namedWindow("output_RGB");
	imshow("output_RGB", output_image_rgb);
	imwrite("output.jpg", output_image_rgb);
	waitKey(0);

	return 0;
}