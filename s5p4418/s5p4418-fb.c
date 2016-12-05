/*
 * s5p4418-fb.c
 *
 * Copyright(c) 2007-2014 Jianjun Jiang <8192542@qq.com>
 * Official site: http://xboot.org
 * Mobile phone: +86-18665388956
 * QQ: 8192542
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 */

#include <s5p4418-fb.h>

enum s5p4418_mlc_rgbfmt_t
{
	S5P4418_MLC_RGBFMT_R5G6B5		= 0x4432,
	S5P4418_MLC_RGBFMT_B5G6R5		= 0xC432,

	S5P4418_MLC_RGBFMT_X1R5G5B5		= 0x4342,
	S5P4418_MLC_RGBFMT_X1B5G5R5		= 0xC342,
	S5P4418_MLC_RGBFMT_X4R4G4B4		= 0x4211,
	S5P4418_MLC_RGBFMT_X4B4G4R4		= 0xC211,
	S5P4418_MLC_RGBFMT_X8R3G3B2		= 0x4120,
	S5P4418_MLC_RGBFMT_X8B3G3R2		= 0xC120,

	S5P4418_MLC_RGBFMT_A1R5G5B5		= 0x3342,
	S5P4418_MLC_RGBFMT_A1B5G5R5		= 0xB342,
	S5P4418_MLC_RGBFMT_A4R4G4B4		= 0x2211,
	S5P4418_MLC_RGBFMT_A4B4G4R4		= 0xA211,
	S5P4418_MLC_RGBFMT_A8R3G3B2		= 0x1120,
	S5P4418_MLC_RGBFMT_A8B3G3R2		= 0x9120,

	S5P4418_MLC_RGBFMT_R8G8B8		= 0x4653,
	S5P4418_MLC_RGBFMT_B8G8R8		= 0xC653,

	S5P4418_MLC_RGBFMT_X8R8G8B8		= 0x4653,
	S5P4418_MLC_RGBFMT_X8B8G8R8		= 0xC653,
	S5P4418_MLC_RGBFMT_A8R8G8B8		= 0x0653,
	S5P4418_MLC_RGBFMT_A8B8G8R8		= 0x8653,
};

enum s5p4418_dpc_format_t
{
	S5P4418_DPC_FORMAT_RGB555		= 0x0,
	S5P4418_DPC_FORMAT_RGB565		= 0x1,
	S5P4418_DPC_FORMAT_RGB666		= 0x2,
	S5P4418_DPC_FORMAT_RGB888		= 0x3,
	S5P4418_DPC_FORMAT_MRGB555A		= 0x4,
	S5P4418_DPC_FORMAT_MRGB555B		= 0x5,
	S5P4418_DPC_FORMAT_MRGB565		= 0x6,
	S5P4418_DPC_FORMAT_MRGB666		= 0x7,
	S5P4418_DPC_FORMAT_MRGB888A		= 0x8,
	S5P4418_DPC_FORMAT_MRGB888B		= 0x9,
	S5P4418_DPC_FORMAT_CCIR656		= 0xa,
	S5P4418_DPC_FORMAT_CCIR601A		= 0xc,
	S5P4418_DPC_FORMAT_CCIR601B		= 0xd,
};

enum s5p4418_dpc_ycorder_t
{
	S5P4418_DPC_YCORDER_CBYCRY		= 0x0,
	S5P4418_DPC_YCORDER_CRYCBY		= 0x1,
	S5P4418_DPC_YCORDER_YCBYCR		= 0x2,
	S5P4418_DPC_YCORDER_YCRYCB		= 0x3,
};

enum s5p4418_dpc_dither_t
{
	S5P4418_DPC_DITHER_BYPASS		= 0x0,
	S5P4418_DPC_DITHER_4BIT			= 0x1,
	S5P4418_DPC_DITHER_5BIT			= 0x2,
	S5P4418_DPC_DITHER_6BIT			= 0x3,
};

struct s5p4418_fb_data_t
{
	/* Register base address */
	physical_addr_t mlcbase;
	physical_addr_t dpcbase;

	/* Horizontal resolution */
	int width;

	/* Vertical resolution */
	int height;

	/* Horizontal dpi */
	int xdpi;

	/* Vertical dpi */
	int ydpi;

	/* Bits per pixel */
	int bits_per_pixel;

	/* Bytes per pixel */
	int bytes_per_pixel;

	struct {
		/* red color */
		s32_t r_mask;
		s32_t r_field;

		/* green color */
		s32_t g_mask;
		s32_t g_field;

		/* blue color */
		s32_t b_mask;
		s32_t b_field;

		/* alpha color */
		s32_t a_mask;
		s32_t a_field;
	} rgba;

	struct {
		/* Specifies output pixel format, YCbCR or RGB */
		int rgbmode;

		/* Scan mode, progressive or interlace */
		int scanmode;

		/* Enbed sync signal for ITU-R BT.656 format */
		int enbedsync;

		/* The polarity of the internal field signal */
		int polfield;

		/* Swap red and blue component */
		int swaprb;

		/* Data out format */
		enum s5p4418_dpc_format_t format;

		/* Data out order */
		enum s5p4418_dpc_ycorder_t ycorder;

		/* Dithering mode */
		enum s5p4418_dpc_dither_t rdither;
		enum s5p4418_dpc_dither_t gdither;
		enum s5p4418_dpc_dither_t bdither;
	} mode;

	struct {
		/* Pixel clock frequency */
		int pixel_clock_hz;

		/* Horizontal front porch */
		int	h_front_porch;

		/* Horizontal sync width */
		int	h_sync_width;

		/* Horizontal back porch */
		int	h_back_porch;

		/* Vertical front porch */
		int	v_front_porch;

		/* Vertical sync width */
		int	v_sync_width;

		/* Vertical back porch */
		int	v_back_porch;

		/* Start veritcal sync offset */
		int vs_start_offset;

		/* End veritcal sync offset */
		int vs_end_offset;

		/* Start even veritcal sync offset */
		int ev_start_offset;

		/* End even veritcal sync offset */
		int ev_end_offset;

		/* The delay value for RGB/PVD signal */
		int d_rgb_pvd;

		/* The delay value for HSYNC/CP1 signal */
		int d_hsync_cp1;

		/* The delay value for VSYNC/FRAM signal */
		int d_vsync_fram;

		/* The delay value for DE/CP2 signal */
		int d_de_cp2;
	} timing;

	struct {
		/* Hsync polarity flag */
		int	h_sync_invert;

		/* Vsync polarity flag */
		int	v_sync_invert;
	} polarity;

	/* video ram front buffer */
	void * vram_front;

	/* video ram back buffer */
	void * vram_back;

	/* Init and exit */
	void (*init)(struct s5p4418_fb_data_t * dat);
	void (*exit)(struct s5p4418_fb_data_t * dat);
	/* Set and get backlight brightness */
	void (*setbl)(struct s5p4418_fb_data_t * dat, int brightness);
	int (*getbl)(struct s5p4418_fb_data_t * dat);

	/* Private data */
	void * priv;
};

/*
 * defined the structure of framebuffer.
 */
struct fb_t
{
	/* the framebuffer's surface */
	struct surface_t surface;

	/* framebuffer's lcd data */
	struct s5p4418_fb_data_t * dat;
};

static inline void s5p4418_mlc_pclk_bclk_enable(struct s5p4418_fb_data_t * dat, bool_t enable)
{
	u32_t cfg;

	cfg = read32(phys_to_virt(dat->mlcbase + MLC_CLKENB));
	cfg &= ~((0x1 << 3) | (0x3 << 0));
	if(enable)
		cfg |= ((0x1 << 3) | (0x3 << 0));
	else
		cfg |= ((0x0 << 3) | (0x0 << 0));
	write32(phys_to_virt(dat->mlcbase + MLC_CLKENB), cfg);
}

static inline void s5p4418_mlc_set_enable(struct s5p4418_fb_data_t * dat, bool_t enable)
{
	u32_t cfg;

	cfg = read32(phys_to_virt(dat->mlcbase + MLC_CONTROLT));
	cfg &= ~(0x1 << 1 | 0x1 << 3);
	if(enable)
		cfg |= (0x1 << 1);
	write32(phys_to_virt(dat->mlcbase + MLC_CONTROLT), cfg);
}

static inline void s5p4418_mlc_set_power_mode(struct s5p4418_fb_data_t * dat, bool_t on)
{
	u32_t cfg;

	cfg = read32(phys_to_virt(dat->mlcbase + MLC_CONTROLT));
	cfg &= ~(0x1 << 11 | 0x1 << 3);
	if(on)
		cfg |= (0x1 << 11);
	write32(phys_to_virt(dat->mlcbase + MLC_CONTROLT), cfg);
}

static inline void s5p4418_mlc_set_sleep_mode(struct s5p4418_fb_data_t * dat, bool_t on)
{
	u32_t cfg;

	cfg = read32(phys_to_virt(dat->mlcbase + MLC_CONTROLT));
	cfg &= ~(0x1 << 10 | 0x1 << 3);
	if(!on)
		cfg |= (0x1 << 10);
	write32(phys_to_virt(dat->mlcbase + MLC_CONTROLT), cfg);
}

static inline void s5p4418_mlc_set_top_dirty_flag(struct s5p4418_fb_data_t * dat)
{
	u32_t cfg;

	cfg = read32(phys_to_virt(dat->mlcbase + MLC_CONTROLT));
	cfg |= (0x1 << 3);
	write32(phys_to_virt(dat->mlcbase + MLC_CONTROLT), cfg);
}

static inline void s5p4418_mlc_set_layer_priority(struct s5p4418_fb_data_t * dat, int priority)
{
	u32_t cfg;

	cfg = read32(phys_to_virt(dat->mlcbase + MLC_CONTROLT));
	cfg &= ~(0x3 << 8 | 0x1 << 3);
	cfg |= ((priority & 0x3) << 8);
	write32(phys_to_virt(dat->mlcbase + MLC_CONTROLT), cfg);
}

static inline void s5p4418_mlc_set_field_enable(struct s5p4418_fb_data_t * dat, bool_t enable)
{
	u32_t cfg;

	cfg = read32(phys_to_virt(dat->mlcbase + MLC_CONTROLT));
	cfg &= ~(0x1 << 0 | 0x1 << 3);
	if(enable)
		cfg |= (0x1 << 0);
	write32(phys_to_virt(dat->mlcbase + MLC_CONTROLT), cfg);
}

static inline void s5p4418_mlc_set_screen_size(struct s5p4418_fb_data_t * dat, u32_t width, u32_t height)
{
	u32_t cfg;

	cfg = (((height - 1) & 0x3ff) << 16) | (((width - 1) & 0x3ff) << 0);
	write32(phys_to_virt(dat->mlcbase + MLC_SCREENSIZE), cfg);
}

static inline void s5p4418_mlc_set_background_color(struct s5p4418_fb_data_t * dat, u32_t color)
{
	write32(phys_to_virt(dat->mlcbase + MLC_BGCOLOR), color);
}

static inline void s5p4418_mlc_set_layer_enable(struct s5p4418_fb_data_t * dat, int layer, bool_t enable)
{
	u32_t cfg;

	switch(layer)
	{
	case 0:
		cfg = read32(phys_to_virt(dat->mlcbase + MLC_CONTROL0));
		cfg &= ~(0x1 << 5 | 0x1 << 4);
		if(enable)
			cfg |= (0x1 << 5);
		write32(phys_to_virt(dat->mlcbase + MLC_CONTROL0), cfg);
		break;

	case 1:
		cfg = read32(phys_to_virt(dat->mlcbase + MLC_CONTROL1));
		cfg &= ~(0x1 << 5 | 0x1 << 4);
		if(enable)
			cfg |= (0x1 << 5);
		write32(phys_to_virt(dat->mlcbase + MLC_CONTROL1), cfg);
		break;

	case 2:
		cfg = read32(phys_to_virt(dat->mlcbase + MLC_CONTROL2));
		cfg &= ~(0x1 << 5 | 0x1 << 4);
		if(enable)
			cfg |= (0x1 << 5);
		write32(phys_to_virt(dat->mlcbase + MLC_CONTROL2), cfg);
		break;

	default:
		break;
	}
}

static inline void s5p4418_mlc_set_dirty_flag(struct s5p4418_fb_data_t * dat, int layer)
{
	u32_t cfg;

	switch(layer)
	{
	case 0:
		cfg = read32(phys_to_virt(dat->mlcbase + MLC_CONTROL0));
		cfg |= (0x1 << 4);
		write32(phys_to_virt(dat->mlcbase + MLC_CONTROL0), cfg);
		break;

	case 1:
		cfg = read32(phys_to_virt(dat->mlcbase + MLC_CONTROL1));
		cfg |= (0x1 << 4);
		write32(phys_to_virt(dat->mlcbase + MLC_CONTROL1), cfg);
		break;

	case 2:
		cfg = read32(phys_to_virt(dat->mlcbase + MLC_CONTROL2));
		cfg |= (0x1 << 4);
		write32(phys_to_virt(dat->mlcbase + MLC_CONTROL2), cfg);
		break;

	default:
		break;
	}
}

static inline bool_t s5p4418_mlc_get_dirty_flag(struct s5p4418_fb_data_t * dat, int layer)
{
	switch(layer)
	{
	case 0:
		return (read32(phys_to_virt(dat->mlcbase + MLC_CONTROL0)) & (0x1 << 4)) ? TRUE : FALSE;
	case 1:
		return (read32(phys_to_virt(dat->mlcbase + MLC_CONTROL1)) & (0x1 << 4)) ? TRUE : FALSE;
	case 2:
		return (read32(phys_to_virt(dat->mlcbase + MLC_CONTROL2)) & (0x1 << 4)) ? TRUE : FALSE;
	default:
		break;
	}
	return FALSE;
}

static inline void s5p4418_mlc_wait_vsync(struct s5p4418_fb_data_t * dat, int layer)
{
	while(s5p4418_mlc_get_dirty_flag(dat, layer));
}

static inline void s5p4418_mlc_set_lock_size(struct s5p4418_fb_data_t * dat, int layer, int size)
{
	u32_t cfg;

	switch(layer)
	{
	case 0:
		cfg = read32(phys_to_virt(dat->mlcbase + MLC_CONTROL0));
		cfg &= ~(0x3 << 12 | 0x1 << 4);
		cfg |= (((size >> 8) & 0x3) << 12);
		write32(phys_to_virt(dat->mlcbase + MLC_CONTROL0), cfg);
		break;

	case 1:
		cfg = read32(phys_to_virt(dat->mlcbase + MLC_CONTROL1));
		cfg &= ~(0x3 << 12 | 0x1 << 4);
		cfg |= (((size >> 8) & 0x3) << 12);
		write32(phys_to_virt(dat->mlcbase + MLC_CONTROL1), cfg);
		break;

	default:
		break;
	}
}

static inline void s5p4418_mlc_set_alpha_blending(struct s5p4418_fb_data_t * dat, int layer, bool_t enable, u32_t alpha)
{
	u32_t cfg;

	switch(layer)
	{
	case 0:
		cfg = read32(phys_to_virt(dat->mlcbase + MLC_CONTROL0));
		cfg &= ~(0x1 << 2 | 0x1 << 4);
		cfg |= ((enable ? 1 : 0) << 2);
		write32(phys_to_virt(dat->mlcbase + MLC_CONTROL0), cfg);

		cfg = read32(phys_to_virt(dat->mlcbase + MLC_TPCOLOR0));
		cfg &= ~(0xff << 24);
		cfg |= ((alpha & 0xff) << 24);
		write32(phys_to_virt(dat->mlcbase + MLC_TPCOLOR0), cfg);
		break;

	case 1:
		cfg = read32(phys_to_virt(dat->mlcbase + MLC_CONTROL1));
		cfg &= ~(0x1 << 2 | 0x1 << 4);
		cfg |= ((enable ? 1 : 0) << 2);
		write32(phys_to_virt(dat->mlcbase + MLC_CONTROL1), cfg);

		cfg = read32(phys_to_virt(dat->mlcbase + MLC_TPCOLOR1));
		cfg &= ~(0xff << 24);
		cfg |= ((alpha & 0xff) << 24);
		write32(phys_to_virt(dat->mlcbase + MLC_TPCOLOR1), cfg);
		break;

	case 2:
		cfg = read32(phys_to_virt(dat->mlcbase + MLC_CONTROL2));
		cfg &= ~(0x1 << 2 | 0x1 << 4);
		cfg |= ((enable ? 1 : 0) << 2);
		write32(phys_to_virt(dat->mlcbase + MLC_CONTROL2), cfg);

		cfg = read32(phys_to_virt(dat->mlcbase + MLC_TPCOLOR2));
		cfg &= ~(0xff << 24);
		cfg |= ((alpha & 0xff) << 24);
		write32(phys_to_virt(dat->mlcbase + MLC_TPCOLOR2), cfg);
		break;

	default:
		break;
	}
}

static inline void s5p4418_mlc_set_transparency(struct s5p4418_fb_data_t * dat, int layer, bool_t enable, u32_t color)
{
	u32_t cfg;

	switch(layer)
	{
	case 0:
		cfg = read32(phys_to_virt(dat->mlcbase + MLC_CONTROL0));
		cfg &= ~(0x1 << 0 | 0x1 << 4);
		cfg |= ((enable ? 1 : 0) << 0);
		write32(phys_to_virt(dat->mlcbase + MLC_CONTROL0), cfg);

		cfg = read32(phys_to_virt(dat->mlcbase + MLC_TPCOLOR0));
		cfg &= ~(0xfffff << 0);
		cfg |= ((color & 0xfffff) << 0);
		write32(phys_to_virt(dat->mlcbase + MLC_TPCOLOR0), cfg);
		break;

	case 1:
		cfg = read32(phys_to_virt(dat->mlcbase + MLC_CONTROL1));
		cfg &= ~(0x1 << 0 | 0x1 << 4);
		cfg |= ((enable ? 1 : 0) << 0);
		write32(phys_to_virt(dat->mlcbase + MLC_CONTROL1), cfg);

		cfg = read32(phys_to_virt(dat->mlcbase + MLC_TPCOLOR1));
		cfg &= ~(0xfffff << 0);
		cfg |= ((color & 0xfffff) << 0);
		write32(phys_to_virt(dat->mlcbase + MLC_TPCOLOR1), cfg);
		break;

	case 2:
		cfg = read32(phys_to_virt(dat->mlcbase + MLC_CONTROL2));
		cfg &= ~(0x1 << 0 | 0x1 << 4);
		cfg |= ((enable ? 1 : 0) << 0);
		write32(phys_to_virt(dat->mlcbase + MLC_CONTROL2), cfg);

		cfg = read32(phys_to_virt(dat->mlcbase + MLC_TPCOLOR2));
		cfg &= ~(0xfffff << 0);
		cfg |= ((color & 0xfffff) << 0);
		write32(phys_to_virt(dat->mlcbase + MLC_TPCOLOR2), cfg);
		break;

	default:
		break;
	}
}

static inline void s5p4418_mlc_set_color_inversion(struct s5p4418_fb_data_t * dat, int layer, bool_t enable, u32_t color)
{
	u32_t cfg;

	switch(layer)
	{
	case 0:
		cfg = read32(phys_to_virt(dat->mlcbase + MLC_CONTROL0));
		cfg &= ~(0x1 << 1 | 0x1 << 4);
		cfg |= ((enable ? 1 : 0) << 1);
		write32(phys_to_virt(dat->mlcbase + MLC_CONTROL0), cfg);

		cfg = read32(phys_to_virt(dat->mlcbase + MLC_INVCOLOR0));
		cfg &= ~(0xfffff << 0);
		cfg |= ((color & 0xfffff) << 0);
		write32(phys_to_virt(dat->mlcbase + MLC_INVCOLOR0), cfg);
		break;

	case 1:
		cfg = read32(phys_to_virt(dat->mlcbase + MLC_CONTROL1));
		cfg &= ~(0x1 << 1 | 0x1 << 4);
		cfg |= ((enable ? 1 : 0) << 1);
		write32(phys_to_virt(dat->mlcbase + MLC_CONTROL1), cfg);

		cfg = read32(phys_to_virt(dat->mlcbase + MLC_INVCOLOR1));
		cfg &= ~(0xfffff << 0);
		cfg |= ((color & 0xfffff) << 0);
		write32(phys_to_virt(dat->mlcbase + MLC_INVCOLOR1), cfg);
		break;

	case 2:
		cfg = read32(phys_to_virt(dat->mlcbase + MLC_CONTROL2));
		cfg &= ~(0x1 << 1 | 0x1 << 4);
		cfg |= ((enable ? 1 : 0) << 1);
		write32(phys_to_virt(dat->mlcbase + MLC_CONTROL2), cfg);

		cfg = read32(phys_to_virt(dat->mlcbase + MLC_INVCOLOR2));
		cfg &= ~(0xfffff << 0);
		cfg |= ((color & 0xfffff) << 0);
		write32(phys_to_virt(dat->mlcbase + MLC_INVCOLOR2), cfg);
		break;

	default:
		break;
	}
}

static inline void s5p4418_mlc_set_layer_invalid_position(struct s5p4418_fb_data_t * dat, int layer, u32_t region, s32_t sx, s32_t sy, s32_t ex, s32_t ey, bool_t enable)
{
	u32_t cfg;

	switch(layer)
	{
	case 0:
		if(region == 0)
		{
			cfg = ((enable ? 1 : 0) << 28) | ((sx & 0x7ff) << 16) | (ex & 0x7ff);
			write32(phys_to_virt(dat->mlcbase + MLC_INVALIDLEFTRIGHT0_0), cfg);
			cfg = ((sy & 0x7ff) << 16) | (ey & 0x7ff);
			write32(phys_to_virt(dat->mlcbase + MLC_INVALIDTOPBOTTOM0_0), cfg);
		}
		else
		{
			cfg = ((enable ? 1 : 0) << 28) | ((sx & 0x7ff) << 16) | (ex & 0x7ff);
			write32(phys_to_virt(dat->mlcbase + MLC_INVALIDLEFTRIGHT0_1), cfg);
			cfg = ((sy & 0x7ff) << 16) | (ey & 0x7ff);
			write32(phys_to_virt(dat->mlcbase + MLC_INVALIDTOPBOTTOM0_1), cfg);
		}
		break;

	case 1:
		if(region == 0)
		{
			cfg = ((enable ? 1 : 0) << 28) | ((sx & 0x7ff) << 16) | (ex & 0x7ff);
			write32(phys_to_virt(dat->mlcbase + MLC_INVALIDLEFTRIGHT1_0), cfg);
			cfg = ((sy & 0x7ff) << 16) | (ey & 0x7ff);
			write32(phys_to_virt(dat->mlcbase + MLC_INVALIDTOPBOTTOM1_0), cfg);
		}
		else
		{
			cfg = ((enable ? 1 : 0) << 28) | ((sx & 0x7ff) << 16) | (ex & 0x7ff);
			write32(phys_to_virt(dat->mlcbase + MLC_INVALIDLEFTRIGHT1_1), cfg);
			cfg = ((sy & 0x7ff) << 16) | (ey & 0x7ff);
			write32(phys_to_virt(dat->mlcbase + MLC_INVALIDTOPBOTTOM1_1), cfg);
		}
		break;

	default:
		break;
	}
}

static inline void s5p4418_mlc_set_rgb_format(struct s5p4418_fb_data_t * dat, int layer, enum s5p4418_mlc_rgbfmt_t fmt)
{
	u32_t cfg;

	switch(layer)
	{
	case 0:
		cfg = read32(phys_to_virt(dat->mlcbase + MLC_CONTROL0));
		cfg &= ~(0xffff << 16 | 0x1 << 4);
		cfg |= (fmt << 16);
		write32(phys_to_virt(dat->mlcbase + MLC_CONTROL0), cfg);
		break;

	case 1:
		cfg = read32(phys_to_virt(dat->mlcbase + MLC_CONTROL1));
		cfg &= ~(0xffff << 16 | 0x1 << 4);
		cfg |= (fmt << 16);
		write32(phys_to_virt(dat->mlcbase + MLC_CONTROL1), cfg);
		break;

	default:
		break;
	}
}

static inline void s5p4418_mlc_set_position(struct s5p4418_fb_data_t * dat, int layer, s32_t sx, s32_t sy, s32_t ex, s32_t ey)
{
	u32_t cfg;

	switch(layer)
	{
	case 0:
		cfg = ((sx & 0xfff) << 16) | (ex & 0xfff);
		write32(phys_to_virt(dat->mlcbase + MLC_LEFTRIGHT0), cfg);
		cfg = ((sy & 0xfff) << 16) | (ey & 0xfff);
		write32(phys_to_virt(dat->mlcbase + MLC_TOPBOTTOM0), cfg);
		break;

	case 1:
		cfg = ((sx & 0xfff) << 16) | (ex & 0xfff);
		write32(phys_to_virt(dat->mlcbase + MLC_LEFTRIGHT1), cfg);
		cfg = ((sy & 0xfff) << 16) | (ey & 0xfff);
		write32(phys_to_virt(dat->mlcbase + MLC_TOPBOTTOM1), cfg);
		break;

	case 2:
		cfg = ((sx & 0xfff) << 16) | (ex & 0xfff);
		write32(phys_to_virt(dat->mlcbase + MLC_LEFTRIGHT2), cfg);
		cfg = ((sy & 0xfff) << 16) | (ey & 0xfff);
		write32(phys_to_virt(dat->mlcbase + MLC_TOPBOTTOM2), cfg);
		break;

	default:
		break;
	}
}

static inline void s5p4418_mlc_set_layer_stride(struct s5p4418_fb_data_t * dat, int layer, s32_t hstride, s32_t vstride)
{
	switch(layer)
	{
	case 0:
		write32(phys_to_virt(dat->mlcbase + MLC_HSTRIDE0), hstride);
		write32(phys_to_virt(dat->mlcbase + MLC_VSTRIDE0), vstride);
		break;

	case 1:
		write32(phys_to_virt(dat->mlcbase + MLC_HSTRIDE1), hstride);
		write32(phys_to_virt(dat->mlcbase + MLC_VSTRIDE1), vstride);
		break;

	default:
		break;
	}
}

static inline void s5p4418_mlc_set_layer_address(struct s5p4418_fb_data_t * dat, int layer, void * vram)
{
	switch(layer)
	{
	case 0:
		write32(phys_to_virt(dat->mlcbase + MLC_ADDRESS0), (u32_t)vram);
		break;
	case 1:
		write32(phys_to_virt(dat->mlcbase + MLC_ADDRESS1), (u32_t)vram);
		break;
	case 2:
		write32(phys_to_virt(dat->mlcbase + MLC_ADDRESS2), (u32_t)vram);
		break;
	default:
		break;
	}
}

static inline void s5p4418_dpc_pclk_enable(struct s5p4418_fb_data_t * dat, bool_t enable)
{
	u32_t cfg;

	cfg = read32(phys_to_virt(dat->dpcbase + DPC_CLKENB));
	cfg &= ~((0x1 << 3) | (0x1 << 2));
	if(enable)
		cfg |= ((0x1 << 3) | (0x1 << 2));
	else
		cfg |= ((0x0 << 3) | (0x0 << 2));
	write32(phys_to_virt(dat->dpcbase + DPC_CLKENB), cfg);
}

static inline void s5p4418_dpc_set_mode(struct s5p4418_fb_data_t * dat)
{
	u32_t cfg;

	cfg = read32(phys_to_virt(dat->dpcbase + DPC_CTRL0));
	cfg &= ~(0x1 << 12);
	cfg |= ((dat->mode.rgbmode ? 1 : 0) << 12);
	cfg &= ~(0x1 << 9);
	cfg |= ((dat->mode.scanmode ? 1 : 0) << 9);
	cfg &= ~(0x1 << 8);
	cfg |= ((dat->mode.enbedsync ? 1 : 0) << 8);
	cfg &= ~(0x1 << 2);
	cfg |= ((dat->mode.polfield ? 1 : 0) << 2);
	write32(phys_to_virt(dat->dpcbase + DPC_CTRL0), cfg);

	cfg = read32(phys_to_virt(dat->dpcbase + DPC_CTRL1));
	cfg &= ~(0x1 << 15);
	cfg |= ((dat->mode.swaprb ? 1 : 0) << 15);
	cfg &= ~(0xf << 8);
	cfg |= (dat->mode.format << 8);
	cfg &= ~(0x3 << 6);
	cfg |= (dat->mode.ycorder << 6);
	cfg &= ~(0x3f << 0);
	cfg |= ((dat->mode.rdither << 0) | (dat->mode.gdither << 2) | (dat->mode.bdither << 4));
	write32(phys_to_virt(dat->dpcbase + DPC_CTRL1), cfg);

	cfg = 0x0;
	write32(phys_to_virt(dat->dpcbase + DPC_CTRL2), cfg);
}

static inline void s5p4418_dpc_set_timing(struct s5p4418_fb_data_t * dat)
{
	u32_t cfg;

	/* horizontal */
	cfg = dat->width + dat->timing.h_front_porch + dat->timing.h_sync_width + dat->timing.h_back_porch - 1;
	write32(phys_to_virt(dat->dpcbase + DPC_HTOTAL), cfg);

	cfg = dat->timing.h_sync_width - 1;
	write32(phys_to_virt(dat->dpcbase + DPC_HSWIDTH), cfg);

	cfg = dat->timing.h_sync_width + dat->timing.h_back_porch - 1;
	write32(phys_to_virt(dat->dpcbase + DPC_HASTART), cfg);

	cfg = dat->width + dat->timing.h_sync_width + dat->timing.h_back_porch - 1;
	write32(phys_to_virt(dat->dpcbase + DPC_HAEND), cfg);

	/* vertical - progressive */
	cfg = dat->height + dat->timing.v_front_porch + dat->timing.v_sync_width + dat->timing.v_back_porch - 1;
	write32(phys_to_virt(dat->dpcbase + DPC_VTOTAL), cfg);

	cfg = dat->timing.v_sync_width - 1;
	write32(phys_to_virt(dat->dpcbase + DPC_VSWIDTH), cfg);

	cfg = dat->timing.v_sync_width + dat->timing.v_back_porch - 1;
	write32(phys_to_virt(dat->dpcbase + DPC_VASTART), cfg);

	cfg = dat->height + dat->timing.v_sync_width + dat->timing.v_back_porch - 1;
	write32(phys_to_virt(dat->dpcbase + DPC_VAEND), cfg);

	/* vertical - interlaced */
	cfg = dat->height + dat->timing.v_front_porch + dat->timing.v_sync_width + dat->timing.v_back_porch - 1;
	write32(phys_to_virt(dat->dpcbase + DPC_EVTOTAL), cfg);

	cfg = dat->timing.v_sync_width - 1;
	write32(phys_to_virt(dat->dpcbase + DPC_EVSWIDTH), cfg);

	cfg = dat->timing.v_sync_width + dat->timing.v_back_porch - 1;
	write32(phys_to_virt(dat->dpcbase + DPC_EVASTART), cfg);

	cfg = dat->height + dat->timing.v_sync_width + dat->timing.v_back_porch - 1;
	write32(phys_to_virt(dat->dpcbase + DPC_EVAEND), cfg);

	/* Sync offset */
	write32(phys_to_virt(dat->dpcbase + DPC_VSSOFFSET), dat->timing.vs_start_offset);
	write32(phys_to_virt(dat->dpcbase + DPC_VSEOFFSET), dat->timing.vs_end_offset);
	write32(phys_to_virt(dat->dpcbase + DPC_EVSSOFFSET), dat->timing.ev_start_offset);
	write32(phys_to_virt(dat->dpcbase + DPC_EVSEOFFSET), dat->timing.ev_end_offset);

	/* Delay value */
	cfg = read32(phys_to_virt(dat->dpcbase + DPC_CTRL0));
	cfg &= ~(0x1 << 10);
	cfg &= ~(0xf << 4);
	cfg |= (dat->timing.d_rgb_pvd & 0xf) << 4;
	write32(phys_to_virt(dat->dpcbase + DPC_CTRL0), cfg);

	cfg = ((dat->timing.d_hsync_cp1 & 0xf) << 0) | ((dat->timing.d_vsync_fram & 0xf) << 8);
	write32(phys_to_virt(dat->dpcbase + DPC_DELAY0), cfg);

	cfg = (dat->timing.d_de_cp2 & 0x3f) << 0;
	write32(phys_to_virt(dat->dpcbase + DPC_DELAY1), cfg);
}

static inline void s5p4418_dpc_set_polarity(struct s5p4418_fb_data_t * dat)
{
	u32_t cfg;

	cfg = read32(phys_to_virt(dat->dpcbase + DPC_CTRL0));
	cfg &= ~(0x1 << 10 | 0x1 << 1 | 0x1 << 0);
	if(dat->polarity.h_sync_invert)
		cfg |= (0x1 << 0);
	if(dat->polarity.v_sync_invert)
		cfg |= (0x1 << 1);
	write32(phys_to_virt(dat->dpcbase + DPC_CTRL0), cfg);
}

static inline void s5p4418_dpc_set_enable(struct s5p4418_fb_data_t * dat, bool_t enable)
{
	u32_t cfg;

	cfg = read32(phys_to_virt(dat->dpcbase + DPC_CTRL0));
	cfg &= ~(0x1 << 10 | 0x1 << 15);
	if(enable)
		cfg |= (0x1 << 15);
	write32(phys_to_virt(dat->dpcbase + DPC_CTRL0), cfg);
}

static inline void s5p4418_dpa_rgb_mux_select(int sel)
{
	write32(phys_to_virt(S5P4418_DPA_BASE + DPA_TFT_MUXCTRL), (sel & 0x3));
}

static inline void s5p4418_fb_cfg_gpios(int base, int nr, int cfg, enum gpio_pull_t pull, enum gpio_drv_t drv)
{
	for(; nr > 0; nr--, base++)
	{
		gpio_set_cfg(base, cfg);
		gpio_set_pull(base, pull);
		gpio_set_drv(base, drv);
	}
}

static void fb_init(struct fb_t * fb)
{
	struct s5p4418_fb_data_t * dat = (struct s5p4418_fb_data_t *)(fb->dat);

	s5p4418_ip_reset(RESET_ID_DISP_TOP, 0);
	s5p4418_ip_reset(RESET_ID_DISPLAY, 0);
	s5p4418_ip_reset(RESET_ID_LCDIF, 0);
	s5p4418_ip_reset(RESET_ID_LVDS, 0);

	/*
	 * Initial digital rgb lcd port
	 */
	s5p4418_fb_cfg_gpios(S5P4418_GPIOA(0), 28, 0x1, GPIO_PULL_NONE, GPIO_DRV_HIGH);

	/*
	 * Lcd init function
	 */
	if(dat->init)
		dat->init(dat);

	/*
	 * Enable some clocks
	 */
	s5p4418_mlc_pclk_bclk_enable(dat, TRUE);
	s5p4418_dpc_pclk_enable(dat, TRUE);

	write32(phys_to_virt(dat->dpcbase + DPC_CLKGEN0L), 0x000001e8);
	write32(phys_to_virt(dat->dpcbase + DPC_CLKGEN1L), 0x0000001c);
	write32(phys_to_virt(dat->dpcbase + DPC_CLKGEN0H), 0x00000000);
	write32(phys_to_virt(dat->dpcbase + DPC_CLKGEN1H), 0x00000000);

	/*
	 * Initial mlc top layer
	 */
	s5p4418_mlc_set_layer_priority(dat, 0);
	s5p4418_mlc_set_background_color(dat, 0);
	s5p4418_mlc_set_field_enable(dat, FALSE);
	s5p4418_mlc_set_power_mode(dat, TRUE);
	s5p4418_mlc_set_sleep_mode(dat, FALSE);

	/*
	 * Initial mlc fb layer
	 */
	s5p4418_mlc_set_lock_size(dat, 0, 16);
	s5p4418_mlc_set_alpha_blending(dat, 0, FALSE, 0);
	s5p4418_mlc_set_transparency(dat, 0, FALSE, 0);
	s5p4418_mlc_set_color_inversion(dat, 0, FALSE, 0);
	s5p4418_mlc_set_layer_invalid_position(dat, 0, 0, 0, 0, 0, 0, FALSE);
	s5p4418_mlc_set_layer_invalid_position(dat, 0, 1, 0, 0, 0, 0, FALSE);
	s5p4418_mlc_set_rgb_format(dat, 0, S5P4418_MLC_RGBFMT_X8R8G8B8);
	s5p4418_mlc_set_position(dat, 0, 0, 0, dat->width - 1, dat->height - 1);
	s5p4418_mlc_set_layer_stride(dat, 0, dat->bytes_per_pixel, dat->bytes_per_pixel * dat->width);
	s5p4418_mlc_set_screen_size(dat, dat->width, dat->height);

	/*
	 * Enable mlc controller
	 */
	s5p4418_mlc_set_enable(dat, TRUE);
	s5p4418_mlc_set_top_dirty_flag(dat);
	s5p4418_mlc_set_layer_enable(dat, 0, TRUE);
	s5p4418_mlc_set_dirty_flag(dat, 0);

	/*
	 * Initial dpc
	 */
	s5p4418_dpc_set_mode(dat);
	s5p4418_dpc_set_timing(dat);
	s5p4418_dpc_set_polarity(dat);

	/*
	 * Enable dpc controller
	 */
	s5p4418_dpc_set_enable(dat, TRUE);

	/*
	 * MUX select for primary dpc(TFT)
	 */
	s5p4418_dpa_rgb_mux_select(0);
}

static void fb_swap(struct fb_t * fb)
{
	struct s5p4418_fb_data_t * dat = (struct s5p4418_fb_data_t *)(fb->dat);
	void * vram;

	vram = dat->vram_front;
	dat->vram_front = dat->vram_back;
	dat->vram_back = vram;

	fb->surface.pixels = dat->vram_front;
}

static void fb_flush(struct fb_t * fb)
{
	struct s5p4418_fb_data_t * dat = (struct s5p4418_fb_data_t *)(fb->dat);

	s5p4418_mlc_wait_vsync(dat, 0);
	s5p4418_mlc_set_layer_address(dat, 0, dat->vram_front);
	s5p4418_mlc_set_dirty_flag(dat, 0);
}

static void fb_backlight(struct fb_t * fb, int brightness)
{
	struct s5p4418_fb_data_t * dat = (struct s5p4418_fb_data_t *)(fb->dat);
	if(dat->setbl)
		dat->setbl(dat, brightness);
}

struct lcd_backlight_data_t {
	struct pwm_t * pwm;
	u32_t period;
	u32_t duty_from;
	u32_t duty_to;
	int polarity;
	int brightness;
};

static u8_t vram[2][1024 * 600 * 32 / 8] __attribute__((aligned(4)));

static void lcd_init(struct s5p4418_fb_data_t * dat)
{
	struct lcd_backlight_data_t * bl;

	bl = malloc(sizeof(struct lcd_backlight_data_t));
	if(!bl)
		return;

	bl->pwm = search_pwm("pwm0");
	bl->period = 1000 * 1000;
	bl->duty_from = 0;
	bl->duty_to = 1000 * 1000;
	bl->polarity = 1;
	bl->brightness = 0;
	dat->priv = bl;

	pwm_config(bl->pwm, bl->duty_from, bl->period, bl->polarity);
	pwm_enable(bl->pwm);

	/* Enable backlight power */
	gpio_set_cfg(S5P4418_GPIOC(10), 0x1);
	gpio_set_pull(S5P4418_GPIOC(10), GPIO_PULL_UP);
	gpio_direction_output(S5P4418_GPIOC(10), 1);
}

static void lcd_exit(struct s5p4418_fb_data_t * dat)
{
	struct lcd_backlight_data_t * bl = (struct lcd_backlight_data_t *)(dat->priv);
	if(bl)
		pwm_disable(bl->pwm);
}

static void lcd_setbl(struct s5p4418_fb_data_t * dat, int brightness)
{
	struct lcd_backlight_data_t * bl = (struct lcd_backlight_data_t *)(dat->priv);
	if(bl)
	{
		bl->brightness = brightness;
		pwm_config(bl->pwm, bl->duty_from + (bl->duty_to - bl->duty_from) * bl->brightness / (1023 + 1), bl->period, bl->polarity);
		pwm_enable(bl->pwm);
	}
}

static int lcd_getbl(struct s5p4418_fb_data_t * dat)
{
	struct lcd_backlight_data_t * bl = (struct lcd_backlight_data_t *)(dat->priv);
	if(bl)
		return bl->brightness;
	return 0;
}

static struct s5p4418_fb_data_t s5p4418_fb_data = {
	.dpcbase				= S5P4418_DPC0_BASE,
	.mlcbase				= S5P4418_MLC0_BASE,

	.width					= 1024,
	.height					= 600,
	.xdpi					= 133,
	.ydpi					= 133,
	.bits_per_pixel			= 32,
	.bytes_per_pixel		= 4,

	.rgba = {
		.r_mask				= 8,
		.r_field			= 0,
		.g_mask				= 8,
		.g_field			= 8,
		.b_mask				= 8,
		.b_field			= 16,
		.a_mask				= 8,
		.a_field			= 24,
	},

	.mode = {
		.rgbmode			= 1,
		.scanmode			= 0,
		.enbedsync			= 0,
		.polfield			= 0,
		.swaprb				= 0,
		.format				= S5P4418_DPC_FORMAT_RGB888,
		.ycorder			= S5P4418_DPC_YCORDER_CBYCRY,
		.rdither			= S5P4418_DPC_DITHER_BYPASS,
		.gdither			= S5P4418_DPC_DITHER_BYPASS,
		.bdither			= S5P4418_DPC_DITHER_BYPASS,
	},

	.timing = {
		.pixel_clock_hz		= 800000,
		.h_front_porch		= 160,
		.h_sync_width		= 20,
		.h_back_porch		= 140,
		.v_front_porch		= 12,
		.v_sync_width		= 3,
		.v_back_porch		= 20,

		.vs_start_offset	= 1,
		.vs_end_offset		= 1,
		.ev_start_offset	= 1,
		.ev_end_offset		= 1,

		.d_rgb_pvd			= 0,
		.d_hsync_cp1		= 7,
		.d_vsync_fram		= 7,
		.d_de_cp2			= 7,
	},

	.polarity = {
		.h_sync_invert		= 1,
		.v_sync_invert		= 1,
	},

	.vram_front				= &vram[0][0],
	.vram_back				= &vram[1][0],

	.init					= lcd_init,
	.exit					= lcd_exit,
	.setbl					= lcd_setbl,
	.getbl					= lcd_getbl,
};

static struct fb_t s5p4418_fb;

void s5p4418_fb_initial(void)
{
	struct s5p4418_fb_data_t * dat = &s5p4418_fb_data;

	if( (dat->bits_per_pixel != 16) && (dat->bits_per_pixel != 24) && (dat->bits_per_pixel != 32) )
		return;

	s5p4418_fb.dat = dat;
	s5p4418_fb.surface.info.bits_per_pixel = dat->bits_per_pixel;
	s5p4418_fb.surface.info.bytes_per_pixel = dat->bytes_per_pixel;
	s5p4418_fb.surface.info.red_mask_size = dat->rgba.r_mask;
	s5p4418_fb.surface.info.red_field_pos = dat->rgba.r_field;
	s5p4418_fb.surface.info.green_mask_size = dat->rgba.g_mask;
	s5p4418_fb.surface.info.green_field_pos = dat->rgba.g_field;
	s5p4418_fb.surface.info.blue_mask_size = dat->rgba.b_mask;
	s5p4418_fb.surface.info.blue_field_pos = dat->rgba.b_field;
	s5p4418_fb.surface.info.alpha_mask_size = dat->rgba.a_mask;
	s5p4418_fb.surface.info.alpha_field_pos = dat->rgba.a_field;
	s5p4418_fb.surface.info.fmt = get_pixel_format(&(s5p4418_fb.surface.info));

	s5p4418_fb.surface.w = dat->width;
	s5p4418_fb.surface.h = dat->height;
	s5p4418_fb.surface.pitch = dat->width * dat->bytes_per_pixel;
	s5p4418_fb.surface.flag = SURFACE_PIXELS_DONTFREE;
	s5p4418_fb.surface.pixels = dat->vram_front;

	s5p4418_fb.surface.clip.x = 0;
	s5p4418_fb.surface.clip.y = 0;
	s5p4418_fb.surface.clip.w = dat->width;
	s5p4418_fb.surface.clip.h = dat->height;

	memset(&s5p4418_fb.surface.maps, 0, sizeof(struct surface_maps));
	surface_set_maps(&s5p4418_fb.surface.maps);

	fb_init(&s5p4418_fb);
	fb_flush(&s5p4418_fb);

	if(dat->setbl)
		dat->setbl(dat, 1023);
}

struct surface_t * s5p4418_screen_surface(void)
{
	return &s5p4418_fb.surface;
}

void s5p4418_screen_swap(void)
{
	fb_swap(&s5p4418_fb);
}

void s5p4418_screen_flush(void)
{
	fb_flush(&s5p4418_fb);
}

void s5p4418_screen_backlight(int brightness)
{
	fb_backlight(&s5p4418_fb, brightness);
}
