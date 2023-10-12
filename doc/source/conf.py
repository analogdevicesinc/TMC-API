# Configuration file for the Sphinx documentation builder.
#
# For the full list of built-in configuration values, see the documentation:
# https://www.sphinx-doc.org/en/master/usage/configuration.html

# -- Project information -----------------------------------------------------
# https://www.sphinx-doc.org/en/master/usage/configuration.html#project-information

from cgitb import html
import subprocess, os

def configureDoxyFile(input_dir, output_dir):
    with open('Doxyfile.in', 'r') as file:
        filedata = file.read()

    filedata = filedata.replace('@DOXYGEN_INPUT_DIR@', input_dir)
    filedata = filedata.replace('@DOXYGEN_OUTPUT_DIR@', output_dir)

    with open('Doxyfile', 'w') as file:
        file.write(filedata)

# Check if we're running on Read the Docs' servers
read_the_docs_build = os.environ.get('READTHEDOCS', None) == 'True'

breathe_projects = {}

if read_the_docs_build:
    input_dir = '../tmc'
    output_dir = 'buid'
    configureDoxyFile(input_dir, output_dir)
    subprocess.call('doxygen', shell=True)
    breathe_projects['TMC-API'] = output_dir + '/xml'
    

project = 'TMC-API'
copyright = '2023, Fabian Muehlberger'
author = 'Fabian Muehlberger'
release = '0.1'

# -- General configuration ---------------------------------------------------
# https://www.sphinx-doc.org/en/master/usage/configuration.html#general-configuration


# extensions:
extensions = ["breathe"]

# Add any paths that contain templates here, relative to this directory.
templates_path = ['_templates']
exclude_patterns = []

# Breathe configuration
# breathe_projects = {
#     "TMC-API": "../doxygen_build/xml/",
# }

# -- Options for HTML output -------------------------------------------------
# https://www.sphinx-doc.org/en/master/usage/configuration.html#options-for-html-output

html_theme = 'sphinx_rtd_theme'
html_static_path = ['_static']
breathe_default_project = "TMC-API"
