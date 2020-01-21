//
// Bitmap.cpp for bomberman in /home/liron_b/rendu/cpp_bomberman/map
// 
// Made by liron_b
// Login   <liron_b@epitech.net>
// 
// Started on  Sat May 24 14:24:08 2014 liron_b
// Last update Thu Jun 12 11:25:29 2014 liron_b
//

#include	<string>
#include	<iostream>
#include	<fstream>
#include	<stdexcept>

#include	"Bitmap.hh"

#define	ABS(x)	((x) >= 0 ? (x) : (x) * -1)

Bitmap::Bitmap()
{}

Bitmap::~Bitmap()
{}

//  Renversement de l'ordre des couleurs dans chaque pixel pour une image 32 bits xbgr.
void	Bitmap::_xbgrToBgra()
{
  char	red;
  char	green;
  char	blue;
  char	alpha;
  int	i;

  i = 0;
  while (i < this->_width * this->_height * 4)
    {
      alpha = 0xFF;
      blue = this->_data[i + 1];
      green = this->_data[i + 2];
      red = this->_data[i + 3];

      this->_data[i] = blue;
      this->_data[i + 1] = green;
      this->_data[i + 2] = red;
      this->_data[i + 3] = alpha;

      i += 4;
    }
}

void				Bitmap::_reverseBitmap(int lineSize, int height)
{
  std::vector<unsigned char>	dest;
  int				y;

  dest.resize(this->_data.size());
  y = 0;
  while (y < this->_height)
    {
      std::copy(this->_data.data() + (height - y - 1) * lineSize,
		this->_data.data() + (height - y) * lineSize,
		dest.data() + y * lineSize);
      y++;
    }
  this->_data = dest;
}
//  Renversement vertical de l'image

void	Bitmap::_convertBitmap(int compression)
{
  if (compression != BI_RGB)
    this->_xbgrToBgra();
  this->_reverseBitmap(4 * this->_width, this->_height);
}

bool		Bitmap::_loadBitmap(const char *name, int& compression)
{
  std::ifstream	file(name);
  int		size;
  BmpHeader	bmpHeader;
  BmpInfoHeader	bmpInfo;

  if (!file)
    {
      std::cerr << "Could not open file " << name << std::endl;
      return (false);
    }

  file.read(reinterpret_cast<char*>(&bmpHeader), sizeof(BmpHeader));
  file.read(reinterpret_cast<char*>(&bmpInfo), sizeof(BmpInfoHeader));

  if (!file || bmpHeader.magic != BM_MAGIC)
    {
      std::cerr << "The file " << name << " isn't a bitmap." << std::endl;
      return (false);
    }
  if (bmpInfo.bpp != 32)
    {
      std::cerr << "The file " << name << " must have 32 bits per pixels." << std::endl;
      return (false);
    }
  if (bmpInfo.compression == BI_RGB || bmpInfo.compression == BI_BITFIELDS)
    compression = bmpInfo.compression;
  else
    {
      std::cerr << "The compression of file " << name << " isn't supported." << std::endl;
      return (false);
    }

  this->_width = bmpInfo.width;
  this->_height = ABS(bmpInfo.height);
  size = bmpHeader.size - bmpHeader.offset;

  this->_data.resize(size);
  file.seekg(bmpHeader.offset);
  file.read(reinterpret_cast<char*>(this->_data.data()), size);
  if (!file)
    {
      std::cerr << "Could not read file " << name << std::endl;
      return (false);
    }
  return (true);
}

bool	Bitmap::openBitmap(const char* name)
{
  int	compression;

  if (this->_loadBitmap(name, compression) == false)
    return (false);
  this->_convertBitmap(compression);
  return (true);
}

bool	Bitmap::openBitmap(const std::string& name)
{
  return (this->openBitmap(name.c_str()));
}

int	Bitmap::getWidth() const
{
  return (this->_width);
}

int	Bitmap::getHeight() const
{
  return (this->_height);
}

Color		Bitmap::operator[](int idx) const
{
  unsigned char	r;
  unsigned char	g;
  unsigned char	b;
  unsigned char	a;

  b = this->_data[idx * 4];
  g = this->_data[idx * 4 + 1];
  r = this->_data[idx * 4 + 2];
  a = this->_data[idx * 4 + 3];

  return (Color(r, g, b, a, Color::RGB));
}
