#pragma once
#include <QImage>
#include <QtGui/qimage.h>


class Filter
{
protected:
	virtual QColor calcNewPixelColor(const QImage& img, int x, int y) const = 0;
	
	
public:
	virtual ~Filter() = default;
	virtual QImage processIdeal(const QImage& img) const;
	QImage processIdeal(const QImage& img);
	virtual QImage processGist(const QImage& img) const;
	QImage processGist(const QImage& img);
	virtual QImage process(const QImage& img) const;
	QImage process(const QImage& img);
	virtual QImage processSobel(const QImage& img) const;
	QImage processSobel(const QImage& img);
	virtual QImage processErosion(const QImage& img) const;
	QImage processErosion(const QImage& img);
	virtual QImage processDilation(const QImage& img) const;
	QImage processDilation(const QImage& img);
	virtual QImage processClosing(const QImage& img) const;
	QImage processClosing(const QImage& img);
	virtual QImage processOpening(const QImage& img) const;
	QImage processOpening(const QImage& img);
	virtual QImage processGrad(const QImage& img) const;
	QImage processGrad(const QImage& img);

};


class InvertFilter : public Filter
{
	QColor calcNewPixelColor(const QImage& img, int x, int y) const override;
};


class Kernel
{
protected:
	std::unique_ptr<float[]>data;
	std::size_t radius;
	std::size_t getLen() const { return getSize() * getSize(); }
public:
	Kernel(std::size_t radius) : radius(radius)
	{
		data = std::make_unique<float[]>(getLen());
	}
	Kernel(const Kernel& other) : Kernel(other.radius)
	{
		std::copy(other.data.get(), other.data.get() + getLen(), data.get());
	}
	std::size_t getradius() const { return radius; }
	std::size_t getSize() const { return 2 * radius + 1; }
	float operator[](std::size_t id) const { return data[id]; }
	float& operator [] (std::size_t id) { return data[id]; }
};


class MatrixFilter : public Filter
{
protected:
	Kernel mKernel;
	QColor calcNewPixelColor(const QImage& img, int x, int y)const override;
	
public:
	MatrixFilter(const Kernel& kernel) : mKernel(kernel) {};
	virtual ~MatrixFilter() = default;
};


class BlurKernel : public Kernel
{
public:
	using Kernel::Kernel;
	BlurKernel(std::size_t radius = 2) : Kernel(radius)
	{
		for (std::size_t i = 0; i < getLen(); ++i)
			data[i] = 1.0f / getLen();
	}
};
class BlurFilter : public MatrixFilter
{
public:
	BlurFilter(std::size_t radius = 1) :MatrixFilter(BlurKernel(radius)) {}
};


class GaussianKernel : public Kernel
{
public:
	using Kernel::Kernel;
	GaussianKernel(std::size_t radius = 2, float sigma = 3.f) :Kernel(radius)
	{
		float norm = 0;
		int signed_radius = static_cast<int>(radius);
		for(int x= -signed_radius;x<=signed_radius;++x)
			for (int y = -signed_radius; y <= signed_radius; ++ y)
			{
				std::size_t idx = (x + radius) * getSize() + (y + radius);
				data[idx] = std::exp(-(x * x + y * y) / (2*sigma * sigma));
				norm += data[idx];
			}

		for (std::size_t i = 0; i < getLen(); ++i)
		{
			data[i] /= norm;
		}

	}
};


class GaussianFilter : public MatrixFilter
{
public:
	GaussianFilter(std::size_t radius = 1) :MatrixFilter(GaussianKernel(radius)) {}
};


class GrayScaleFilter : public Filter
{
	QColor calcNewPixelColor(const QImage& img, int x, int y) const override;
};


class SepiaFilter : public Filter
{
	QColor calcNewPixelColor(const QImage& img, int x, int y) const override;
};


class BrightFilter : public Filter
{
	QColor calcNewPixelColor(const QImage& img, int x, int y) const override;
};


class PerenosFilter : public Filter
{
	QColor calcNewPixelColor(const QImage& img, int x, int y) const override;
};


class WaveFilter : public Filter
{
	QColor calcNewPixelColor(const QImage& img, int x, int y) const override;
};


class MedianFilter : public Filter
{
	QColor calcNewPixelColor(const QImage& img, int x, int y) const override;
};


class DefaultFilter : public Filter
{
	QColor calcNewPixelColor(const QImage& img, int x, int y)const override;
};



class Contr1Kernel : public Kernel
{
public:
	using Kernel::Kernel;
	Contr1Kernel(std::size_t radius = 1) : Kernel(radius)
	{
		data[0] = 0.f;
		data[1] = -1.f;
		data[2] = 0.f;
		data[3] = -1.f;
		data[4] = 5.f;
		data[5] = -1.f;
		data[6] = 0.f;
		data[7] = -1.f;
		data[8] = 0.f;
	}
};
class Contr1Filter : public MatrixFilter
{
public:
	Contr1Filter(std::size_t radius = 1) :MatrixFilter(Contr1Kernel(radius)) {}
};


class Contr2Kernel : public Kernel
{
public:
	using Kernel::Kernel;
	Contr2Kernel(std::size_t radius = 1) : Kernel(radius)
	{
		data[0] = -1.f;
		data[1] = -1.f;
		data[2] = -1.f;
		data[3] = -1.f;
		data[4] = 9.f;
		data[5] = -1.f;
		data[6] = -1.f;
		data[7] = -1.f;
		data[8] = -1.f;
	}
};
class Contr2Filter : public MatrixFilter
{
public:
	Contr2Filter(std::size_t radius = 1) :MatrixFilter(Contr2Kernel(radius)) {}
};




class MotionBlurKernel : public Kernel
{
public:
	using Kernel::Kernel;
	MotionBlurKernel(std::size_t radius = 2) : Kernel(radius)
	{
		data[0] = 0.2;
		data[1] = 0;
		data[2] = 0;
		data[3] = 0;
		data[4] = 0;
		data[5] = 0;
		data[6] = 0.2;
		data[7] = 0;
		data[8] = 0;
		data[9] = 0;
		data[10] = 0;
		data[11] = 0;
		data[12] = 0.2;
		data[13] = 0;
		data[14] = 0;
		data[15] = 0;
		data[16] = 0;
		data[17] = 0;
		data[18] = 0.2;
		data[19] = 0;
		data[20] = 0;
		data[21] = 0;
		data[22] = 0;
		data[23] = 0;
		data[24] = 0.2;
		
	}
};
class MotionBlurFilter : public MatrixFilter
{
public:
	MotionBlurFilter(std::size_t radius = 2) :MatrixFilter(MotionBlurKernel(radius)) {}
};