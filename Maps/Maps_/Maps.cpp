#include <iostream>
#include <map>
#include <unordered_map>

struct CityRecord
{
	std::string Name;
	uint32_t Population;
	double Latitude, Longitude;

	bool operator==(const CityRecord& other) const
	{
		return Name == other.Name && Population == other.Population && Latitude == other.Latitude && Longitude == other.Longitude;
	}

	// This is so that you can use ordered map, helps with sorting.
	// But also defines your unique key. Whatever parameter you compare here must be unique or they will clash.
	bool operator<(const CityRecord& other) const
	{
		return Name < other.Name;
	}
};

std::ostream& operator<<(std::ostream& stream, const CityRecord& record)
{
	stream << "City Name: " << record.Name << "\nCity Population: " << record.Population << "\nCity Latitude/Longitude: (" << record.Latitude << ", " << record.Longitude << ")";
	return stream;
}


// This is a template specialization for the std::hash function for our CityRecord struct. It helps us create the hash function specifically for our CityRecord struct, which is necessary if we want to use it as a key in an unordered map
namespace std
{
	template <>
	struct hash<CityRecord>
	{
		size_t operator()(const CityRecord& key) const
		{
			// Since they are unique to every possible city, we could use the latitude and longitude as well, but for simplicity's sake, we will just use the name of the city as the key for our hash function. std::string already has a hash function defined for it, so we can just use that. We do that by initializing a hash function(that's the first set of paranthesis) for std::string(we also need to send this as template) and then calling it with the name of the city as the argument. This will return a size_t value that represents the hash of the city name, which we can then use as the hash value for our CityRecord.
			return hash<std::string>()(key.Name);
		}
	};
}

int main()
{
	// std::map<std::string, CityRecord> cityMap;
	std::unordered_map<std::string, CityRecord> cityMap;

	cityMap["Melbourne"] = CityRecord{ "Melbourne", 500000, 2.4, 3.5 };
	cityMap["Ankara"] = CityRecord{ "Ankara", 500000, 2.4, 3.5 };
	cityMap["Berlin"] = CityRecord{ "Berlin", 500000, 2.4, 3.5 };
	cityMap["Paris"] = CityRecord{ "Paris", 500000, 2.4, 3.5 };
	cityMap["London"] = CityRecord{ "London", 500000, 2.4, 3.5 };

	// If the CityRecord 'Berlin' didn't exist, the '[]' operator would create one and return it.
	// If the map was const, then this code wouldn't work because there is no const version of this operator.
	// If you want to retrieve data from a const map you use: 'map.at(key)'. But this function breaks code if you don't have the thing you are looking for inside your map.
	// If you want to make sure first if the data you are looking for is there, you can wrap it with an if block with 'map.find(key) != map.end()' as the condition.
	CityRecord& berlin = cityMap["Berlin"];
	std::cout << berlin << std::endl;

	CityRecord& istanbul = cityMap["Istanbul"];
	istanbul.Name = "Istanbul";
	istanbul.Population = 10;
	istanbul.Longitude = 5.0f;
	istanbul.Latitude = 5.0f;

	std::cout << "--------------------\n";
	std::cout << istanbul << std::endl;

	// Since the CityRecord is a custom struct we've created, we need to define a hash function for it if we want to use it as a key in an unordered map. This is because the unordered map needs to be able to hash the keys in order to store them efficiently.
	std::unordered_map<CityRecord, uint32_t> foundedMap;

	foundedMap[berlin] = 1850;

	cityMap.erase("Paris");

	std::cout << "--------------------\n";
	// Iterating through a map.
	for (auto& [name, city] : cityMap)
	{
		std::cout << city << std::endl;
	}
	std::cin.get();
}