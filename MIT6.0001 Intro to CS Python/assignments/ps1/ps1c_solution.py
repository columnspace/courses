start_salary = float(input("Enter the starting salary:"))
semi_annual_raise = 0.07
r = 0.04
portion_down_payment = 0.25
total_cost = 1000000

low = 0
high = 10000
steps = 0
while low <= high:
    annual_salary = start_salary
    mid = (low + high)//2
    portion_saved = mid/10000.0
    steps += 1
    current_savings = 0
    time = 0
    for time in range(36):
        current_savings = current_savings * (1+r/12) + annual_salary/12*portion_saved
        if time % 6 == 5:
            annual_salary *= 1 + semi_annual_raise
    if abs(current_savings - total_cost*portion_down_payment) < 100:
        break
    elif current_savings > total_cost*portion_down_payment:
        high = mid - 1
    else:
        low = mid + 1

if low > 10000:
    print('It is not possible to pay the down payment in three years.')
else:
    print('Best savings rate:', portion_saved)
    print('Steps in bisection search:', steps)
