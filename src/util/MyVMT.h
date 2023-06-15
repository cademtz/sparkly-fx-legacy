#pragma once

/*
* Screw all the code in this project lol I'm coming here from the future and doing my thing
*/

class CVMTHook
{
public:
	CVMTHook() { }

	// Initializes and immediately hooks
	CVMTHook(void* Instance, bool AllInstances = false) { Hook(Instance, AllInstances); }
	~CVMTHook() { Unhook(); }

	inline bool IsHooked() { return m_inst; }
	void Hook(void* Instance, bool AllInstances = false);
	void Unhook();

	template <class T>
	inline T Get(size_t Index) { return (T)m_oldvmt[Index]; }
	void Set(size_t Index, void* Function);

	static CVMTHook* FindHook(void* Instance) { return (CVMTHook*)(*(void***)Instance)[-1]; }

private:
	void* m_inst = 0;
	void** m_oldvmt = 0, ** m_newvmt = 0;
	size_t m_count = 0;
	bool m_all = false;
};