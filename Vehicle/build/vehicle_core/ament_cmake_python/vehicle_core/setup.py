from setuptools import find_packages
from setuptools import setup

setup(
    name='vehicle_core',
    version='0.0.0',
    packages=find_packages(
        include=('vehicle_core', 'vehicle_core.*')),
)
