from setuptools import setup

package_name = 'opi_vision'

setup(
    name=package_name,
    version='0.1.0',
    packages=[package_name],
    data_files=[
        ('share/ament_index/resource_index/packages', ['resource/opi_vision']),
        ('share/' + package_name, ['package.xml']),
        ('share/' + package_name + '/launch', [
            'launch/bringup.launch.py',
            'launch/camera_only.launch.py'
        ]),
    ],
    install_requires=['setuptools'],
    zip_safe=True,
    maintainer='Your Name',
    maintainer_email='you@example.com',
    description='Orange Pi 5 Pro vision stack: gscam + YOLO + MJPEG',
    license='Apache-2.0',
    tests_require=['pytest'],
    entry_points={
        'console_scripts': [
            'image_rate = opi_vision.image_rate:main',
            'yolo_annotate = opi_vision.yolo_annotate:main',
            'mjpeg_server = opi_vision.mjpeg_server:main',
        ],
    },
)
