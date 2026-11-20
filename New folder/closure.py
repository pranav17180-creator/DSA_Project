def make_greet(name):
    def greet():
        return f"Hello, {name}!"
    return greet