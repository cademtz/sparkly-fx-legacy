#include "Controls.h"
#include "CDraw.h"
#include "Menu.h"
#include "Styles.h"
#include "Icons.h"
#include "Clipboard.h"
#include <string_view>
#include <optional>

static TextureHolder arrow_tex, arrowside_tex, arrowdown_tex;
static TextureHolder colorpicker_tex, brightness_tex, picker_tex;

#define LTEXT SColor(220)
#define BTEXT SColor(150)
#define HTEXT SColor(90, 160, 225)
#define CTEXT SColor(180)
#define BACKGR SColor(65, 65, 72)

void InitTextures()
{
	arrow_tex = TextureHolder(arrow, 8, 8);
	arrowside_tex = TextureHolder(arrowside, 8, 8);
	arrowdown_tex = TextureHolder(arrowdown, 8, 8);

	// Hue and saturation gradient
	uint8_t* coloures = new uint8_t[128 * 128 * 4];
	int i = 0;
	for (int h = 0; h < 128; h++)
	{
		for (int w = 0; w < 128; w++)
		{
			SColor hsv = hsv2rgb(float(w) / 128, float(128 - h) / 128.f, 1);
			coloures[i] = hsv[0], coloures[i + 1] = hsv[1], coloures[i + 2] = hsv[2], coloures[i + 3] = hsv[3];
			i += 4;
		}
	}
	i = 0;

	// Value gradient
	uint8_t* value = new uint8_t[32 * 128 * 4];
	for (int h = 0; h < 128; h++)
	{
		for (int w = 0; w < 32; w++)
		{
			SColor clr(((128 - h) / 128.f) * 255.f, w > 15 ? 0 : 255);
			value[i] = clr[0], value[i + 1] = clr[1], value[i + 2] = clr[2], value[i + 3] = clr[3];
			i += 4;
		}
	}

	colorpicker_tex = TextureHolder(coloures, 128, 128);
	brightness_tex = TextureHolder(value, 32, 128);
	picker_tex = TextureHolder(picker, 8, 8);
}

// ===== BaseControl =====

void BaseControl::RunControl(int Index)
{
	if (type == e_control::null)
		return;

	bool mouse = gMenu.mouseOver(x, y, GetWidth(), GetHeight());
	if (gMenu.GetFocus() == Index && !(flags & noinput) && mouse)
		HandleInput();
	if (!(flags & nodraw))
		Draw(mouse);
}

// ===== TabGroup =====

int TabGroup::Draw(bool mouseOver)
{
	h = GetHeight();

	int ty = y;
	for (size_t i = 0; i < tabs.size(); i++)
	{
		//if (tab->visible != nullptr && !*tab->visible)
		//continue;

		tabs[i]->SetWidth(w);
		tabs[i]->SetPos(x, ty);
		tabs[i]->enabled = tabs[i] == active;

		tabs[i]->HandleInput();
		tabs[i]->Draw(gMenu.mouseOver(x, ty, w, GetTabHeight));

		ty += GetTabHeight + spacing;
	}

	return h;
}

void TabGroup::HandleInput()
{
	h = GetHeight();
	if (!gMenu.mouseOver(x, y, w, h))
		return;

	int ty = y;
	for (size_t i = 0; i < tabs.size(); i++)
	{
		if (gMenu.mouseOver(x, ty, w, GetTabHeight) && gMenu.mb == e_mb::lclick)
		{
			active = tabs[i];
			break;
		}

		ty += GetTabHeight + spacing;
	}
}

// ===== Tab =====

int Tab::Draw(bool mouseOver)
{
	SColor clr = enabled ? LTEXT : BTEXT;

	if (mouseOver)
		gDraw.DrawRect(x, y, w, h, SColor(18));
	gDraw.DrawString(x + 20, y + 2, clr, name, gFonts.calibri_light);

	return h;
}

// ===== Groupbox =====

int Groupbox::Draw(bool mouseOver)
{
	// Initializing our height variable
	GetHeight();

	int strw, strh;
	gBase.Surface->GetTextSize(gFonts.verdana_bold, ToWchar(name).c_str(), strw, strh);

	y += (strh / 2);

	gDraw.DrawLine(x, y, x, y + h, SColor(80));
	gDraw.DrawLine(x + w, y, x + w, y + h, SColor(80));
	gDraw.DrawLine(x, y + h, x + w, y + h, SColor(80));

	gDraw.DrawString(x + (w / 2) - (strw / 2), y - (strh / 2), SColor(110), name, gFonts.verdana_bold);
	gDraw.DrawLine(x, y, x + (w / 2) - (strw / 2) - 5, y, SColor(80));
	gDraw.DrawLine(x + (w / 2) + (strw / 2) + 5, y, x + w, y, SColor(80));

	int cx = x + SPACING, cy = y + SPACING;
	for (size_t i = 0; i < children.size(); i++)
	{
		children[i]->SetPos(cx, cy);
		children[i]->SetWidth(w - (SPACING * 2));

		bool over = gMenu.mouseOver(cx, cy, children[i]->GetWidth(), children[i]->GetHeight());
		bool getInput = !(children[i]->flags & noinput) && over && !gMenu.IsDialogOpen();

		children[i]->Draw(getInput);
		cy += children[i]->GetHeight() + SPACING;
	}

	y -= (strh / 2);

	return h;
}

void Groupbox::HandleInput()
{
	int strw, strh;
	gBase.Surface->GetTextSize(gFonts.verdana_bold, ToWchar(name).c_str(), strw, strh);

	int cx = x + SPACING, cy = y + SPACING + (strh / 2);
	for (size_t i = 0; i < children.size(); i++)
	{
		children[i]->SetPos(cx, cy);
		children[i]->SetWidth(w - (SPACING * 2));

		bool over = gMenu.mouseOver(cx, cy, children[i]->GetWidth(), children[i]->GetHeight());
		bool getInput = !(children[i]->flags & noinput) && over && !gMenu.IsDialogOpen();
		if (getInput)
			children[i]->HandleInput();

		cy += children[i]->GetHeight() + SPACING;
	}
}

int Groupbox::GetHeight()
{
	h = SPACING;
	for (size_t i = 0; i < children.size(); i++)
	{
		if (children[i]->visible && !*children[i]->visible)
			continue;
		h += children[i]->GetHeight() + SPACING;
	}

	int strw, strh;
	gBase.Surface->GetTextSize(gFonts.verdana_bold, ToWchar(name).c_str(), strw, strh);

	return h + (strh / 2);
}

// ===== Checkbox =====

int Checkbox::Draw(bool mouseOver)
{
	if (value)
		gDraw.DrawRect(x + 2, y + 2, h - 4, h - 4, SColor(35, 135, 230));

	gDraw.OutlineRect(x, y, h, h, SColor(100));
	gDraw.DrawString(x + 18, y - 1, mouseOver ? HTEXT : CTEXT, name, gFonts.verdana_bold);

	return h;
}

void Checkbox::HandleInput()
{
	if (gMenu.mb == e_mb::lclick || gMenu.mb == e_mb::rclick)
		value = !value;
}

bool Checkbox::QuickReturn(bool Value, int X, int Y, int W)
{
	int Width = W == -1 ? w : W;
	bool hovered = gMenu.mouseOver(X, Y, Width, h);
	value = Value, x = X, y = Y, w = Width;
	Draw(hovered);
	if (hovered)
		HandleInput();

	return value;
}

// ===== DrawPanel =====

int DrawPanel::Draw(bool mouseOver)
{
	// Draw a control panel, then draw our stuff within it
	int topbar = gMenu.style->ControlPanel(x, y, w, h, name);
	draw(x, y + topbar, w, h - topbar);

	return h;
}

// ===== Slider =====

int Slider::Draw(bool mouseOver)
{
	int nw = w - 30;
	SColor clr = mouseOver ? HTEXT : CTEXT;
	gDraw.DrawString(x, y, clr, name, gFonts.verdana_bold);
	gDraw.DrawRect(x, y + 17, nw, 4, BACKGR);

	int percent = nw * (value - min) / (max - min);
	if (mouseOver)
	{
		gDraw.DrawRect(x, y + 17, percent, 4, HTEXT);
		arrow_tex.Draw(x + percent - 3, y + 17, CTEXT);
	}
	else
		gDraw.DrawRect(x, y + 17, percent, 4, SColor(85, 85, 95));
	gDraw.DrawString(x + nw + 3, y + 9, SColor(125, 125, 130), to_string(value), gFonts.verdana_bold);

	return h;
}

void Slider::HandleInput()
{
	if (gMenu.mb == e_mb::lclick || gMenu.mw == e_mw::up)
		value -= step;
	else if (gMenu.mb == e_mb::rclick || gMenu.mw == e_mw::down)
		value += step;

	if (value > max)
		value = min;
	else if (value < min)
		value = max;
}

// ===== Listbox =====
#define TEXTH 15
int Listbox::Draw(bool mouseOver)
{
	SColor clr = mouseOver ? HTEXT : CTEXT;

	gDraw.DrawString(x, y, clr, name, gFonts.verdana_bold);

	gMenu.style->DialogButton(x, y + TEXTH, w, list[value].c_str(), mouseOver);

	arrowdown_tex.Draw(x + w - 10, y + TEXTH + 6, SColor(125, 125, 140));
	return h;
}

void DrawListbox(void* data, size_t Index);
static Dialog listDlg(DrawListbox);

void Listbox::HandleInput()
{
	if (value > list.size())
		value = list.size() - 1;

	if (gMenu.mb != e_mb::lclick)
		return;

	listDlg.data = this;
	gMenu.OpenDialog(listDlg);
}

void DrawListbox(void* data, size_t Index)
{
	BaseControl* control = (BaseControl*)data;
	if (control == nullptr || control->type != e_control::listbox)
		return gMenu.CloseDialog(Index);

	Listbox* listbox = (Listbox*)control;
	int x = listbox->x, y = listbox->y + listbox->GetHeight(), w = listbox->GetWidth(), h = listbox->list.size() * 16 + 20;

	if (gMenu.mb == e_mb::lclick && !gMenu.mouseOver(x, y - listbox->GetHeight(), w, h + listbox->GetHeight()))
		return gMenu.CloseDialog(Index);

	gMenu.style->Dialog(x, y, w, h);

	x += 10, y += 8, w -= 20, h -= 20;
	for (size_t i = 0; i < listbox->list.size(); i++)
	{
		if (gMenu.mouseOver(x, y, w, 15))
		{
			if (gMenu.mb == e_mb::lclick)
			{
				listbox->value = i;
				return gMenu.CloseDialog(Index);
			}

			gDraw.DrawRect(x, y, w, 16, SColor(44, 44, 55));
		}
		gDraw.DrawString(x, y + 1, CTEXT, listbox->list[i], gFonts.verdana_bold);
		y += 16;
	}
}

// ===== SColor =====

int ColorPicker::Draw(bool mouseOver)
{
	gDraw.DrawString(x, y, mouseOver ? HTEXT : CTEXT, name, gFonts.verdana_bold);
	gDraw.DrawRect(x, y + 17, w, 5, color);

	if (!mouseOver)
		gDraw.DrawRect(x, y + 17, w, 5, SColor(0, 150));

	return h;
}

void DrawColorBox(void* data, size_t Index);
static Dialog colorDlg(DrawColorBox);
// Parse color in the form of `#RRGGBB` or `RRGGBB`
static std::optional<SColor> ParseHexRGB(std::string_view text)
{
	if (text.length() == 0)
		return std::nullopt;
	
	size_t str_index = 0;
	if (text[0] == '#')
		++str_index;
	
	SColor result(0);
	for (size_t c = 0; c < 3; ++c) // For each color channel
	{
		for (size_t _i = 0; _i < 2; ++_i, ++str_index) // Parse 2 nibbles
		{
			if (str_index >= text.length())
				return std::nullopt;
			
			uint8_t nibble;
			char ch = text[str_index];
			if (ch >= 'a' && ch <= 'f')
				nibble = ch - 'a' + 0xA;
			else if (ch >= 'A' && ch <= 'F')
				nibble = ch - 'A' + 0xA;
			else if (ch >= '0' && ch <= '9')
				nibble = ch - '0';
			else
				return std::nullopt;
			
			result[c] = (result[c] << 4) | nibble;
		}
	}
	return result;
}

void ColorPicker::HandleInput()
{
	if (gMenu.mb != e_mb::lclick)
		return;

	colorDlg.x = x, colorDlg.y = y;
	colorDlg.data = this;
	gMenu.OpenDialog(colorDlg);
}

void DrawColorBox(void* data, size_t Index)
{
	const int dlg_width = 173;
	const int dlg_height = 220;

	ColorPicker* colorpicker = (ColorPicker*)data;
	if (colorpicker == nullptr || colorpicker->type != e_control::colorpicker)
		return gMenu.CloseDialog(Index);

	if (gMenu.mb == e_mb::lclick && !gMenu.mouseOver(colorDlg.x, colorDlg.y, dlg_width, dlg_height))
		return gMenu.CloseDialog(Index);

	gMenu.style->Dialog(colorDlg.x, colorDlg.y, dlg_width, dlg_height);
	int X = colorDlg.x + 2, Y = colorDlg.y + 2, W = dlg_width - 4, H = dlg_height - 4;

	char text_buffer[64];
	static int ccursorx = 50, ccursory = 50;
	static int vcursory = 0;
	int next_control_y = Y + 30 + colorpicker_tex.GetHeight() + 5;
	static bool mColorbox = false, mValue = false;

	if (gMenu.mb == e_mb::lclick && gMenu.mouseOver(X + 5, Y + 30, colorpicker_tex.GetWidth(), colorpicker_tex.GetHeight()))
		mColorbox = true;
	else if (gMenu.mb != e_mb::ldown)
		mColorbox = false;

	if (gMenu.mb == e_mb::lclick && gMenu.mouseOver(X + colorpicker_tex.GetWidth() + 10, Y + 30, 15, brightness_tex.GetHeight()))
		mValue = true;
	else if (gMenu.mb != e_mb::ldown)
		mValue = false;

	bool is_dragging_color = mColorbox || mValue;
	if (mColorbox)
	{
		ccursorx = gMenu.mouse.x - X - 5, ccursory = gMenu.mouse.y - Y - 30;

		if (ccursorx < 0)
			ccursorx = 0;
		else if (ccursorx > colorpicker_tex.GetWidth() - 1)
			ccursorx = colorpicker_tex.GetWidth() - 1;

		if (ccursory < 0)
			ccursory = 0;
		else if (ccursory > colorpicker_tex.GetHeight())
			ccursory = colorpicker_tex.GetHeight();
	}
	else if (mValue)
	{
		vcursory = gMenu.mouse.y - Y - 30;

		if (vcursory < 0)
			vcursory = 0;
		else if (vcursory > brightness_tex.GetHeight())
			vcursory = brightness_tex.GetHeight();
	}


	static Checkbox checkbox("Default");
	bool was_default = colorpicker->bDef;
	colorpicker->bDef = checkbox.QuickReturn(colorpicker->bDef, X + 5, next_control_y);
	next_control_y += checkbox.GetHeight() + 5;

	// If 'Default' was unchecked, then make the picker grab the color under the cursor
	if (was_default && !colorpicker->bDef)
		is_dragging_color = true;

	if (colorpicker->bDef)
		colorpicker->color = colorpicker->cDef;
	else if (is_dragging_color)
	{
		colorpicker->color = hsv2rgb(
			float(ccursorx) / colorpicker_tex.GetWidth(),
			1.f - (float(ccursory) / colorpicker_tex.GetHeight()),
			1.f - (float(vcursory) / brightness_tex.GetHeight()));
	}
	else // Copy/paste color
	{
		if (gMenu.keys[VK_CONTROL] && gMenu.keys['C'])
		{
			sprintf_s(text_buffer, "#%.2X%.2X%.2X", colorpicker->color[0], colorpicker->color[1], colorpicker->color[2]);
			CClipboard::Paste(text_buffer);
		}
		else if (gMenu.keys[VK_CONTROL] && gMenu.keys['V'])
		{
			std::optional<std::string> result = CClipboard::CopyAscii();
			if (result)
			{
				std::optional<SColor> new_color = ParseHexRGB(result.value());
				if (new_color)
					colorpicker->color = new_color.value();
			}
		}
	}
	
	sprintf_s(text_buffer, "#%.2X%.2X%.2X", colorpicker->color[0], colorpicker->color[1], colorpicker->color[2]);
	gDraw.DrawString(X + 5, next_control_y, SColor(230), text_buffer, gFonts.verdana_bold);
	next_control_y += 18;

	sprintf_s(text_buffer, "(Use Ctrl+C & Ctrl+V)", ccursorx, ccursory, vcursory);
	gDraw.DrawString(X + 5, next_control_y, SColor(150), text_buffer, gFonts.verdana_bold);

	gDraw.OutlineRect(X + 4, Y + 29, colorpicker_tex.GetWidth() + 2, colorpicker_tex.GetHeight() + 2, SColor(58, 58, 70));
	colorpicker_tex.Draw(X + 5, Y + 30, SColor(255 - (float(vcursory) / brightness_tex.GetHeight()) * 255));

	gDraw.OutlineRect(X + colorpicker_tex.GetWidth() + 9, Y + 29, 16 + 2, brightness_tex.GetHeight() + 2, SColor(58, 58, 70));
	brightness_tex.Draw(X + colorpicker_tex.GetWidth() + 10, Y + 30);

	gDraw.OutlineRect(X + 4, Y + 4, colorpicker_tex.GetWidth() + 23, 22, SColor(58, 58, 70));
	gDraw.DrawRect(X + 5, Y + 5, colorpicker_tex.GetWidth() + 21, 20, colorpicker->color);

	picker_tex.Draw(X + 5 + ccursorx - 4, Y + 30 + ccursory - 4);
	arrowside_tex.Draw(X + colorpicker_tex.GetWidth() + 30, Y + 30 + vcursory - 2);
}

// ===== KeyBind =====

int KeyBind::Draw(bool mouseOver)
{
	SColor clr = mouseOver ? HTEXT : CTEXT;

	gDraw.DrawString(x, y, clr, name, gFonts.verdana_bold);

	gDraw.DrawRect(x, y + TEXTH, w, TEXTH, SColor(42, 42, 48));
	gDraw.OutlineRect(x, y + TEXTH, w, TEXTH, SColor(60));

	gDraw.DrawString(x + 3, y + TEXTH, mouseOver ? clr : SColor(125, 125, 130), gKey.KeyToString(key), gFonts.verdana_bold);

	gDraw.DrawRect(x + w - 10, y + TEXTH + 5, 6, 1, SColor(125, 125, 140));
	gDraw.DrawRect(x + w - 10, y + TEXTH + 7, 6, 1, SColor(125, 125, 140));
	gDraw.DrawRect(x + w - 10, y + TEXTH + 9, 6, 1, SColor(125, 125, 140));

	return h;
}

void DrawKeyBindBox(void* data, size_t Index);
static Dialog keyDlg(DrawKeyBindBox);

void KeyBind::HandleInput()
{
	if (gMenu.mb != e_mb::lclick)
		return;

	keyDlg.x = x, keyDlg.y = y;
	keyDlg.h = 100;

	keyDlg.data = this;
	gMenu.OpenDialog(keyDlg);
}
bool KeyBind::UpdateKeys()
{
	if (!gMenu.last_key || !gKey.AcceptedKey(gMenu.last_key))
		return false;

	if (gMenu.last_key == VK_ESCAPE)
		return true;

	key = gMenu.last_key;
	return true;
}

bool KeyBind::KeyDown()
{
	switch (mode)
	{
	case e_kbmode::disabled:
		return false;
	case e_kbmode::always:
		return true;
	case e_kbmode::hold:
		return gMenu.keys[key];
	case e_kbmode::toggle:
		if (!gMenu.keys[key])
			keyHeld = false;

		if (!keyHeld && gMenu.keys[key])
		{
			toggled = !toggled;
			keyHeld = true;
		}

		return toggled;
	}
	return false;
}

void DrawKeyBindBox(void* data, size_t Index)
{
	BaseControl* control = (BaseControl*)data;
	if (control == nullptr || control->type != e_control::keybind)
		return gMenu.CloseDialog(Index);

	static bool bWait = false;
	if (gMenu.mb == e_mb::lclick && !bWait && !gMenu.mouseOver(keyDlg.x, keyDlg.y, keyDlg.w, keyDlg.h))
		return gMenu.CloseDialog(Index);

	KeyBind* kb = (KeyBind*)control;

	gMenu.style->Dialog(keyDlg.x, keyDlg.y, keyDlg.w, keyDlg.h);
	int x = keyDlg.x + 2, y = keyDlg.y + 2, w = keyDlg.w - 4, h = keyDlg.h - 4;

	gDraw.DrawString(x + 5, y + 5, SColor(100), kb->name, gFonts.verdana_bold);
	y += 21, h -= 21;

	bool hover_setkey = gMenu.mouseOver(x + 6, y + 6, w - 12, 18);
	if (!bWait && hover_setkey && gMenu.mb == e_mb::lclick)
		bWait = true;

	if (bWait)
		bWait = !kb->UpdateKeys();

	gDraw.OutlineRect(x + 6, y + 6, w - 12, 18, SColor(80));
	gDraw.DrawRect(x + 7, y + 7, w - 14, 16, SColor(hover_setkey ? 65 : 40));
	gDraw.DrawString(x + 9, y + 8, SColor(200), bWait ? "Select a key (or Escape)" : gKey.KeyToString(kb->key), gFonts.verdana_bold);

	static Listbox list("Setting", { "Disabled", "Always on", "Hold key", "Toggle with key" });
	list.SetPos(x + 6, y + 30), list.SetWidth(w - 12);

	static bool list_open = false;
	if (gMenu.GetFocus() == Index && list_open)
		kb->mode = (e_kbmode)list.value, list_open = false;

	list_open = gMenu.GetFocus() != Index;

	list.value = (int)kb->mode;
	list.RunControl(Index);
}