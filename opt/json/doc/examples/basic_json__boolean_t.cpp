#include <json.hpp>

using namespace nlohmann;

int main()
{
    // create boolean values
    json j_truth = true;
    json j_falsity = false;

    // serialize the JSON booleans
    std::cout << j_truth << '\n';
    std::cout << j_falsity << '\n';
}
