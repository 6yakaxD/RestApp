#include <vector>
#include <iostream>
#include <string>


class Order
{
public:

	int summa_;
	bool is_payed_okay;
	std::string discount_type_;
	std::string way_to_pay_;
	std::string customer_name_;
	std::string additional_text_;
	std::vector<std::vector<std::string>> order_full_list_;
	
};
inline Order g_Order;