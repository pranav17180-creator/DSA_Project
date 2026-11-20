def tax_calculator(rate):
    def calculate_tax(amount):
        return amount * rate
    return calculate_tax