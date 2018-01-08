#include <iostream>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
using namespace std;
using namespace cv;

// ���o����摜�̋P�x�l�͈̔͂��w��
#define B_MAX 100
#define B_MIN 0
#define G_MAX 100
#define G_MIN 0
#define R_MAX 255
#define R_MIN 100

// ���C���֐�
int main(void)
{
	// ���͉摜��(�t�@�C���p�X)
	string input_filename = "input.jpg";

	// �摜��3�`�����l��(BGR)�œǂݍ���
	Mat input_image_rgb = imread(input_filename, CV_LOAD_IMAGE_COLOR);
	if (input_image_rgb.empty()) {
		cerr << "���͉摜��������܂���" << endl;
		return -1;
	}

	// �\�����Ċm�F
	namedWindow("input_RGB");
	imshow("input_RGB", input_image_rgb);

	// ���ʕۑ��pMat���`
	Mat mask_image, output_image_rgb;

	// inRange��p���ăt�B���^�����O
	Scalar s_min = Scalar(B_MIN, G_MIN, R_MIN);
	Scalar s_max = Scalar(B_MAX, G_MAX, R_MAX);
	inRange(input_image_rgb, s_min, s_max, mask_image);

	// �}�X�N�摜��\��
	namedWindow("mask");
	imshow("mask", mask_image);
	imwrite("mask.jpg", mask_image);

	// �}�X�N����ɓ��͉摜���t�B���^�����O
	input_image_rgb.copyTo(output_image_rgb, mask_image);

	// ���ʂ̕\���ƕۑ�
	namedWindow("output");
	imshow("output", output_image_rgb);
	imwrite("output.jpg", output_image_rgb);
	waitKey(0);

	return 0;
}