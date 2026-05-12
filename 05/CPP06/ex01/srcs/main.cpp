#include "../includes/Serializer.hpp"
#include "../includes/Data.hpp"

int main() {
	Data *data = new Data;
	data->name = "Marco";
	data->last = "Paulo";
	data->age = 21;

	std::cout << "BEFORE\nname: " << data->name
			  << " last: " << data->last << ", age: " 
			  << data->age << std::endl;

	uintptr_t raw = Serializer::serialize(data);
	Data *serialized = Serializer::deserialize(raw);

	std::cout << "AFTER\nname: " << serialized->name
			  << " last: " << serialized->last << ", age: " 
			  << serialized->age << std::endl;
	delete data;
	return 0;
}