#pragma once
#include "Base.h"
#include "getvfunc.h"

class IClientPanel;
class KeyValues;
class SurfacePlat;
class Panel;
typedef unsigned VPANEL;
typedef unsigned HScheme;

class IPanel
{
public:
	virtual ~IPanel() = 0;
	virtual void Init(VPANEL vguiPanel, IClientPanel *panel) = 0;

	// methods
	virtual void SetPos(VPANEL vguiPanel, int x, int y) = 0;
	virtual void GetPos(VPANEL vguiPanel, int &x, int &y) = 0;
	virtual void SetSize(VPANEL vguiPanel, int wide, int tall) = 0;
	virtual void GetSize(VPANEL vguiPanel, int &wide, int &tall) = 0;
	virtual void SetMinimumSize(VPANEL vguiPanel, int wide, int tall) = 0;
	virtual void GetMinimumSize(VPANEL vguiPanel, int &wide, int &tall) = 0;
	virtual void SetZPos(VPANEL vguiPanel, int z) = 0;
	virtual int  GetZPos(VPANEL vguiPanel) = 0;

	virtual void GetAbsPos(VPANEL vguiPanel, int &x, int &y) = 0;
	virtual void GetClipRect(VPANEL vguiPanel, int &x0, int &y0, int &x1, int &y1) = 0;
	virtual void SetInset(VPANEL vguiPanel, int left, int top, int right, int bottom) = 0;
	virtual void GetInset(VPANEL vguiPanel, int &left, int &top, int &right, int &bottom) = 0;

	virtual void SetVisible(VPANEL vguiPanel, bool state) = 0;
	virtual bool IsVisible(VPANEL vguiPanel) = 0;
	virtual void SetParent(VPANEL vguiPanel, VPANEL newParent) = 0;
	virtual int GetChildCount(VPANEL vguiPanel) = 0;
	virtual VPANEL GetChild(VPANEL vguiPanel, int index) = 0;
private: // Too lazy to add CUtlVector class
	virtual void GetChildren(VPANEL vguiPanel) = 0;
public:
	virtual VPANEL GetParent(VPANEL vguiPanel) = 0;
	virtual void MoveToFront(VPANEL vguiPanel) = 0;
	virtual void MoveToBack(VPANEL vguiPanel) = 0;
	virtual bool HasParent(VPANEL vguiPanel, VPANEL potentialParent) = 0;
	virtual bool IsPopup(VPANEL vguiPanel) = 0;
	virtual void SetPopup(VPANEL vguiPanel, bool state) = 0;
	virtual bool IsFullyVisible(VPANEL vguiPanel) = 0;

	// gets the scheme this panel uses
	virtual HScheme GetScheme(VPANEL vguiPanel) = 0;
	// gets whether or not this panel should scale with screen resolution
	virtual bool IsProportional(VPANEL vguiPanel) = 0;
	// returns true if auto-deletion flag is set
	virtual bool IsAutoDeleteSet(VPANEL vguiPanel) = 0;
	// deletes the Panel * associated with the vpanel
	virtual void DeletePanel(VPANEL vguiPanel) = 0;

	// input interest
	virtual void SetKeyBoardInputEnabled(VPANEL vguiPanel, bool state) = 0;
	virtual void SetMouseInputEnabled(VPANEL vguiPanel, bool state) = 0;
	virtual bool IsKeyBoardInputEnabled(VPANEL vguiPanel) = 0;
	virtual bool IsMouseInputEnabled(VPANEL vguiPanel) = 0;

	// calculates the panels current position within the hierarchy
	virtual void Solve(VPANEL vguiPanel) = 0;

	// gets names of the object (for debugging purposes)
	virtual const char *GetName(VPANEL vguiPanel) = 0;
	virtual const char *GetClassName(VPANEL vguiPanel) = 0;

	// delivers a message to the panel
	virtual void SendMessage(VPANEL vguiPanel, KeyValues *params, VPANEL ifromPanel) = 0;

	// these pass through to the IClientPanel
	virtual void Think(VPANEL vguiPanel) = 0;
	virtual void PerformApplySchemeSettings(VPANEL vguiPanel) = 0;
	virtual void PaintTraverse(VPANEL vguiPanel, bool forceRepaint, bool allowForce = true) = 0;
	virtual void Repaint(VPANEL vguiPanel) = 0;
	virtual VPANEL IsWithinTraverse(VPANEL vguiPanel, int x, int y, bool traversePopups) = 0;
	virtual void OnChildAdded(VPANEL vguiPanel, VPANEL child) = 0;
	virtual void OnSizeChanged(VPANEL vguiPanel, int newWide, int newTall) = 0;

	virtual void InternalFocusChanged(VPANEL vguiPanel, bool lost) = 0;
	virtual bool RequestInfo(VPANEL vguiPanel, KeyValues *outputData) = 0;
	virtual void RequestFocus(VPANEL vguiPanel, int direction = 0) = 0;
	virtual bool RequestFocusPrev(VPANEL vguiPanel, VPANEL existingPanel) = 0;
	virtual bool RequestFocusNext(VPANEL vguiPanel, VPANEL existingPanel) = 0;
	virtual VPANEL GetCurrentKeyFocus(VPANEL vguiPanel) = 0;
	virtual int GetTabPosition(VPANEL vguiPanel) = 0;

	// used by ISurface to store platform-specific data
	virtual SurfacePlat *Plat(VPANEL vguiPanel) = 0;
	virtual void SetPlat(VPANEL vguiPanel, SurfacePlat *Plat) = 0;

	// returns a pointer to the vgui controls baseclass Panel *
	// destinationModule needs to be passed in to verify that the returned Panel * is from the same module
	// it must be from the same module since Panel * vtbl may be different in each module
	virtual Panel *GetPanel(VPANEL vguiPanel, const char *destinationModule) = 0;

	virtual bool IsEnabled(VPANEL vguiPanel) = 0;
	virtual void SetEnabled(VPANEL vguiPanel, bool state) = 0;

	// Used by the drag/drop manager to always draw on top
	virtual bool IsTopmostPopup(VPANEL vguiPanel) = 0;
	virtual void SetTopmostPopup(VPANEL vguiPanel, bool state) = 0;
};

class Panel
{
	void* _vtable;
	int _pad[18];
	VPANEL _vpanel;
public:
	inline VPANEL GetVPanel() { return _vpanel; }
};

struct Vertex_t;
class ISurface
{
public:
	void DrawSetColor(int r, int g, int b, int a)
	{
		typedef void(__thiscall* OriginalFn)(void*, int, int, int, int);
		getvfunc<OriginalFn>(this, 11)(this, r, g, b, a);
	}
	void DrawFilledRect(int x0, int y0, int x1, int y1)
	{
		typedef void(__thiscall* OriginalFn)(void*, int, int, int, int);
		getvfunc<OriginalFn>(this, 12)(this, x0, y0, x1, y1);
	}
	void DrawOutlinedRect(int x0, int y0, int x1, int y1)
	{
		typedef void(__thiscall* OriginalFn)(void*, int, int, int, int);
		getvfunc<OriginalFn>(this, 14)(this, x0, y0, x1, y1);
	}
	void DrawSetTextFont(unsigned long font)
	{
		typedef void(__thiscall* OriginalFn)(void*, unsigned long);
		getvfunc<OriginalFn>(this, 17)(this, font);
	}
	void DrawSetTextColor(int r, int g, int b, int a)
	{
		typedef void(__thiscall* OriginalFn)(void*, int, int, int, int);
		getvfunc<OriginalFn>(this, 19)(this, r, g, b, a);
	}
	void DrawSetTextPos(int x, int y)
	{
		typedef void(__thiscall* OriginalFn)(void*, int, int);
		getvfunc<OriginalFn>(this, 20)(this, x, y);
	}
	void DrawPrintText(const wchar_t *text, int textLen)
	{
		typedef void(__thiscall* OriginalFn)(void*, const wchar_t *, int, int);
		return getvfunc<OriginalFn>(this, 22)(this, text, textLen, 0);
	}
	unsigned long CreateFont()
	{
		typedef unsigned int(__thiscall* OriginalFn)(void*);
		return getvfunc<OriginalFn>(this, 66)(this);
	}
	void SetFontGlyphSet(unsigned long &font, const char *windowsFontName, int tall, int weight, int blur, int scanlines, int flags)
	{
		typedef void(__thiscall* OriginalFn)(void*, unsigned long, const char*, int, int, int, int, int, int, int);
		getvfunc<OriginalFn>(this, 67)(this, font, windowsFontName, tall, weight, blur, scanlines, flags, 0, 0);
	}
	void GetTextSize(unsigned long font, const wchar_t *text, int &wide, int &tall)
	{
		typedef void(__thiscall* OriginalFn)(void*, unsigned long, const wchar_t *, int&, int&);
		getvfunc<OriginalFn>(this, 75)(this, font, text, wide, tall);
	}
	int CreateNewTextureID(bool procedural = true)
	{
		typedef int(__thiscall *OriginalFn)(void*, bool);
		return getvfunc<OriginalFn>(this, 37)(this, procedural);
	}
	void DrawSetTextureRGBA(int id, unsigned char const* rgba, int wide, int tall, int hardwareFilter = 0, bool forceReload = 0)
	{
		typedef void(__thiscall *OriginalFn)(void*, int, unsigned char const*, int, int, int, bool);
		return getvfunc<OriginalFn>(this, 31)(this, id, rgba, wide, tall, hardwareFilter, forceReload);
	}
	void DrawSetTexture(int id)
	{
		typedef void(__thiscall *OriginalFn)(void*, int);
		return getvfunc<OriginalFn>(this, 32)(this, id);
	}
	bool IsTextureIDValid(int id)
	{
		typedef bool(__thiscall *OriginalFn)(void*, int);
		return getvfunc<OriginalFn>(this, 35)(this, id);
	}
	void DrawTexturedRect(int x, int y, int width, int height)
	{
		typedef void(__thiscall *OriginalFn)(void*, int, int, int, int);
		return getvfunc<OriginalFn>(this, 34)(this, x, y, width, height);
	}
	void DrawTexturedPolygon(int n, Vertex_t *vertices, bool bClipVertices = true)
	{
		typedef void(__thiscall *OriginalFn)(PVOID, int, Vertex_t*, bool);
		return getvfunc<OriginalFn>(this, 102)(this, n, vertices, bClipVertices);
	}
	void DrawLine(int x, int y, int x1, int y1)
	{
		typedef void(__thiscall *OriginalFn)(void*, int, int, int, int);
		return getvfunc<OriginalFn>(this, 15)(this, x, y, x1, y1);
	}
	void GetCursorPosition(int &x, int &y)
	{
		return getvfunc<void(__thiscall *)(void*, int &, int &)>(this, 96)(this, x, y);
	}
};