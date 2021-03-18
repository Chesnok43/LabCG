#include "Filter.h"
#include <QImage>
#include <cmath>
#include <algorithm>
#include <fstream>
#include <string>
#define pi 3.14159265 


template <class T>
T clamp(T value, T max, T min)
{
	if (value > max)
		return max;
	if (value < min)
		return min;
	return value;
}


QImage Filter::processIdeal(const QImage& img) const
{
	return QImage();
}

QImage Filter::processIdeal(const QImage& img)
{
	QImage result(img);
	float rMax = 0.f, gMax = 0.f, bMax = 0.f;
	for(int i=0;i<img.width();++i)
		for (int j = 0; j < img.height(); ++j)
		{
			QColor color = img.pixelColor(i, j);
			if (rMax < color.red())rMax = color.red();
			if (gMax < color.green())gMax = color.green();
			if (bMax < color.blue())bMax = color.blue();
			

		}
	for (int x = 0; x < int(img.width() / 2); ++x)
		for (int y = 0; y < img.height(); y++)
		{
			QColor colora = calcNewPixelColor(img, x, y);
			result.setPixelColor(x, y, QColor(clamp(colora.red()*255/rMax,255.f,0.f),
				clamp(colora.green() * 255 / gMax, 255.f, 0.f),
				clamp(colora.blue() * 255 / bMax, 255.f, 0.f)));
		}

	
	return result;
}

QImage Filter::processGist(const QImage& img) const
{
	return QImage();
}


QImage Filter::processGist(const QImage& img)
{
	QImage result(img);
	float rMax = 0.f, gMax = 0.f, bMax = 0.f,rMin=255.f,gMin=255.f,bMin=255.f;
	for (int i = 0; i < img.width(); ++i)
		for (int j = 0; j < img.height(); ++j)
		{
			QColor color = img.pixelColor(i, j);
			if (rMax < color.red())rMax = color.red();
			if (gMax < color.green())gMax = color.green();
			if (bMax < color.blue())bMax = color.blue();
			if (rMin > color.red())rMin = color.red();
			if (gMin > color.green())gMin = color.green();
			if (bMin > color.blue())bMin = color.blue();
			

		}
	for (int x = 0; x < int(img.width() / 2); ++x)
		for (int y = 0; y < img.height(); y++)
		{
			QColor colora = calcNewPixelColor(img, x, y);
			result.setPixelColor(x, y, QColor(clamp((colora.red() - rMin) * 255 / (rMax - rMin), 255.f, 0.f),
				clamp((colora.green() - gMin) * 255 / (gMax - gMin), 255.f, 0.f),
				clamp((colora.blue() - bMin) * 255 / (bMax - bMin), 255.f, 0.f)) );
		}
	

	return result;
}


QImage Filter::processErosion(const QImage& img) const
{
	return QImage();
}


QImage Filter::processErosion(const QImage& img)
{
	QImage result(img);
	

	std::string inFileName = "element.txt";
	std::ifstream element;
	element.open("C:\\Images\\element.txt");
	int n;
	int size=0;
	while(element>>n)size++;
	element.close();
	element.open("C:\\Images\\element.txt");
	int* data=new int[size];
	for (int i = 0; i < size; i++)
	{
		element >> data[i];

	}
	int rad = (sqrt(size) - 1) / 2;

	


	for (int x = rad; x<int(img.width() / 2); x++)
		for (int y = rad; y < img.height() - rad; y++)
		{
			int num = 0;
			float rMin = 255.f;
			float gMin = 255.f;
			float bMin = 255.f;
			for (int j = y - rad; j <= y + rad; j++)
				for (int i = x - rad; i <= x + rad; i++)
				{
					if (num < size) {
						if (data[num] )
						{
							if (img.pixelColor(i, j).red() < rMin)rMin = img.pixelColor(i, j).red();
							if (img.pixelColor(i, j).green() < gMin)gMin = img.pixelColor(i, j).green();
							if (img.pixelColor(i, j).blue() < bMin)bMin = img.pixelColor(i, j).blue();
						}
						num++;
					}
				}



			QColor color(rMin, gMin, bMin);
			result.setPixelColor(x, y, color);
		}
	delete[]data;
	return result;
}


QImage Filter::processDilation(const QImage& img) const
{
	return QImage();
}


QImage Filter::processDilation(const QImage& img)
{
	QImage result(img);


	std::string inFileName = "element.txt";
	std::ifstream element;
	element.open("C:\\Images\\element.txt");
	int n;
	int size = 0;
	while (element >> n)size++;
	element.close();
	element.open("C:\\Images\\element.txt");
	int* data = new int[size];
	for (int i = 0; i < size; i++)
	{
		element >> data[i];

	}
	int rad = (sqrt(size) - 1) / 2;
	element.close();



	for (int x = rad; x<int(img.width() / 2); x++)
		for (int y = rad; y < img.height() - rad; y++)
		{
			
			int num = 0;
			
			float rMax = 0.f;
			float gMax = 0.f;
			float bMax = 0.f;
			for (int j = y - rad; j <= y + rad; j++)
				for (int i = x - rad; i <= x + rad; i++)
				{
					if (num < size) {
						if (data[num])
						{
							if (img.pixelColor(i, j).red() > rMax)rMax = img.pixelColor(i, j).red();
							if (img.pixelColor(i, j).green() > gMax)gMax = img.pixelColor(i, j).green();
							if (img.pixelColor(i, j).blue() > bMax)bMax = img.pixelColor(i, j).blue();
						}
						num++;
					}
				}



			QColor color(rMax, gMax, bMax);
			
			result.setPixelColor(x, y, color);
		}
	delete[]data;
	return result;
}



QImage Filter::processGrad(const QImage& img) const
{
	return QImage();
}


QImage Filter::processGrad(const QImage& img)
{
	QImage result(img);


	std::string inFileName = "element.txt";
	std::ifstream element;
	element.open("C:\\Images\\element.txt");
	int n;
	int size = 0;
	while (element >> n)size++;
	element.close();
	element.open("C:\\Images\\element.txt");
	int* data = new int[size];
	for (int i = 0; i < size; i++)
	{
		element >> data[i];

	}
	int rad = (sqrt(size) - 1) / 2;
	element.close();



	for (int x = rad; x<int(img.width() / 2); x++)
		for (int y = rad; y < img.height() - rad; y++)
		{
			int num = 0;
			float rMin = 255.f;
			float gMin = 255.f;
			float bMin = 255.f;
			float rMax = 0.f;
			float gMax = 0.f;
			float bMax = 0.f;
			for (int j = y - rad; j <= y + rad; j++)
				for (int i = x - rad; i <= x + rad; i++)
				{
					if (num < size) {
						if (data[num])
						{
							if (img.pixelColor(i, j).red() < rMin)rMin = img.pixelColor(i, j).red();
							if (img.pixelColor(i, j).green() < gMin)gMin = img.pixelColor(i, j).green();
							if (img.pixelColor(i, j).blue() < bMin)bMin = img.pixelColor(i, j).blue();
							if (img.pixelColor(i, j).red() > rMax)rMax = img.pixelColor(i, j).red();
							if (img.pixelColor(i, j).green() > gMax)gMax = img.pixelColor(i, j).green();
							if (img.pixelColor(i, j).blue() > bMax)bMax = img.pixelColor(i, j).blue();
						}
						num++;
					}
				}



			//QColor color(rMin + 255.f - rMax, gMin + 255.f - gMax, bMin + 255.f - bMax);
			QColor color(rMax - rMin, gMax - gMin, bMax - bMin);
			result.setPixelColor(x, y, color);
		}
	delete[]data;
	return result;
}



QImage Filter::processClosing(const QImage& img) const
{
	return QImage();
}


QImage Filter::processClosing(const QImage& img)
{
	QImage result(img);


	std::string inFileName = "element.txt";
	std::ifstream element;
	element.open("C:\\Images\\element.txt");
	int n;
	int size = 0;
	while (element >> n)size++;
	element.close();
	element.open("C:\\Images\\element.txt");
	int* data = new int[size];
	for (int i = 0; i < size; i++)
	{
		element >> data[i];

	}
	int rad = (sqrt(size) - 1) / 2;
	element.close();



	for (int x = rad; x<int(img.width() / 2); x++)
		for (int y = rad; y < img.height() - rad; y++)
		{
			int num = 0;
			float rMax = 0.f;
			float gMax = 0.f;
			float bMax = 0.f;
			for (int j = y - rad; j <= y + rad; j++)
				for (int i = x - rad; i <= x + rad; i++)
				{
					if (num < size) {
						if (data[num])
						{
							if (img.pixelColor(i, j).red() > rMax)rMax = img.pixelColor(i, j).red();
							if (img.pixelColor(i, j).green() > gMax)gMax = img.pixelColor(i, j).green();
							if (img.pixelColor(i, j).blue() > bMax)bMax = img.pixelColor(i, j).blue();
						}
						num++;
					}
				}



			QColor color(rMax, gMax, bMax);
			result.setPixelColor(x, y, color);
		}
	QImage result1(result);
	for (int x = rad; x<int(img.width() / 2); x++)
		for (int y = rad; y < img.height() - rad; y++)
		{
			int num = 0;
			float rMin = 255.f;
			float gMin = 255.f;
			float bMin = 255.f;
			for (int j = y - rad; j <= y + rad; j++)
				for (int i = x - rad; i <= x + rad; i++)
				{
					if (num < size) {
						if (data[num])
						{
							if (result.pixelColor(i, j).red() < rMin)rMin = result.pixelColor(i, j).red();
							if (result.pixelColor(i, j).green() < gMin)gMin = result.pixelColor(i, j).green();
							if (result.pixelColor(i, j).blue() < bMin)bMin = result.pixelColor(i, j).blue();
						}
						num++;
					}
				}



			QColor color(rMin, gMin, bMin);
			result1.setPixelColor(x, y, color);
		}
	delete[]data;
	return result1;
}


QImage Filter::processOpening(const QImage& img) const
{
	return QImage();
}


QImage Filter::processOpening(const QImage& img)
{
	QImage result(img);


	std::string inFileName = "element.txt";
	std::ifstream element;
	element.open("C:\\Images\\element.txt");
	int n;
	int size = 0;
	while (element >> n)size++;
	element.close();
	element.open("C:\\Images\\element.txt");
	int* data = new int[size];
	for (int i = 0; i < size; i++)
	{
		element >> data[i];

	}
	int rad = (sqrt(size) - 1) / 2;
	element.close();



	for (int x = rad; x<int(img.width() / 2); x++)
		for (int y = rad; y < img.height() - rad; y++)
		{
			int num = 0;
			float rMin = 255.f;
			float gMin = 255.f;
			float bMin = 255.f;
			for (int j = y - rad; j <= y + rad; j++)
				for (int i = x - rad; i <= x + rad; i++)
				{
					if (num < size) {
						if (data[num])
						{
							if (img.pixelColor(i, j).red() < rMin)rMin = img.pixelColor(i, j).red();
							if (img.pixelColor(i, j).green() < gMin)gMin = img.pixelColor(i, j).green();
							if (img.pixelColor(i, j).blue() < bMin)bMin = img.pixelColor(i, j).blue();
						}
						num++;
					}
				}



			QColor color(rMin, gMin, bMin);
			result.setPixelColor(x, y, color);
		}
	QImage result1(result);
	for (int x = rad; x<int(img.width() / 2); x++)
		for (int y = rad; y < img.height() - rad; y++)
		{
			int num = 0;
			float rMax= 0.f;
			float gMax = 0.f;
			float bMax = 0.f;
			for (int j = y - rad; j <= y + rad; j++)
				for (int i = x - rad; i <= x + rad; i++)
				{
					if (num < size) {
						if (data[num])
						{
							if (result.pixelColor(i, j).red() >rMax)rMax = result.pixelColor(i, j).red();
							if (result.pixelColor(i, j).green() > gMax)gMax = result.pixelColor(i, j).green();
							if (result.pixelColor(i, j).blue() > bMax)bMax = result.pixelColor(i, j).blue();
						}
						num++;
					}
				}



			QColor color(rMax, gMax, bMax);
			result1.setPixelColor(x, y, color);
		}
	delete[]data;
	return result1;
}



QImage Filter::process(const QImage& img) const
{
	return QImage();
}


QImage Filter::process(const QImage& img)
{
	QImage result(img);

	for(int x=0;x<int(img.width() / 2);++x)
		for (int y = 0; y < img.height(); y++)
		{
			QColor color = calcNewPixelColor(img, x, y);
			result.setPixelColor(x, y, color);
		}

	return result;
}


QImage Filter::processSobel(const QImage& img) const
{
	return QImage();
}


QImage Filter::processSobel(const QImage& img)
{
	QImage result(img);
	float redX=0.f;
	float greenX = 0.f;
	float blueX = 0.f;
	float redY = 0.f;
	float greenY = 0.f;
	float blueY = 0.f;

	for (int x = 1; x < int(img.width()/2); ++x)
		for (int y = 1; y < img.height()-1; y++)
		{
			redX = img.pixelColor(x-1, y-1).red()*(-1)-2* img.pixelColor(x - 1, y ).red()- img.pixelColor(x - 1, y + 1).red()+ img.pixelColor(x + 1, y - 1).red()  + 2 * img.pixelColor(x + 1, y).red() + img.pixelColor(x + 1, y + 1).red();
			greenX = img.pixelColor(x - 1, y - 1).green() * (-1) - 2 * img.pixelColor(x - 1, y).green() - img.pixelColor(x - 1, y + 1).green() + img.pixelColor(x + 1, y - 1).green() + 2 * img.pixelColor(x + 1, y).green() + img.pixelColor(x + 1, y + 1).green();
			blueX = img.pixelColor(x - 1, y - 1).blue() * (-1) - 2 * img.pixelColor(x - 1, y).blue() - img.pixelColor(x - 1, y + 1).blue() + img.pixelColor(x + 1, y - 1).blue() + 2 * img.pixelColor(x + 1, y).blue() + img.pixelColor(x + 1, y + 1).blue();
			redY = img.pixelColor(x - 1, y - 1).red() * (-1) - 2 * img.pixelColor(x , y-1).red() - img.pixelColor(x +1, y -1 ).red() + img.pixelColor(x - 1, y + 1).red() + 2 * img.pixelColor(x , y+1).red() + img.pixelColor(x + 1, y + 1).red();
			greenY = img.pixelColor(x - 1, y - 1).green() * (-1) - 2 * img.pixelColor(x, y - 1).green() - img.pixelColor(x + 1, y - 1).green() + img.pixelColor(x - 1, y + 1).green() + 2 * img.pixelColor(x, y + 1).green() + img.pixelColor(x + 1, y + 1).green();
			blueY = img.pixelColor(x - 1, y - 1).blue() * (-1) - 2 * img.pixelColor(x, y - 1).blue() - img.pixelColor(x + 1, y - 1).blue() + img.pixelColor(x - 1, y + 1).blue() + 2 * img.pixelColor(x, y + 1).blue() + img.pixelColor(x + 1, y + 1).blue();
			QColor color(clamp(sqrt(redX*redX+redY*redY),255.f,0.f),
				clamp(sqrt(greenX*greenX+greenY*greenY), 255.f, 0.f),
				clamp(sqrt(blueX*blueX+blueY*blueY), 255.f, 0.f));
			result.setPixelColor(x, y, color);
		}

	return result;
}


QColor InvertFilter::calcNewPixelColor(const QImage& img, int x, int y)const
{
	QColor color = img.pixelColor(x, y);
	color.setRgb(255 - color.red(), 255 - color.green(), 255 - color.blue());
	return color;
}


QColor MatrixFilter::calcNewPixelColor(const QImage& img, int x, int y)const
{
	float returnR = 0;
	float returnG = 0;
	float returnB = 0;
	int size = mKernel.getSize();
	int radius = mKernel.getradius();
	for(int i=-radius;i<=radius;++i)
		for (int j = -radius; j <= radius; ++j)
		{
			int idx = (i + radius) * size + j + radius;

			QColor color = img.pixelColor(clamp(x + j, img.width() - 1, 0),
				clamp(y + i, img.height() - 1, 0));

			returnR += color.red() * mKernel[idx];
			returnG += color.green() * mKernel[idx];
			returnB += color.blue() * mKernel[idx];

		}
	return QColor(clamp(returnR, 255.f, 0.f),
		clamp(returnG, 255.f, 0.f),
		clamp(returnB, 255.f, 0.f));

}


QColor GrayScaleFilter::calcNewPixelColor(const QImage& img, int x, int y)const 
{
	QColor color = img.pixelColor(x, y);
	float intensity = 0.299 * color.red() + 0.587 * color.green() + 0.114 * color.blue();
	color.setRgb(intensity, intensity, intensity);
	return color;
}


QColor SepiaFilter::calcNewPixelColor(const QImage& img, int x, int y)const
{
	QColor color = img.pixelColor(x, y);
	float intensity = 0.299 * color.red() + 0.587 * color.green() + 0.114 * color.blue();
	float k = 50;
	return QColor(clamp(intensity+2*k,255.f,0.f),
		clamp(float(intensity+0.5*k), 255.f, 0.f),
		clamp(intensity-1*k, 255.f, 0.f));
	
}


QColor BrightFilter::calcNewPixelColor(const QImage& img, int x, int y)const
{
	QColor color = img.pixelColor(x, y);
	float k = 50;
	return QColor(clamp(color.red() + k, 255.f, 0.f),
		clamp(color.green() + k, 255.f, 0.f),
		clamp(color.blue()+k, 255.f, 0.f));
	
}


QColor PerenosFilter::calcNewPixelColor(const QImage& img, int x, int y)const
{
	if (x >= img.width() - 50) return QColor(0.f, 0.f, 0.f);
	QColor color = img.pixelColor(x + 50, y);
	
	return color;
}


QColor WaveFilter::calcNewPixelColor(const QImage& img, int x, int y) const
{
	QColor color = img.pixelColor(x, y);
	if (x > img.width() - int(20 * sin(pi * x / 30))-1) return color;
	color = img.pixelColor(x+ int(20 * sin(pi * x / 30)), y);
	return color;
}


QColor DefaultFilter::calcNewPixelColor(const QImage& img, int x, int y) const
{
	QColor color = img.pixelColor(x, y);
	return color;


}





QColor MedianFilter::calcNewPixelColor(const QImage& img, int x, int y) const
{
	const int rad = 2;
	if ((x >= rad) && (x < img.width()-rad) && (y >=rad) && (y <img.height()-rad))
	{
		float bright = 0.f;
		
		const int  size = (2 * rad + 1) * (2 * rad + 1);
		float arrR[size];
		float arrG[size];
		float arrB[size];
		int k = 0;
		int center = (size - 1) / 2;
		for (int i = x - rad; i <= x + rad; ++i)
			for (int j = y - rad; j <= y + rad; ++j)
			{
				QColor color = img.pixelColor(i, j);
				arrR[k] = color.red();
				arrG[k] = color.green();
				arrB[k] = color.blue();
				++k;
			}
		std::sort(arrR, arrR + size);
		std::sort(arrG, arrG + size);
		std::sort(arrB, arrB + size);
		return QColor(arrR[center], arrG[center], arrB[center]);
	}
	else
	{
		QColor color1 = img.pixelColor(x, y);
		return color1;
	}
}
