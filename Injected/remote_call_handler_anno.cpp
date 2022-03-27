#include "remote_call_handler_anno.h"
#include "hook.h"
#include "anno_native.h"
#include "anno_tools.h"
#include "log.h"
#include <windows.h>

extern "C"
{
	uint64_t get_area_from_tls();
}

bool RemoteCallHandlerAnno::WriteMessageBox(const std::string& message)
{
	MessageBoxA(NULL, message.c_str(), "Write message to log", MB_OK);
	return true;
}

bool RemoteCallHandlerAnno::GetGameTime(uint64_t* time, uint64_t* frame)
{
	HookManager::Get().ExecuteInHookSync(HookedFunction::GameTimeHook,
		[&](HookData data) -> bool
		{
			*time = *(uint64_t*)(data.rbx + 0x60);
			*frame = *(uint64_t*)(data.rbx + 0x70);

			return true;
		});

	return true;
}

bool RemoteCallHandlerAnno::DebugGetResourceInfoFromAddress(const uint64_t& address, IslandResource* resource)
{
	return ExtractResourceNodeInfo(address, resource);
}

bool RemoteCallHandlerAnno::DebugGetResourceChainInfoFromAddress(const uint64_t& address, std::vector<IslandResource>* resource)
{
	return ExtractResourceNodeChianInfo(address, resource);
}

bool RemoteCallHandlerAnno::DebugGetIslandNameFromAddress(const uint64_t& address, std::string* name)
{
	uint64_t name_address = address + 0x118;
	ReadAnnoString(name_address, *name);
	return true;
}

bool RemoteCallHandlerAnno::DebugReadStringFromAddress(const uint64_t& address, std::string* name)
{
	ReadAnnoString(address, *name);
	return true;
}

bool RemoteCallHandlerAnno::DebugGetIslandResources(const uint64_t& address, std::vector<IslandResource>* resources)
{
	uint64_t resource_struct_address = *(uint64_t*)(address + 0x170);
	uint64_t resource_chain_start = **(uint64_t**)(resource_struct_address + 0x40);

	if (!ExtractResourceNodeChianInfo(resource_chain_start, resources))
		return false;

	return true;
}

bool RemoteCallHandlerAnno::DebugGetIslandChainFromAddress(const uint64_t& address, std::vector<IslandInfo>* islands)
{
	return ExtractIslandChainFromAddress(address, islands);
}

bool RemoteCallHandlerAnno::DebugGetFirstAreaStructAddress(uint64_t* address)
{
	HookManager::Get().ExecuteInHookSync(HookedFunction::SessionTickHook,
		[&](HookData data) -> bool
		{
			*address = get_area_from_tls();
			return true;
		});

	return true;
}

bool RemoteCallHandlerAnno::DebugGetAreaWithCode(const uint32_t& areaCode, uint64_t* address)
{
	uint64_t temporary_address = 0;
	int attempts = 0;
	HookManager::Get().ExecuteInHookSync(HookedFunction::SessionTickHook,
		[&](HookData data) -> bool
		{
			// Don't keep going forever, if you pass a bad code,
			// we want to return eventually
			if (++attempts > 100)
				return true;

			temporary_address = get_area_from_tls();

			uint16_t current_area_code = 0;
			GetAreaCode(temporary_address, &current_area_code);

			if (current_area_code == areaCode)
			{
				*address = temporary_address;
				return true;
			}

			return false;
		});

	return true;
}

bool RemoteCallHandlerAnno::GetPlayerIslandsInWorld(const uint32_t& area, std::vector<IslandInfo>* islands)
{
	uint64_t area_address = 0;
	int attempts = 0;

	HookManager::Get().ExecuteInHookSync(HookedFunction::SessionTickHook,
		[&](HookData data) -> bool
		{
			// Don't keep going forever, if you pass a bad code,
			// we want to return eventually
			if (++attempts > 512)
				return true;

			area_address = get_area_from_tls();

			uint16_t current_area_code = 0;
			GetAreaCode(area_address, &current_area_code);

			if (current_area_code == area)
			{
				uint64_t island_list_pointer;
				GetIslandListFromAreaAddress(area_address, &island_list_pointer);

				// Follow the pointer once to get past the 'dud' pointers???
				island_list_pointer = *(uint64_t*)island_list_pointer;
				island_list_pointer = *(uint64_t*)island_list_pointer;

				ExtractIslandChainFromAddress(island_list_pointer, islands);
				return true;
			}

			return false;
		});

	return true;
}
	