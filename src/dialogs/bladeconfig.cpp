 /* BonkEnc Audio Encoder
  * Copyright (C) 2001-2004 Robert Kausch <robert.kausch@bonkenc.org>
  *
  * This program is free software; you can redistribute it and/or
  * modify it under the terms of the "GNU General Public License".
  *
  * THIS PACKAGE IS PROVIDED "AS IS" AND WITHOUT ANY EXPRESS OR
  * IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
  * WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE. */

#include <dialogs/bladeconfig.h>
#include <resources.h>

configureBladeEnc::configureBladeEnc()
{
	Point	 pos;
	Size	 size;

	currentConfig = bonkEnc::currentConfig;

	bitrate = GetSliderValue();
	crc = currentConfig->blade_crc;
	copyright = currentConfig->blade_copyright;
	original = currentConfig->blade_original;
	priv = currentConfig->blade_private;
	dualchannel = currentConfig->blade_dualchannel;

	mainWnd			= new Window(bonkEnc::i18n->TranslateString("%1 encoder configuration").Replace("%1", "BladeEnc"));
	mainWnd_titlebar	= new Titlebar(TB_CLOSEBUTTON);
	divbar			= new Divider(42, OR_HORZ | OR_BOTTOM);

	pos.x = 175;
	pos.y = 29;
	size.cx = 0;
	size.cy = 0;

	btn_cancel		= new Button(bonkEnc::i18n->TranslateString("Cancel"), NIL, pos, size);
	btn_cancel->onClick.Connect(&configureBladeEnc::Cancel, this);
	btn_cancel->SetOrientation(OR_LOWERRIGHT);

	pos.x -= 88;

	btn_ok			= new Button(bonkEnc::i18n->TranslateString("OK"), NIL, pos, size);
	btn_ok->onClick.Connect(&configureBladeEnc::OK, this);
	btn_ok->SetOrientation(OR_LOWERRIGHT);

	pos.x = 7;
	pos.y = 11;
	size.cx = 168;
	size.cy = 43;

	group_bit		= new GroupBox(bonkEnc::i18n->TranslateString("Bitrate"), pos, size);

	pos.x += 176;

	group_copyright		= new GroupBox(bonkEnc::i18n->TranslateString("Copyright bit"), pos, size);

	pos.x -= 176;
	pos.y += 55;

	group_crc		= new GroupBox(bonkEnc::i18n->TranslateString("CRC"), pos, size);

	pos.x += 176;

	group_original		= new GroupBox(bonkEnc::i18n->TranslateString("Original bit"), pos, size);

	pos.x -= 176;
	pos.y += 55;

	group_dualchannel	= new GroupBox(bonkEnc::i18n->TranslateString("Channels"), pos, size);

	pos.x += 176;

	group_private		= new GroupBox(bonkEnc::i18n->TranslateString("Private bit"), pos, size);

	pos.x = 17;
	pos.y = 24;
	size.cx = 103;
	size.cy = 0;

	slider_bit		= new Slider(pos, size, OR_HORZ, &bitrate, 0, 13);
	slider_bit->onClick.Connect(&configureBladeEnc::SetBitrate, this);

	pos.x += 110;
	pos.y += 2;

	text_bit		= new Text("", pos);
	SetBitrate();

	pos.x += 66;
	pos.y -= 2;
	size.cx += 44;

	check_copyright		= new CheckBox(bonkEnc::i18n->TranslateString("Set Copyright bit"), pos, size, &copyright);

	pos.x = 17;
	pos.y += 55;
	size.cx = 147;
	size.cy = 0;

	check_crc		= new CheckBox(bonkEnc::i18n->TranslateString("Enable CRC"), pos, size, &crc);

	pos.x += 176;

	check_original		= new CheckBox(bonkEnc::i18n->TranslateString("Set Original bit"), pos, size, &original);

	pos.x = 17;
	pos.y += 55;
	size.cx = 147;
	size.cy = 0;

	check_dualchannel	= new CheckBox(bonkEnc::i18n->TranslateString("Dual channel encoding"), pos, size, &dualchannel);

	pos.x += 176;

	check_private		= new CheckBox(bonkEnc::i18n->TranslateString("Set Private bit"), pos, size, &priv);

	RegisterObject(mainWnd);

	mainWnd->RegisterObject(btn_ok);
	mainWnd->RegisterObject(btn_cancel);
	mainWnd->RegisterObject(group_bit);
	mainWnd->RegisterObject(slider_bit);
	mainWnd->RegisterObject(text_bit);
	mainWnd->RegisterObject(group_crc);
	mainWnd->RegisterObject(check_crc);
	mainWnd->RegisterObject(group_copyright);
	mainWnd->RegisterObject(check_copyright);
	mainWnd->RegisterObject(group_original);
	mainWnd->RegisterObject(check_original);
	mainWnd->RegisterObject(group_private);
	mainWnd->RegisterObject(check_private);
	mainWnd->RegisterObject(group_dualchannel);
	mainWnd->RegisterObject(check_dualchannel);
	mainWnd->RegisterObject(mainWnd_titlebar);
	mainWnd->RegisterObject(divbar);

	mainWnd->SetFlags(WF_NOTASKBUTTON);
	mainWnd->SetIcon(Bitmap::LoadBitmap("bonkenc.pci", 0, NIL));
	mainWnd->SetMetrics(Point(140, 140), Size(364, 242));
}

configureBladeEnc::~configureBladeEnc()
{
	delete mainWnd_titlebar;
	delete mainWnd;
	delete divbar;
	delete group_bit;
	delete slider_bit;
	delete text_bit;
	delete btn_ok;
	delete btn_cancel;
	delete group_crc;
	delete check_crc;
	delete group_copyright;
	delete check_copyright;
	delete group_original;
	delete check_original;
	delete group_private;
	delete check_private;
	delete group_dualchannel;
	delete check_dualchannel;
}

Int configureBladeEnc::ShowDialog()
{
	mainWnd->Stay();

	return mainWnd->value;
}

Void configureBladeEnc::OK()
{
	currentConfig->blade_bitrate = GetBitrate();
	currentConfig->blade_crc = crc;
	currentConfig->blade_copyright = copyright;
	currentConfig->blade_original = original;
	currentConfig->blade_private = priv;
	currentConfig->blade_dualchannel = dualchannel;

	mainWnd->Close();
}

Void configureBladeEnc::Cancel()
{
	mainWnd->Close();
}

Void configureBladeEnc::SetBitrate()
{
	text_bit->SetText(String::FromInt(GetBitrate()).Append(" kbit"));
}

Int configureBladeEnc::GetBitrate()
{
	switch (bitrate)
	{
		case 0:
			return 32;
		case 1:
			return 40;
		case 2:
			return 48;
		case 3:
			return 56;
		case 4:
			return 64;
		case 5:
			return 80;
		case 6:
			return 96;
		case 7:
			return 112;
		case 8:
			return 128;
		case 9:
			return 160;
		case 10:
			return 192;
		case 11:
			return 224;
		case 12:
			return 256;
		case 13:
			return 320;
		default:
			return 128;
	}
}

Int configureBladeEnc::GetSliderValue()
{
	switch (currentConfig->blade_bitrate)
	{
		case 32:
			return 0;
		case 40:
			return 1;
		case 48:
			return 2;
		case 56:
			return 3;
		case 64:
			return 4;
		case 80:
			return 5;
		case 96:
			return 6;
		case 112:
			return 7;
		case 128:
			return 8;
		case 160:
			return 9;
		case 192:
			return 10;
		case 224:
			return 11;
		case 256:
			return 12;
		case 320:
			return 13;
		default:
			return 8;
	}
}