#ifndef	_PACK_H
#define	_PACK_H
#include "hbnet/HBStreamHeader.h"

///////////////////////////////////////////////////////////////////////////////
// output definitions 
///////////////////////////////////////////////////////////////////////////////

#define		PACK_OK				0
#define		PACK_ERROR			1
#define		PACK_MEMORY_ERROR	2
#define		PACK_BITS_ERROR		3
#define		PACK_SIZE_ERROR		4

/*

#define MAX_OSD_CHAR_PER_LINE	44
#define MAX_FONT_HEIGHT 32
#define MAX_FONT_WIDTH 16

#define	MAX_OSD_LINE		44

#define	FORMAT_STRING_BITS	16	//	8

// definition for file header
typedef	struct
{
	char	manufacture[8];
	int		algorithm;
	int		version;
	int		size;
}FILE_PARAM;

// definition for audio pack
typedef	struct
{
	int		algorithm;
	int		version;
	long	dts;
	int		a_size;
	int		size;
}AUDIO_PARAM;

// definition for osd info
typedef	struct {
	unsigned short	x;				// 10  bits (x>>2) 4-aligned
	unsigned short	y;				// 10 bits
	unsigned char	yuvf[3];		// 24 bits
	unsigned char	yuvb[3];		// 24 bits
	unsigned char	transparencef;	// 4  bits
	unsigned char	transparenceb;	// 4  bits
	unsigned short	width;			// 8  bits (width>>3) 8-aligned
	unsigned short	height;			// 10  bits ()
	unsigned short  fontwidth;		// 5 (>>2)
	unsigned short	fontheight;		// 5 (>>2)
	unsigned short	osd_format_string[MAX_OSD_CHAR_PER_LINE];	// width/(font_width)
	unsigned short	o_size;					// osd data size 
	unsigned char	osd_data[MAX_OSD_CHAR_PER_LINE*MAX_FONT_HEIGHT*MAX_FONT_WIDTH/8];		// osd data	
	
}OSD_INFO;

// definition for video pack
typedef	struct
{
	int	algorithm;
	int	version;
	int	frame_type;
	int	e_flag;
	int	e_key;
	int	e_text;
	struct {
		short	year;
		short	month;
		short	day;
		short	hour;
		short	minute;
		short	second;
		short	milli;	
		short	week;
	}ets;
	long	dts;
	long	frame_num;
	int	width;
	int	height;
	int	osd_flag;
	int	osd_lines;
	OSD_INFO	*osd;	// or OSD_INFO[MAX_OSD_LINE]
	int	v_size;
	int	size;
}VIDEO_PARAM;

// definition for user pack
typedef	struct
{
	int	type;
	int	u_size;
}USER_PARAM;

*/
#define	MAX_OSD_LINE 8
#define OSD_MAX_DATA_SIZE 50
char osddatabuf[5][OSD_MAX_DATA_SIZE];
typedef	struct
{
    STREAM_SEGMENT_HEADER osd_header;
    char *osd_data;
}OSD_PARAM;
// definition for video pack
#ifndef _VIDEO_PARAM
#define _VIDEO_PARAM
typedef	struct
{
    STREAM_HEADER stream_header;
    STREAM_VIDEO_HEADER video_header;
    //STREAM_SEGMENT_HEADER osd_header[5];
    int osd_flag;
    OSD_PARAM osd_info[MAX_OSD_LINE];
}VIDEO_PARAM;
#endif

/////////////////////////////////////////////////////////////////////////////////////////
// output functions
/////////////////////////////////////////////////////////////////////////////////////////
//void 	create_file_header(FILE_PARAM file_info,	unsigned char *file_head, int *size);
int		create_video_pack(VIDEO_PARAM video_info,void *buffer, unsigned char *pack_head, int *size);
int		create_audio_pack(STREAM_HEADER audio_info,	unsigned char *pack_head, int *size);

int		extract_video_pack(VIDEO_PARAM *video_info,	unsigned char *pack_head, int size);
int		extract_audio_pack(STREAM_HEADER *audio_info,	unsigned char *pack_head, int size);


/////////////////////////////////////////////////////////////////////////////////////////
// internal functions and definitions
/////////////////////////////////////////////////////////////////////////////////////////

// bitstream read and write 

#define int8_t   char
#define uint8_t  unsigned char
#define int16_t  short
#define uint16_t unsigned short
#define int32_t  int
#define uint32_t unsigned int
#define int64_t  __int64
#define uint64_t unsigned __int64
#define ptr_t uint32_t

#define BSWAPS(a) \
                ((a) = (((a) & 0xff) << 24)  | (((a) & 0xff00) << 8) | \
                       (((a) >> 8) & 0xff00) | (((a) >> 24) & 0xff))

typedef unsigned int size_t;

// bit stream structure 
typedef struct
{
	uint32_t bufa;
	uint32_t bufb;
	uint32_t buf;
	uint32_t pos;
	uint32_t *tail;
	uint32_t *start;
	uint32_t length;
	uint32_t initpos;
}bs;

// initialise bitstream structure 
static void __inline
bs_init(bs * const bs,
			  void *const bitstream,
			  uint32_t length)
{
	uint32_t tmp;
	size_t bitpos;
	ptr_t adjbitstream = (ptr_t)bitstream;

	//
	bitpos = ((sizeof(uint32_t)-1) & (size_t)bitstream);
	adjbitstream = adjbitstream - bitpos;
	bs->start = bs->tail = (uint32_t *) adjbitstream;

	tmp = *bs->start;
#ifndef ARCH_IS_BIG_ENDIAN
	BSWAPS(tmp);
#endif
	bs->bufa = tmp;

	tmp = *(bs->start + 1);
#ifndef ARCH_IS_BIG_ENDIAN
	BSWAPS(tmp);
#endif
	bs->bufb = tmp;

	bs->buf = 0;
	bs->pos = bs->initpos = bitpos*8;
	bs->length = length;
}

// reset bitstream state 
static void __inline
bs_reset(bs * const bs)
{
	uint32_t tmp;

	bs->tail = bs->start;

	tmp = *bs->start;
#ifndef ARCH_IS_BIG_ENDIAN
	BSWAPS(tmp);
#endif
	bs->bufa = tmp;

	tmp = *(bs->start + 1);
#ifndef ARCH_IS_BIG_ENDIAN
	BSWAPS(tmp);
#endif
	bs->bufb = tmp;

	bs->buf = 0;
	bs->pos = bs->initpos;
}

// reads n bits from bitstream without changing the stream pos 
static uint32_t __inline
bs_showbits(bs * const bs,
				  const uint32_t bits)
{
	int nbit = (bits + bs->pos) - 32;
	if (nbit > 0) {
		return ((bs->bufa & (0xffffffff >> bs->pos)) << nbit) | (bs->
																 bufb >> (32 -  nbit));
	} else {
		return (bs->bufa & (0xffffffff >> bs->pos)) >> (32 - bs->pos - bits);
	}
}

// skip n bits forward in bitstream 
static void __inline
bs_skip(bs * const bs,
			  const uint32_t bits)
{
	bs->pos += bits;

	if (bs->pos >= 32) {
		uint32_t tmp;

		bs->bufa = bs->bufb;
		tmp = *((uint32_t *) bs->tail + 2);
#ifndef ARCH_IS_BIG_ENDIAN
		BSWAPS(tmp);
#endif
		bs->bufb = tmp;
		bs->tail++;
		bs->pos -= 32;
	}
}

// number of bits to next byte alignment 
static uint32_t __inline
bs_numbits2bytealign(bs *bs)
{
	uint32_t n = (32 - bs->pos) % 8;
	return n == 0 ? 8 : n;
}

// show nbits from next byte alignment 
static uint32_t __inline
bs_showbitsfrombytealign(bs *bs, int bits)
{
	int bspos = bs->pos + bs_numbits2bytealign(bs);
	int nbit = (bits + bspos) - 32;

	if (bspos >= 32) {
		return bs->bufb >> (32 - nbit);
	} else	if (nbit > 0) {
		return ((bs->bufa & (0xffffffff >> bspos)) << nbit) | (bs->
																 bufb >> (32 - nbit));
	} else {
		return (bs->bufa & (0xffffffff >> bspos)) >> (32 - bspos - bits);
	}
}

// move forward to the next byte boundary 
static void __inline
bs_bytealign(bs * const bs)
{
	uint32_t remainder = bs->pos % 8;

	if (remainder) {
		bs_skip(bs, 8 - remainder);
	}
}

// bitstream length (unit bits) 
static uint32_t __inline
bs_pos(const bs * const bs)
{
	return((uint32_t)(8*((ptr_t)bs->tail - (ptr_t)bs->start) + bs->pos - bs->initpos));
}


//	flush the bitstream & return length (unit bytes)
//	NOTE: assumes no futher bitstream functions will be called.
 
static uint32_t __inline
bs_length(bs * const bs)
{
	uint32_t len = (uint32_t)((ptr_t)bs->tail - (ptr_t)bs->start);

	if (bs->pos) {
		uint32_t b = bs->buf;

#ifndef ARCH_IS_BIG_ENDIAN
		BSWAPS(b);
#endif
		*bs->tail = b;

		len += (bs->pos + 7) / 8;
	}

	// initpos is always on a byte boundary 
	if (bs->initpos)
		len -= bs->initpos/8;

	return len;
}


// move bitstream position forward by n bits and write out buffer if needed 
static void __inline
bs_forward(bs * const bs,
				 const uint32_t bits)
{
	bs->pos += bits;

	if (bs->pos >= 32) {
		uint32_t b = bs->buf;

#ifndef ARCH_IS_BIG_ENDIAN
		BSWAPS(b);
#endif
		*bs->tail++ = b;
		bs->buf = 0;
		bs->pos -= 32;
	}
}

// read n bits from bitstream 
static uint32_t __inline
bs_getbits(bs * const bs,
				 const uint32_t n)
{
	uint32_t ret = bs_showbits(bs, n);

	bs_skip(bs, n);
	return ret;
}

// read single bit from bitstream 
static uint32_t __inline
bs_getbit(bs * const bs)
{
	return bs_getbits(bs, 1);
}

// write single bit to bitstream 
static void __inline
bs_putbit(bs * const bs,
				const uint32_t bit)
{
	if (bit)
		bs->buf |= (0x80000000 >> bs->pos);

	bs_forward(bs, 1);
}

// write n bits to bitstream 
static void __inline
bs_putbits(bs * const bs,
				 const uint32_t value,
				 const uint32_t size)
{
	uint32_t shift = 32 - bs->pos - size;

	if (shift <= 32) 
	{
		bs->buf |= value << shift;
		bs_forward(bs, size);
	} else 
	{
		uint32_t remainder;

		shift = size - (32 - bs->pos);
		bs->buf |= value >> shift;
		bs_forward(bs, size - shift);
		remainder = shift;

		shift = 32 - shift;

		bs->buf |= value << shift;
		bs_forward(bs, remainder);
	}
}


#endif

