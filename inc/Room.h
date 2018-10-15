#pragma once

#include <memory>
#include <string>
#include <unordered_map>


class RoomPrototype
{
public:
	static std::shared_ptr<RoomPrototype> GenerateFromFile(const std::string& filename);
	static std::unordered_map<std::string, std::shared_ptr<RoomPrototype> > ms_StoredRooms;
};

class RoomInstance
{
private:
	std::shared_ptr<RoomPrototype> m_RoomPrototype;
};