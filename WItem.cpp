﻿#include <lbpch.h>
#include<api\types\types.h>
#include<api\event\genericEvent.h>
static uintptr_t icnt_off;
static bool inMagic;
unsigned char WItem::getCount() const {
	return *(unsigned char*)(((uintptr_t)v) + icnt_off);
}
THook(void*, "?_setItem@ItemStackBase@@IEAA_NH@Z", void* a, int b) {
	if (inMagic)
		return nullptr;
	return original(a, b);
}
#include<random>
static void procoff() {
	unsigned char RV = 0;
	while (!RV)
		RV = std::random_device()();
	bool success = false;
	inMagic = true;
	char filler[700];
	memset(filler, 0xff, sizeof(filler));
	SymCall("?init@ItemStackBase@@IEAAXHHH@Z", void, void*, int, int, int)(filler, 0, 125, 0);
	inMagic = false;
	for (int i = 0; i < 512; ++i) {
		if (filler[i] == 125) {
			if (icnt_off) {
				LOG.p<LOGLVL::Error>("[WItem] Warning!!! last off ", icnt_off,"try again");
				success = false;
				break;
			}
			icnt_off = i;
			success = true;
		}
	}
	if (icnt_off == 0) {
		LOG.p<LOGLVL::Fatal>("[WItem] Cant Find off!!!", icnt_off);
	}
	else {
		if (success)
			LOG("[WItem] Debug!!! off", icnt_off);
		else
			procoff();
	}
}
struct determine_off {
	determine_off() {
		addListener([](ServerStartedEvent&) {
			procoff();
		});
	}
};
static determine_off __execnow;