# basic function definition and calling
def greet(name):
    print(f"Hello, {name}!")

# function with multiple paramters
def add(x, y):
    return x+y

# function with default paramters
def power(base, exponent=2):
    return base ** exponent

# function returning multiple values
def min_max_avg(numbers):
    return min(numbers), max(numbers), sum(numbers) / len(numbers) 

# function with variable number of arguments
def sum_all(*args):
    return sum(args)

# function with keyword arguments
def print_info(**kwargs):
    for key, value in kwargs.items():
        print(f"{key}: {value}")

def main():
    print_info(name="Alice", age=30, city="New York")

if __name__ == "__main__":
    main()
