//
// Bitmap.hh for bomberman in /home/liron_b/rendu/cpp_bomberman/map
// 
// Made by liron_b
// Login   <liron_b@epitech.net>
// 
// Started on  Mon May 19 11:42:02 2014 liron_b
// Last update Sat May 24 14:23:51 2014 liron_b
//

#ifndef		BITMAP_HH_
# define	BITMAP_HH_

# include	<vector>
# include	<stdint.h>
//# include	<X11/Xlib.h>
# include	"Color.hh"

# define	BM_MAGIC	0x4D42
# define	BI_RGB		0
# define	BI_BITFIELDS	3

struct __attribute__((packed))	BmpHeader
{
  uint16_t			magic;
  uint32_t			size;
  uint16_t			_app1;
  uint16_t			_app2;
  uint32_t			offset;

};

struct __attribute__((packed))	BmpInfoHeader
{
  uint32_t			size;
  int32_t			width;
  int32_t			height;
  uint16_t			planes;
  uint16_t			bpp;
  uint32_t			compression;
  uint32_t			raw_data_size;
  int32_t			h_resolution;
  int32_t			v_resolution;
  uint32_t			palette_size;
  uint32_t			important_colors;
};



class	Bitmap
{
private:
  std::vector<unsigned char>	_data;
  int				_width;
  int				_height;

  bool				_loadBitmap(const char *name, int& compression);
  void				_convertBitmap(int compression);
  void				_xbgrToBgra();
  void				_reverseBitmap(int line_size, int height);

  Bitmap(const Bitmap& src);
  Bitmap&			operator=(const Bitmap& src);

public:
  Bitmap();
  ~Bitmap();

  bool	openBitmap(const char *name);
  bool	openBitmap(const std::string& name);
  int	getWidth() const;
  int	getHeight() const;
  Color	operator[](int idx) const;
};

#endif /* !BITMAP_HH_ */
