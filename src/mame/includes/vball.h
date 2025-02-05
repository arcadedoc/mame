// license:BSD-3-Clause
// copyright-holders:Paul Hampson

#include "machine/gen_latch.h"
#include "machine/timer.h"
#include "emupal.h"
#include "screen.h"
#include "tilemap.h"

class vball_state : public driver_device
{
public:
	vball_state(const machine_config &mconfig, device_type type, const char *tag)
		: driver_device(mconfig, type, tag),
		m_maincpu(*this, "maincpu"),
		m_audiocpu(*this, "audiocpu"),
		m_gfxdecode(*this, "gfxdecode"),
		m_screen(*this, "screen"),
		m_palette(*this, "palette"),
		m_soundlatch(*this, "soundlatch"),
		m_attribram(*this, "attribram"),
		m_videoram(*this, "videoram"),
		m_scrolly_lo(*this, "scrolly_lo"),
		m_spriteram(*this, "spriteram") { }

	void vball(machine_config &config);

private:
	required_device<cpu_device> m_maincpu;
	required_device<cpu_device> m_audiocpu;
	required_device<gfxdecode_device> m_gfxdecode;
	required_device<screen_device> m_screen;
	required_device<palette_device> m_palette;
	required_device<generic_latch_8_device> m_soundlatch;

	required_shared_ptr<uint8_t> m_attribram;
	required_shared_ptr<uint8_t> m_videoram;
	required_shared_ptr<uint8_t> m_scrolly_lo;
	required_shared_ptr<uint8_t> m_spriteram;

	int m_scrollx_hi = 0;
	int m_scrolly_hi = 0;
	int m_scrollx_lo = 0;
	int m_gfxset = 0;
	int m_scrollx[256]{};
	int m_bgprombank = 0;
	int m_spprombank = 0;
	tilemap_t *m_bg_tilemap = nullptr;

	void irq_ack_w(offs_t offset, uint8_t data);
	void bankswitch_w(uint8_t data);
	void scrollx_hi_w(uint8_t data);
	void scrollx_lo_w(uint8_t data);
	void videoram_w(offs_t offset, uint8_t data);
	void attrib_w(offs_t offset, uint8_t data);

	TILEMAP_MAPPER_MEMBER(background_scan);
	TILE_GET_INFO_MEMBER(get_bg_tile_info);

	virtual void machine_start() override;
	virtual void video_start() override;

	uint32_t screen_update(screen_device &screen, bitmap_ind16 &bitmap, const rectangle &cliprect);
	TIMER_DEVICE_CALLBACK_MEMBER(vball_scanline);
	void bgprombank_w(int bank);
	void spprombank_w(int bank);
	void draw_sprites(bitmap_ind16 &bitmap, const rectangle &cliprect);
	inline int scanline_to_vcount(int scanline);

	void main_map(address_map &map);
	void sound_map(address_map &map);
};
