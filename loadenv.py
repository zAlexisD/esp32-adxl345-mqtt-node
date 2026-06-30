"""
Python script to load .env variables
"""
from dotenv import dotenv_values
import os

env_vars = dotenv_values(".env")

for key, value in env_vars.items():
    print("ENV BEFORE:", os.environ.get(key))
    os.environ[key] = value
    print("ENV AFTER:", os.environ.get(key))