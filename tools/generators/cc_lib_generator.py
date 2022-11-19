import requests

def version():
    return requests.__version__

print("hello world")
print(version())
