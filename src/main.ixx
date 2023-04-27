
#include <torch/torch.h>
import <iostream>;

int main() {

	auto ten = at::empty({ 3,3 });

	std::cout << ten << std::endl;

}