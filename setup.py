from setuptools import setup
import os
from glob import glob

package_name = 'av_cpp2025'

setup(
    name=package_name,
    version='0.0.0',
    packages=[package_name],
    data_files=[
        ('share/ament_index/resource_index/packages', ['resource/' + package_name]),
        ('share/' + package_name, ['package.xml']),
    ],
    install_requires=['setuptools'],
    zip_safe=True,
    maintainer='avcpp',
    maintainer_email='avcpp@todo.todo',
    description='Autonomous Vehicle C++ 2025 - D300 LiDAR Driver',
    license='Apache-2.0',
    entry_points={
        'console_scripts': [
            'd300_custom_driver = av_cpp2025.scripts.d300_custom_driver:main',
        ],
    },
)
