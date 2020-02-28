#pragma once
#include "eventBase.h"

class PlayerChatEvent : public IGenericPlayerEvent<PlayerChatEvent> {
public:
	string& _chat;
	string& _name;
	PlayerChatEvent(ServerPlayer& sp, string& chat, string& name) : IGenericPlayerEvent(sp), _chat(chat), _name(name) {}
	const string& getChat() {
		return _chat;
	}
	const string& getName() {
		return _name;
	}
};
class PlayerCMDEvent : public IGenericPlayerEvent<PlayerCMDEvent> {
public:
	string& _cmd;
	PlayerCMDEvent(ServerPlayer& sp, string& cmd) : IGenericPlayerEvent(sp), _cmd(cmd) {}
	const string& getCMD() {
		return _cmd;
	}
};
class PlayerPreJoinEvent : public IEventBase<PlayerPreJoinEvent> {
public:
	class Certificate& cert;
	class NetworkIdentifier& neti;
	PlayerPreJoinEvent(class Certificate& a, class NetworkIdentifier& b) : cert(a), neti(b) {}
};
class PlayerJoinEvent : public IEventBase<PlayerJoinEvent>, public IPlayerEvent {
public:
	PlayerJoinEvent(ServerPlayer& sp) : IPlayerEvent(sp) {}
};
class PlayerLeftEvent : public IEventBase<PlayerLeftEvent>, public IPlayerEvent {
public:
	PlayerLeftEvent(ServerPlayer& sp) : IPlayerEvent(sp) {}
};

class PlayerDestroyEvent : public IGenericPlayerEvent<PlayerDestroyEvent> {
public:
	BlockPos& pos;
	PlayerDestroyEvent(ServerPlayer& sp, BlockPos& _pos) : IGenericPlayerEvent(sp), pos(_pos) {}
	const BlockPos& getPos() {
		return pos;
	}
};
class PlayerUseItemOnEntityEvent : public IGenericPlayerEvent<PlayerUseItemOnEntityEvent> {
public:
	struct ActorUniqueID rtid;
	PlayerUseItemOnEntityEvent(ServerPlayer& sp, ActorUniqueID rti) : IGenericPlayerEvent<PlayerUseItemOnEntityEvent>(sp), rtid(rti) {}
};
class PlayerUseItemOnEvent : public IGenericPlayerEvent<PlayerUseItemOnEvent> {
public:
	BlockPos& pos;
	uchar side;
	PlayerUseItemOnEvent(ServerPlayer& sp, BlockPos& _pos, uchar _side) : IGenericPlayerEvent(sp), pos(_pos), side(_side) {}
	BlockPos& getPos() {
		return pos;
	}
	BlockPos getPlacePos() {
		const int Z[] = { 0, 0, -1, 1, 0, 0 };
		const int X[] = { 0, 0, 0, 0, -1, 1 };
		const int Y[] = { -1, 1, 0, 0, 0, 0 };
		BlockPos dpos = { pos.x + X[side], pos.y + Y[side], pos.z + Z[side] };
		return dpos;
	}
	uchar getSide() {
		return side;
	}
};