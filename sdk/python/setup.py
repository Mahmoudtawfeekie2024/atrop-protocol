from setuptools import setup, find_packages

setup(
    name='atrop-sdk',
    version='0.1.0',
    description='ATROP Python SDK',
    author='Mahmoud Tawfeek',
    package_dir={'': 'src'},
    packages=find_packages(where='src'),
    python_requires='>=3.7',
)
