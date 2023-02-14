#-----------------------------------------#
# Decision Modelling
#-----------------------------------------#


# Define the data
annual_demand <- 15000
unit_cost <- 80
opportunity_cost_of_holding_stock <- 0.18
order_cost <- 220


# Define the decision variables
order_quantity <- 677
reorder_point <- 0

# Compute the number of orders
number_of_orders <- annual_demand / order_quantity

# Compute the average inventory
average_inventory <- (order_quantity / 2) + reorder_point

# Compute the holding cost per unit per year
holding_cost_per_unit_per_year <- unit_cost * opportunity_cost_of_holding_stock

# Compute the annual holding cost
annual_holding_cost <- average_inventory * holding_cost_per_unit_per_year

# Compute the annual ordering cost
annual_ordering_cost <- number_of_orders * order_cost

# Compute the total annual inventory cost
total_annual_inventory_cost <- annual_holding_cost + annual_ordering_cost

# Print the results
cat("Total annual inventory cost: $", total_annual_inventory_cost, "\n")
