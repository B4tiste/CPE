from setuptools import setup

package_name = 'qr_code'

setup(
    name=package_name,
    version='0.0.0',
    packages=[package_name],
    data_files=[
        ('share/ament_index/resource_index/packages',
            ['resource/' + package_name]),
        ('share/' + package_name, ['package.xml']),
    ],
    install_requires=['setuptools'],
    zip_safe=True,
    maintainer='triton_09',
    maintainer_email='triton_09@todo.todo',
    description='TODO: Package description',
    license='TODO: License declaration',
    tests_require=['pytest'],
    entry_points={
        'console_scripts': [
            'qr_code_control = qr_code.qr_code_control:main',
            'qr_code_cv2 = qr_code.qr_code_cv2:main'
        ],
    },
)
